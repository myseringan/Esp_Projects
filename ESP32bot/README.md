# 🤖 ESP32bot - Smart IoT Monitoring System

[![ESP32](https://img.shields.io/badge/ESP32-DevKit-red?logo=espressif)](https://www.espressif.com/)
[![HTTPS](https://img.shields.io/badge/Protocol-HTTPS-green)](https://en.wikipedia.org/wiki/HTTPS)
[![License](https://img.shields.io/badge/License-MIT-blue.svg)](LICENSE)

## 🌍 Languages / Tillar / Языки

- [O'zbek](#ozbek)
- [English](#english)
- [Русский](#русский)

---

## O'zbek

### 📖 Loyiha Haqida

**ESP32bot** — bu ultrasonik sensor yordamida idish to'lganligini o'lchaydigan va ma'lumotlarni serverga HTTPS orqali yuboradigan IoT qurilma. Shu bilan birga, WiFi sozlamalari uchun qulay web interfeys taqdim etadi.

### ✨ Imkoniyatlari

- 📏 **Ultrasonik o'lchash** - HC-SR04 sensori bilan masofa o'lchash
- 📊 **To'lganlik foizi** - avtomatik hisoblash (0-100%)
- 🔐 **HTTPS protokoli** - xavfsiz ma'lumot uzatish
- 📶 **Ikki rejimli WiFi** - AP + STA bir vaqtda
- 🖥️ **Web interfeys** - WiFi sozlash uchun
- 💾 **Preferences** - WiFi ma'lumotlarni saqlash
- 🔄 **Avtomatik qayta ulanish** - aloqa uzilganda

### 🔧 Kerakli Komponentlar

| Komponent | Miqdor | Izoh |
|-----------|--------|------|
| ESP32 DevKit | 1 | Asosiy kontroler |
| HC-SR04 | 1 | Ultrasonik sensor |
| Breadboard | 1 | Prototiplash uchun |
| Jumper simlar | 4+ | Ulanish uchun |

### 📌 Ulanish Sxemasi

```
HC-SR04 Ultrasonik Sensor:
  - VCC → 5V (yoki Vin)
  - GND → GND
  - TRIG → GPIO 5
  - ECHO → GPIO 18
```

### ⚙️ Konfiguratsiya

`ESP32bot.ino` faylida quyidagi parametrlarni o'zgartiring:

```cpp
const char* server_ip = "5.8.51.154";     // Server IP manzili
const int server_port = 443;               // HTTPS port
const char* api_password = "your_api_key"; // API kaliti
const int MIN_DISTANCE_CM = 5;             // Minimal masofa (to'la)
const int MAX_DISTANCE_CM = 100;           // Maksimal masofa (bo'sh)
```

### 📡 Server API

Qurilma serverga quyidagi JSON ma'lumotlarni yuboradi:

```json
{
  "distance": 25.5,
  "percentage": 75,
  "password": "api_kaliti"
}
```

**Endpoint:** `POST https://server_ip:port/data`

### 🚀 O'rnatish

1. Arduino IDE ni oching
2. ESP32 platasini qo'shing (Boards Manager orqali)
3. Kerakli kutubxonalarni o'rnating:
   ```
   - WiFi (ESP32 Core bilan keladi)
   - WebServer (ESP32 Core bilan keladi)
   - Preferences (ESP32 Core bilan keladi)
   - WiFiClientSecure (ESP32 Core bilan keladi)
   - HTTPClient (ESP32 Core bilan keladi)
   - ArduinoJson
   ```
4. `ESP32bot.ino` ni ESP32 ga yuklang

### 📶 WiFi Sozlash

**Birinchi marta:**
1. "ESP32-Config" WiFi tarmog'iga ulaning
2. Brauzerda `192.168.4.1` manzilini oching
3. WiFi ma'lumotlarini kiriting
4. Qurilma avtomatik qayta ishga tushadi

**Ishlayotgan paytda:**
- Qurilma har doim "ESP32-Config" AP ni ishga tushiradi
- Asosiy WiFi ga ulangan holda ham sozlamalarni o'zgartirish mumkin

---

## English

### 📖 About

**ESP32bot** is an IoT device that measures container fullness using an ultrasonic sensor and sends data to a server via HTTPS. It also provides a convenient web interface for WiFi configuration.

### ✨ Features

- 📏 **Ultrasonic measurement** - distance sensing with HC-SR04
- 📊 **Fullness percentage** - automatic calculation (0-100%)
- 🔐 **HTTPS protocol** - secure data transmission
- 📶 **Dual-mode WiFi** - AP + STA simultaneously
- 🖥️ **Web interface** - for WiFi setup
- 💾 **Preferences** - persistent WiFi storage
- 🔄 **Auto-reconnect** - on connection loss

### 🔧 Required Components

| Component | Qty | Description |
|-----------|-----|-------------|
| ESP32 DevKit | 1 | Main controller |
| HC-SR04 | 1 | Ultrasonic sensor |
| Breadboard | 1 | For prototyping |
| Jumper wires | 4+ | For connections |

### 📌 Wiring Diagram

```
HC-SR04 Ultrasonic Sensor:
  - VCC → 5V (or Vin)
  - GND → GND
  - TRIG → GPIO 5
  - ECHO → GPIO 18
```

### ⚙️ Configuration

Modify the following parameters in `ESP32bot.ino`:

```cpp
const char* server_ip = "5.8.51.154";     // Server IP address
const int server_port = 443;               // HTTPS port
const char* api_password = "your_api_key"; // API key
const int MIN_DISTANCE_CM = 5;             // Min distance (full)
const int MAX_DISTANCE_CM = 100;           // Max distance (empty)
```

### 📡 Server API

The device sends the following JSON data to the server:

```json
{
  "distance": 25.5,
  "percentage": 75,
  "password": "api_key"
}
```

**Endpoint:** `POST https://server_ip:port/data`

### 🚀 Installation

1. Open Arduino IDE
2. Add ESP32 board (via Boards Manager)
3. Install required libraries:
   ```
   - WiFi (included with ESP32 Core)
   - WebServer (included with ESP32 Core)
   - Preferences (included with ESP32 Core)
   - WiFiClientSecure (included with ESP32 Core)
   - HTTPClient (included with ESP32 Core)
   - ArduinoJson
   ```
4. Upload `ESP32bot.ino` to ESP32

### 📶 WiFi Setup

**First time:**
1. Connect to "ESP32-Config" WiFi network
2. Open `192.168.4.1` in browser
3. Enter your WiFi credentials
4. Device will automatically restart

**While running:**
- Device always runs "ESP32-Config" AP
- Settings can be changed even while connected to main WiFi

---

## Русский

### 📖 О проекте

**ESP32bot** — это IoT устройство, которое измеряет наполненность ёмкости с помощью ультразвукового датчика и отправляет данные на сервер по HTTPS. Также предоставляет удобный веб-интерфейс для настройки WiFi.

### ✨ Возможности

- 📏 **Ультразвуковое измерение** - определение расстояния с HC-SR04
- 📊 **Процент наполненности** - автоматический расчёт (0-100%)
- 🔐 **Протокол HTTPS** - безопасная передача данных
- 📶 **Двойной режим WiFi** - AP + STA одновременно
- 🖥️ **Веб-интерфейс** - для настройки WiFi
- 💾 **Preferences** - сохранение WiFi данных
- 🔄 **Авто-переподключение** - при потере связи

### 🔧 Необходимые компоненты

| Компонент | Кол-во | Описание |
|-----------|--------|----------|
| ESP32 DevKit | 1 | Основной контроллер |
| HC-SR04 | 1 | Ультразвуковой датчик |
| Breadboard | 1 | Для прототипирования |
| Перемычки | 4+ | Для подключения |

### 📌 Схема подключения

```
HC-SR04 Ультразвуковой датчик:
  - VCC → 5V (или Vin)
  - GND → GND
  - TRIG → GPIO 5
  - ECHO → GPIO 18
```

### ⚙️ Конфигурация

Измените следующие параметры в `ESP32bot.ino`:

```cpp
const char* server_ip = "5.8.51.154";     // IP-адрес сервера
const int server_port = 443;               // HTTPS порт
const char* api_password = "your_api_key"; // API ключ
const int MIN_DISTANCE_CM = 5;             // Мин. расстояние (полный)
const int MAX_DISTANCE_CM = 100;           // Макс. расстояние (пустой)
```

### 📡 Server API

Устройство отправляет на сервер следующие JSON данные:

```json
{
  "distance": 25.5,
  "percentage": 75,
  "password": "api_ключ"
}
```

**Endpoint:** `POST https://server_ip:port/data`

### 🚀 Установка

1. Откройте Arduino IDE
2. Добавьте плату ESP32 (через Boards Manager)
3. Установите необходимые библиотеки:
   ```
   - WiFi (входит в ESP32 Core)
   - WebServer (входит в ESP32 Core)
   - Preferences (входит в ESP32 Core)
   - WiFiClientSecure (входит в ESP32 Core)
   - HTTPClient (входит в ESP32 Core)
   - ArduinoJson
   ```
4. Загрузите `ESP32bot.ino` в ESP32

### 📶 Настройка WiFi

**Первый запуск:**
1. Подключитесь к сети "ESP32-Config"
2. Откройте `192.168.4.1` в браузере
3. Введите данные вашей WiFi сети
4. Устройство автоматически перезагрузится

**Во время работы:**
- Устройство всегда запускает точку доступа "ESP32-Config"
- Настройки можно изменить даже при подключении к основной WiFi

---

## 📁 Project Structure / Fayl Tuzilishi / Структура проекта

```
ESP32bot/
└── ESP32bot.ino    # Main ESP32 code
```

## 🔌 Pin Configuration / Pin Konfiguratsiyasi / Конфигурация пинов

| Pin | Function | Description |
|-----|----------|-------------|
| GPIO 5 | TRIG | Ultrasonic trigger |
| GPIO 18 | ECHO | Ultrasonic echo |

## 📊 Data Flow / Ma'lumot Oqimi / Поток данных

```
HC-SR04 → ESP32 → HTTPS → Server
   ↓
Distance (cm) → Percentage (%) → JSON POST
```

## 🔒 Security Notes / Xavfsizlik / Безопасность

- 🔐 SSL/TLS orqali shifrlangan ma'lumot uzatish
- 🔑 API parol bilan autentifikatsiya
- ⚠️ `client.setInsecure()` ishlab chiqarish uchun sertifikat tekshiruvi bilan almashtirilishi kerak

## 📄 License

MIT License - Feel free to use and modify

## 👨‍💻 Author

**Temur Eshmurodov**

---

⭐ **Star this repository if you find it useful!**
