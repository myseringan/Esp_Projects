# 🌱 Bio Master - Smart Agriculture System

[![Arduino](https://img.shields.io/badge/Arduino-UNO-00979D?logo=arduino)](https://www.arduino.cc/)
[![ESP8266](https://img.shields.io/badge/ESP8266-WiFi-orange)](https://www.espressif.com/)
[![Blynk](https://img.shields.io/badge/Blynk-IoT-23C48E)](https://blynk.io/)
[![License](https://img.shields.io/badge/License-MIT-blue.svg)](LICENSE)

## 🌍 Languages / Tillar / Языки

- [O'zbek](#ozbek)
- [English](#english)
- [Русский](#русский)

---

## O'zbek

### 📖 Loyiha Haqida

**Bio Master** — bu qishloq xo'jaligini avtomatlashtirish uchun mo'ljallangan aqlli tizim. U Arduino UNO va ESP8266 asosida ishlaydi va Blynk ilovasi orqali masofadan boshqariladi.

### ✨ Imkoniyatlari

- 🌡️ **Harorat va namlik nazorati** - DHT11 sensori orqali
- 💧 **Avtomatik sug'orish** - tuproq namligi sensori bilan
- 💡 **Avtomatik yoritish** - LDR sensori orqali
- 🌾 **Oldindan sozlangan ekin rejimlari**:
  - Pomidor, Sabzi, Kartoshka
  - Piyoz, Baqlajon, Karam
  - Qovoq, Tarvuz, Qovun, Bodring
- 📱 **Blynk orqali masofadan boshqarish**
- 🖥️ **LCD displey** - barcha ko'rsatkichlarni ko'rsatadi
- 🔄 **Encoder menyusi** - qulay sozlash interfeysi
- 📶 **Captive Portal** - WiFi sozlash uchun

### 🔧 Kerakli Komponentlar

| Komponent | Miqdor | Izoh |
|-----------|--------|------|
| Arduino UNO | 1 | Asosiy kontroler |
| ESP8266 (NodeMCU/Wemos D1) | 1 | WiFi moduli |
| DHT11 | 1 | Harorat/namlik sensori |
| Tuproq namligi sensori | 1 | Kapasitiv yoki rezistiv |
| LDR (fotorezi̇stor) | 1 | Yorug'lik sensori |
| LCD 16x2 I2C | 1 | Displey |
| Rotary Encoder | 1 | Menyu boshqaruvi |
| 4-kanalli rele moduli | 1 | Yukni boshqarish |
| Buzzer | 1 | Ovozli signal |
| Suv pompasi | 1 | Sug'orish uchun |

### 📌 Ulanish Sxemasi (Arduino UNO)

```
DHT11:
  - VCC → 5V
  - GND → GND
  - DATA → D8

Encoder:
  - CLK → D6
  - DT → D7
  - SW → D5

LCD I2C:
  - SDA → A4
  - SCL → A5

Sensorlar:
  - Tuproq namligi → A0
  - LDR → A1

Releler:
  - Suv pompasi → D13
  - Yorug'lik → D2
  - Isitgich → D12
  - Ventilyator → D11

ESP8266 aloqa:
  - Arduino TX (D4) → ESP RX (D2)
  - Arduino RX (D3) → ESP TX (D3)
```

### 📲 Blynk Sozlamalari

| Virtual Pin | Vazifa |
|-------------|--------|
| V1 | Harorat (°C) |
| V2 | Havo namligi (%) |
| V3 | Tuproq namligi (%) |
| V4 | Suv pompasi (0/1) |
| V5 | Yorug'lik (0/1) |
| V6 | LDR qiymati (%) |

### 🚀 O'rnatish

1. Arduino IDE ni oching
2. Kerakli kutubxonalarni o'rnating:
   ```
   - GyverEncoder
   - LiquidCrystal_I2C
   - DHT sensor library
   - SoftwareSerial
   ```
3. `Bio_Master.ino` ni Arduino UNO ga yuklang
4. ESP8266 uchun qo'shimcha kutubxonalar:
   ```
   - ESP8266WiFi
   - BlynkSimpleEsp8266
   - LittleFS
   - ArduinoJson
   ```
5. `Bio_Master_Wifi.ino` ni ESP8266 ga yuklang

### 📡 WiFi Sozlash

1. "Bio Master" WiFi tarmog'iga ulaning
2. Parol: `samurai2023`
3. Brauzerda har qanday sahifani oching
4. WiFi ma'lumotlarini kiriting

---

## English

### 📖 About

**Bio Master** is a smart agriculture automation system based on Arduino UNO and ESP8266. It can be remotely controlled via the Blynk app.

### ✨ Features

- 🌡️ **Temperature & humidity monitoring** - via DHT11 sensor
- 💧 **Automatic irrigation** - soil moisture sensor
- 💡 **Automatic lighting** - LDR sensor
- 🌾 **Pre-configured crop modes**:
  - Tomato, Carrot, Potato
  - Onion, Eggplant, Cabbage
  - Pumpkin, Watermelon, Melon, Cucumber
- 📱 **Remote control via Blynk**
- 🖥️ **LCD display** - shows all readings
- 🔄 **Encoder menu** - convenient settings interface
- 📶 **Captive Portal** - for WiFi setup

### 🔧 Required Components

| Component | Qty | Description |
|-----------|-----|-------------|
| Arduino UNO | 1 | Main controller |
| ESP8266 (NodeMCU/Wemos D1) | 1 | WiFi module |
| DHT11 | 1 | Temperature/humidity sensor |
| Soil moisture sensor | 1 | Capacitive or resistive |
| LDR (photoresistor) | 1 | Light sensor |
| LCD 16x2 I2C | 1 | Display |
| Rotary Encoder | 1 | Menu control |
| 4-channel relay module | 1 | Load control |
| Buzzer | 1 | Audio signal |
| Water pump | 1 | For irrigation |

### 📌 Wiring Diagram (Arduino UNO)

```
DHT11:
  - VCC → 5V
  - GND → GND
  - DATA → D8

Encoder:
  - CLK → D6
  - DT → D7
  - SW → D5

LCD I2C:
  - SDA → A4
  - SCL → A5

Sensors:
  - Soil moisture → A0
  - LDR → A1

Relays:
  - Water pump → D13
  - Light → D2
  - Heater → D12
  - Fan → D11

ESP8266 communication:
  - Arduino TX (D4) → ESP RX (D2)
  - Arduino RX (D3) → ESP TX (D3)
```

### 📲 Blynk Configuration

| Virtual Pin | Function |
|-------------|----------|
| V1 | Temperature (°C) |
| V2 | Air humidity (%) |
| V3 | Soil moisture (%) |
| V4 | Water pump (0/1) |
| V5 | Light (0/1) |
| V6 | LDR value (%) |

### 🚀 Installation

1. Open Arduino IDE
2. Install required libraries:
   ```
   - GyverEncoder
   - LiquidCrystal_I2C
   - DHT sensor library
   - SoftwareSerial
   ```
3. Upload `Bio_Master.ino` to Arduino UNO
4. For ESP8266, install additional libraries:
   ```
   - ESP8266WiFi
   - BlynkSimpleEsp8266
   - LittleFS
   - ArduinoJson
   ```
5. Upload `Bio_Master_Wifi.ino` to ESP8266

### 📡 WiFi Setup

1. Connect to "Bio Master" WiFi network
2. Password: `samurai2023`
3. Open any webpage in browser
4. Enter your WiFi credentials

---

## Русский

### 📖 О проекте

**Bio Master** — это умная система автоматизации сельского хозяйства на базе Arduino UNO и ESP8266. Управляется удалённо через приложение Blynk.

### ✨ Возможности

- 🌡️ **Контроль температуры и влажности** - через датчик DHT11
- 💧 **Автоматический полив** - датчик влажности почвы
- 💡 **Автоматическое освещение** - фоторезистор LDR
- 🌾 **Предустановленные режимы для культур**:
  - Помидор, Морковь, Картофель
  - Лук, Баклажан, Капуста
  - Тыква, Арбуз, Дыня, Огурец
- 📱 **Удалённое управление через Blynk**
- 🖥️ **LCD дисплей** - показывает все показания
- 🔄 **Меню на энкодере** - удобный интерфейс настроек
- 📶 **Captive Portal** - для настройки WiFi

### 🔧 Необходимые компоненты

| Компонент | Кол-во | Описание |
|-----------|--------|----------|
| Arduino UNO | 1 | Основной контроллер |
| ESP8266 (NodeMCU/Wemos D1) | 1 | WiFi модуль |
| DHT11 | 1 | Датчик температуры/влажности |
| Датчик влажности почвы | 1 | Ёмкостной или резистивный |
| LDR (фоторезистор) | 1 | Датчик освещённости |
| LCD 16x2 I2C | 1 | Дисплей |
| Rotary Encoder | 1 | Управление меню |
| 4-канальный модуль реле | 1 | Управление нагрузкой |
| Buzzer | 1 | Звуковой сигнал |
| Водяная помпа | 1 | Для полива |

### 📌 Схема подключения (Arduino UNO)

```
DHT11:
  - VCC → 5V
  - GND → GND
  - DATA → D8

Энкодер:
  - CLK → D6
  - DT → D7
  - SW → D5

LCD I2C:
  - SDA → A4
  - SCL → A5

Датчики:
  - Влажность почвы → A0
  - LDR → A1

Реле:
  - Водяная помпа → D13
  - Освещение → D2
  - Обогреватель → D12
  - Вентилятор → D11

Связь с ESP8266:
  - Arduino TX (D4) → ESP RX (D2)
  - Arduino RX (D3) → ESP TX (D3)
```

### 📲 Настройка Blynk

| Virtual Pin | Функция |
|-------------|---------|
| V1 | Температура (°C) |
| V2 | Влажность воздуха (%) |
| V3 | Влажность почвы (%) |
| V4 | Водяная помпа (0/1) |
| V5 | Освещение (0/1) |
| V6 | Значение LDR (%) |

### 🚀 Установка

1. Откройте Arduino IDE
2. Установите необходимые библиотеки:
   ```
   - GyverEncoder
   - LiquidCrystal_I2C
   - DHT sensor library
   - SoftwareSerial
   ```
3. Загрузите `Bio_Master.ino` в Arduino UNO
4. Для ESP8266 установите дополнительные библиотеки:
   ```
   - ESP8266WiFi
   - BlynkSimpleEsp8266
   - LittleFS
   - ArduinoJson
   ```
5. Загрузите `Bio_Master_Wifi.ino` в ESP8266

### 📡 Настройка WiFi

1. Подключитесь к сети "Bio Master"
2. Пароль: `samurai2023`
3. Откройте любую веб-страницу в браузере
4. Введите данные вашей WiFi сети

---

## 📁 Project Structure / Fayl Tuzilishi / Структура проекта

```
Bio_Master/
├── Bio_Master.ino          # Main Arduino code
├── Bio_Master_Wifi/
│   └── Bio_Master_Wifi.ino # ESP8266 WiFi code
├── Boshqalar.ino           # Custom settings menu
├── Chiqish.ino             # Exit function
├── Ekinlar.ino             # Crop presets
├── Encoder.ino             # Encoder handling
├── Harorat.ino             # Temperature control
└── Rele.ino                # Relay functions
```

## 📄 License

MIT License - Feel free to use and modify

## 👨‍💻 Author

**Temur Eshmurodov** - Samurai Product

---

⭐ **Star this repository if you find it useful!**
