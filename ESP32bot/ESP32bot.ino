#include <WiFi.h>
#include <WebServer.h>
#include <Preferences.h>
#include <WiFiClientSecure.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

const char* server_ip = "5.8.51.154";
const int server_port = 443;
const char* api_password = "OnksDXA_ixPo7fsFcrDsF97n";
const int trigPin = 5;
const int echoPin = 18;
const int MIN_DISTANCE_CM = 5;
const int MAX_DISTANCE_CM = 100;

WiFiClientSecure client;
WebServer server(80);
Preferences preferences;

unsigned long previousMillis = 0;
const long interval = 10000; // Интервал отправки данных на сервер (10 секунд)


// ================================================================
// Функция для настройки маршрутов (адресов) веб-сервера
// ================================================================
void setupWebServer() {
  server.on("/", HTTP_GET, []() {
    String html = R"rawliteral(
      <!DOCTYPE html><html><head><title>ESP32 WiFi Setup</title>
      <meta name="viewport" content="width=device-width, initial-scale=1">
      <style>
        body{font-family: Arial, sans-serif; text-align: center; background-color: #f0f0f0;}
        .container{background-color: white; padding: 20px; border-radius: 10px; display: inline-block; margin-top: 50px; box-shadow: 0 4px 8px rgba(0,0,0,0.1);}
        input[type=text], input[type=password]{width: 90%; padding: 12px; margin: 8px 0; display: inline-block; border: 1px solid #ccc; border-radius: 4px; box-sizing: border-box;}
        input[type=submit]{width: 95%; background-color: #4CAF50; color: white; padding: 14px 20px; margin: 8px 0; border: none; border-radius: 4px; cursor: pointer;}
        input[type=submit]:hover{background-color: #45a049;}
        h2{color: #333;}
      </style></head><body>
      <div class="container">
        <h2>WiFi Settings</h2>
        <p>Current WiFi: )rawliteral" + preferences.getString("ssid", "Not Set") + R"rawliteral(</p>
        <form action="/save" method="POST">
          <p><input type="text" name="ssid" placeholder="New WiFi Network (SSID)"></p>
          <p><input type="password" name="password" placeholder="New Password"></p>
          <p><input type="submit" value="Save and Restart"></p>
        </form>
      </div></body></html>)rawliteral";
    server.send(200, "text/html", html);
  });

  
  server.on("/save", HTTP_POST, []() {
    String new_ssid = server.arg("ssid");
    String new_password = server.arg("password");

    Serial.println("New WiFi credentials received via AP:");
    Serial.print("SSID: ");
    Serial.println(new_ssid);

    preferences.begin("wifi-creds", false);
    preferences.putString("ssid", new_ssid);
    preferences.putString("password", new_password);
    preferences.end();

    String html = R"rawliteral(
      <!DOCTYPE html><html><body><h2>Settings Saved!</h2><p>The device will now restart to connect to the new WiFi network.</p></body></html>)rawliteral";
    server.send(200, "text/html", html);
    
    delay(1000);
    ESP.restart();
  });
}

// ================================================================
// Функция для запуска режима ТОЛЬКО точки доступа (для первоначальной настройки)
// ================================================================
void startInitialAPMode() {
  Serial.println("\nNo saved credentials. Starting initial AP mode.");
  
  WiFi.softAP("ESP32-Config");
  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);

  setupWebServer(); // Настраиваем обработчики
  server.begin();   // Запускаем сервер

  // Бесконечный цикл для обработки запросов к веб-серверу
  while (true) {
    server.handleClient();
    delay(1);
  }
}

// ================================================================
// SETUP
// ================================================================
void setup() {
  Serial.begin(115200);
  
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  client.setInsecure();

  // Загружаем сохраненные данные
  preferences.begin("wifi-creds", true);
  String saved_ssid = preferences.getString("ssid", "");
  String saved_password = preferences.getString("password", "");
  preferences.end();

  // Если нет сохраненных данных, запускаем режим первоначальной настройки
  if (saved_ssid.length() == 0) {
    startInitialAPMode();
  }

  // Устанавливаем режим STA (клиент) и пытаемся подключиться
  WiFi.mode(WIFI_AP_STA); // *** Включаем двойной режим ***
  WiFi.begin(saved_ssid.c_str(), saved_password.c_str());

  Serial.print("Connecting to WiFi: " + saved_ssid);
  int attempts = 0;
  while (WiFi.status() != WL_CONNECTED && attempts < 30) {
    delay(500);
    Serial.print(".");
    attempts++;
  }

  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("\nCould not connect. Restarting in initial AP mode...");
    delay(2000);
    startInitialAPMode(); // Если не удалось подключиться, снова уходим в режим настройки
  }
  
  // Если подключение успешно
  Serial.println("\nWiFi connected!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  // Запускаем точку доступа, которая будет работать ПАРАЛЛЕЛЬНО
  Serial.println("Starting configuration AP: ESP32-Config");
  WiFi.softAP("ESP32-Config");
  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);

  // Настраиваем и запускаем веб-сервер для постоянного доступа
  setupWebServer();
  server.begin();
  
  Serial.println("Setup complete. Device is running in dual mode.");
}

// ================================================================
// LOOP - Основной цикл работы устройства
// ================================================================
void loop() {
  // 1. Постоянно обрабатываем клиентские запросы к веб-серверу
  server.handleClient(); 

  // 2. Используем неблокирующий таймер для основной задачи
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis; // Сброс таймера

    // Проверяем, есть ли еще подключение. Если нет - перезагружаемся.
    if (WiFi.status() != WL_CONNECTED) {
      Serial.println("WiFi connection lost. Restarting...");
      delay(1000);
      ESP.restart();
    }

    // --- Основная логика измерения и отправки данных ---
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    
    long duration = pulseIn(echoPin, HIGH);
    float distance_cm = duration * 0.034 / 2;
    
    long percentage = map(distance_cm, MAX_DISTANCE_CM, MIN_DISTANCE_CM, 0, 100);
    percentage = constrain(percentage, 0, 100);
    
    Serial.printf("Sending Data -> Distance: %.2f cm, Fullness: %ld %%\n", distance_cm, percentage);

    HTTPClient http;
    String serverPath = "https://" + String(server_ip) + ":" + String(server_port) + "/data";
                                                                  
    if (http.begin(client, serverPath)) {
      http.addHeader("Content-Type", "application/json");

      StaticJsonDocument<256> jsonDoc;
      jsonDoc["distance"] = distance_cm;
      jsonDoc["percentage"] = percentage;
      jsonDoc["password"] = api_password;
      
      String requestBody;
      serializeJson(jsonDoc, requestBody);

      int httpResponseCode = http.POST(requestBody);

      if (httpResponseCode > 0) {
        Serial.printf("HTTPS Response code: %d\n", httpResponseCode);
      } else {
        Serial.printf("Error on sending POST: %s\n", http.errorToString(httpResponseCode).c_str());
      }
      http.end();
    } else {
      Serial.println("Failed to start HTTP client.");
    }
  }
}
// H1k2U7y0
