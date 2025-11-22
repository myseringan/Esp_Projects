# ESP32 Smart Monitoring Bot 🤖

![ESP32](https://img.shields.io/badge/ESP32-Smart%20Bot-red)
![WiFi](https://img.shields.io/badge/WiFi-Dual%20Mode-blue)
![HTTPS](https://img.shields.io/badge/Protocol-HTTPS-green)
![Web Server](https://img.shields.io/badge/Interface-Web%20Server-orange)

## 🌍 Multi-language README
- [English](#english) | [Русский](#русский) | [O'zbek](#ozbek)

---

## English

### 🤖 Smart Distance Monitoring & Data Transmission System

Advanced ESP32-based monitoring device with dual WiFi mode, web configuration interface, and secure HTTPS data transmission to remote servers.

### ✨ Key Features

- **📡 Dual WiFi Operation**
  - STA mode for internet connectivity
  - AP mode for configuration access
  - Automatic fallback and recovery
  - Web-based configuration portal

- **📊 Distance Monitoring**
  - HC-SR04 ultrasonic sensor
  - Real-time distance measurement
  - Percentage fullness calculation
  - Configurable min/max ranges

- **🔒 Secure Communication**
  - HTTPS with insecure bypass
  - API password protection
  - JSON data formatting
  - Secure server communication

- **⚙️ Smart Configuration**
  - Web-based setup interface
  - Persistent credential storage
  - One-time initial configuration
  - Remote reconfiguration capability

### 🛠 Technical Specifications

#### Hardware Components
- **Controller**: ESP32
- **Sensor**: HC-SR04 Ultrasonic
- **Communication**: WiFi 2.4GHz
- **Storage**: Preferences (NVS)

#### Communication
- **Local**: Web Server (HTTP)
- **Remote**: HTTPS REST API
- **Protocol**: JSON over HTTP/HTTPS
- **Security**: API Key Authentication

### 📦 Pin Configuration

```cpp
// Ultrasonic Sensor Pins
const int trigPin = 5;   // Trigger
const int echoPin = 18;  // Echo

// Distance Configuration
const int MIN_DISTANCE_CM = 5;   // Minimum range
const int MAX_DISTANCE_CM = 100; // Maximum range
```

### 🚀 Installation & Setup

#### 1. Initial Setup
- Power on the ESP32
- Connect to "ESP32-Config" WiFi network
- Open browser to access web interface
- Configure WiFi credentials
- Device restarts and connects

#### 2. Library Dependencies
```cpp
#include <WiFi.h>
#include <WebServer.h>
#include <Preferences.h>
#include <WiFiClientSecure.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
```

#### 3. Server Configuration
```cpp
const char* server_ip = "5.8.51.154";
const int server_port = 443;
const char* api_password = "your_api_password";
```

### 🎮 Operation Modes

#### Initial Setup Mode
- **Access Point**: "ESP32-Config"
- **Web Interface**: Configuration portal
- **Function**: WiFi credential setup
- **Access**: http://192.168.4.1

#### Normal Operation Mode
- **STA Mode**: Connected to configured WiFi
- **AP Mode**: Configuration access remains
- **Data Transmission**: Regular HTTPS posts
- **Monitoring**: Continuous distance measurement

### 📊 Data Transmission

#### Measurement Cycle
- **Interval**: 10 seconds
- **Sensor**: HC-SR04 ultrasonic
- **Calculation**: Distance to percentage
- **Range**: 5cm to 100cm

#### JSON Payload
```json
{
  "distance": 25.5,
  "percentage": 75,
  "password": "api_password"
}
```

### 🔧 Configuration Interface

#### Web Server Features
- **Real-time Status**: Current WiFi connection
- **Form-based Setup**: Simple credential input
- **Automatic Restart**: Applies new settings
- **Persistent Storage**: Saves credentials

#### Access Methods
1. **Initial Setup**: Connect to AP "ESP32-Config"
2. **Reconfiguration**: Access via local IP or AP
3. **Remote Access**: Network connectivity required

### ⚙️ Technical Details

#### WiFi Management
```cpp
WiFi.mode(WIFI_AP_STA); // Dual mode operation
WiFi.softAP("ESP32-Config"); // Configuration AP
```

#### Data Storage
```cpp
Preferences preferences;
preferences.begin("wifi-creds", false);
preferences.putString("ssid", new_ssid);
preferences.end();
```

#### Secure Communication
```cpp
WiFiClientSecure client;
client.setInsecure(); // Bypass certificate validation
```

### 🐛 Troubleshooting

**Common Issues:**
- **AP not visible**: Check ESP32 power and reset
- **Web interface inaccessible**: Verify IP address
- **No server connection**: Check WiFi credentials
- **Sensor errors**: Verify HC-SR04 wiring

**Recovery Procedures:**
1. Power cycle device
2. Connect to ESP32-Config AP
3. Reconfigure WiFi settings
4. Monitor serial output (115200 baud)

---

## Русский

### 🤖 Умная система мониторинга расстояния и передачи данных

Продвинутое устройство на базе ESP32 с двойным режимом WiFi, веб-интерфейсом для настройки и безопасной передачей данных по HTTPS.

### ✨ Основные возможности

- **📡 Двойной режим WiFi**
  - STA режим для подключения к интернету
  - AP режим для конфигурации
  - Автоматическое восстановление
  - Веб-интерфейс настройки

- **📊 Мониторинг расстояния**
  - Ультразвуковой датчик HC-SR04
  - Измерение расстояния в реальном времени
  - Расчет процента заполнения
  - Настраиваемые диапазоны

- **🔒 Безопасная связь**
  - HTTPS соединение
  - Защита паролем API
  - Форматирование данных JSON
  - Безопасная передача на сервер

### 📦 Конфигурация пинов

```cpp
// Ультразвуковой датчик
const int trigPin = 5;   // Trigger
const int echoPin = 18;  // Echo

// Диапазон измерений
const int MIN_DISTANCE_CM = 5;   // Минимальное расстояние
const int MAX_DISTANCE_CM = 100; // Максимальное расстояние
```

### 🚀 Использование

#### Веб-интерфейс
- Подключитесь к WiFi "ESP32-Config"
- Откройте браузер для доступа к настройкам
- Введите данные WiFi сети
- Устройство перезагрузится и подключится

#### Передача данных
- **Интервал**: 10 секунд
- **Данные**: Расстояние и процент заполнения
- **Протокол**: HTTPS с JSON
- **Безопасность**: Защита паролем API

---

## O'zbek

### 🤖 Aqlli Masofa Kuzatish va Ma'lumot Uzatish Tizimi

ESP32 asosidagi ilg'or qurilma, qo'shma WiFi rejimi, veb-sozlash interfeysi va masofaviy serverlarga xavfsiz HTTPS ma'lumot uzatish.

### ✨ Asosiy xususiyatlar

- **📡 Qo'shma WiFi ishlashi**
  - Internet uchun STA rejimi
  - Sozlash uchun AP rejimi
  - Avtomatik tiklanuvchanlik
  - Veb-asosidagi sozlash portali

- **📊 Masofa monitoringi**
  - HC-SR04 ultratovush sensori
  - Real vaqtda masofa o'lchash
  - Foiz to'liqlik hisoblash
  - Sozlanishi mumkin diapazonlar

- **🔒 Xavfsiz aloqa**
  - HTTPS bilan xavfsiz uzatish
  - API parol himoyasi
  - JSON ma'lumot formatlash
  - Xavfsiz server aloqasi

### 📦 Pin konfiguratsiyasi

```cpp
// Ultratovush sensori
const int trigPin = 5;   // Trigger
const int echoPin = 18;  // Echo

// O'lchash diapazoni
const int MIN_DISTANCE_CM = 5;   // Minimal masofa
const int MAX_DISTANCE_CM = 100; // Maksimal masofa
```

### 🚀 Foydalanish

#### Dastlabki sozlash
- ESP32 ni yoqing
- "ESP32-Config" WiFi tarmog'iga ulaning
- Veb-interfeysga kirish uchun brauzerni oching
- WiFi ma'lumotlarini sozlang
- Qurilma qayta ishga tushadi va ulanadi

#### Ma'lumot uzatish
- **Interval**: 10 soniya
- **Ma'lumot**: Masofa va to'liqlik foizi
- **Protokol**: HTTPS va JSON
- **Xavfsizlik**: API parol himoyasi

---

## 👨‍💻 Author

**Temur Eshmurodov**

## 📄 License

This project is open source. Feel free to use and modify for your needs.

---

<div align="center">

**🤖 Smart Monitoring Made Simple & Secure! 🤖**

</div>
