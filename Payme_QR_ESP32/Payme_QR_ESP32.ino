#include <WiFi.h>
#include <PubSubClient.h>

// ==== Wi-Fi ====
const char* ssid = "Siren";
const char* password = "00152010";

// ==== MQTT ====
const char* mqtt_server = "broker.hivemq.com";
const char* mqtt_topic  = "payments/68ffc803d2d01cc2d62db3a4"; // тот же merchant_id, что и в сервере

WiFiClient espClient;
PubSubClient client(espClient);

// ==== Подключение к Wi-Fi ====
void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Connecting to WiFi: ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\n✅ WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

// ==== Callback при получении MQTT ====
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.println("\n📩 New payment received!");

  String msg;
  for (unsigned int i = 0; i < length; i++) msg += (char)payload[i];

  // Показываем весь JSON
  Serial.println("RAW message: " + msg);

  // Находим статус
  int statusPos = msg.indexOf("\"status\":\"");
  if (statusPos != -1) {
    int start = statusPos + 10;
    int end = msg.indexOf("\"", start);
    String status = msg.substring(start, end);
    Serial.print("💰 Status: ");
    Serial.println(status);
  }

  // Находим сумму
  int amountPos = msg.indexOf("\"amount\":");
  if (amountPos != -1) {
    int start = amountPos + 9;
    int end = msg.indexOf(",", start);
    if (end == -1) end = msg.indexOf("}", start);
    String amount = msg.substring(start, end);
    Serial.print("💵 Amount: ");
    Serial.println(amount);
    if (amount == "5000") {
      digitalWrite(LED_BUILTIN, HIGH);
    }
    else if (amount == "10000") {
      digitalWrite(LED_BUILTIN, LOW);
    }
  }

  Serial.println("------------------------------");
}

// ==== Повторное подключение ====
void reconnect() {
  while (!client.connected()) {
    Serial.print("Connecting to MQTT...");
    if (client.connect("ESP32-Payme-Client")) {
      Serial.println(" connected!");
      client.subscribe(mqtt_topic);
      Serial.print("Subscribed to: ");
      Serial.println(mqtt_topic);
    } else {
      Serial.print(" failed, rc=");
      Serial.print(client.state());
      Serial.println(" — retrying in 3s");
      delay(3000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  if (!client.connected()) reconnect();
  client.loop();
}
