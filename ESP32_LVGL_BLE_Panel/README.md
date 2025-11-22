# ESP32 LVGL BLE Control Panel 🎮

![ESP32](https://img.shields.io/badge/ESP32-LVGL%20BLE%20Control-red)
![LVGL](https://img.shields.io/badge/UI-LVGL%208.3.11-blue)
![BLE](https://img.shields.io/badge/Communication-BLE-green)
![TFT](https://img.shields.io/badge/Display-TFT%20eSPI-orange)

## 🌍 Multi-language README
- [English](#english) | [Русский](#русский) | [O'zbek](#ozbek)

---

## English

### 🎮 Advanced BLE-Controlled LVGL Interface System

Professional ESP32-based control system featuring LVGL graphical interface with BLE remote control capability. Perfect for IoT dashboards, remote monitoring, and interactive control panels.

### ✨ Key Features

- **🎨 Advanced LVGL Interface**
  - SquareLine Studio designed UI
  - Smooth animations and transitions
  - Dynamic element control
  - Professional visual design

- **📱 BLE Remote Control**
  - Bluetooth Low Energy communication
  - Real-time command processing
  - Connection status monitoring
  - Automatic reconnection

- **🖥️ TFT Display Integration**
  - High-resolution 320x480 display
  - TFT_eSPI driver optimization
  - Double buffering for smooth rendering
  - Custom flush implementation

- **🔌 Hardware Integration**
  - Built-in LED status indicators
  - External device control capability
  - Expandable I/O interfaces
  - Robust connection handling

### 🛠 Technical Specifications

#### Hardware Components
- **Controller**: ESP32
- **Display**: TFT (320x480) with SPI interface
- **Communication**: BLE 4.2+
- **Indicator**: Built-in LED (GPIO 2)

#### Software Architecture
- **Graphics**: LVGL 8.3.11
- **UI Design**: SquareLine Studio 1.5.3
- **BLE Stack**: ESP32 BLE Library
- **Display Driver**: TFT_eSPI 2.5.43

### 📦 Project Structure

```
Project/
├── main.cpp              # Main application logic
├── ble_service.h/cpp     # BLE communication handling
├── tft_draw.h/cpp        # TFT display functions
├── ui.h/c                # LVGL UI implementation
├── ui_*.h/c              # SquareLine generated UI
└── platformio.ini        # Build configuration
```

### 🚀 Installation & Setup

#### 1. PlatformIO Configuration
```ini
[env:esp32dev]
platform = espressif32
board = esp32dev
framework = arduino
lib_deps = 
    bodmer/TFT_eSPI@^2.5.43
    lvgl/lvgl@8.3.11
monitor_speed = 115200
board_build.partitions = huge_app.csv
```

#### 2. Library Dependencies
```cpp
#include <Arduino.h>
#include <lvgl.h>
#include <TFT_eSPI.h>
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
```

#### 3. Hardware Setup
- Connect TFT display via SPI
- Ensure proper power supply (3.3V)
- Built-in LED on GPIO 2 for status

### 🎮 Usage Instructions

#### BLE Connection
1. **Device Advertising**: "ESP32_BLE_Server"
2. **Service UUID**: `12345678-1234-1234-1234-123456789abc`
3. **Characteristic UUID**: `abcd1234-5678-1234-5678-abcdef123456`

#### Control Commands
- **"ON"**: Shows play button, hides stop button
- **"OFF"**: Shows stop button, hides play button
- **Connection Status**: Real-time UI updates

#### UI Elements
- **Image1**: Connection indicator (hidden by default)
- **Image2**: Disconnection indicator
- **Image3**: Play button (controlled by BLE)
- **Image4**: Stop button (controlled by BLE)
- **Label1**: Connection status text

### 🔧 Technical Implementation

#### BLE Service Setup
```cpp
void ble_begin() {
    BLEDevice::init(DEVICE_NAME);
    BLEServer *pServer = BLEDevice::createServer();
    BLEService *pService = pServer->createService(SERVICE_UUID);
    // Characteristic setup and callbacks
}
```

#### Display Configuration
```cpp
static lv_color_t buf1[320 * 20];  // Display buffer
lv_disp_draw_buf_init(&draw_buf, buf1, NULL, 320 * 20);
disp_drv.hor_res = 320;
disp_drv.ver_res = 480;
disp_drv.flush_cb = my_disp_flush;
```

#### UI State Management
```cpp
// Show/hide elements based on BLE commands
if (value == "ON") {
    lv_obj_add_flag(ui_Image4, LV_OBJ_FLAG_HIDDEN);
    lv_obj_clear_flag(ui_Image3, LV_OBJ_FLAG_HIDDEN);
}
```

### 🔌 BLE Protocol Details

#### Service Characteristics
- **Read/Write Permissions**: Both enabled
- **Initial Value**: "Ready"
- **Callback Handling**: Immediate command processing
- **Connection Management**: Automatic advertising restart

#### Message Processing
```cpp
void MyCallbacks::onWrite(BLECharacteristic *pChar) {
    value = pChar->getValue();
    // Process ON/OFF commands and update UI
}
```

### 🎨 UI Customization

#### Adding New Elements
1. Design in SquareLine Studio
2. Generate new UI files
3. Integrate with existing codebase
4. Add control logic in BLE callbacks

#### Modifying Behavior
- Change command strings in BLE handler
- Add new UI states
- Implement additional BLE characteristics
- Extend control capabilities

### ⚡ Performance Optimization

#### Memory Management
- Double buffering with 320x20 buffer
- PROGMEM for static assets
- Efficient LVGL tick handling
- Minimal dynamic allocation

#### Display Optimization
- Custom flush function for TFT_eSPI
- Efficient region-based updates
- Optimized SPI transactions
- Proper display initialization

### 🐛 Troubleshooting

**Common Issues:**
- **BLE not advertising**: Check device name and service setup
- **Display not working**: Verify TFT_eSPI configuration and SPI pins
- **UI not updating**: Ensure LVGL tick handling is proper
- **Memory issues**: Check partition scheme (huge_app.csv)

**Debug Features:**
- Serial output at 115200 baud
- Connection status monitoring
- BLE message logging
- UI state tracking

---

## Русский

### 🎮 Продвинутая система управления с BLE и LVGL интерфейсом

Профессиональная система управления на базе ESP32 с графическим интерфейсом LVGL и возможностью удаленного управления по BLE.

### ✨ Основные возможности

- **🎨 Продвинутый интерфейс LVGL**
  - UI разработан в SquareLine Studio
  - Плавные анимации и переходы
  - Динамическое управление элементами
  - Профессиональный визуальный дизайн

- **📱 Удаленное управление по BLE**
  - Связь по Bluetooth Low Energy
  - Обработка команд в реальном времени
  - Мониторинг статуса соединения
  - Автоматическое переподключение

### 🚀 Использование

#### Команды BLE
- **"ON"**: Показывает кнопку play, скрывает stop
- **"OFF"**: Показывает кнопку stop, скрывает play
- **Статус соединения**: Обновления UI в реальном времени

#### Подключение BLE
1. **Имя устройства**: "ESP32_BLE_Server"
2. **UUID сервиса**: `12345678-1234-1234-1234-123456789abc`
3. **UUID характеристики**: `abcd1234-5678-1234-5678-abcdef123456`

---

## O'zbek

### 🎮 BLE bilan Boshqariladigan LVGL Interfeys Tizimi

ESP32 asosidagi professional boshqaruv tizimi, LVGL grafik interfeysi va BLE orqali masofaviy boshqarish imkoniyati.

### ✨ Asosiy xususiyatlar

- **🎨 Ilg'or LVGL interfeys**
  - SquareLine Studio da ishlab chiqilgan UI
  - Silliq animatsiyalar va o'tishlar
  - Dinamik elementlarni boshqarish
  - Professional vizual dizayn

- **📱 BLE masofaviy boshqaruv**
  - Bluetooth Low Energy aloqasi
  - Real vaqtda buyruqlarni qayta ishlash
  - Ulanish holatini kuzatish
  - Avtomatik qayta ulanish

### 🚀 Foydalanish

#### BLE buyruqlari
- **"ON"**: Play tugmasini ko'rsatadi, stop ni yashiradi
- **"OFF"**: Stop tugmasini ko'rsatadi, play ni yashiradi
- **Ulanish holati**: UI ni real vaqtda yangilash

#### BLE ulanish
1. **Qurilma nomi**: "ESP32_BLE_Server"
2. **Service UUID**: `12345678-1234-1234-1234-123456789abc`
3. **Characteristic UUID**: `abcd1234-5678-1234-5678-abcdef123456`

---

## 👨‍💻 Author

**Temur Eshmurodov**

## 📄 License

This project is open source. Feel free to use and modify for your needs.

---

<div align="center">

**🎮 Transform Your ESP32 into a Professional Control Panel! 🎮**

</div>
