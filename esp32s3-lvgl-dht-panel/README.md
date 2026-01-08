# 🌡️ ESP32-S3 LVGL DHT Panel

[![ESP32-S3](https://img.shields.io/badge/ESP32--S3-DevKit-red?logo=espressif)](https://www.espressif.com/)
[![LVGL](https://img.shields.io/badge/LVGL-v8.3-purple)](https://lvgl.io/)
[![DHT11](https://img.shields.io/badge/Sensor-DHT11-green)](https://www.adafruit.com/product/386)
[![SquareLine](https://img.shields.io/badge/UI-SquareLine_Studio-orange)](https://squareline.io/)
[![License](https://img.shields.io/badge/License-MIT-blue.svg)](LICENSE)

## 🌍 Languages / Tillar / Языки

- [O'zbek](#ozbek)
- [English](#english)
- [Русский](#русский)

---

## O'zbek

### 📖 Loyiha Haqida

**ESP32-S3 LVGL DHT Panel** — bu DHT11 sensori yordamida harorat va namlikni o'lchaydigan va LVGL kutubxonasi bilan yaratilgan zamonaviy UI panelda ko'rsatadigan loyiha. UI SquareLine Studio da ishlab chiqilgan bo'lib, animatsiyali arc (yoy) indikatorlari va raqamli ko'rsatkichlarni o'z ichiga oladi.

### ✨ Imkoniyatlari

- 🌡️ **Harorat o'lchash** - DHT11 sensori bilan aniq o'lchash
- 💧 **Namlik o'lchash** - foiz ko'rsatkichida
- 📺 **320x480 TFT displey** - ILI9488 yoki shunga o'xshash
- 🎨 **LVGL UI** - professional grafik interfeys
- 🔄 **Animatsiyali arc'lar** - silliq harakat effektlari
- 📊 **Real vaqt yangilanish** - har 2 soniyada
- 🎯 **SquareLine Studio** - UI dizayn vositasi

### 🔧 Kerakli Komponentlar

| Komponent | Miqdor | Izoh |
|-----------|--------|------|
| ESP32-S3 DevKit | 1 | Asosiy kontroler |
| ILI9488 TFT 3.5" | 1 | 320x480 SPI displey |
| DHT11 | 1 | Harorat/namlik sensori |
| Breadboard | 1 | Prototiplash uchun |
| Jumper simlar | 10+ | Ulanish uchun |

### 📌 Ulanish Sxemasi

```
ESP32-S3 DevKit       ILI9488 TFT Display
───────────────       ───────────────────
(TFT_eSPI config)     SPI interfeysi

ESP32-S3 DevKit       DHT11 Sensor
───────────────       ─────────────
GPIO 22        ──────► DATA
3.3V           ──────► VCC
GND            ──────► GND
```

### 📊 Pin Konfiguratsiyasi

| ESP32-S3 Pin | Funksiya | Ulanish |
|--------------|----------|---------|
| GPIO 22 | DHTPIN | DHT11 DATA |
| TFT_eSPI | SPI | Displey (config faylida) |

**Eslatma:** TFT pinlari `TFT_eSPI` kutubxonasining `User_Setup.h` faylida sozlanadi.

### ⚙️ Konfiguratsiya

`esp32s3-lvgl-dht-panel.ino` faylida quyidagi parametrlarni o'zgartiring:

```cpp
#define DHTPIN 22        // DHT11 data pin
#define DHTTYPE DHT11    // Sensor turi

// Displey sozlamalari
disp_drv.hor_res = 320;  // Gorizontal o'lcham
disp_drv.ver_res = 480;  // Vertikal o'lcham
```

### 🎨 UI Elementlari

UI SquareLine Studio 1.5.3 da yaratilgan va quyidagi elementlarni o'z ichiga oladi:

| Element | Turi | Funksiya |
|---------|------|----------|
| ui_Screen1 | Screen | Asosiy ekran |
| ui_Arc3 | Arc | Harorat indikatori (0-100) |
| ui_Arc4 | Arc | Namlik indikatori (0-100) |
| ui_Label2 | Label | Harorat qiymati (°C) |
| ui_Label3 | Label | Namlik qiymati (%) |

### 🚀 O'rnatish

1. Arduino IDE ni oching
2. ESP32-S3 platasini qo'shing (Boards Manager orqali)
3. Kerakli kutubxonalarni o'rnating:
   - `LVGL` (v8.3.11)
   - `TFT_eSPI`
   - `DHT sensor library`
4. `TFT_eSPI` kutubxonasida `User_Setup.h` ni sozlang
5. UI fayllarini loyihaga qo'shing
6. Kodni yuklang va ESP32-S3 ni dasturlang

### 📚 Kutubxonalar

```cpp
#define LV_CONF_INCLUDE_SIMPLE 1
#include <lvgl.h>
#include "ui.h"
#include "DHT.h"
#include "TFT_eSPI.h"
```

### 📁 Loyiha Fayllari

```
esp32s3-lvgl-dht-panel/
├── esp32s3-lvgl-dht-panel.ino  # Asosiy kod
├── ui.h                         # UI sarlavha fayli
├── ui.c                         # UI boshlang'ich kodi
├── ui_helpers.h                 # UI yordamchi funksiyalar
├── ui_helpers.c                 # UI yordamchi implementatsiya
├── ui_comp.h                    # UI komponentlar
├── ui_comp_hook.h               # UI hook'lar
├── ui_events.h                  # UI hodisalar
├── ui_Screen1.h                 # Ekran sarlavhasi
├── ui_Screen1.c                 # Ekran implementatsiyasi
└── assets/                      # Rasm resurslari
    ├── guage (2).png           # Arc fon rasmi
    └── guage (3).png           # Arc fon rasmi
```

---

## English

### 📖 About

**ESP32-S3 LVGL DHT Panel** is a project that measures temperature and humidity using DHT11 sensor and displays them on a modern UI panel created with LVGL library. The UI is designed in SquareLine Studio and includes animated arc indicators and numeric displays.

### ✨ Features

- 🌡️ **Temperature measurement** - accurate readings with DHT11 sensor
- 💧 **Humidity measurement** - percentage display
- 📺 **320x480 TFT display** - ILI9488 or similar
- 🎨 **LVGL UI** - professional graphical interface
- 🔄 **Animated arcs** - smooth motion effects
- 📊 **Real-time updates** - every 2 seconds
- 🎯 **SquareLine Studio** - UI design tool

### 🔧 Required Components

| Component | Quantity | Notes |
|-----------|----------|-------|
| ESP32-S3 DevKit | 1 | Main controller |
| ILI9488 TFT 3.5" | 1 | 320x480 SPI display |
| DHT11 | 1 | Temperature/humidity sensor |
| Breadboard | 1 | For prototyping |
| Jumper wires | 10+ | For connections |

### 📌 Wiring Diagram

```
ESP32-S3 DevKit       ILI9488 TFT Display
───────────────       ───────────────────
(TFT_eSPI config)     SPI interface

ESP32-S3 DevKit       DHT11 Sensor
───────────────       ─────────────
GPIO 22        ──────► DATA
3.3V           ──────► VCC
GND            ──────► GND
```

### 📊 Pin Configuration

| ESP32-S3 Pin | Function | Connection |
|--------------|----------|------------|
| GPIO 22 | DHTPIN | DHT11 DATA |
| TFT_eSPI | SPI | Display (in config file) |

**Note:** TFT pins are configured in `TFT_eSPI` library's `User_Setup.h` file.

### ⚙️ Configuration

Modify following parameters in `esp32s3-lvgl-dht-panel.ino`:

```cpp
#define DHTPIN 22        // DHT11 data pin
#define DHTTYPE DHT11    // Sensor type

// Display settings
disp_drv.hor_res = 320;  // Horizontal resolution
disp_drv.ver_res = 480;  // Vertical resolution
```

### 🎨 UI Elements

UI created in SquareLine Studio 1.5.3 and includes the following elements:

| Element | Type | Function |
|---------|------|----------|
| ui_Screen1 | Screen | Main screen |
| ui_Arc3 | Arc | Temperature indicator (0-100) |
| ui_Arc4 | Arc | Humidity indicator (0-100) |
| ui_Label2 | Label | Temperature value (°C) |
| ui_Label3 | Label | Humidity value (%) |

### 🚀 Installation

1. Open Arduino IDE
2. Add ESP32-S3 board (via Boards Manager)
3. Install required libraries:
   - `LVGL` (v8.3.11)
   - `TFT_eSPI`
   - `DHT sensor library`
4. Configure `User_Setup.h` in `TFT_eSPI` library
5. Add UI files to project
6. Upload code and program ESP32-S3

### 📚 Libraries

```cpp
#define LV_CONF_INCLUDE_SIMPLE 1
#include <lvgl.h>
#include "ui.h"
#include "DHT.h"
#include "TFT_eSPI.h"
```

### 🎯 Technical Details

**LVGL Configuration:**
- Color depth: 16-bit
- Color swap: Disabled (LV_COLOR_16_SWAP = 0)
- Display buffer: 320 × 60 pixels

**Animation System:**
- Arc animations with 500ms duration
- Cubic easing for smooth transitions
- Tick increment for proper timing

**Sensor Reading:**
- 2-second interval between readings
- Integer rounding for display values
- NaN check for error handling

### 📝 SquareLine Studio Settings

The UI was generated with:
- SquareLine Studio version: 1.5.3
- LVGL version: 8.3.11
- Theme: Default (Blue/Red palette)
- Color depth: 16-bit

---

## Русский

### 📖 О проекте

**ESP32-S3 LVGL DHT Panel** — это проект для измерения температуры и влажности с помощью датчика DHT11 и отображения на современной UI-панели, созданной с помощью библиотеки LVGL. UI разработан в SquareLine Studio и включает анимированные дуговые индикаторы и числовые дисплеи.

### ✨ Возможности

- 🌡️ **Измерение температуры** - точные показания с датчиком DHT11
- 💧 **Измерение влажности** - отображение в процентах
- 📺 **320x480 TFT дисплей** - ILI9488 или аналогичный
- 🎨 **LVGL UI** - профессиональный графический интерфейс
- 🔄 **Анимированные дуги** - плавные эффекты движения
- 📊 **Обновление в реальном времени** - каждые 2 секунды
- 🎯 **SquareLine Studio** - инструмент дизайна UI

### 🔧 Необходимые компоненты

| Компонент | Кол-во | Примечание |
|-----------|--------|------------|
| ESP32-S3 DevKit | 1 | Основной контроллер |
| ILI9488 TFT 3.5" | 1 | 320x480 SPI дисплей |
| DHT11 | 1 | Датчик температуры/влажности |
| Макетная плата | 1 | Для прототипирования |
| Провода | 10+ | Для подключения |

### 📌 Схема подключения

```
ESP32-S3 DevKit       ILI9488 TFT Дисплей
───────────────       ───────────────────
(TFT_eSPI config)     SPI интерфейс

ESP32-S3 DevKit       DHT11 Датчик
───────────────       ─────────────
GPIO 22        ──────► DATA
3.3V           ──────► VCC
GND            ──────► GND
```

### 📊 Конфигурация пинов

| Пин ESP32-S3 | Функция | Подключение |
|--------------|---------|-------------|
| GPIO 22 | DHTPIN | DHT11 DATA |
| TFT_eSPI | SPI | Дисплей (в конфиг файле) |

**Примечание:** Пины TFT настраиваются в файле `User_Setup.h` библиотеки `TFT_eSPI`.

### ⚙️ Конфигурация

Измените следующие параметры в `esp32s3-lvgl-dht-panel.ino`:

```cpp
#define DHTPIN 22        // Пин данных DHT11
#define DHTTYPE DHT11    // Тип датчика

// Настройки дисплея
disp_drv.hor_res = 320;  // Горизонтальное разрешение
disp_drv.ver_res = 480;  // Вертикальное разрешение
```

### 🎨 Элементы UI

UI создан в SquareLine Studio 1.5.3 и включает следующие элементы:

| Элемент | Тип | Функция |
|---------|-----|---------|
| ui_Screen1 | Screen | Главный экран |
| ui_Arc3 | Arc | Индикатор температуры (0-100) |
| ui_Arc4 | Arc | Индикатор влажности (0-100) |
| ui_Label2 | Label | Значение температуры (°C) |
| ui_Label3 | Label | Значение влажности (%) |

### 🚀 Установка

1. Откройте Arduino IDE
2. Добавьте плату ESP32-S3 (через Boards Manager)
3. Установите необходимые библиотеки:
   - `LVGL` (v8.3.11)
   - `TFT_eSPI`
   - `DHT sensor library`
4. Настройте `User_Setup.h` в библиотеке `TFT_eSPI`
5. Добавьте UI файлы в проект
6. Загрузите код и прошейте ESP32-S3

### 📚 Библиотеки

```cpp
#define LV_CONF_INCLUDE_SIMPLE 1
#include <lvgl.h>
#include "ui.h"
#include "DHT.h"
#include "TFT_eSPI.h"
```

### 🎯 Технические детали

**Конфигурация LVGL:**
- Глубина цвета: 16 бит
- Обмен цветов: Отключён (LV_COLOR_16_SWAP = 0)
- Буфер дисплея: 320 × 60 пикселей

**Система анимации:**
- Анимация дуг длительностью 500мс
- Кубическое сглаживание для плавных переходов
- Инкремент тиков для правильной синхронизации

**Чтение датчика:**
- Интервал 2 секунды между чтениями
- Округление до целых для отображения
- Проверка NaN для обработки ошибок

---

## 📁 Project Structure / Loyiha Tuzilishi / Структура проекта

```
esp32s3-lvgl-dht-panel/
├── esp32s3-lvgl-dht-panel.ino  # Main code / Asosiy kod
├── ui.h                         # UI header file
├── ui.c                         # UI initialization
├── ui_helpers.h                 # UI helper functions
├── ui_helpers.c                 # UI helper implementation
├── ui_comp.h                    # UI components
├── ui_comp_hook.h               # UI hooks
├── ui_events.h                  # UI events
├── ui_Screen1.h                 # Screen header
├── ui_Screen1.c                 # Screen implementation
└── assets/                      # Image resources
    ├── guage (2).png           # Arc background image
    └── guage (3).png           # Arc background image
```

---

## 📄 License / Litsenziya / Лицензия

MIT License - See [LICENSE](LICENSE) file for details.

---

## 👤 Author / Muallif / Автор

**myseringan**

- GitHub: [@myseringan](https://github.com/myseringan)
