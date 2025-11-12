# 🖼️ PHOTO_TO_TFT_SHOW

## 🇬🇧 English

This project demonstrates how to display a static image on a **TFT display (ST7735)** using an **ESP32** board.  
It converts an image into a 16-bit RGB565 array and stores it in **PROGMEM** to show on startup.

### 🔧 Features
- Displays an embedded image (`qr_image_data`) stored in flash memory.  
- Uses **Adafruit_GFX** and **Adafruit_ST7735** libraries.  
- Configured for SPI pins on **ESP32**.  
- Can be used as a **startup splash screen** for any ESP32 project.  

### ⚙️ Hardware connections
| Signal | ESP32 Pin | Description |
|--------|------------|-------------|
| MOSI   | 26 | Data (SDA/MOSI) |
| SCLK   | 27 | Clock (SCK) |
| CS     | 13 | Chip Select |
| DC     | 12 | Data/Command |
| RST    | 14 | Reset |

### 📦 Required Libraries
- `Adafruit_GFX`
- `Adafruit_ST7735`
- `SPI`

Install them via PlatformIO (`platformio.ini`) or Arduino Library Manager.

### ▶️ Usage
1. Convert your image to RGB565 array (using LCD-Image-Converter or online tools).  
2. Replace `qr_image_data[]` in the `.ino` file with your image array.  
3. Adjust width and height constants (`QR_WIDTH`, `QR_HEIGHT`).  
4. Build and upload with PlatformIO.  
5. On boot, your image will appear on the TFT screen.

---

## 🇷🇺 Русский

Этот проект демонстрирует, как вывести статическое изображение на **TFT-дисплей (ST7735)** с помощью платы **ESP32**.  
Изображение преобразуется в массив формата RGB565 и хранится в **PROGMEM**, чтобы отображаться при старте устройства.

### 🔧 Возможности
- Отображает встроенное изображение (`qr_image_data`), сохранённое во флеш-памяти.  
- Использует библиотеки **Adafruit_GFX** и **Adafruit_ST7735**.  
- Настроен под SPI-пины **ESP32**.  
- Подходит как стартовая заставка для ваших проектов.

### ⚙️ Подключение дисплея
| Сигнал | Пин ESP32 | Назначение |
|--------|------------|-------------|
| MOSI   | 26 | Передача данных (SDA/MOSI) |
| SCLK   | 27 | Тактирование (SCK) |
| CS     | 13 | Выбор чипа |
| DC     | 12 | Команда/данные |
| RST    | 14 | Сброс |

### 📦 Необходимые библиотеки
- `Adafruit_GFX`
- `Adafruit_ST7735`
- `SPI`

Можно установить через **PlatformIO** или **Arduino IDE**.

### ▶️ Как использовать
1. Конвертируйте изображение в формат RGB565 (например, через **LCD Image Converter**).  
2. Замените массив `qr_image_data[]` в коде на свой.  
3. Укажите размеры изображения (`QR_WIDTH`, `QR_HEIGHT`).  
4. Скомпилируйте и загрузите прошивку.  
5. При включении устройство отобразит ваше изображение на экране.

---

## 🇺🇿 Oʻzbekcha

Ushbu loyiha **ESP32** platasi yordamida **TFT displey (ST7735)** da rasmni ko‘rsatishni namoyish etadi.  
Rasm RGB565 formatiga o‘tkazilib, **PROGMEM** ichida saqlanadi va qurilma ishga tushganda ekranga chiqariladi.

### 🔧 Xususiyatlar
- Flash xotirada saqlangan (`qr_image_data`) rasmni ko‘rsatadi.  
- **Adafruit_GFX** va **Adafruit_ST7735** kutubxonalaridan foydalanadi.  
- SPI pinlari **ESP32** uchun moslashtirilgan.  
- Har qanday loyiha uchun start logosi sifatida ishlatiladi.

### ⚙️ Ulanish sxemasi
| Signal | ESP32 pin | Tavsif |
|--------|------------|---------|
| MOSI | 26 | Ma’lumot uzatish (SDA/MOSI) |
| SCLK | 27 | Soat signali (SCK) |
| CS | 13 | Chip tanlash |
| DC | 12 | Ma’lumot/Boshqaruv |
| RST | 14 | Qayta ishga tushirish |

### 📦 Kerakli kutubxonalar
- `Adafruit_GFX`
- `Adafruit_ST7735`
- `SPI`

### ▶️ Foydalanish tartibi
1. Rasmni RGB565 formatiga o‘tkazing (masalan, **LCD Image Converter** orqali).  
2. `qr_image_data[]` massivini o‘zingizning rasm ma’lumotlariga almashtiring.  
3. `QR_WIDTH` va `QR_HEIGHT` qiymatlarini moslang.  
4. PlatformIO orqali dasturiy ta’minotni qurib yuklang.  
5. Qurilma yoqilganda, rasm ekranda ko‘rinadi.
