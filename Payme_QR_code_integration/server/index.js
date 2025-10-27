// index.js
import express from 'express';
import fs from 'fs-extra';
import mqtt from 'mqtt';
import crypto from 'crypto';
import dotenv from 'dotenv';
dotenv.config();

const {
  PORT = 3000,
  MERCHANT_ID,
  WEBHOOK_SECRET,
  MQTT_URL = 'mqtt://broker.hivemq.com:1883',
  MQTT_USER,
  MQTT_PASS,
  PROCESSED_FILE = './processed.json'
} = process.env;

if (!MERCHANT_ID) console.warn('WARNING: MERCHANT_ID not set in .env');

const app = express();
// raw needed if signature checks need exact bytes; we accept json and raw
app.use(express.raw({ type: '*/*', limit: '1mb' }));

// helper: safe parse
function tryParseRaw(raw) {
  try {
    if (Buffer.isBuffer(raw)) return JSON.parse(raw.toString());
    if (typeof raw === 'string') return JSON.parse(raw);
    return raw;
  } catch (e) {
    return null;
  }
}

// MQTT client
const mqttOptions = {};
if (MQTT_USER) mqttOptions.username = MQTT_USER;
if (MQTT_PASS) mqttOptions.password = MQTT_PASS;
const mqttClient = mqtt.connect(MQTT_URL, mqttOptions);
mqttClient.on('connect', () => console.log('✅ MQTT connected to', MQTT_URL));
mqttClient.on('error', (e) => console.error('MQTT error', e));

// ensure processed file exists
try {
  if (!fs.existsSync(PROCESSED_FILE)) fs.writeJsonSync(PROCESSED_FILE, {});
} catch (e) {
  console.error('Failed to ensure processed file:', e);
  process.exit(1);
}

// read processed into Set helper
function readProcessedSet() {
  try {
    const data = fs.readFileSync(PROCESSED_FILE, 'utf8');
    const arr = JSON.parse(data || '{}');
    // if stored as object keys -> convert to Set of keys
    if (typeof arr === 'object' && !Array.isArray(arr)) return new Set(Object.keys(arr));
    if (Array.isArray(arr)) return new Set(arr);
    return new Set();
  } catch (e) {
    return new Set();
  }
}
function writeProcessedSet(set) {
  try {
    // write as object for readability {id: {time:..., status:...}}
    const obj = {};
    for (const k of set) obj[k] = true;
    fs.writeFileSync(PROCESSED_FILE, JSON.stringify(obj, null, 2), 'utf8');
  } catch (e) {
    console.error('Failed to write processed file', e);
  }
}

// verify HMAC SHA256 signature (header: X-Signature) — accepts hex or base64
function verifySignature(rawBuffer, signatureHeader) {
  if (!WEBHOOK_SECRET) return true; // disabled if secret not provided
  if (!signatureHeader) return false;
  const hmac = crypto.createHmac('sha256', WEBHOOK_SECRET).update(rawBuffer).digest();
  const sig = signatureHeader.trim();
  try {
    const bufHex = Buffer.from(sig, 'hex');
    if (crypto.timingSafeEqual(hmac, bufHex)) return true;
  } catch (e) {}
  try {
    const bufB64 = Buffer.from(sig, 'base64');
    if (crypto.timingSafeEqual(hmac, bufB64)) return true;
  } catch (e) {}
  return false;
}

// Main webhook handler
app.post('/webhook/payme', async (req, res) => {
  const raw = req.body; // Buffer
  const sigHeader = req.headers['x-signature'] || req.headers['x-payme-signature'] || req.headers['signature'] || '';

  if (WEBHOOK_SECRET && !verifySignature(raw, String(sigHeader))) {
    console.warn('❌ Invalid signature for webhook');
    return res.status(403).send('forbidden');
  }

  const payload = tryParseRaw(raw);
  if (!payload) {
    console.error('Invalid JSON payload');
    return res.status(400).send('bad request');
  }

  // handle JSON-RPC style (Payme)
  let params = payload.params || payload;
  if (payload.method && payload.params) params = payload.params;

  console.log('📩 Webhook received:', params);

  // extract fields
  const merchant_id = params.merchant_id || merchantFromParams(params) || MERCHANT_ID || 'default';
  const payment_id = params.id || params.payment_id || params.transaction_id || (payload.id || null);
  const amount = params.amount || params.sum || (params && params.amount) || 0;

  // Get order_id (account.order_id typical for Payme)
  let order_id = null;
  if (params.account && params.account.order_id) order_id = params.account.order_id;
  else if (params.order_id) order_id = params.order_id;
  else if (payload.params && payload.params.account && payload.params.account.order_id) order_id = payload.params.account.order_id;

  // Try cashbox_id (if using different cashboxes)
  const cashboxId = params.cashbox_id || params.cashboxId || (params && params.params && params.params.cashbox_id) || null;

  // Determine deviceId:
  // priority: parse from order_id (format device:DEVICE:...), else map cashboxId -> device, else 'default'
  let deviceId = 'default';
  if (order_id && typeof order_id === 'string') {
    const parts = order_id.split(':').map(p => p.trim()).filter(Boolean);
    if (parts.length >= 2 && (parts[0].toLowerCase() === 'device' || parts[0].toLowerCase() === 'kiosk')) {
      deviceId = parts[1];
    } else if (parts.length >= 1) {
      deviceId = parts[0];
    }
  } else if (cashboxId) {
    // Optionally maintain a mapping here or use cashboxId directly
    deviceId = String(cashboxId);
  }

  // normalize status: Payme uses 'state' numeric (1 = performed)
  const rawStatus = params.state || params.status || params.event || '';
  const statusNormalized = normalizeStatus(rawStatus);

  // idempotency key
  const keyToCheck = payment_id || `${merchant_id}:${order_id || Date.now()}`;

  // load processed
  const processedSet = readProcessedSet();

  const confirmedStates = new Set(['confirmed','success','performed','done','ok','1', 1]); // includes numeric 1
  if (statusNormalized && confirmedStates.has(String(statusNormalized).toLowerCase())) {
    if (processedSet.has(keyToCheck)) {
      console.log('⚠️ Duplicate confirmed event, skipping:', keyToCheck);
    } else {
      const topic = `payments/${merchant_id}/${deviceId}`;
      const event = {
        type: 'payment_confirmed',
        data: {
          payment_id,
          order_id,
          deviceId,
          amount,
          status: statusNormalized,
          received_at: Date.now(),
          raw: params
        }
      };
      mqttClient.publish(topic, JSON.stringify(event), { qos: 1 }, (err) => {
        if (err) console.error('MQTT publish error', err);
        else console.log('📡 Published confirmed payment to', topic, event);
      });
      processedSet.add(keyToCheck);
      writeProcessedSet(processedSet);
    }
    return res.status(200).send('OK');
  }

  // publish updates (non-confirmed)
  const updateTopic = `payments/${merchant_id}/${deviceId}`;
  const updateEvent = { type: 'payment_update', data: { payment_id, order_id, deviceId, amount, status: statusNormalized, raw: params } };
  mqttClient.publish(updateTopic, JSON.stringify(updateEvent), { qos: 0 }, () => {});
  console.log('📡 Published update to', updateTopic);
  return res.status(200).send('OK');
});

function merchantFromParams(p) {
  if (!p) return null;
  return p.merchant_id || p.merchantId || (p.params && p.params.merchant_id) || null;
}
function normalizeStatus(s) {
  if (s === undefined || s === null) return '';
  // numeric Payme state -> map
  if (typeof s === 'number' || !isNaN(Number(s))) {
    const n = Number(s);
    if (n === 1) return 'confirmed';
    if (n === 0) return 'created';
    if (n === 2) return 'cancelled';
    return String(n);
  }
  return String(s).toLowerCase();
}

// health
app.get('/health', (_req, res) => res.send('ok'));

// start server
const host = '127.0.0.1';
app.listen(PORT, host, () => console.log(`🚀 Server running on ${host}:${PORT}`));
