# 📱 ESP32 LVGL BLE Panel

[![ESP32](https://img.shields.io/badge/ESP32-DevKit-red?logo=espressif)](https://www.espressif.com/)
[![LVGL](https://img.shields.io/badge/LVGL-v8-pink)](https://lvgl.io/)
[![BLE](https://img.shields.io/badge/BLE-Bluetooth-blue)](https://www.bluetooth.com/)
[![PlatformIO](https://img.shields.io/badge/PlatformIO-IDE-orange)](https://platformio.org/)
[![License](https://img.shields.io/badge/License-MIT-blue.svg)](LICENSE)

## 🌍 Languages / Tillar / Языки

- [O'zbek](#ozbek)
- [English](#english)
- [Русский](#русский)

---

## O'zbek

### 📖 Loyiha Haqida

**ESP32 LVGL BLE Panel** — bu TFT displey va Bluetooth Low Energy (BLE) asosida ishlaydigan boshqaruv paneli. LVGL kutubxonasi yordamida chiroyli grafik interfeys yaratilgan bo'lib, BLE orqali telefondan boshqarish mumkin.

### ✨ Imkoniyatlari

- 🖥️ **LVGL grafik interfeys** - professional UI dizayni
- 📶 **BLE boshqaruv** - Bluetooth orqali buyruqlar
- 🔌 **Ulanish holati** - vizual ko'rsatkich
- 💡 **ON/OFF boshqaruv** - qurilmani yoqish/o'chirish
- 🎨 **SquareLine Studio** - UI dizayni uchun
- ⚡ **Real-time yangilanish** - tezkor interfeys

### 🔧 Kerakli Komponentlar

| Komponent | Miqdor | Izoh |
|-----------|--------|------|
| ESP32 DevKit | 1 | BLE qo'llab-quvvatlaydigan |
| ILI9488 TFT Displey | 1 | 320x480, SPI |
| Jumper simlar | 10+ | Ulanish uchun |

### 📌 TFT Displey Ulanishi

```
ILI9488 TFT → ESP32:
  - VCC → 3.3V
  - GND → GND
  - CS → GPIO 15
  - RESET → GPIO 4
  - DC → GPIO 2
  - SDI(MOSI) → GPIO 23
  - SCK → GPIO 18
  - LED → 3.3V
  - SDO(MISO) → GPIO 19
```

### 📱 BLE Konfiguratsiyasi

```cpp
// ble_service.h da o'zgartiring:
#define DEVICE_NAME "ESP32_Panel"
#define SERVICE_UUID "12345678-1234-1234-1234-123456789abc"
#define CHARACTERISTIC_UUID "abcd1234-ab12-cd34-ef56-123456789abc"
```

### 📡 BLE Buyruqlari

| Buyruq | Ta'siri |
|--------|---------|
| `ON` | Qurilmani yoqadi |
| `OFF` | Qurilmani o'chiradi |

### 🚀 O'rnatish (PlatformIO)

1. PlatformIO ni o'rnating
2. Loyihani oching
3. `platformio.ini` da kutubxonalarni tekshiring:
   ```ini
   [env:esp32dev]
   platform = espressif32
   board = esp32dev
   framework = arduino
   lib_deps = 
       lvgl/lvgl@^8.3.0
       bodmer/TFT_eSPI@^2.5.0
   ```
4. `User_Setup.h` da TFT sozlamalarini sozlang
5. SquareLine Studio dan UI fayllarni eksport qiling
6. Loyihani yuklang

### 🎨 UI Dizayni

UI SquareLine Studio da yaratilgan:
- `ui.h` - UI deklaratsiyalari
- `ui.c` - UI implementatsiyasi
- `ui_img_*.c` - Rasmlar

---

## English

### 📖 About

**ESP32 LVGL BLE Panel** is a control panel based on TFT display and Bluetooth Low Energy (BLE). It features a beautiful graphical interface created with LVGL library and can be controlled via phone over BLE.

### ✨ Features

- 🖥️ **LVGL graphical interface** - professional UI design
- 📶 **BLE control** - commands via Bluetooth
- 🔌 **Connection status** - visual indicator
- 💡 **ON/OFF control** - device power control
- 🎨 **SquareLine Studio** - for UI design
- ⚡ **Real-time updates** - responsive interface

### 🔧 Required Components

| Component | Qty | Description |
|-----------|-----|-------------|
| ESP32 DevKit | 1 | With BLE support |
| ILI9488 TFT Display | 1 | 320x480, SPI |
| Jumper wires | 10+ | For connections |

### 📌 TFT Display Wiring

```
ILI9488 TFT → ESP32:
  - VCC → 3.3V
  - GND → GND
  - CS → GPIO 15
  - RESET → GPIO 4
  - DC → GPIO 2
  - SDI(MOSI) → GPIO 23
  - SCK → GPIO 18
  - LED → 3.3V
  - SDO(MISO) → GPIO 19
```

### 📱 BLE Configuration

```cpp
// Modify in ble_service.h:
#define DEVICE_NAME "ESP32_Panel"
#define SERVICE_UUID "12345678-1234-1234-1234-123456789abc"
#define CHARACTERISTIC_UUID "abcd1234-ab12-cd34-ef56-123456789abc"
```

### 📡 BLE Commands

| Command | Effect |
|---------|--------|
| `ON` | Turns device on |
| `OFF` | Turns device off |

### 🚀 Installation (PlatformIO)

1. Install PlatformIO
2. Open project
3. Check libraries in `platformio.ini`:
   ```ini
   [env:esp32dev]
   platform = espressif32
   board = esp32dev
   framework = arduino
   lib_deps = 
       lvgl/lvgl@^8.3.0
       bodmer/TFT_eSPI@^2.5.0
   ```
4. Configure TFT settings in `User_Setup.h`
5. Export UI files from SquareLine Studio
6. Upload project

### 🎨 UI Design

UI created in SquareLine Studio:
- `ui.h` - UI declarations
- `ui.c` - UI implementation
- `ui_img_*.c` - Images

---

## Русский

### 📖 О проекте

**ESP32 LVGL BLE Panel** — это панель управления на базе TFT дисплея и Bluetooth Low Energy (BLE). Красивый графический интерфейс создан с помощью библиотеки LVGL, управление возможно с телефона через BLE.

### ✨ Возможности

- 🖥️ **Графический интерфейс LVGL** - профессиональный UI дизайн
- 📶 **Управление по BLE** - команды через Bluetooth
- 🔌 **Статус подключения** - визуальный индикатор
- 💡 **Управление ON/OFF** - включение/выключение устройства
- 🎨 **SquareLine Studio** - для дизайна UI
- ⚡ **Обновление в реальном времени** - отзывчивый интерфейс

### 🔧 Необходимые компоненты

| Компонент | Кол-во | Описание |
|-----------|--------|----------|
| ESP32 DevKit | 1 | С поддержкой BLE |
| ILI9488 TFT Дисплей | 1 | 320x480, SPI |
| Перемычки | 10+ | Для подключения |

### 📌 Подключение TFT дисплея

```
ILI9488 TFT → ESP32:
  - VCC → 3.3V
  - GND → GND
  - CS → GPIO 15
  - RESET → GPIO 4
  - DC → GPIO 2
  - SDI(MOSI) → GPIO 23
  - SCK → GPIO 18
  - LED → 3.3V
  - SDO(MISO) → GPIO 19
```

### 📱 Конфигурация BLE

```cpp
// Измените в ble_service.h:
#define DEVICE_NAME "ESP32_Panel"
#define SERVICE_UUID "12345678-1234-1234-1234-123456789abc"
#define CHARACTERISTIC_UUID "abcd1234-ab12-cd34-ef56-123456789abc"
```

### 📡 BLE Команды

| Команда | Действие |
|---------|----------|
| `ON` | Включает устройство |
| `OFF` | Выключает устройство |

### 🚀 Установка (PlatformIO)

1. Установите PlatformIO
2. Откройте проект
3. Проверьте библиотеки в `platformio.ini`:
   ```ini
   [env:esp32dev]
   platform = espressif32
   board = esp32dev
   framework = arduino
   lib_deps = 
       lvgl/lvgl@^8.3.0
       bodmer/TFT_eSPI@^2.5.0
   ```
4. Настройте TFT в `User_Setup.h`
5. Экспортируйте UI файлы из SquareLine Studio
6. Загрузите проект

### 🎨 UI Дизайн

UI создан в SquareLine Studio:
- `ui.h` - объявления UI
- `ui.c` - реализация UI
- `ui_img_*.c` - изображения

---

## 📁 Project Structure / Fayl Tuzilishi / Структура проекта

```
ESP32_LVGL_BLE_Panel/
├── src/
│   ├── main.cpp           # Main application
│   ├── ble_service.cpp    # BLE server implementation
│   ├── ble_service.h      # BLE definitions
│   ├── tft_draw.cpp       # TFT flush callback
│   └── tft_draw.h         # TFT definitions
├── ui/                    # SquareLine Studio export
│   ├── ui.h
│   ├── ui.c
│   └── ui_img_*.c
├── lib/
│   └── TFT_eSPI/
│       └── User_Setup.h   # TFT configuration
└── platformio.ini         # PlatformIO config
```

## 📱 Mobile App / Mobil Ilova / Мобильное приложение

BLE boshqarish uchun quyidagi ilovalardan foydalanish mumkin:
- **nRF Connect** (Android/iOS)
- **LightBlue** (iOS)
- **BLE Scanner** (Android)

### Ulanish tartibi:
1. Ilovani oching
2. "ESP32_Panel" qurilmasini toping
3. Ulanish tugmasini bosing
4. Characteristic ga "ON" yoki "OFF" yozing

## 🔌 Display States / Displey Holatlari / Состояния дисплея

| Holat | Ko'rinish |
|-------|-----------|
| Disconnected | Image2 ko'rinadi, "Disconnect" yozuvi |
| Connected | Image1 ko'rinadi, "Connect" yozuvi |
| ON | Image3 ko'rinadi (yashil) |
| OFF | Image4 ko'rinadi (qizil) |

## 📄 License

MIT License - Feel free to use and modify

## 👨‍💻 Author

**Temur Eshmurodov**

---

⭐ **Star this repository if you find it useful!**
