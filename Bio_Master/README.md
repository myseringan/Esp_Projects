# Bio Master - Smart Agriculture System 🌱

![Bio Master](https://img.shields.io/badge/Project-Bio%20Master-green)
![Arduino](https://img.shields.io/badge/Platform-Arduino-blue)
![ESP8266](https://img.shields.io/badge/ESP8266-WiFi-orange)
![Blynk](https://img.shields.io/badge/Integration-Blynk-yellow)

## 🌍 Multi-language README
- [English](#english) | [Русский](#русский) | [O'zbek](#ozbek)

---

## English

### 🤖 Smart Plant Monitoring and Control System

Bio Master is an advanced smart agriculture system that automates plant care using IoT technology. The system monitors environmental conditions and automatically controls watering, lighting, and temperature.

### ✨ Key Features

- **🌡️ Multi-sensor Monitoring**
  - Temperature and humidity (DHT11)
  - Soil moisture levels
  - Light intensity (LDR sensor)
  
- **💧 Smart Automation**
  - Automatic watering based on soil moisture
  - Intelligent lighting control
  - Temperature regulation
  - Customizable plant profiles

- **📱 Remote Control**
  - Blynk mobile app integration
  - Captive portal WiFi configuration
  - Real-time sensor data monitoring
  - Manual override controls

- **🌿 Plant Profiles**
  - Pre-configured settings for 10+ plants
  - Custom parameter settings
  - Easy profile switching

### 🛠 Technical Specifications

#### Hardware Components
- **Main Controller**: Arduino Uno/Nano
- **WiFi Module**: ESP8266
- **Sensors**: 
  - DHT11 (Temperature & Humidity)
  - Soil Moisture Sensor
  - LDR (Light Sensor)
- **Actuators**:
  - Water pump
  - Heating elements
  - Cooling fans
  - Grow lights
- **Interface**:
  - Rotary encoder with push button
  - 16x2 LCD with I2C
  - Buzzer for alerts

#### Communication
- **Serial Communication** between Arduino and ESP8266
- **Blynk Cloud** for mobile app
- **Captive Portal** for WiFi setup
- **Custom protocol** with frame-based messaging

### 📦 Installation

#### 1. Hardware Setup
```cpp
// Pin Configuration:
// Encoder: CLK=6, DT=7, SW=5
// LCD: I2C (0x27)
// DHT11: Pin 8
// Relays: 13, 2, 12, 11
// Buzzer: 9
// LDR: A1
// Soil Sensor: A0
// ESP8266: RX=3, TX=4
```
2. Software Requirements
ini
; Required Libraries:
; - GyverEncoder
; - LiquidCrystal_I2C
; - DHT sensor library
; - SoftwareSerial
; - ESP8266WiFi
; - Blynk
; - LittleFS
; - ArduinoJson
3. Blynk Setup
Create new project in Blynk app

Use Template ID: TMPL6-Qhz9qFz

Add widgets for sensors and controls

🚀 Usage
Main Menu Navigation
Rotate encoder to browse plants

Press encoder to select plant

"Boshqalar" for custom settings

"Chiqish" to exit menu

Supported Plants
Tomato 🍅, Carrot 🥕, Potato 🥔, Onion

Eggplant, Cabbage, Zucchini

Watermelon 🍉, Melon, Cucumber 🥒

Custom Settings
Adjustable parameters:

Temperature range (min/max)

Humidity range (min/max)

Soil moisture threshold

📁 Project Structure
text
Bio_Master/
├── Bio_Master.ino      # Main controller logic
├── Encoder.ino         # Rotary encoder handling
├── Ekinlar.ino         # Plant profiles
├── Boshqalar.ino       # Custom settings menu
├── Harorat.ino         # Temperature control
├── Rele.ino            # Relay control functions
├── Chiqish.ino         # Exit routines
└── Bio_Master_Wifi.ino # ESP8266 WiFi & Blynk
🔧 Configuration
WiFi Setup
Connect to "Bio Master" access point

Open browser to configure WiFi

Enter SSID and password

System automatically connects

Blynk Virtual Pins
V1: Temperature 🌡️

V2: Humidity 💧

V3: Soil Moisture 🌱

V4: Water Pump Control 💦

V5: Light Control 💡

V6: Light Intensity 📊

🐛 Troubleshooting
Common Issues:

LCD not displaying: Check I2C address

Sensors not reading: Verify pin connections

WiFi not connecting: Reset and reconfigure

Blynk disconnected: Check internet connection

Русский
🤖 Умная система мониторинга и контроля растений
Bio Master - это продвинутая система умного земледелия, которая автоматизирует уход за растениями с использованием IoT технологий.

✨ Основные возможности
🌡️ Мультисенсорный мониторинг

Температура и влажность (DHT11)

Уровень влажности почвы

Интенсивность освещения (LDR sensor)

💧 Умная автоматизация

Автополив по влажности почвы

Интеллектуальное управление светом

Регулировка температуры

Настраиваемые профили растений

📱 Удаленное управление

Интеграция с Blynk приложением

Captive portal для настройки WiFi

Мониторинг данных с датчиков в реальном времени

Ручное управление

🌿 Профили растений

Предустановленные настройки для 10+ растений

Пользовательские параметры

Легкое переключение профилей

🛠 Технические характеристики
Аппаратные компоненты
Главный контроллер: Arduino Uno/Nano

WiFi модуль: ESP8266

Датчики:

DHT11 (Температура и влажность)

Датчик влажности почвы

LDR (Датчик освещенности)

Исполнительные устройства:

Водяная помпа

Нагревательные элементы

Вентиляторы охлаждения

Фитолампы

Интерфейс:

Ротационный энкодер с кнопкой

LCD 16x2 с I2C

Зуммер для оповещений

🚀 Использование
Навигация в главном меню
Вращайте энкодер для выбора растений

Нажмите энкодер для выбора растения

"Boshqalar" для пользовательских настроек

"Chiqish" для выхода из меню

Поддерживаемые растения
Помидор 🍅, Морковь 🥕, Картофель 🥔, Лук

Баклажан, Капуста, Кабачок

Арбуз 🍉, Дыня, Огурец 🥒

O'zbek
🤖 Aqlli O'simlik Kuzatish va Nazorat Tizimi
Bio Master - bu IoT texnologiyalaridan foydalanib o'simliklarni parvarish qilishni avtomatlashtiradigan ilg'or aqlli qishloq xo'jaligi tizimi.

✨ Asosiy Xususiyatlar
🌡️ Ko'p sensorli monitoring

Harorat va namlik (DHT11)

Tuproq namlik darajasi

Yorug'lik intensivligi (LDR sensor)

💧 Aqlli avtomatlashtirish

Tuproq namligiga asoslangan avtomatik sug'orish

Aqlli yorug'lik boshqaruv

Haroratni tartibga solish

Sozlanishi mumkin bo'lgan o'simlik profillari

📱 Masofadan boshqarish

Blynk mobil ilova integratsiyasi

WiFi sozlash uchun captive portal

Real vaqtda sensor ma'lumotlarini kuzatish

Qo'lda boshqarish

🌿 O'simlik profillari

10+ o'simlik uchun oldindan sozlangan parametrlar

Foydalanuvchi parametrlari

Oson profil almashish

🚀 Foydalanish
Asosiy menyu navigatsiyasi
Enkoderni aylantiring - o'simliklarni ko'rib chiqish

Enkoderni bosing - o'simlikni tanlash

"Boshqalar" - maxsus sozlamalar

"Chiqish" - menyudan chiqish

Qo'llab-quvvatlanadigan o'simliklar
Pamidor 🍅, Sabzi 🥕, Kartoshka 🥔, Piyoz

Baqlajon, Karam, Qovoq

Tarvuz 🍉, Qovun, Bodring 🥒

👨‍💻 Author
Temur Eshmurodov

📄 License
This project is open source. Feel free to use and modify for your needs.

<div align="center">
🌱 Grow Smart, Harvest More with Bio Master! 🌱

</div> ```
