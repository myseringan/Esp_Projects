#include <WiFi.h>
#include <PubSubClient.h>

const char* ssid = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";
const char* mqtt_server = "broker.hivemq.com";
const char* mqtt_topic  = "payments/you are payme MERCHANT_ID";  // поменяй на свой topic

WiFiClient espClient;
PubSubClient client(espClient);

void setup_wifi() {
  Serial.println();
  Serial.print("Connecting to WiFi: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.println("\n📩 New payment received:");
  String msg;
  for (unsigned int i = 0; i < length; i++) msg += (char)payload[i];

  Serial.println("RAW: " + msg);

  int statusPos = msg.indexOf("\"status\":\"");
  if (statusPos != -1) {
    int start = statusPos + 10;
    int end = msg.indexOf("\"", start);
    String status = msg.substring(start, end);
    Serial.print("Status: ");
    Serial.println(status);
  }

  int amountPos = msg.indexOf("\"amount\":");
  if (amountPos != -1) {
    int start = amountPos + 9;
    int end = msg.indexOf(",", start);
    if (end == -1) end = msg.indexOf("}", start);
    String amount = msg.substring(start, end);
    Serial.print("Amount: ");
    Serial.println(amount);
  }
  Serial.println("-------------------------");
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Connecting to MQTT...");
    if (client.connect("ESP32-PaymeClient")) {
      Serial.println("connected");
      client.subscribe(mqtt_topic);
      Serial.print("Subscribed to: ");
      Serial.println(mqtt_topic);
    } else {
      Serial.print("failed, rc=");
      Serial.println(client.state());
      delay(3000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void loop() {
  if (!client.connected()) reconnect();
  client.loop();
}
