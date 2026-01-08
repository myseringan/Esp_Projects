# 🔌 ESP Projects Collection

**IoT проектлар тўплами | IoT Projects Collection | Коллекция IoT проектов**

[![ESP32](https://img.shields.io/badge/ESP32-000000?style=flat&logo=espressif&logoColor=white)](https://www.espressif.com/)
[![ESP8266](https://img.shields.io/badge/ESP8266-00979D?style=flat&logo=espressif&logoColor=white)](https://www.espressif.com/)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)
[![Arduino](https://img.shields.io/badge/Arduino-00979D?style=flat&logo=arduino&logoColor=white)](https://www.arduino.cc/)
[![PlatformIO](https://img.shields.io/badge/PlatformIO-FF7F00?style=flat&logo=platformio&logoColor=white)](https://platformio.org/)

**Тил танланг | Choose language | Выберите язык:**

[🇺🇿 O'zbekcha](#-ozbekcha) • [🇬🇧 English](#-english) • [🇷🇺 Русский](#-русский)

---

# 🇺🇿 O'zbekcha

## 📋 Проектлар рўйхати

| # | Проект | Тавсиф | Платформа |
|---|--------|--------|-----------|
| 1 | [Bio_Master](./Bio_Master) | 🌱 Ақлли қишлоқ хўжалиги | Arduino UNO + ESP8266 |
| 2 | [ESP32bot](./ESP32bot) | 📦 Контейнер мониторинги | ESP32 |
| 3 | [ESP32_LVGL_BLE_Panel](./ESP32_LVGL_BLE_Panel) | 📱 BLE бошқарув панели | ESP32 |
| 4 | [ESP32_TFT_display_temperature_output](./ESP32_TFT_display_temperature_output) | 🌡️ Ҳарорат дисплейи | ESP32 |
| 5 | [esp32s3-lvgl-dht-panel](./esp32s3-lvgl-dht-panel) | 🎨 LVGL иқлим панели | ESP32-S3 |
| 6 | [Payme_QR_ESP32](./Payme_QR_ESP32) | 💳 Тўлов хабарномалари | ESP32 |
| 7 | [Wireless_Soil_Sensor_Gateway](./Wireless_Soil_Sensor_Gateway) | 🌍 Тупроқ сенсорлари | ESP32-S3 |

---

### 🌱 Bio_Master
**Ақлли қишлоқ хўжалиги автоматлаштириш тизими**

Blynk IoT платформаси орқали масофадан бошқариладиган суғориш ва ёритиш тизими.

| Компонент | Функция |
|-----------|---------|
| DHT11 | Ҳарорат ва намлик |
| Тупроқ сенсори | Тупроқ намлиги |
| LDR | Ёруғлик даражаси |
| LCD 16x2 I2C | Маълумотларни кўрсатиш |
| 4-канал реле | Қурилмаларни бошқариш |
| Rotary Encoder | Менюда навигация |

**Хусусиятлар:** 10 та экин режими, автоматик суғориш, WiFi Captive Portal

```
WiFi: "Bio Master" / Парол: "samurai2023"
```

---

### 📦 ESP32bot
**IoT контейнер тўлиш мониторинги**

HC-SR04 ультратовуш сенсори орқали контейнер тўлиш даражасини аниқлаш.

| Компонент | Функция |
|-----------|---------|
| ESP32 | Асосий контроллер |
| HC-SR04 | Масофа ўлчаш |

**Хусусиятлар:** 0-100% тўлиш даражаси, HTTPS JSON API, веб-созлаш

```
AP: "ESP32-Config" → 192.168.4.1
```

---

### 📱 ESP32_LVGL_BLE_Panel
**BLE орқали бошқариладиган сенсорли панел**

ILI9488 TFT дисплей ва LVGL графика билан профессионал интерфейс.

| Компонент | Функция |
|-----------|---------|
| ESP32 | Контроллер + BLE |
| ILI9488 | 320x480 TFT дисплей |

**Хусусиятлар:** LVGL v8 UI, BLE командалар ("ON"/"OFF"), SquareLine Studio дизайн

---

### 🌡️ ESP32_TFT_display_temperature_output
**Анимацияли ҳарорат дисплейи**

DHT11 маълумотларини ST7735 экранда чиройли визуализация.

| Компонент | Функция |
|-----------|---------|
| ESP32 | Контроллер |
| ST7735 | 128x160 TFT дисплей |
| DHT11 | Ҳарорат сенсори |

**Хусусиятлар:** Термометр анимацияси, sparkline график, 2 сония янгиланиш

---

### 🎨 esp32s3-lvgl-dht-panel
**Замонавий LVGL иқлим панели**

ESP32-S3 ва LVGL билан профессионал UI дизайн.

| Компонент | Функция |
|-----------|---------|
| ESP32-S3 | Контроллер |
| ILI9488 | 320x480 TFT дисплей |
| DHT11 | Ҳарорат/намлик |

**Хусусиятлар:** Анимацияли arc индикаторлар, SquareLine Studio 1.5.3, 500ms анимациялар

---

### 💳 Payme_QR_ESP32
**Payme тўлов хабарномалари**

MQTT орқали Payme тизимидан реал вақтда хабарномалар.

| Компонент | Функция |
|-----------|---------|
| ESP32 | Контроллер + WiFi |
| LED | Тўлов индикатори |

**Хусусиятлар:** MQTT (HiveMQ), JSON парсинг, Payme интеграция

```
Архитектура: Payme → Server → MQTT → ESP32
```

---

### 🌍 Wireless_Soil_Sensor_Gateway
**Кўп сенсорли тупроқ мониторинги**

METER GS3 SDI-12 сенсорлари билан професионал тупроқ таҳлили.

| Компонент | Функция |
|-----------|---------|
| ESP32-S3 | Контроллер |
| METER GS3 (4x) | Тупроқ сенсорлари |

**Хусусиятлар:** Намлик/ҳарорат/EC ўлчаш, Deep Sleep (1 соат), 10μA уйқу режими

---

## 🛠️ Ўрнатиш

### Arduino IDE
1. [Arduino IDE](https://www.arduino.cc/en/software) юклаб олинг
2. ESP платалари URL қўшинг (`File` → `Preferences` → `Additional Board URLs`):
```
https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
https://arduino.esp8266.com/stable/package_esp8266com_index.json
```
3. Керакли кутубхоналарни ўрнатинг

### PlatformIO
1. [VS Code](https://code.visualstudio.com/) + [PlatformIO](https://platformio.org/) ўрнатинг
2. Проект папкасини очинг

---

## 📚 Кутубхоналар

| Кутубхона | Мақсад |
|-----------|--------|
| WiFi / ESP8266WiFi | WiFi уланиш |
| Blynk | IoT платформа |
| LVGL | Графика UI |
| TFT_eSPI | TFT дисплейлар |
| DHT | Ҳарорат сенсори |
| PubSubClient | MQTT |
| SDI12 | SDI-12 протокол |
| ArduinoJson | JSON |

---

# 🇬🇧 English

## 📋 Projects List

| # | Project | Description | Platform |
|---|---------|-------------|----------|
| 1 | [Bio_Master](./Bio_Master) | 🌱 Smart Agriculture System | Arduino UNO + ESP8266 |
| 2 | [ESP32bot](./ESP32bot) | 📦 Container Monitoring | ESP32 |
| 3 | [ESP32_LVGL_BLE_Panel](./ESP32_LVGL_BLE_Panel) | 📱 BLE Touch Panel | ESP32 |
| 4 | [ESP32_TFT_display_temperature_output](./ESP32_TFT_display_temperature_output) | 🌡️ Temperature Display | ESP32 |
| 5 | [esp32s3-lvgl-dht-panel](./esp32s3-lvgl-dht-panel) | 🎨 LVGL Climate Panel | ESP32-S3 |
| 6 | [Payme_QR_ESP32](./Payme_QR_ESP32) | 💳 Payment Notifications | ESP32 |
| 7 | [Wireless_Soil_Sensor_Gateway](./Wireless_Soil_Sensor_Gateway) | 🌍 Soil Sensors Gateway | ESP32-S3 |

---

### 🌱 Bio_Master
**Smart Agriculture Automation System**

Remote-controlled irrigation and lighting system via Blynk IoT platform.

| Component | Function |
|-----------|----------|
| DHT11 | Temperature & humidity |
| Soil sensor | Soil moisture |
| LDR | Light level |
| LCD 16x2 I2C | Data display |
| 4-channel relay | Device control |
| Rotary Encoder | Menu navigation |

**Features:** 10 crop modes, auto irrigation, WiFi Captive Portal

```
WiFi: "Bio Master" / Password: "samurai2023"
```

---

### 📦 ESP32bot
**IoT Container Fill Level Monitoring**

Container fill level detection using HC-SR04 ultrasonic sensor.

| Component | Function |
|-----------|----------|
| ESP32 | Main controller |
| HC-SR04 | Distance measurement |

**Features:** 0-100% fill level, HTTPS JSON API, web configuration

```
AP: "ESP32-Config" → 192.168.4.1
```

---

### 📱 ESP32_LVGL_BLE_Panel
**BLE-Controlled Touch Panel**

Professional UI with ILI9488 TFT display and LVGL graphics.

| Component | Function |
|-----------|----------|
| ESP32 | Controller + BLE |
| ILI9488 | 320x480 TFT display |

**Features:** LVGL v8 UI, BLE commands ("ON"/"OFF"), SquareLine Studio design

---

### 🌡️ ESP32_TFT_display_temperature_output
**Animated Temperature Display**

Beautiful visualization of DHT11 data on ST7735 screen.

| Component | Function |
|-----------|----------|
| ESP32 | Controller |
| ST7735 | 128x160 TFT display |
| DHT11 | Temperature sensor |

**Features:** Thermometer animation, sparkline graph, 2-second refresh

---

### 🎨 esp32s3-lvgl-dht-panel
**Modern LVGL Climate Panel**

Professional UI design with ESP32-S3 and LVGL.

| Component | Function |
|-----------|----------|
| ESP32-S3 | Controller |
| ILI9488 | 320x480 TFT display |
| DHT11 | Temperature/humidity |

**Features:** Animated arc indicators, SquareLine Studio 1.5.3, 500ms animations

---

### 💳 Payme_QR_ESP32
**Payme Payment Notifications**

Real-time notifications from Payme system via MQTT.

| Component | Function |
|-----------|----------|
| ESP32 | Controller + WiFi |
| LED | Payment indicator |

**Features:** MQTT (HiveMQ), JSON parsing, Payme integration

```
Architecture: Payme → Server → MQTT → ESP32
```

---

### 🌍 Wireless_Soil_Sensor_Gateway
**Multi-Sensor Soil Monitoring**

Professional soil analysis with METER GS3 SDI-12 sensors.

| Component | Function |
|-----------|----------|
| ESP32-S3 | Controller |
| METER GS3 (4x) | Soil sensors |

**Features:** Moisture/temperature/EC measurement, Deep Sleep (1 hour), 10μA sleep mode

---

## 🛠️ Installation

### Arduino IDE
1. Download [Arduino IDE](https://www.arduino.cc/en/software)
2. Add ESP board URLs (`File` → `Preferences` → `Additional Board URLs`):
```
https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
https://arduino.esp8266.com/stable/package_esp8266com_index.json
```
3. Install required libraries

### PlatformIO
1. Install [VS Code](https://code.visualstudio.com/) + [PlatformIO](https://platformio.org/)
2. Open project folder

---

## 📚 Libraries

| Library | Purpose |
|---------|---------|
| WiFi / ESP8266WiFi | WiFi connection |
| Blynk | IoT platform |
| LVGL | Graphics UI |
| TFT_eSPI | TFT displays |
| DHT | Temperature sensor |
| PubSubClient | MQTT |
| SDI12 | SDI-12 protocol |
| ArduinoJson | JSON |

---

# 🇷🇺 Русский

## 📋 Список проектов

| # | Проект | Описание | Платформа |
|---|--------|----------|-----------|
| 1 | [Bio_Master](./Bio_Master) | 🌱 Умное сельское хозяйство | Arduino UNO + ESP8266 |
| 2 | [ESP32bot](./ESP32bot) | 📦 Мониторинг контейнеров | ESP32 |
| 3 | [ESP32_LVGL_BLE_Panel](./ESP32_LVGL_BLE_Panel) | 📱 BLE сенсорная панель | ESP32 |
| 4 | [ESP32_TFT_display_temperature_output](./ESP32_TFT_display_temperature_output) | 🌡️ Дисплей температуры | ESP32 |
| 5 | [esp32s3-lvgl-dht-panel](./esp32s3-lvgl-dht-panel) | 🎨 LVGL климат-панель | ESP32-S3 |
| 6 | [Payme_QR_ESP32](./Payme_QR_ESP32) | 💳 Уведомления об оплате | ESP32 |
| 7 | [Wireless_Soil_Sensor_Gateway](./Wireless_Soil_Sensor_Gateway) | 🌍 Датчики почвы | ESP32-S3 |

---

### 🌱 Bio_Master
**Система автоматизации умного сельского хозяйства**

Дистанционное управление поливом и освещением через платформу Blynk IoT.

| Компонент | Функция |
|-----------|---------|
| DHT11 | Температура и влажность |
| Датчик почвы | Влажность почвы |
| LDR | Уровень освещённости |
| LCD 16x2 I2C | Отображение данных |
| 4-канальное реле | Управление устройствами |
| Rotary Encoder | Навигация по меню |

**Особенности:** 10 режимов культур, автополив, WiFi Captive Portal

```
WiFi: "Bio Master" / Пароль: "samurai2023"
```

---

### 📦 ESP32bot
**IoT мониторинг заполненности контейнеров**

Определение уровня заполнения контейнера с помощью ультразвукового датчика HC-SR04.

| Компонент | Функция |
|-----------|---------|
| ESP32 | Основной контроллер |
| HC-SR04 | Измерение расстояния |

**Особенности:** Уровень 0-100%, HTTPS JSON API, веб-настройка

```
AP: "ESP32-Config" → 192.168.4.1
```

---

### 📱 ESP32_LVGL_BLE_Panel
**Сенсорная панель с управлением по BLE**

Профессиональный интерфейс с дисплеем ILI9488 и графикой LVGL.

| Компонент | Функция |
|-----------|---------|
| ESP32 | Контроллер + BLE |
| ILI9488 | TFT дисплей 320x480 |

**Особенности:** LVGL v8 UI, BLE команды ("ON"/"OFF"), дизайн SquareLine Studio

---

### 🌡️ ESP32_TFT_display_temperature_output
**Анимированный дисплей температуры**

Красивая визуализация данных DHT11 на экране ST7735.

| Компонент | Функция |
|-----------|---------|
| ESP32 | Контроллер |
| ST7735 | TFT дисплей 128x160 |
| DHT11 | Датчик температуры |

**Особенности:** Анимация термометра, sparkline график, обновление каждые 2 сек

---

### 🎨 esp32s3-lvgl-dht-panel
**Современная LVGL климат-панель**

Профессиональный UI дизайн на ESP32-S3 и LVGL.

| Компонент | Функция |
|-----------|---------|
| ESP32-S3 | Контроллер |
| ILI9488 | TFT дисплей 320x480 |
| DHT11 | Температура/влажность |

**Особенности:** Анимированные arc-индикаторы, SquareLine Studio 1.5.3, анимации 500мс

---

### 💳 Payme_QR_ESP32
**Уведомления об оплате Payme**

Уведомления в реальном времени из системы Payme через MQTT.

| Компонент | Функция |
|-----------|---------|
| ESP32 | Контроллер + WiFi |
| LED | Индикатор оплаты |

**Особенности:** MQTT (HiveMQ), парсинг JSON, интеграция с Payme

```
Архитектура: Payme → Сервер → MQTT → ESP32
```

---

### 🌍 Wireless_Soil_Sensor_Gateway
**Многосенсорный мониторинг почвы**

Профессиональный анализ почвы с датчиками METER GS3 SDI-12.

| Компонент | Функция |
|-----------|---------|
| ESP32-S3 | Контроллер |
| METER GS3 (4x) | Датчики почвы |

**Особенности:** Измерение влажности/температуры/EC, Deep Sleep (1 час), 10μA в спящем режиме

---

## 🛠️ Установка

### Arduino IDE
1. Скачайте [Arduino IDE](https://www.arduino.cc/en/software)
2. Добавьте URL плат ESP (`File` → `Preferences` → `Additional Board URLs`):
```
https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
https://arduino.esp8266.com/stable/package_esp8266com_index.json
```
3. Установите необходимые библиотеки

### PlatformIO
1. Установите [VS Code](https://code.visualstudio.com/) + [PlatformIO](https://platformio.org/)
2. Откройте папку проекта

---

## 📚 Библиотеки

| Библиотека | Назначение |
|------------|------------|
| WiFi / ESP8266WiFi | WiFi подключение |
| Blynk | IoT платформа |
| LVGL | Графический UI |
| TFT_eSPI | TFT дисплеи |
| DHT | Датчик температуры |
| PubSubClient | MQTT |
| SDI12 | Протокол SDI-12 |
| ArduinoJson | JSON |

---

## 📁 Структура репозитория

```
Esp_Projects/
├── Bio_Master/                 # Умное сельское хозяйство
├── ESP32bot/                   # Мониторинг контейнеров
├── ESP32_LVGL_BLE_Panel/       # BLE сенсорная панель
├── ESP32_TFT_display_.../      # Дисплей температуры
├── esp32s3-lvgl-dht-panel/     # LVGL климат-панель
├── Payme_QR_ESP32/             # Уведомления об оплате
├── Wireless_Soil_Sensor_.../   # Датчики почвы
└── README.md
```

---

## 📄 Лицензия | License | Лицензия

MIT License

---

## 👤 Муаллиф | Author | Автор

**myseringan**

[![GitHub](https://img.shields.io/badge/GitHub-myseringan-181717?style=flat&logo=github)](https://github.com/myseringan)
