// ======================= Bio Master (ESP8266 + Blynk + Captive Portal) =======================
#define BLYNK_TEMPLATE_ID   "TMPL6-Qhz9qFz"
#define BLYNK_TEMPLATE_NAME "Bio Master"

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <SoftwareSerial.h>
#include <DNSServer.h>
#include <BlynkSimpleEsp8266.h>

// === сохранение настроек ===
#include <LittleFS.h>
#include <ArduinoJson.h>

// ----------------- Константы/AP -----------------
const byte DNS_PORT = 53;
const char *ap_ssid = "Bio Master";
const char *ap_pass = "samurai2023";

// дефолтный токен (если ещё не сохранён)
char auth[] = "b-4atMkevFd_1iP5NTRkZr1t_zIO4iS0";

// ----------------- Глобальные -----------------
DNSServer dnsServer;
ESP8266WebServer server(80);

// обмен с UNO по SoftwareSerial: RX=D2(GPIO4), TX=D3(GPIO0)
SoftwareSerial arduinoSerial(D2, D3);

float val;
int rele;
int ldr;

// ====== конфиг, сохраняемый в LittleFS ======
struct WifiCfg {
  String staSsid;
  String staPass;
  String blynkToken;  // опционально
} wc;

bool loadCfg() {
  if (!LittleFS.exists("/wifi.json")) return false;   // <-- begin() больше не здесь
  File f = LittleFS.open("/wifi.json", "r");
  if (!f) return false;
  StaticJsonDocument<256> doc;                        // было 384 → 256
  auto err = deserializeJson(doc, f);
  f.close();
  if (err) return false;

  wc.staSsid    = String((const char*)doc["ssid"]);
  wc.staPass    = String((const char*)doc["pass"]);
  wc.blynkToken = String((const char*)doc["token"]);
  return wc.staSsid.length() > 0;
}

bool saveCfg(const String& s, const String& p, const String& t) {
  StaticJsonDocument<256> doc;                        // было 384 → 256
  doc["ssid"]  = s;
  doc["pass"]  = p;
  doc["token"] = t;
  File f = LittleFS.open("/wifi.json", "w");
  if (!f) return false;
  serializeJson(doc, f);
  f.close();
  wc.staSsid = s; wc.staPass = p; wc.blynkToken = t;
  return true;
}

// ======================= HTML (твой дизайн + liquid/glass CSS, цвета те же) =======================
const char loginPage[] PROGMEM = R"(
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>WiFi Biomaster</title>
  <link rel="stylesheet" href="wfibio.css">
  <style>
  :root{
    --bg:#000000;
    --txt:#ffffff;
    --accent:#28de32;
    --focus:#03f417;
    --glass:rgba(255,255,255,.10);
    --glass-border:rgba(255,255,255,.28);
  }
  body{
    margin:0; padding:0; font-family:sans-serif; color:var(--txt);
    background:linear-gradient(var(--bg), var(--bg));
    min-height:100dvh; position:relative; overflow:hidden;
  }
  body::before, body::after{
    content:""; position:absolute; inset:auto; pointer-events:none; mix-blend-mode:screen;
    width:360px; height:360px; border-radius:50%; filter:blur(44px); opacity:.16; background:#ffffff;
  }
  body::before{ left:-80px; top:-60px; }
  body::after { right:-80px; top:10vh; }

  .login-box{
    width:80%; max-width:400px; margin:auto; position:absolute; top:50%; left:50%;
    transform:translate(-50%,-50%);
    padding:40px;
    background:var(--glass);
    border:1px solid var(--glass-border);
    border-radius:10px;
    box-sizing:border-box;
    box-shadow:0 15px 25px rgba(0,0,0,.6), inset 0 1px 0 rgba(255,255,255,.06);
    backdrop-filter: blur(18px) saturate(120%);
    -webkit-backdrop-filter: blur(18px) saturate(120%);
  }

  .login-box h2{
    margin:0 0 30px; padding:0; color:var(--txt); text-align:center;
    text-shadow:0 1px 0 rgba(255,255,255,.06);
  }

  .user-box{ position:relative; margin-bottom:30px; }
  .user-box input{
    width:100%; padding:12px 10px 10px; font-size:16px; color:var(--txt);
    background:linear-gradient(180deg, rgba(255,255,255,.14), rgba(255,255,255,.06));
    border:1px solid rgba(255,255,255,.22);
    border-radius:12px;
    outline:none;
    transition:border-color .2s, box-shadow .2s, background .2s, color .2s;
  }
  .user-box input:focus{
    border-color:var(--focus);
    box-shadow:0 0 0 3px rgba(3,244,23,.22);
    background:linear-gradient(180deg, rgba(255,255,255,.18), rgba(255,255,255,.08));
  }

  .user-box label{
    position:absolute; top:0; left:0; padding:10px 6px; font-size:16px; color:var(--txt);
    pointer-events:none; transition:.18s;
    background:transparent; border-radius:8px;
  }
  .user-box input:focus ~ label,
  .user-box input:valid ~ label{
    top:-14px; left:6px; color:var(--focus); font-size:12px;
    background:rgba(255,255,255,.10); backdrop-filter:blur(10px); -webkit-backdrop-filter:blur(10px);
  }

  input[type="submit"]{
    position:relative; display:inline-block; padding:12px 20px;
    color:var(--accent); font-size:16px; text-decoration:none; text-transform:uppercase;
    overflow:hidden; transition:.15s; margin-top:40px; letter-spacing:4px; cursor:pointer;
    background:linear-gradient(180deg, rgba(40,222,50,0.00), rgba(40,222,50,0.10));
    border:2px solid var(--accent);
    border-radius:10px;
    box-shadow:0 10px 22px rgba(0,0,0,.25), inset 0 1px 0 rgba(255,255,255,.15);
  }
  input[type="submit"]:hover{
    background:var(--accent);
    color:#fff;
    box-shadow:0 14px 28px rgba(0,0,0,.28), inset 0 1px 0 rgba(255,255,255,.25);
  }

  @media only screen and (min-width:768px){
    .login-box{ width:400px; }
  }
  </style>
</head>
<body>
  <div class="login-box">
    <h2>Настройка Wi-Fi</h2>
    <form action="/save" method="post">
      <div class="user-box">
        <input type="text" name="ssid" required="">
        <label>SSID</label>
      </div>
      <div class="user-box">
        <input type="password" name="password" required="">
        <label>Password</label>
      </div>
      <input type="submit" value="Сохранить">
    </form>
  </div>
</body>
</html>
)";

// ======================= Обработчики страниц =======================
void handleRoot() {
  server.send_P(200, "text/html", loginPage);
}

// iOS-дружественный редирект: 200 OK + meta-refresh (не 302 после POST)
const char redirectAfterSavePage[] PROGMEM = 
"<!doctype html><meta charset='utf-8'>"
"<meta http-equiv='refresh' content='1;url=/result'>"
"<meta http-equiv='cache-control' content='no-cache'>"
"<title>Redirect</title>"
"<body style='font-family:sans-serif;background:#000;color:#fff'>"
"<p style='text-align:center;margin-top:2rem'>Переход… "
"<a href='/result' style='color:#28de32'>если не перенаправило</a></p>"
"</body>";

void handleSave() {
  String ssidValue = server.arg("ssid");
  String passwordValue = server.arg("password");
  String tokenValue = server.arg("token");

  if (ssidValue.length() && passwordValue.length()) {
    saveCfg(ssidValue, passwordValue, tokenValue);
  }
  WiFi.mode(WIFI_AP_STA);
  WiFi.begin(ssidValue.c_str(), passwordValue.c_str());

  server.send_P(200, "text/html; charset=utf-8", redirectAfterSavePage);  // <-- send_P
}


// УСПЕХ
const char resultOkPage[] PROGMEM = R"(
<html>
<head>
<meta charset="UTF-8">
<style>
  :root{ --bg:#000000; --txt:#ffffff; --glass:rgba(255,255,255,.10); --bor:rgba(255,255,255,.28); --ok:#2bff00; }
  body{ margin:0; padding:0; font-family:sans-serif; color:var(--txt); min-height:100dvh; display:grid; place-items:center;
        background: radial-gradient(1100px 900px at 12% 12%, #ffffff20, transparent 40%),
                    radial-gradient(900px 750px at 86% 14%, #ffffff18, transparent 45%),
                    linear-gradient(var(--bg),var(--bg)); overflow:hidden; }
  body::before, body::after{ content:""; position:absolute; width:360px; height:360px; border-radius:50%; filter:blur(44px);
        opacity:.16; background:#ffffff; pointer-events:none; mix-blend-mode:screen; }
  body::before{ left:-80px; top:-60px; } body::after{ right:-80px; top:10vh; }
  h1{ margin:0 0 16px; text-align:center; background:var(--glass); border:1px solid var(--bor); padding:10px 16px; border-radius:14px;
      box-shadow:inset 0 1px 0 rgba(255,255,255,.06), 0 20px 60px rgba(0,0,0,.35); backdrop-filter:blur(18px) saturate(120%);
      -webkit-backdrop-filter:blur(18px) saturate(120%); }
  .fa-check-circle{ font-size:150px; display:flex; justify-content:center; align-items:center; text-align:center; color:#ffffff;
      border-radius:24px; background-color:var(--ok); width:200px; height:200px; margin:auto; margin-top:20px; border:1px solid var(--bor);
      box-shadow:0 24px 48px rgba(0,0,0,.35), inset 0 1px 0 rgba(255,255,255,.25); }
</style>
</head>
<body>
  <div>
    <h1>Подключено к Wi-Fi</h1>
    <div class="fa-check-circle">&#10003;</div>
  </div>
</body>
</html>
)";

// ОШИБКА
const char resultErrPage[] PROGMEM = R"(
<html>
<head>
<meta charset="UTF-8">
<style>
  :root{ --bg:#000000; --txt:#ffffff; --glass:rgba(255,255,255,.10); --bor:rgba(255,255,255,.28); --bad:#ff0000; }
  body{ margin:0; padding:0; font-family:sans-serif; color:var(--txt); min-height:100dvh; display:grid; place-items:center;
        background: radial-gradient(1100px 900px at 12% 12%, #ffffff20, transparent 40%),
                    radial-gradient(900px 750px at 86% 14%, #ffffff18, transparent 45%),
                    linear-gradient(var(--bg),var(--bg)); overflow:hidden; }
  body::before, body::after{ content:""; position:absolute; width:360px; height:360px; border-radius:50%; filter:blur(44px);
        opacity:.16; background:#ffffff; pointer-events:none; mix-blend-mode:screen; }
  body::before{ left:-80px; top:-60px; } body::after{ right:-80px; top:10vh; }
  h1{ margin:0 0 16px; text-align:center; background:var(--glass); border:1px solid var(--bor); padding:10px 16px; border-radius:14px;
      box-shadow:inset 0 1px 0 rgba(255,255,255,.06), 0 20px 60px rgba(0,0,0,.35); backdrop-filter:blur(18px) saturate(120%);
      -webkit-backdrop-filter:blur(18px) saturate(120%); }
  .fa-times-circle{ font-size:150px; display:flex; justify-content:center; align-items:center; text-align:center; color:#ffffff;
      border-radius:24px; background-color:var(--bad); width:200px; height:200px; margin:auto; margin-top:20px; border:1px solid var(--bor);
      box-shadow:0 24px 48px rgba(0,0,0,.35), inset 0 1px 0 rgba(255,255,255,.25); }
</style>
</head>
<body>
  <div>
    <h1>Не удалось подключиться к Wi-Fi. Проверьте учетные данные.</h1>
    <div class="fa-times-circle">&#10007;</div>
  </div>
</body>
</html>
)";

void handleResult() {
  const uint32_t WAIT_MS = 8000;
  uint32_t t0 = millis();
  while (WiFi.status() != WL_CONNECTED && millis() - t0 < WAIT_MS) {
    delay(100);
    yield();
  }
  if (WiFi.status() == WL_CONNECTED) {
    server.send_P(200, "text/html", resultOkPage);
  } else {
    server.send_P(200, "text/html", resultErrPage);
  }
}


// ======================= Blynk virtual pins =======================
BLYNK_WRITE(V4) {
  int v = param.asInt();
  static int last = -9999;         // антидребезг по значению
  if (v == last) return;           // не дублировать
  last = v;

  arduinoSerial.write('<');
  arduinoSerial.write('R');
  arduinoSerial.print(v);
  arduinoSerial.write('>');
  arduinoSerial.write('\n');
}

BLYNK_WRITE(V5) {
  int v = param.asInt();
  static int last = -9999;
  if (v == last) return;

  last = v;
  arduinoSerial.write('<');
  arduinoSerial.write('L');
  arduinoSerial.print(v);
  arduinoSerial.write('>');
  arduinoSerial.write('\n');
}

void pollUNO() {
  static char frame[24];         // буфер одного кадра
  static uint8_t idx = 0;
  static bool inFrame = false;

  while (arduinoSerial.available()) {
    char c = (char)arduinoSerial.read();

    if (!inFrame) {
      if (c == '<') { inFrame = true; idx = 0; }
      continue;
    }

    if (c == '>') {
      frame[idx] = '\0';         // строка готова: frame[0] = тип, дальше число
      inFrame = false;

      if (idx >= 2) {            // минимум: тип + 1 символ числа
        char type = frame[0];

        // заменить запятую на точку (на всякий случай)
        for (uint8_t i = 1; i < idx; i++) if (frame[i] == ',') frame[i] = '.';

        float v = atof(&frame[1]);   // без блокировок, быстро

        switch (type) {
          case 'T': Serial.print(v); Serial.println("°C"); Blynk.virtualWrite(V1, v); break;
          case 'H': Serial.print(v); Serial.println("%");  Blynk.virtualWrite(V2, v); break;
          case 'S': Serial.print(v); Serial.println("%");  Blynk.virtualWrite(V3, v); break;
          case 'I': Blynk.virtualWrite(V6, v); break;
          default: /* неизвестный тип — игнор */ break;
        }
      }
      idx = 0;
      continue;
    }

    if (c == '\n' || c == '\r') {
      // игнорируем переводы строк внутри кадра
      continue;
    }

    if (idx < sizeof(frame) - 1) {
      frame[idx++] = c;
    } else {
      // переполнение — сбросить кадр
      inFrame = false;
      idx = 0;
    }
  }
}

// ======================= Setup / Loop =======================
void setup() {
  Serial.begin(115200);
  arduinoSerial.begin(9600);
  LittleFS.begin();
  // автоподключение к сохранённой сети, если есть
  bool have = loadCfg();
  WiFi.persistent(false);
  WiFi.setSleep(false);
  WiFi.mode(WIFI_AP_STA);
  WiFi.softAP(ap_ssid, ap_pass);
  // (опционально, иногда помогает iOS)
  WiFi.softAPConfig(WiFi.softAPIP(), WiFi.softAPIP(), IPAddress(255,255,255,0));

  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: "); Serial.println(IP);

  if (have) {
    Serial.printf("Trying STA: %s\n", wc.staSsid.c_str());
    WiFi.begin(wc.staSsid.c_str(), wc.staPass.c_str());
  }

  // DNS сервер для captive-перенаправления (до start настроим коды/TTL)
  dnsServer.setErrorReplyCode(DNSReplyCode::NoError);
  dnsServer.setTTL(300);
  dnsServer.start(DNS_PORT, "*", WiFi.softAPIP());

  // --- HTTP маршруты (ДО server.begin()) ---
  server.on("/", HTTP_ANY, handleRoot);
  server.on("/save",   HTTP_POST, handleSave);
  server.on("/result", HTTP_GET,  handleResult);

  // Captive endpoints разных ОС
  auto cp_ok = [](){ server.send(200, "text/plain", "OK"); };
  auto cp_html_redirect = [](){
    server.send(200, "text/html; charset=utf-8",
                "<!doctype html><meta http-equiv='refresh' content='0;url=/'><a href='/'>Continue</a>");
  };
  // Android / Chrome
  server.on("/generate_204", HTTP_ANY, cp_ok);
  server.on("/gen_204",      HTTP_ANY, cp_ok);
  // Apple (iOS/macOS)
  server.on("/hotspot-detect.html", HTTP_ANY, cp_html_redirect);
  // Windows
  server.on("/ncsi.txt",        HTTP_ANY, [](){ server.send(200, "text/plain", "Microsoft NCSI"); });
  server.on("/connecttest.txt", HTTP_ANY, [](){ server.send(200, "text/plain", "OK"); });
  server.on("/fwlink",          HTTP_ANY, cp_html_redirect);

  // внешний CSS из <head>, чтобы не было 404 (у нас стили встроены, но пусть 200)
  server.on("/wfibio.css", HTTP_GET, [](){ server.send(200, "text/css", ""); });

  // Остальное — на корень
  server.onNotFound([](){
    server.sendHeader("Location", "/", true);
    server.send(302, "text/plain", "Redirecting...");
  });

  server.begin();

  // Blynk токен: если сохранён — используем его; иначе дефолт
  if (wc.blynkToken.length() > 0) {
    Blynk.config(wc.blynkToken.c_str());
  } else {
    Blynk.config(auth);
  }
}

void loop() {
  dnsServer.processNextRequest();  // сначала DNS
  server.handleClient();           // затем HTTP
  Blynk.run();
  pollUNO();
}