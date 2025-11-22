# ESP32 TFT Temperature Monitor 🌡️

![ESP32](https://img.shields.io/badge/ESP32-TFT%20Display-red)
![DHT11](https://img.shields.io/badge/Sensor-DHT11-green)
![ST7735](https://img.shields.io/badge/Display-ST7735-blue)

## 🌍 Multi-language README
- [English](#english) | [Русский](#русский) | [O'zbek](#ozbek)

---

## English

### 🌡️ Real-time Temperature Monitoring with Animated Display

Advanced ESP32-based temperature monitoring system with ST7735 TFT display featuring smooth animations, real-time graphing, and professional visualization.

### ✨ Key Features

- **📊 Professional Visualization**
  - Large animated temperature display
  - Color-gradient thermometer
  - Real-time sparkline history graph
  - Smooth value transitions

- **🎨 Advanced Animations**
  - Sliding number transitions
  - Exponential smoothing
  - Easing functions for natural motion
  - 25 FPS refresh rate

- **📈 Data Logging**
  - Continuous temperature history
  - 88-point sparkline buffer
  - Min/max auto-scaling
  - Real-time graph updates

### 🛠 Technical Specifications

#### Hardware Components
- **Controller**: ESP32
- **Display**: ST7735 TFT (128x160)
- **Sensor**: DHT11 Temperature & Humidity
- **Communication**: SPI interface

#### Display Features
- **Resolution**: 128x160 pixels
- **Colors**: 16-bit RGB (65K colors)
- **Interface**: SPI
- **Refresh Rate**: 25 FPS

### 📦 Pin Configuration

```cpp
// TFT Display Pins
#define TFT_MOSI  26  // SDA
#define TFT_SCLK  27  // SCK  
#define TFT_MISO  19  // MISO
#define TFT_CS    13  // Chip Select
#define TFT_DC    12  // Data/Command
#define TFT_RST   14  // Reset

// Sensor Pin
#define DHTPIN    25  // DHT11 Data
```

### 🚀 Installation & Setup

#### 1. Library Dependencies
```cpp
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include "DHT.h"
```

#### 2. Hardware Connections
- Connect TFT display using SPI pins
- Connect DHT11 to GPIO 25
- Ensure proper 3.3V power supply

#### 3. Upload Code
- Select ESP32 board in Arduino IDE
- Install required libraries
- Upload the sketch

### 🎮 Display Sections

#### Main Temperature Display
- **Large numeric readout** with sliding animation
- **Smooth value transitions** with easing
- **Accent color highlighting**

#### Thermometer Graphic
- **Color gradient** from blue to red
- **Real-time level indication**
- **Text label with current value**

#### History Sparkline
- **88-sample buffer** for trend visualization
- **Auto-scaling** to min/max values
- **Real-time updates** every 2 seconds

### ⚙️ Configuration Options

#### Timing Parameters
```cpp
const unsigned long READ_INTERVAL = 2000;  // Sensor read interval
const unsigned int FRAME_MS = 300;         // Display refresh rate
const float SMOOTH_ALPHA = 0.08f;          // Value smoothing
```

#### Display Settings
- **Temperature range**: -10°C to 50°C
- **Graph history**: 88 samples
- **Animation duration**: 420ms

### 🔧 Customization

#### Color Scheme
```cpp
// Customize colors in setup()
colBg     = tft.color565(8,10,12);      // Background
colAccent = tft.color565(255,200,80);   // Accent color
colThermBg= tft.color565(40,40,45);     // Thermometer background
```

#### Animation Settings
- Adjust `NUMERIC_ANIM_MS` for animation speed
- Modify `SMOOTH_ALPHA` for smoothing intensity
- Change `FRAME_MS` for refresh rate

### 🐛 Troubleshooting

**Common Issues:**
- **No display**: Check SPI connections and power
- **Sensor errors**: Verify DHT11 wiring
- **Flickering**: Ensure stable power supply
- **Wrong colors**: Check TFT initialization

---

## Русский

### 🌡️ Мониторинг температуры с анимированным дисплеем

Продвинутая система мониторинга температуры на базе ESP32 с дисплеем ST7735, плавными анимациями и профессиональной визуализацией.

### ✨ Основные возможности

- **📊 Профессиональная визуализация**
  - Большой анимированный дисплей температуры
  - Термометр с цветовым градиентом
  - График истории в реальном времени
  - Плавные переходы значений

- **🎨 Продвинутая анимация**
  - Скользящие переходы чисел
  - Экспоненциальное сглаживание
  - Функции easing для естественного движения
  - Частота обновления 25 FPS

- **📈 Ведение истории данных**
  - Непрерывная история температуры
  - Буфер графика на 88 точек
  - Автоматическое масштабирование
  - Обновление графика в реальном времени

### 🛠 Технические характеристики

#### Аппаратные компоненты
- **Контроллер**: ESP32
- **Дисплей**: ST7735 TFT (128x160)
- **Датчик**: DHT11 (температура и влажность)
- **Интерфейс**: SPI

### 📦 Конфигурация пинов

```cpp
// Дисплей TFT
#define TFT_MOSI  26  // SDA
#define TFT_SCLK  27  // SCK  
#define TFT_MISO  19  // MISO
#define TFT_CS    13  // Chip Select
#define TFT_DC    12  // Data/Command
#define TFT_RST   14  // Reset

// Датчик
#define DHTPIN    25  // DHT11 Data
```

### 🚀 Использование

#### Секции дисплея
- **Основной дисплей температуры** - большие цифры с анимацией
- **Графический термометр** - цветной градиент
- **График истории** - тренд изменений температуры

---

## O'zbek

### 🌡️ Animatsiyali displey bilan haroratni kuzatish

ESP32 asosidagi ilg'or harorat kuzatish tizimi, ST7735 TFT displey, silliq animatsiyalar va professional vizualizatsiya.

### ✨ Asosiy xususiyatlar

- **📊 Professional vizualizatsiya**
  - Katta animatsiyali harorat displeyi
  - Rang gradientli termometr
  - Real vaqtda grafik tarix
  - Silliq qiymat o'tishlari

- **🎨 Ilg'or animatsiyalar**
  - Sirg'aluvchi raqam o'tishlari
  - Eksponensial silliqlash
  - Tabiiy harakat uchun easing funksiyalari
  - 25 FPS yangilash chastotasi

- **📈 Ma'lumotlar tarixi**
  - Doimiy harorat tarixi
  - 88 nuqtali grafik buferi
  - Avtomatik masshtablashtirish
  - Real vaqtda grafik yangilanishi

### 🛠 Texnik xususiyatlar

#### Uskuna komponentlari
- **Kontroller**: ESP32
- **Displey**: ST7735 TFT (128x160)
- **Senser**: DHT11 (harorat va namlik)
- **Interfeys**: SPI

### 📦 Pin konfiguratsiyasi

```cpp
// TFT Displey
#define TFT_MOSI  26  // SDA
#define TFT_SCLK  27  // SCK  
#define TFT_MISO  19  // MISO
#define TFT_CS    13  // Chip Select
#define TFT_DC    12  // Data/Command
#define TFT_RST   14  // Reset

// Senser
#define DHTPIN    25  // DHT11 Data
```

### 🚀 Foydalanish

#### Displey bo'limlari
- **Asosiy harorat displeyi** - animatsiyali katta raqamlar
- **Grafik termometr** - rangli gradient
- **Tarix grafigi** - harorat o'zgarishi trendi

---

## 👨‍💻 Author

**ESP32 TFT Display Projects**

## 📄 License

This project is open source. Feel free to use and modify for your needs.

---

<div align="center">

**🌡️ Professional Temperature Monitoring Made Simple! 🌡️**

</div>
