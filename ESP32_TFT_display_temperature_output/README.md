# 🌡️ ESP32 TFT Temperature Display

[![ESP32](https://img.shields.io/badge/ESP32-DevKit-red?logo=espressif)](https://www.espressif.com/)
[![ST7735](https://img.shields.io/badge/Display-ST7735_TFT-blue)](https://www.adafruit.com/product/358)
[![DHT11](https://img.shields.io/badge/Sensor-DHT11-green)](https://www.adafruit.com/product/386)
[![License](https://img.shields.io/badge/License-MIT-blue.svg)](LICENSE)

## 🌍 Languages / Tillar / Языки

- [O'zbek](#ozbek)
- [English](#english)
- [Русский](#русский)

---

## O'zbek

### 📖 Loyiha Haqida

**ESP32 TFT Temperature Display** — bu DHT11 sensori yordamida haroratni o'lchaydigan va ST7735 TFT displeyda chiroyli animatsiyali interfeysda ko'rsatadigan loyiha. Termometr ko'rinishi, sparkline grafigi va silliq raqamli animatsiyalar bilan jihozlangan.

### ✨ Imkoniyatlari

- 🌡️ **Harorat o'lchash** - DHT11 sensori bilan aniq o'lchash
- 📺 **TFT displey** - ST7735 128x160 piksel rangli ekran
- 📈 **Sparkline grafik** - harorat tarixini real vaqtda ko'rsatish
- 🎨 **Termometr vizualizatsiya** - gradient rangli to'ldirish
- ✨ **Silliq animatsiyalar** - raqamlarning siljish effekti
- 🔄 **Eksponensial silliqlashtirish** - tebranishlarni kamaytirish
- ⏱️ **2 soniyada yangilanish** - barqaror o'qishlar

### 🔧 Kerakli Komponentlar

| Komponent | Miqdor | Izoh |
|-----------|--------|------|
| ESP32 DevKit | 1 | Asosiy kontroler |
| ST7735 TFT 1.8" | 1 | 128x160 SPI displey |
| DHT11 | 1 | Harorat sensori |
| Breadboard | 1 | Prototiplash uchun |
| Jumper simlar | 10+ | Ulanish uchun |

### 📌 Ulanish Sxemasi

```
ESP32 DevKit          ST7735 TFT Display
─────────────         ──────────────────
GPIO 26 (MOSI) ──────► SDA
GPIO 27 (SCLK) ──────► SCK
GPIO 13 (CS)   ──────► CS
GPIO 12 (DC)   ──────► A0/DC
GPIO 14 (RST)  ──────► RST
3.3V           ──────► VCC
GND            ──────► GND

ESP32 DevKit          DHT11 Sensor
─────────────         ─────────────
GPIO 25        ──────► DATA
3.3V           ──────► VCC
GND            ──────► GND
```

### 📊 Pin Konfiguratsiyasi

| ESP32 Pin | Funksiya | Ulanish |
|-----------|----------|---------|
| GPIO 26 | TFT_MOSI | SDA (ma'lumot) |
| GPIO 27 | TFT_SCLK | SCK (soat) |
| GPIO 19 | TFT_MISO | MISO (ixtiyoriy) |
| GPIO 13 | TFT_CS | CS (tanlash) |
| GPIO 12 | TFT_DC | A0/DC (buyruq) |
| GPIO 14 | TFT_RST | RST (reset) |
| GPIO 25 | DHTPIN | DHT11 DATA |

### ⚙️ Konfiguratsiya

`ESP32_TFT_display_temperature_output.ino` faylida quyidagi parametrlarni o'zgartiring:

```cpp
// TFT pinlari (zarur bo'lsa o'zgartiring)
#define TFT_MOSI  26
#define TFT_SCLK  27
#define TFT_CS    13
#define TFT_DC    12
#define TFT_RST   14

// DHT11 pin
#define DHTPIN    25

// Animatsiya parametrlari
const unsigned long READ_INTERVAL = 2000;  // O'qish oralig'i (ms)
const unsigned int FRAME_MS = 300;          // Kadr tezligi
const float SMOOTH_ALPHA = 0.08f;           // Silliqlashtirish koeffitsienti
```

### 🎨 Interfeys Elementlari

| Element | Joylashuv | Tavsif |
|---------|-----------|--------|
| Sarlavha | Yuqori | "DHT11 Temp" yozuvi |
| Katta raqam | O'rta-o'ng | Animatsiyali harorat qiymati |
| Termometr | Chap | Gradient to'ldirilgan ustun |
| Sparkline | Pastki | Harorat tarixi grafigi |

### 🚀 O'rnatish

1. Arduino IDE ni oching
2. ESP32 platasini qo'shing (Boards Manager orqali)
3. Kerakli kutubxonalarni o'rnating:
   - `Adafruit GFX Library`
   - `Adafruit ST7735 and ST7789 Library`
   - `DHT sensor library`
4. Kodni yuklang va ESP32 ni dasturlang

### 📚 Kutubxonalar

```cpp
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include "DHT.h"
```

---

## English

### 📖 About

**ESP32 TFT Temperature Display** is a project that measures temperature using DHT11 sensor and displays it on ST7735 TFT display with beautiful animated interface. Features thermometer visualization, sparkline graph, and smooth numeric animations.

### ✨ Features

- 🌡️ **Temperature measurement** - accurate readings with DHT11 sensor
- 📺 **TFT display** - ST7735 128x160 pixel color screen
- 📈 **Sparkline graph** - real-time temperature history
- 🎨 **Thermometer visualization** - gradient-filled bar
- ✨ **Smooth animations** - sliding number effects
- 🔄 **Exponential smoothing** - reduces fluctuations
- ⏱️ **2-second updates** - stable readings

### 🔧 Required Components

| Component | Quantity | Notes |
|-----------|----------|-------|
| ESP32 DevKit | 1 | Main controller |
| ST7735 TFT 1.8" | 1 | 128x160 SPI display |
| DHT11 | 1 | Temperature sensor |
| Breadboard | 1 | For prototyping |
| Jumper wires | 10+ | For connections |

### 📌 Wiring Diagram

```
ESP32 DevKit          ST7735 TFT Display
─────────────         ──────────────────
GPIO 26 (MOSI) ──────► SDA
GPIO 27 (SCLK) ──────► SCK
GPIO 13 (CS)   ──────► CS
GPIO 12 (DC)   ──────► A0/DC
GPIO 14 (RST)  ──────► RST
3.3V           ──────► VCC
GND            ──────► GND

ESP32 DevKit          DHT11 Sensor
─────────────         ─────────────
GPIO 25        ──────► DATA
3.3V           ──────► VCC
GND            ──────► GND
```

### 📊 Pin Configuration

| ESP32 Pin | Function | Connection |
|-----------|----------|------------|
| GPIO 26 | TFT_MOSI | SDA (data) |
| GPIO 27 | TFT_SCLK | SCK (clock) |
| GPIO 19 | TFT_MISO | MISO (optional) |
| GPIO 13 | TFT_CS | CS (chip select) |
| GPIO 12 | TFT_DC | A0/DC (command) |
| GPIO 14 | TFT_RST | RST (reset) |
| GPIO 25 | DHTPIN | DHT11 DATA |

### ⚙️ Configuration

Modify following parameters in `ESP32_TFT_display_temperature_output.ino`:

```cpp
// TFT pins (change if needed)
#define TFT_MOSI  26
#define TFT_SCLK  27
#define TFT_CS    13
#define TFT_DC    12
#define TFT_RST   14

// DHT11 pin
#define DHTPIN    25

// Animation parameters
const unsigned long READ_INTERVAL = 2000;  // Read interval (ms)
const unsigned int FRAME_MS = 300;          // Frame rate
const float SMOOTH_ALPHA = 0.08f;           // Smoothing coefficient
```

### 🎨 Interface Elements

| Element | Position | Description |
|---------|----------|-------------|
| Title | Top | "DHT11 Temp" text |
| Large number | Center-right | Animated temperature value |
| Thermometer | Left | Gradient-filled column |
| Sparkline | Bottom | Temperature history graph |

### 🚀 Installation

1. Open Arduino IDE
2. Add ESP32 board (via Boards Manager)
3. Install required libraries:
   - `Adafruit GFX Library`
   - `Adafruit ST7735 and ST7789 Library`
   - `DHT sensor library`
4. Upload code and program ESP32

### 📚 Libraries

```cpp
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include "DHT.h"
```

### 🎯 Technical Details

The display features several advanced visualization techniques:

**Temperature Range:** -10°C to 50°C (configurable)

**Smoothing Algorithm:** Exponential moving average with alpha = 0.08

**Animation:** Cubic easing for smooth number transitions

**Color Scheme:**
- Background: Dark (RGB: 8,10,12)
- Accent: Warm orange (RGB: 255,200,80)
- Thermometer gradient: Blue (cold) → Red (hot)
- Sparkline: Green (RGB: 100,255,120)

---

## Русский

### 📖 О проекте

**ESP32 TFT Temperature Display** — это проект для измерения температуры с помощью датчика DHT11 и отображения на дисплее ST7735 TFT с красивым анимированным интерфейсом. Включает визуализацию термометра, sparkline-график и плавные числовые анимации.

### ✨ Возможности

- 🌡️ **Измерение температуры** - точные показания с датчиком DHT11
- 📺 **TFT дисплей** - ST7735 128x160 пикселей цветной экран
- 📈 **Sparkline график** - история температуры в реальном времени
- 🎨 **Визуализация термометра** - столбик с градиентной заливкой
- ✨ **Плавные анимации** - эффект скольжения цифр
- 🔄 **Экспоненциальное сглаживание** - уменьшает колебания
- ⏱️ **Обновление каждые 2 сек** - стабильные показания

### 🔧 Необходимые компоненты

| Компонент | Кол-во | Примечание |
|-----------|--------|------------|
| ESP32 DevKit | 1 | Основной контроллер |
| ST7735 TFT 1.8" | 1 | 128x160 SPI дисплей |
| DHT11 | 1 | Датчик температуры |
| Макетная плата | 1 | Для прототипирования |
| Провода | 10+ | Для подключения |

### 📌 Схема подключения

```
ESP32 DevKit          ST7735 TFT Дисплей
─────────────         ──────────────────
GPIO 26 (MOSI) ──────► SDA
GPIO 27 (SCLK) ──────► SCK
GPIO 13 (CS)   ──────► CS
GPIO 12 (DC)   ──────► A0/DC
GPIO 14 (RST)  ──────► RST
3.3V           ──────► VCC
GND            ──────► GND

ESP32 DevKit          DHT11 Датчик
─────────────         ─────────────
GPIO 25        ──────► DATA
3.3V           ──────► VCC
GND            ──────► GND
```

### 📊 Конфигурация пинов

| Пин ESP32 | Функция | Подключение |
|-----------|---------|-------------|
| GPIO 26 | TFT_MOSI | SDA (данные) |
| GPIO 27 | TFT_SCLK | SCK (тактирование) |
| GPIO 19 | TFT_MISO | MISO (опционально) |
| GPIO 13 | TFT_CS | CS (выбор чипа) |
| GPIO 12 | TFT_DC | A0/DC (команда) |
| GPIO 14 | TFT_RST | RST (сброс) |
| GPIO 25 | DHTPIN | DHT11 DATA |

### ⚙️ Конфигурация

Измените следующие параметры в `ESP32_TFT_display_temperature_output.ino`:

```cpp
// Пины TFT (измените при необходимости)
#define TFT_MOSI  26
#define TFT_SCLK  27
#define TFT_CS    13
#define TFT_DC    12
#define TFT_RST   14

// Пин DHT11
#define DHTPIN    25

// Параметры анимации
const unsigned long READ_INTERVAL = 2000;  // Интервал чтения (мс)
const unsigned int FRAME_MS = 300;          // Частота кадров
const float SMOOTH_ALPHA = 0.08f;           // Коэффициент сглаживания
```

### 🎨 Элементы интерфейса

| Элемент | Позиция | Описание |
|---------|---------|----------|
| Заголовок | Верх | Надпись "DHT11 Temp" |
| Крупное число | Центр-справа | Анимированное значение температуры |
| Термометр | Слева | Столбик с градиентной заливкой |
| Sparkline | Низ | График истории температуры |

### 🚀 Установка

1. Откройте Arduino IDE
2. Добавьте плату ESP32 (через Boards Manager)
3. Установите необходимые библиотеки:
   - `Adafruit GFX Library`
   - `Adafruit ST7735 and ST7789 Library`
   - `DHT sensor library`
4. Загрузите код и прошейте ESP32

### 📚 Библиотеки

```cpp
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include "DHT.h"
```

### 🎯 Технические детали

**Диапазон температур:** от -10°C до 50°C (настраивается)

**Алгоритм сглаживания:** Экспоненциальное скользящее среднее с alpha = 0.08

**Анимация:** Кубическое сглаживание для плавных переходов цифр

**Цветовая схема:**
- Фон: Тёмный (RGB: 8,10,12)
- Акцент: Тёплый оранжевый (RGB: 255,200,80)
- Градиент термометра: Синий (холодно) → Красный (горячо)
- Sparkline: Зелёный (RGB: 100,255,120)

---

## 📁 Project Structure / Loyiha Tuzilishi / Структура проекта

```
ESP32_TFT_display_temperature_output/
├── ESP32_TFT_display_temperature_output.ino  # Main code / Asosiy kod
└── README.md                                  # This file / Ushbu fayl
```

---

## 📄 License / Litsenziya / Лицензия

MIT License - See [LICENSE](LICENSE) file for details.

---

## 👤 Author / Muallif / Автор

**myseringan**

- GitHub: [@myseringan](https://github.com/myseringan)
