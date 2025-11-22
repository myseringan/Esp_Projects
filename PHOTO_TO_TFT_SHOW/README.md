
# ESP32 TFT QR Code Display 📱

![ESP32](https://img.shields.io/badge/ESP32-TFT%20Display-red)
![ST7735](https://img.shields.io/badge/Display-ST7735-blue)
![QR Code](https://img.shields.io/badge/Feature-QR%20Code-green)

## 🌍 Multi-language README
- [English](#english) | [Русский](#русский) | [O'zbek](#ozbek)

---

## English

### 📱 ESP32 TFT QR Code Display System

A compact ESP32-based system for displaying QR codes on ST7735 TFT displays. Perfect for payment systems, WiFi configuration, or information sharing applications.

### ✨ Key Features

- **🖥️ TFT Display Integration**
  - ST7735 128x160 resolution
  - SPI communication interface
  - Adafruit GFX library support
  - Black tab initialization

- **📱 QR Code Display**
  - Custom QR code rendering
  - Centered display positioning
  - RGB bitmap drawing
  - Program memory storage

- **⚡ Efficient Design**
  - PROGMEM data storage
  - Minimal memory footprint
  - Fast rendering
  - Stable operation

### 🛠 Technical Specifications

#### Hardware Components
- **Controller**: ESP32
- **Display**: ST7735 TFT (128x160)
- **Interface**: SPI
- **Resolution**: 128x160 pixels

#### Pin Configuration
```cpp
#define TFT_MOSI  26  // SDA/MOSI
#define TFT_SCLK  27  // SCK
#define TFT_CS    13  // Chip Select
#define TFT_DC    12  // Data/Command
#define TFT_RST   14  // Reset
```

### 🚀 Quick Start

#### 1. Hardware Connections
```cpp
// Connect your ST7735 TFT to ESP32:
// MOSI -> GPIO 26
// SCK  -> GPIO 27
// CS   -> GPIO 13
// DC   -> GPIO 12
// RST  -> GPIO 14
// VCC  -> 3.3V
// GND  -> GND
```

#### 2. Library Dependencies
```cpp
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <SPI.h>
```

#### 3. QR Code Generation
1. Prepare your QR code image (140x180 pixels recommended)
2. Use [FileToCArray Converter](https://notisrac.github.io/FileToCArray/)
3. Convert image to RGB565 C array
4. Replace the empty `qr_image_data` array

### 🔧 Configuration

#### Display Settings
```cpp
tft.initR(INITR_BLACKTAB);  // Display initialization
tft.setRotation(0);         // Screen orientation
tft.fillScreen(0x0000);     // Clear screen (black)
```

#### QR Code Positioning
```cpp
const int QR_WIDTH = 140;
const int QR_HEIGHT = 180;
const int start_x = (128 - 140) / 2;  // Center horizontally
const int start_y = (160 - 180) / 2;  // Center vertically
```

### 🎯 Usage Examples

#### Payment QR Codes
- Payme, Click, Uzumbile payment systems
- Static payment links
- Dynamic amount generation

#### WiFi Configuration
- WiFi credential sharing
- Network access codes
- Guest WiFi access

#### Information Sharing
- Contact information
- Website links
- Document access
- Event details

### 📊 Performance Notes

#### Memory Considerations
- QR code data stored in PROGMEM
- 140x180 RGB565 image = 50,400 bytes
- Adjust size based on available memory
- Consider compression for larger codes

#### Display Optimization
- Use appropriate QR code dimensions
- Consider screen aspect ratio
- Test visibility and scanability
- Optimize contrast levels

### 🔧 Customization

#### Different QR Code Sizes
```cpp
// For smaller QR code (100x100)
const int QR_WIDTH = 100;
const int QR_HEIGHT = 100;
const int start_x = (128 - 100) / 2;
const int start_y = (160 - 100) / 2;
```

#### Multiple QR Codes
```cpp
// Store multiple QR codes
const unsigned short qr_codes[][QR_SIZE] PROGMEM = {
    { /* QR Code 1 data */ },
    { /* QR Code 2 data */ },
    // Add more as needed
};

// Display function
void displayQRCode(int index) {
    tft.drawRGBBitmap(x, y, qr_codes[index], QR_WIDTH, QR_HEIGHT);
}
```

### 🐛 Troubleshooting

**Common Issues:**
- **Blank display**: Check SPI connections and power
- **Wrong colors**: Verify INITR_BLACKTAB compatibility
- **QR not scanning**: Ensure proper image dimensions
- **Memory issues**: Reduce QR code size or resolution

**Debug Steps:**
1. Verify all connections
2. Check power supply (3.3V)
3. Test with simple graphics first
4. Monitor serial output for errors

---

## Русский

### 📱 Система отображения QR-кодов на TFT дисплее ESP32

Компактная система на базе ESP32 для отображения QR-кодов на TFT дисплеях ST7735. Идеально для платежных систем, конфигурации WiFi или приложений обмена информацией.

### ✨ Основные возможности

- **🖥️ Интеграция TFT дисплея**
  - ST7735 разрешение 128x160
  - Интерфейс SPI связи
  - Поддержка библиотеки Adafruit GFX
  - Инициализация Black tab

- **📱 Отображение QR-кодов**
  - Кастомный рендеринг QR-кодов
  - Центрированное позиционирование
  - Отрисовка RGB bitmap
  - Хранение в памяти программ

### 📦 Конфигурация пинов

```cpp
#define TFT_MOSI  26  // SDA/MOSI
#define TFT_SCLK  27  // SCK
#define TFT_CS    13  // Chip Select
#define TFT_DC    12  // Data/Command
#define TFT_RST   14  // Reset
```

### 🚀 Использование

#### Генерация QR-кода
1. Подготовьте изображение QR-кода (рекомендуется 140x180 пикселей)
2. Используйте [FileToCArray Converter](https://notisrac.github.io/FileToCArray/)
3. Конвертируйте изображение в C массив RGB565
4. Замените пустой массив `qr_image_data`

---

## O'zbek

### 📱 ESP32 TFT QR Kod Displey Tizimi

ST7735 TFT displeylarida QR kodlarni ko'rsatish uchun ESP32 asosidagi ixcham tizim. To'lov tizimlari, WiFi sozlash yoki ma'lumot almashish ilovalari uchun ideal.

### ✨ Asosiy xususiyatlar

- **🖥️ TFT displey integratsiyasi**
  - ST7735 128x160 o'lchov
  - SPI aloqa interfeysi
  - Adafruit GFX kutubxonasi qo'llab-quvvatlash
  - Black tab ishga tushirish

- **📱 QR kodni ko'rsatish**
  - Maxsus QR kod renderlash
  - Markazlashtirilgan joylashtirish
  - RGB bitmap chizish
  - Dastur xotirasida saqlash

### 📦 Pin konfiguratsiyasi

```cpp
#define TFT_MOSI  26  // SDA/MOSI
#define TFT_SCLK  27  // SCK
#define TFT_CS    13  // Chip Select
#define TFT_DC    12  // Data/Command
#define TFT_RST   14  // Reset
```

### 🚀 Foydalanish

#### QR kod yaratish
1. QR kod tasvirini tayyorlang (140x180 piksel tavsiya etiladi)
2. [FileToCArray Converter](https://notisrac.github.io/FileToCArray/) dan foydalaning
3. Tasvirni RGB565 C massiviga aylantiring
4. Bo'sh `qr_image_data` massivini almashtiring

---

## 👨‍💻 Author

**Temur Eshmurodov**

## 📄 License

This project is open source. Feel free to use and modify for your needs.

---

<div align="center">

**📱 Transform Your ESP32 into a QR Code Display! 📱**

</div>
