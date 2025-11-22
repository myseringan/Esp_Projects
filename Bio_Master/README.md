# Bio Master - Smart Agriculture System 🌱

![Bio Master](https://img.shields.io/badge/Project-Bio%20Master-green)
![Arduino](https://img.shields.io/badge/Platform-Arduino-blue)
![ESP8266](https://img.shields.io/badge/ESP8266-WiFi-orange)
![Blynk](https://img.shields.io/badge/Integration-Blynk-yellow)

## 🌍 Multi-language README
- [English](#english)
- [Русский](#русский)
- [O'zbek](#ozbek)

---

## English

### 🤖 Smart Plant Monitoring and Control System

**Bio Master** is an advanced smart agriculture system that automates plant care using IoT technology. The system monitors environmental conditions and automatically controls watering, lighting, and temperature.

### ✨ Key Features

* **🌡️ Multi-sensor Monitoring**
  * Temperature and humidity (DHT11)
  * Soil moisture levels
  * Light intensity (LDR sensor)
* **💧 Smart Automation**
  * Automatic watering based on soil moisture
  * Intelligent lighting control
  * Temperature regulation
  * Customizable plant profiles
* **📱 Remote Control**
  * Blynk mobile app integration
  * Captive portal WiFi configuration
  * Real-time sensor data monitoring
  * Manual override controls
* **🌿 Plant Profiles**
  * Pre-configured settings for 10+ plants
  * Custom parameter settings
  * Easy profile switching

### 🛠 Technical Specifications

#### Hardware Components
* **Main Controller:** Arduino Uno/Nano
* **WiFi Module:** ESP8266
* **Sensors:**
  * DHT11 (Temperature & Humidity)
  * Soil Moisture Sensor
  * LDR (Light Sensor)
* **Actuators:**
  * Water pump
  * Heating elements
  * Cooling fans
  * Grow lights
* **Interface:**
  * Rotary encoder with push button
  * 16x2 LCD with I2C
  * Buzzer for alerts

#### Communication
* **Serial Communication:** Bridge between Arduino and ESP8266
* **Blynk Cloud:** For mobile app control
* **Captive Portal:** For easy WiFi setup
* **Custom Protocol:** Frame-based messaging

### 📦 Installation

#### 1. Hardware Setup (Pinout)
```cpp
// Pin Configuration:
// Encoder:
//   CLK = 6
//   DT  = 7
//   SW  = 5
// LCD: I2C Address (0x27)
// DHT11: Pin 8
// Relays:
//   Relay 1 = 13
//   Relay 2 = 2
//   Relay 3 = 12
//   Relay 4 = 11
// Buzzer: 9
// LDR: A1
// Soil Sensor: A0
// ESP8266: RX = 3, TX = 4
````

#### 2\. Software Requirements

Ensure you have the following libraries installed in your Arduino IDE:

```ini
; Required Libraries:
; - GyverEncoder
; - LiquidCrystal_I2C
; - DHT sensor library
; - SoftwareSerial
; - ESP8266WiFi
; - Blynk
; - LittleFS
; - ArduinoJson
```

#### 3\. Blynk Setup

1.  Create a new project in the Blynk app.
2.  Use Template ID: `TMPL6-Qhz9qFz`
3.  Add widgets for sensors and controls mapped to the Virtual Pins listed below.

### 🚀 Usage

#### Main Menu Navigation

  * **Rotate Encoder:** Browse plants
  * **Press Encoder:** Select plant
  * **"Boshqalar":** Enter custom settings menu
  * **"Chiqish":** Exit menu

#### Supported Plants

| Category | Plants |
| :--- | :--- |
| **Root Veg** | Tomato 🍅, Carrot 🥕, Potato 🥔, Onion |
| **Greens** | Eggplant, Cabbage, Zucchini |
| **Melons** | Watermelon 🍉, Melon, Cucumber 🥒 |

#### Custom Settings

You can manually adjust:

  * Temperature range (min/max)
  * Humidity range (min/max)
  * Soil moisture threshold

### 📁 Project Structure

```text
Bio_Master/
├── Bio_Master.ino      # Main controller logic
├── Encoder.ino         # Rotary encoder handling
├── Ekinlar.ino         # Plant profiles database
├── Boshqalar.ino       # Custom settings menu
├── Harorat.ino         # Temperature control logic
├── Rele.ino            # Relay control functions
├── Chiqish.ino         # Exit routines
└── Bio_Master_Wifi.ino # ESP8266 WiFi & Blynk logic
```

### 🔧 Configuration

#### WiFi Setup

1.  Connect to the **"Bio Master"** WiFi access point.
2.  Open a browser; the configuration page should load (Captive Portal).
3.  Enter your Router SSID and Password.
4.  The system will save and automatically connect.

#### Blynk Virtual Pins

  * **V1:** Temperature 🌡️
  * **V2:** Humidity 💧
  * **V3:** Soil Moisture 🌱
  * **V4:** Water Pump Control 💦
  * **V5:** Light Control 💡
  * **V6:** Light Intensity 📊

### 🐛 Troubleshooting

  * **LCD not displaying:** Check I2C address (usually 0x27 or 0x3F).
  * **Sensors not reading:** Verify pin connections and power supply.
  * **WiFi not connecting:** Reset the ESP8266 and reconfigure via Captive Portal.
  * **Blynk disconnected:** Check internet connection and Auth Token.

-----

## Русский

### 🤖 Умная система мониторинга и контроля растений

**Bio Master** — это продвинутая система умного земледелия, которая автоматизирует уход за растениями с использованием IoT технологий.

### ✨ Основные возможности

  * **🌡️ Мультисенсорный мониторинг:** Температура/влажность (DHT11), влажность почвы, освещение (LDR).
  * **💧 Умная автоматизация:** Автополив, управление светом и температурой.
  * **📱 Удаленное управление:** Приложение Blynk, Captive portal для WiFi, мониторинг в реальном времени.
  * **🌿 Профили растений:** Настройки для 10+ видов растений + пользовательский режим.

### 🛠 Технические характеристики

  * **Контроллер:** Arduino Uno/Nano + ESP8266
  * **Датчики:** DHT11, Датчик влажности почвы, LDR
  * **Исполнители:** Помпа, нагреватели, вентиляторы, фитолампы
  * **Интерфейс:** Энкодер, LCD 16x2, Зуммер

### 🚀 Использование

  * **Навигация:** Вращайте энкодер для выбора, нажмите для подтверждения.
  * **Меню:** Выберите растение или "Boshqalar" для ручной настройки.
  * **Растения:** Помидор 🍅, Морковь 🥕, Картофель 🥔, Лук, Баклажан, Капуста, Кабачок, Арбуз 🍉, Дыня, Огурец 🥒.

-----

## O'zbek

### 🤖 Aqlli O'simlik Kuzatish va Nazorat Tizimi

**Bio Master** — bu IoT texnologiyalaridan foydalanib o'simliklarni parvarish qilishni avtomatlashtiradigan ilg'or aqlli qishloq xo'jaligi tizimi.

### ✨ Asosiy Xususiyatlar

  * **🌡️ Ko'p sensorli monitoring:** Harorat/namlik (DHT11), tuproq namligi, yorug'lik (LDR).
  * **💧 Aqlli avtomatlashtirish:** Tuproq namligiga qarab sug'orish, yorug'lik va haroratni boshqarish.
  * **📱 Masofadan boshqarish:** Blynk ilovasi, WiFi sozlash portali, real vaqtda kuzatuv.
  * **🌿 O'simlik profillari:** 10+ o'simlik uchun tayyor sozlamalar va maxsus rejim.

### 🛠 Texnik Xususiyatlar

  * **Kontroller:** Arduino Uno/Nano + ESP8266
  * **Sensorlar:** DHT11, Tuproq namlik sensori, LDR
  * **Boshqaruv:** Nasos, isitgich, ventilyator, fitolampalar
  * **Interfeys:** Enkoder, LCD 16x2, Buzzer

### 🚀 Foydalanish

  * **Navigatsiya:** Enkoderni aylantirib tanlang, tasdiqlash uchun bosing.
  * **Menyu:** O'simlikni tanlang yoki "Boshqalar" orqali o'zingiz sozlang.
  * **O'simliklar:** Pomidor 🍅, Sabzi 🥕, Kartoshka 🥔, Piyoz, Baqlajon, Karam, Qovoq, Tarvuz 🍉, Qovun, Bodring 🥒.

-----

### 👨‍💻 Author

**Temur Eshmurodov**

### 📄 License

This project is open source. Feel free to use and modify for your needs.

🌱 Grow Smart, Harvest More with Bio Master! 🌱

```
```
