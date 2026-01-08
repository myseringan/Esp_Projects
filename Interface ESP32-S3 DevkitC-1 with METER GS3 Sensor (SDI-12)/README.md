# 🌱 Wireless Soil Sensor Gateway

[![Platform](https://img.shields.io/badge/Platform-ESP32--S3-blue.svg)](https://www.espressif.com/)
[![Protocol](https://img.shields.io/badge/Protocol-SDI--12-green.svg)](https://en.wikipedia.org/wiki/SDI-12)
[![Sensor](https://img.shields.io/badge/Sensor-METER_GS3-orange.svg)](https://www.metergroup.com/)
[![License](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)

---

## 🌐 Tilni tanlang / Select Language / Выберите язык

- [🇺🇿 O'zbekcha](#-ozbek-tilida)
- [🇬🇧 English](#-english)
- [🇷🇺 Русский](#-русский)

---

## 🇺🇿 O'zbek tilida

### 📖 Loyiha haqida

Bu loyiha ESP32-S3 mikrokontrolleri yordamida bir nechta METER GS3 tuproq sensorlaridan ma'lumotlarni o'qish imkonini beradi. Tizim SDI-12 protokoli orqali 4 tagacha sensorni qo'llab-quvvatlaydi va energiya tejash uchun deep sleep rejimidan foydalanadi.

### ✨ Xususiyatlar

| Xususiyat | Tavsif |
|-----------|--------|
| 📊 **Multi-sensor** | 4 ta SDI-12 sensorgacha parallel o'qish |
| 🔋 **Energiya tejash** | Deep sleep rejimi (1 soat interval) |
| ⚡ **Quvvat boshqaruvi** | Sensorlar uchun alohida quvvat nazorati |
| 🔄 **Holat mashinasi** | Ishonchli asinxron so'rovlar |
| ⏱️ **Sozlanuvchi** | O'lchash va uyqu vaqtlarini sozlash |

### 🔧 Kerakli komponentlar

| Komponent | Miqdori | Tavsif |
|-----------|---------|--------|
| ESP32-S3 DevKitC-1 | 1 | Asosiy kontroller |
| METER GS3 Sensor | 1-4 | Tuproq namligi/harorati/EC sensori |
| MOSFET/Rele | 1 | Quvvat boshqaruvi |
| Quvvat manbai | 1 | 3.3V/5V |
| Ulanish simlari | - | SDI-12 aloqasi uchun |

### 📐 Ulanish sxemasi

```
┌─────────────────────────────────────────────────────────────────┐
│                      ESP32-S3 DevKitC-1                         │
│                                                                 │
│    GPIO8 ─────────────────────────────┐                        │
│    (ENERGY_SAVING)                     │                        │
│                                        ▼                        │
│                              ┌─────────────────┐                │
│                              │   MOSFET/Rele   │                │
│                              │   (Quvvat SW)   │                │
│                              └────────┬────────┘                │
│                                       │                         │
│         ┌─────────────────────────────┼─────────────────┐      │
│         │                             │                  │      │
│         ▼                             ▼                  ▼      │
│    ┌─────────┐                  ┌─────────┐       ┌─────────┐  │
│    │ Sensor 1│                  │ Sensor 2│  ...  │ Sensor 4│  │
│    │  GS3    │                  │  GS3    │       │  GS3    │  │
│    │ Addr: 1 │                  │ Addr: 2 │       │ Addr: 4 │  │
│    └────┬────┘                  └────┬────┘       └────┬────┘  │
│         │                             │                  │      │
│    GPIO15                        GPIO16             GPIO18      │
│    (SDI-12)                     (SDI-12)           (SDI-12)     │
│                                                                 │
└─────────────────────────────────────────────────────────────────┘
```

### 📌 Pin konfiguratsiyasi

| ESP32-S3 Pin | Funksiya | Tavsif |
|--------------|----------|--------|
| GPIO8 | ENERGY_SAVING | Sensor quvvatini boshqarish |
| GPIO15 | SDI12_pin1 | Sensor 1 (manzil '1') |
| GPIO16 | SDI12_pin2 | Sensor 2 (manzil '2') |
| GPIO17 | SDI12_pin3 | Sensor 3 (manzil '3') |
| GPIO18 | SDI12_pin4 | Sensor 4 (manzil '4') |

### ⚙️ Sozlash

Vaqt parametrlari:
```cpp
const unsigned long MEAS_CYCLE_INTERVAL_MS = 1200000UL;  // Sikl oralig'i (20 min)
const unsigned long WAKE_DELAY_MS = 2000UL;              // Sensor uyg'onish vaqti
const unsigned long RESPONSE_TIMEOUT_MS = 5000UL;        // Javob kutish vaqti
const unsigned long READ_TIMEOUT_MS = 5000UL;            // Ma'lumot o'qish vaqti
```

Deep sleep sozlamalari:
```cpp
const bool USE_DEEP_SLEEP = true;           // Deep sleep yoqish
const unsigned long DEEP_SLEEP_TIME_SEC = 3600UL;  // Uyqu vaqti (1 soat)
```

### 📚 Kutubxonalar

| Kutubxona | Versiya | Maqsad |
|-----------|---------|--------|
| SDI12 | 2.1.4+ | SDI-12 protokoli |
| esp_sleep | Built-in | Deep sleep funksiyasi |

### 🚀 O'rnatish

1. Arduino IDE yoki PlatformIO o'rnating
2. ESP32-S3 platasini qo'shing
3. `SDI-12` kutubxonasini o'rnating: `Arduino Library Manager → SDI-12`
4. Sensor manzillarini tekshiring va sozlang
5. Kodni ESP32-S3 ga yuklang

---

## 🇬🇧 English

### 📖 About

This project enables ESP32-S3 microcontroller to read data from multiple METER GS3 soil sensors using SDI-12 protocol. The system supports up to 4 sensors and utilizes deep sleep mode for energy efficiency.

### ✨ Features

| Feature | Description |
|---------|-------------|
| 📊 **Multi-sensor** | Parallel reading of up to 4 SDI-12 sensors |
| 🔋 **Energy Saving** | Deep sleep mode (1 hour interval) |
| ⚡ **Power Management** | Separate power control for sensors |
| 🔄 **State Machine** | Reliable asynchronous polling |
| ⏱️ **Configurable** | Adjustable measurement and sleep times |

### 🔧 Required Components

| Component | Quantity | Description |
|-----------|----------|-------------|
| ESP32-S3 DevKitC-1 | 1 | Main controller |
| METER GS3 Sensor | 1-4 | Soil moisture/temperature/EC sensor |
| MOSFET/Relay | 1 | Power switching |
| Power Supply | 1 | 3.3V/5V |
| Wires | - | For SDI-12 connection |

### 📐 Wiring Diagram

```
┌─────────────────────────────────────────────────────────────────┐
│                      ESP32-S3 DevKitC-1                         │
│                                                                 │
│    GPIO8 ─────────────────────────────┐                        │
│    (ENERGY_SAVING)                     │                        │
│                                        ▼                        │
│                              ┌─────────────────┐                │
│                              │   MOSFET/Relay  │                │
│                              │  (Power Switch) │                │
│                              └────────┬────────┘                │
│                                       │                         │
│         ┌─────────────────────────────┼─────────────────┐      │
│         │                             │                  │      │
│         ▼                             ▼                  ▼      │
│    ┌─────────┐                  ┌─────────┐       ┌─────────┐  │
│    │ Sensor 1│                  │ Sensor 2│  ...  │ Sensor 4│  │
│    │  GS3    │                  │  GS3    │       │  GS3    │  │
│    │ Addr: 1 │                  │ Addr: 2 │       │ Addr: 4 │  │
│    └────┬────┘                  └────┬────┘       └────┬────┘  │
│         │                             │                  │      │
│    GPIO15                        GPIO16             GPIO18      │
│    (SDI-12)                     (SDI-12)           (SDI-12)     │
│                                                                 │
└─────────────────────────────────────────────────────────────────┘
```

### 📌 Pin Configuration

| ESP32-S3 Pin | Function | Description |
|--------------|----------|-------------|
| GPIO8 | ENERGY_SAVING | Sensor power control |
| GPIO15 | SDI12_pin1 | Sensor 1 (address '1') |
| GPIO16 | SDI12_pin2 | Sensor 2 (address '2') |
| GPIO17 | SDI12_pin3 | Sensor 3 (address '3') |
| GPIO18 | SDI12_pin4 | Sensor 4 (address '4') |

### ⚙️ Configuration

Timing parameters:
```cpp
const unsigned long MEAS_CYCLE_INTERVAL_MS = 1200000UL;  // Cycle interval (20 min)
const unsigned long WAKE_DELAY_MS = 2000UL;              // Sensor wake-up time
const unsigned long RESPONSE_TIMEOUT_MS = 5000UL;        // Response timeout
const unsigned long READ_TIMEOUT_MS = 5000UL;            // Data read timeout
```

Deep sleep settings:
```cpp
const bool USE_DEEP_SLEEP = true;           // Enable deep sleep
const unsigned long DEEP_SLEEP_TIME_SEC = 3600UL;  // Sleep duration (1 hour)
```

### 📚 Libraries

| Library | Version | Purpose |
|---------|---------|---------|
| SDI12 | 2.1.4+ | SDI-12 protocol |
| esp_sleep | Built-in | Deep sleep functionality |

### 🚀 Installation

1. Install Arduino IDE or PlatformIO
2. Add ESP32-S3 board support
3. Install `SDI-12` library: `Arduino Library Manager → SDI-12`
4. Verify and configure sensor addresses
5. Upload code to ESP32-S3

### 📊 SDI-12 Protocol

The system uses standard SDI-12 commands:

| Command | Response | Description |
|---------|----------|-------------|
| `aM!` | `atttn` | Start measurement (a=address, ttt=wait time, n=values) |
| `aD0!` | `a+val1+val2...` | Request data |

### 🔄 State Machine

```
┌──────┐     ┌─────────────┐     ┌───────────┐     ┌──────────────────┐
│ IDLE │────►│ WAKE_SENSORS│────►│ WAIT_WAKE │────►│ SEND_MEASUREMENT │
└──────┘     └─────────────┘     └───────────┘     └────────┬─────────┘
                                                             │
┌──────────────┐     ┌───────────┐     ┌──────────────────┐ │
│ FINISH_CYCLE │◄────│ READ_DATA │◄────│ WAIT_MEASUREMENT │◄┘
└──────┬───────┘     └───────────┘     └──────────────────┘
       │
       ▼
  Deep Sleep (1 hour)
       │
       ▼
    Reboot
```

---

## 🇷🇺 Русский

### 📖 О проекте

Этот проект позволяет микроконтроллеру ESP32-S3 считывать данные с нескольких почвенных датчиков METER GS3 по протоколу SDI-12. Система поддерживает до 4 датчиков и использует режим глубокого сна для энергоэффективности.

### ✨ Функции

| Функция | Описание |
|---------|----------|
| 📊 **Мульти-сенсор** | Параллельное чтение до 4 датчиков SDI-12 |
| 🔋 **Энергосбережение** | Режим глубокого сна (интервал 1 час) |
| ⚡ **Управление питанием** | Отдельное управление питанием датчиков |
| 🔄 **Конечный автомат** | Надёжный асинхронный опрос |
| ⏱️ **Настраиваемость** | Регулируемое время измерений и сна |

### 🔧 Необходимые компоненты

| Компонент | Кол-во | Описание |
|-----------|--------|----------|
| ESP32-S3 DevKitC-1 | 1 | Основной контроллер |
| METER GS3 Sensor | 1-4 | Датчик влажности/температуры/EC почвы |
| MOSFET/Реле | 1 | Коммутация питания |
| Блок питания | 1 | 3.3V/5V |
| Провода | - | Для подключения SDI-12 |

### 📐 Схема подключения

```
┌─────────────────────────────────────────────────────────────────┐
│                      ESP32-S3 DevKitC-1                         │
│                                                                 │
│    GPIO8 ─────────────────────────────┐                        │
│    (ENERGY_SAVING)                     │                        │
│                                        ▼                        │
│                              ┌─────────────────┐                │
│                              │  MOSFET/Реле    │                │
│                              │ (Выкл. питания) │                │
│                              └────────┬────────┘                │
│                                       │                         │
│         ┌─────────────────────────────┼─────────────────┐      │
│         │                             │                  │      │
│         ▼                             ▼                  ▼      │
│    ┌─────────┐                  ┌─────────┐       ┌─────────┐  │
│    │ Датчик 1│                  │ Датчик 2│  ...  │ Датчик 4│  │
│    │  GS3    │                  │  GS3    │       │  GS3    │  │
│    │ Адрес: 1│                  │ Адрес: 2│       │ Адрес: 4│  │
│    └────┬────┘                  └────┬────┘       └────┬────┘  │
│         │                             │                  │      │
│    GPIO15                        GPIO16             GPIO18      │
│    (SDI-12)                     (SDI-12)           (SDI-12)     │
│                                                                 │
└─────────────────────────────────────────────────────────────────┘
```

### 📌 Конфигурация пинов

| Пин ESP32-S3 | Функция | Описание |
|--------------|---------|----------|
| GPIO8 | ENERGY_SAVING | Управление питанием датчиков |
| GPIO15 | SDI12_pin1 | Датчик 1 (адрес '1') |
| GPIO16 | SDI12_pin2 | Датчик 2 (адрес '2') |
| GPIO17 | SDI12_pin3 | Датчик 3 (адрес '3') |
| GPIO18 | SDI12_pin4 | Датчик 4 (адрес '4') |

### ⚙️ Настройка

Параметры времени:
```cpp
const unsigned long MEAS_CYCLE_INTERVAL_MS = 1200000UL;  // Интервал цикла (20 мин)
const unsigned long WAKE_DELAY_MS = 2000UL;              // Время пробуждения датчиков
const unsigned long RESPONSE_TIMEOUT_MS = 5000UL;        // Таймаут ответа
const unsigned long READ_TIMEOUT_MS = 5000UL;            // Таймаут чтения данных
```

Настройки глубокого сна:
```cpp
const bool USE_DEEP_SLEEP = true;           // Включить глубокий сон
const unsigned long DEEP_SLEEP_TIME_SEC = 3600UL;  // Время сна (1 час)
```

### 📚 Библиотеки

| Библиотека | Версия | Назначение |
|------------|--------|------------|
| SDI12 | 2.1.4+ | Протокол SDI-12 |
| esp_sleep | Built-in | Функция глубокого сна |

### 🚀 Установка

1. Установите Arduino IDE или PlatformIO
2. Добавьте поддержку платы ESP32-S3
3. Установите библиотеку `SDI-12`: `Arduino Library Manager → SDI-12`
4. Проверьте и настройте адреса датчиков
5. Загрузите код на ESP32-S3

### 📊 Протокол SDI-12

Система использует стандартные команды SDI-12:

| Команда | Ответ | Описание |
|---------|-------|----------|
| `aM!` | `atttn` | Начать измерение (a=адрес, ttt=время ожидания, n=значения) |
| `aD0!` | `a+val1+val2...` | Запросить данные |

---

## 📁 Struktura loyiha / Project Structure / Структура проекта

```
Wireless_Soil_Sensor_Gateway/
├── Wireless_Soil_Sensor_Gateway.ino   # Asosiy kod / Main code / Основной код
└── README.md                           # Hujjatlar / Documentation / Документация
```

---

## 📈 METER GS3 Sensor ma'lumotlari / Sensor Data / Данные датчика

GS3 sensori quyidagi qiymatlarni qaytaradi:
The GS3 sensor returns the following values:
Датчик GS3 возвращает следующие значения:

| Parametr / Parameter / Параметр | Birlik / Unit / Единица | Diapazon / Range / Диапазон |
|--------------------------------|-------------------------|----------------------------|
| Dielektrik o'tkazuvchanlik / Dielectric Permittivity / Диэлектрическая проницаемость | - | 1-80 |
| Harorat / Temperature / Температура | °C | -40 to +60 |
| EC | dS/m | 0-23 |

---

## 🔋 Energiya iste'moli / Power Consumption / Энергопотребление

| Holat / State / Состояние | Tok / Current / Ток |
|---------------------------|---------------------|
| Aktiv o'lchash / Active measurement / Активное измерение | ~80 mA |
| Deep sleep | ~10 μA |

---

## 📝 Litsenziya / License / Лицензия

MIT License - Batafsil ma'lumot uchun [LICENSE](LICENSE) faylini ko'ring.
MIT License - See [LICENSE](LICENSE) file for details.
MIT Лицензия - См. файл [LICENSE](LICENSE) для подробностей.

---

## 👨‍💻 Muallif / Author / Автор

**myseringan**

- GitHub: [@myseringan](https://github.com/myseringan)
