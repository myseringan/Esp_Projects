# ESP32-S3 LVGL DHT Panel 🌡️

![ESP32-S3](https://img.shields.io/badge/ESP32--S3-LVGL%20Panel-red)
![TFT Display](https://img.shields.io/badge/Display-TFT%20eSPI-blue)
![DHT11](https://img.shields.io/badge/Sensor-DHT11-green)
![SquareLine](https://img.shields.io/badge/Design-SquareLine%20Studio-orange)

## 🌍 Multi-language README
- [English](#english) | [Русский](#русский) | [O'zbek](#ozbek)

---

## English

### 🌡️ Advanced Environmental Monitoring Dashboard

Professional ESP32-S3 based environmental monitoring system with LVGL graphical interface, real-time sensor data visualization, and smooth animated gauges.

### ✨ Key Features

- **🎨 Professional GUI**
  - LVGL 8.3.11 graphics library
  - SquareLine Studio designed interface
  - Smooth arc gauge animations
  - Real-time value updates

- **📊 Sensor Monitoring**
  - DHT11 temperature & humidity
  - Real-time data acquisition
  - Animated gauge transitions
  - Automatic refresh every 2 seconds

- **🖥️ Display Features**
  - TFT_eSPI driver support
  - 320x480 resolution display
  - Double buffering for smooth rendering
  - Custom flush callback implementation

### 🛠 Technical Specifications

#### Hardware Components
- **Controller**: ESP32-S3
- **Display**: TFT (320x480) with TFT_eSPI
- **Sensor**: DHT11 Temperature & Humidity
- **Interface**: SPI for display

#### Software Stack
- **Graphics**: LVGL 8.3.11
- **Design Tool**: SquareLine Studio 1.5.3
- **Drivers**: TFT_eSPI, DHT sensor library
- **Protocol**: SPI communication

### 📦 Pin Configuration

```cpp
// DHT11 Sensor
#define DHTPIN 22
#define DHTTYPE DHT11

// Display Configuration
// Using TFT_eSPI with default SPI pins
```

### 🚀 Installation & Setup

#### 1. Library Dependencies
```cpp
#include <lvgl.h>
#include "ui.h"  // SquareLine generated UI
#include "DHT.h"
#include "TFT_eSPI.h"
```

#### 2. Hardware Setup
- Connect TFT display using SPI interface
- Connect DHT11 to GPIO 22
- Ensure proper 3.3V power supply
- Verify SPI connections

#### 3. Software Configuration
- Install LVGL library
- Configure TFT_eSPI settings
- Include SquareLine generated UI files
- Set up display buffer

### 🎮 User Interface

#### Screen Components
- **Arc3**: Temperature gauge (0-100°C)
- **Arc4**: Humidity gauge (0-100%)
- **Label2**: Temperature value display
- **Label3**: Humidity value display
- **Label4/5**: Additional information labels

#### Animation Features
- **Smooth Transitions**: 500ms arc animations
- **Real-time Updates**: 2-second sensor intervals
- **Direct Value Setting**: Immediate gauge response
- **Invalidation Control**: Manual display refresh

### 🔧 Technical Implementation

#### Display Initialization
```cpp
static lv_color_t buf1[320 * 60];  // Display buffer
lv_disp_draw_buf_init(&draw_buf, buf1, NULL, 320 * 60);
disp_drv.hor_res = 320;
disp_drv.ver_res = 480;
```

#### Animation System
```cpp
// Custom animation callback
static void arc_anim_exec(void * a, int32_t v) {
    lv_arc_set_value((lv_obj_t*)a, v);
}

// Animation configuration
lv_anim_set_time(&animT, 500);
lv_anim_set_exec_cb(&animT, arc_anim_exec);
```

#### Sensor Integration
```cpp
void updateDHT() {
    float tf = dht.readTemperature();
    float hf = dht.readHumidity();
    updateArcs(tf, hf);  // Update UI with sensor data
}
```

### ⚙️ Customization

#### UI Modifications
- Edit `ui_Screen1.h` for screen components
- Modify `ui_helpers.c` for custom animations
- Update assets in SquareLine Studio
- Adjust gauge ranges and styles

#### Performance Tuning
- Adjust buffer size in `buf1[320 * 60]`
- Modify animation timing (500ms default)
- Change sensor read interval (2000ms default)
- Optimize LVGL tick handling

### 🐛 Troubleshooting

**Common Issues:**
- **Display not working**: Check SPI connections and TFT_eSPI configuration
- **LVGL not rendering**: Verify buffer size and flush callback
- **Sensor readings failed**: Check DHT11 wiring and GPIO 22
- **Animations sluggish**: Reduce buffer size or increase CPU frequency

**Debug Features:**
- Serial output at 115200 baud
- Sensor value logging
- Animation state monitoring
- Memory usage tracking

---

## Русский

### 🌡️ Продвинутая система мониторинга окружающей среды

Профессиональная система мониторинга на базе ESP32-S3 с графическим интерфейсом LVGL, визуализацией данных с датчиков и плавными анимированными датчиками.

### ✨ Основные возможности

- **🎨 Профессиональный GUI**
  - Графическая библиотека LVGL 8.3.11
  - Интерфейс разработан в SquareLine Studio
  - Плавные анимации дуговых датчиков
  - Обновление значений в реальном времени

- **📊 Мониторинг датчиков**
  - DHT11 температура и влажность
  - Получение данных в реальном времени
  - Анимированные переходы датчиков
  - Автоматическое обновление каждые 2 секунды

### 🛠 Технические характеристики

#### Аппаратные компоненты
- **Контроллер**: ESP32-S3
- **Дисплей**: TFT (320x480) с TFT_eSPI
- **Датчик**: DHT11 Температура и Влажность
- **Интерфейс**: SPI для дисплея

### 📦 Конфигурация пинов

```cpp
// Датчик DHT11
#define DHTPIN 22
#define DHTTYPE DHT11
```

### 🚀 Использование

#### Компоненты экрана
- **Arc3**: Датчик температуры (0-100°C)
- **Arc4**: Датчик влажности (0-100%)
- **Label2**: Отображение значения температуры
- **Label3**: Отображение значения влажности

#### Особенности анимации
- **Плавные переходы**: Анимации 500ms
- **Обновления в реальном времени**: Интервал датчиков 2 секунды
- **Непосредственная установка значений**: Мгновенный отклик датчиков

---

## O'zbek

### 🌡️ Ilg'or Atrof-muhit Monitoring Tizimi

ESP32-S3 asosidagi professional monitoring tizimi, LVGL grafik interfeysi, sensordagi ma'lumotlarni vizuallashtirish va silliq animatsiyali o'lchagichlar.

### ✨ Asosiy xususiyatlar

- **🎨 Professional GUI**
  - LVGL 8.3.11 grafik kutubxonasi
  - SquareLine Studio da ishlab chiqilgan interfeys
  - Silliq yoy o'lchagich animatsiyalari
  - Real vaqtda qiymat yangilanishlari

- **📊 Sensor monitoringi**
  - DHT11 harorat va namlik
  - Real vaqtda ma'lumot olish
  - Animatsiyali o'lchagich o'tishlari
  - 2 soniyada avtomatik yangilash

### 🛠 Texnik xususiyatlar

#### Uskuna komponentlari
- **Kontroller**: ESP32-S3
- **Displey**: TFT (320x480) TFT_eSPI bilan
- **Senser**: DHT11 Harorat va Namlik
- **Interfeys**: Displey uchun SPI

### 📦 Pin konfiguratsiyasi

```cpp
// DHT11 Sensori
#define DHTPIN 22
#define DHTTYPE DHT11
```

### 🚀 Foydalanish

#### Ekran komponentlari
- **Arc3**: Harorat o'lchagichi (0-100°C)
- **Arc4**: Namlik o'lchagichi (0-100%)
- **Label2**: Harorat qiymati displeyi
- **Label3**: Namlik qiymati displeyi

#### Animatsiya xususiyatlari
- **Silliq o'tishlar**: 500ms yoy animatsiyalari
- **Real vaqtda yangilanish**: Sensor intervali 2 soniya
- **To'g'ridan-to'g'ri qiymat o'rnatish**: O'lchagichlarning darhol javobi

---

## 👨‍💻 Author

**Temur Eshmurodov**

## 📄 License

This project is open source. Feel free to use and modify for your needs.

---

<div align="center">

**🌡️ Professional Environmental Monitoring Made Beautiful! 🌡️**

</div>
