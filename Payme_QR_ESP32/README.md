# 💳 Payme QR ESP32

[![Platform](https://img.shields.io/badge/Platform-ESP32-blue.svg)](https://www.espressif.com/)
[![Protocol](https://img.shields.io/badge/Protocol-MQTT-green.svg)](https://mqtt.org/)
[![Broker](https://img.shields.io/badge/Broker-HiveMQ-orange.svg)](https://www.hivemq.com/)
[![License](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)

---

## 🌐 Tilni tanlang / Select Language / Выберите язык

- [🇺🇿 O'zbekcha](#-ozbek-tilida)
- [🇬🇧 English](#-english)
- [🇷🇺 Русский](#-русский)

---

## 🇺🇿 O'zbek tilida

### 📖 Loyiha haqida

Bu loyiha ESP32 mikrokontrolleri yordamida Payme to'lov tizimidan real vaqt rejimida to'lov bildirishnomalarini qabul qilish imkonini beradi. Tizim MQTT protokoli orqali ishlaydi va to'lov mablag'iga qarab LED bilan signal beradi.

### ✨ Xususiyatlar

| Xususiyat | Tavsif |
|-----------|--------|
| 📡 **MQTT aloqa** | HiveMQ broker orqali real vaqt xabarlari |
| 💰 **To'lov kuzatuvi** | To'lov holati va summasini olish |
| 💡 **LED indikator** | To'lov summasiga qarab LED boshqaruvi |
| 🔄 **Avtomatik ulanish** | WiFi va MQTT uzilganda qayta ulanish |
| 📊 **JSON tahlili** | To'lov ma'lumotlarini olish |

### 🔧 Kerakli komponentlar

| Komponent | Miqdori | Tavsif |
|-----------|---------|--------|
| ESP32 DevKit | 1 | Asosiy kontroller |
| LED | 1 | Holat indikatori (o'rnatilgan) |
| USB kabeli | 1 | Dasturlash va quvvatlash |

### 📐 Ulanish sxemasi

```
┌─────────────────────────────────────────────────────────┐
│                      ESP32 DevKit                        │
│                                                          │
│   ┌─────────────────────────────────────────────────┐   │
│   │                                                  │   │
│   │    WiFi: "Siren" ────────► Internet             │   │
│   │              │                                   │   │
│   │              ▼                                   │   │
│   │    broker.hivemq.com:1883                       │   │
│   │              │                                   │   │
│   │              ▼                                   │   │
│   │    Topic: payments/{merchant_id}                │   │
│   │              │                                   │
│   │              ▼                                   │   │
│   │    LED_BUILTIN ◄── To'lov summasi bo'yicha     │   │
│   │    (5000 = ON, 10000 = OFF)                     │   │
│   │                                                  │   │
│   └─────────────────────────────────────────────────┘   │
│                                                          │
└─────────────────────────────────────────────────────────┘
```

### ⚙️ Sozlash

WiFi sozlamalari:
```cpp
const char* ssid = "Siren";           // WiFi nomi
const char* password = "00152010";    // WiFi paroli
```

MQTT sozlamalari:
```cpp
const char* mqtt_server = "broker.hivemq.com";
const char* mqtt_topic  = "payments/68ffc803d2d01cc2d62db3a4";
```

LED boshqaruvi (summaga qarab):
```cpp
if (amount == "5000") {
  digitalWrite(LED_BUILTIN, HIGH);    // 5000 so'm = LED yonadi
}
else if (amount == "10000") {
  digitalWrite(LED_BUILTIN, LOW);     // 10000 so'm = LED o'chadi
}
```

### 📚 Kutubxonalar

| Kutubxona | Versiya | Maqsad |
|-----------|---------|--------|
| WiFi | Built-in | WiFi ulanishi |
| PubSubClient | 2.8+ | MQTT mijoz |

### 🚀 O'rnatish

1. Arduino IDE yoki PlatformIO o'rnating
2. ESP32 platasini qo'shing
3. `PubSubClient` kutubxonasini o'rnating
4. WiFi va MQTT sozlamalarini o'zgartiring
5. Kodni ESP32 ga yuklang

---

## 🇬🇧 English

### 📖 About

This project enables ESP32 microcontroller to receive real-time payment notifications from Payme payment system via MQTT protocol. The system indicates payment amounts using the built-in LED.

### ✨ Features

| Feature | Description |
|---------|-------------|
| 📡 **MQTT Communication** | Real-time messages via HiveMQ broker |
| 💰 **Payment Tracking** | Receive payment status and amounts |
| 💡 **LED Indicator** | LED control based on payment amount |
| 🔄 **Auto Reconnect** | Automatic reconnection on WiFi/MQTT disconnect |
| 📊 **JSON Parsing** | Extract payment data from JSON messages |

### 🔧 Required Components

| Component | Quantity | Description |
|-----------|----------|-------------|
| ESP32 DevKit | 1 | Main controller |
| LED | 1 | Status indicator (built-in) |
| USB cable | 1 | Programming and power |

### 📐 Connection Diagram

```
┌─────────────────────────────────────────────────────────┐
│                      ESP32 DevKit                        │
│                                                          │
│   ┌─────────────────────────────────────────────────┐   │
│   │                                                  │   │
│   │    WiFi: "Siren" ────────► Internet             │   │
│   │              │                                   │   │
│   │              ▼                                   │   │
│   │    broker.hivemq.com:1883                       │   │
│   │              │                                   │   │
│   │              ▼                                   │   │
│   │    Topic: payments/{merchant_id}                │   │
│   │              │                                   │   │
│   │              ▼                                   │   │
│   │    LED_BUILTIN ◄── Based on payment amount     │   │
│   │    (5000 = ON, 10000 = OFF)                     │   │
│   │                                                  │   │
│   └─────────────────────────────────────────────────┘   │
│                                                          │
└─────────────────────────────────────────────────────────┘
```

### ⚙️ Configuration

WiFi settings:
```cpp
const char* ssid = "Siren";           // WiFi name
const char* password = "00152010";    // WiFi password
```

MQTT settings:
```cpp
const char* mqtt_server = "broker.hivemq.com";
const char* mqtt_topic  = "payments/68ffc803d2d01cc2d62db3a4";
```

LED control (based on amount):
```cpp
if (amount == "5000") {
  digitalWrite(LED_BUILTIN, HIGH);    // 5000 sum = LED ON
}
else if (amount == "10000") {
  digitalWrite(LED_BUILTIN, LOW);     // 10000 sum = LED OFF
}
```

### 📚 Libraries

| Library | Version | Purpose |
|---------|---------|---------|
| WiFi | Built-in | WiFi connectivity |
| PubSubClient | 2.8+ | MQTT client |

### 🚀 Installation

1. Install Arduino IDE or PlatformIO
2. Add ESP32 board support
3. Install `PubSubClient` library
4. Modify WiFi and MQTT settings
5. Upload code to ESP32

### 📊 MQTT Message Format

The system expects JSON messages in this format:
```json
{
  "status": "paid",
  "amount": 5000
}
```

### 🔌 System Architecture

```
┌────────────┐    HTTP     ┌────────────┐    MQTT    ┌────────────┐
│            │ ──────────► │            │ ─────────► │            │
│   Payme    │             │   Server   │            │   ESP32    │
│   System   │             │  (Webhook) │            │            │
│            │ ◄────────── │            │ ◄───────── │            │
└────────────┘   Response  └────────────┘  Subscribe └────────────┘
```

---

## 🇷🇺 Русский

### 📖 О проекте

Этот проект позволяет микроконтроллеру ESP32 получать уведомления о платежах в реальном времени из платёжной системы Payme через протокол MQTT. Система индицирует суммы платежей с помощью встроенного светодиода.

### ✨ Функции

| Функция | Описание |
|---------|----------|
| 📡 **MQTT связь** | Сообщения в реальном времени через брокер HiveMQ |
| 💰 **Отслеживание платежей** | Получение статуса и суммы платежа |
| 💡 **LED индикатор** | Управление светодиодом в зависимости от суммы |
| 🔄 **Авто-переподключение** | Автоматическое переподключение при разрыве WiFi/MQTT |
| 📊 **Парсинг JSON** | Извлечение данных платежа из JSON сообщений |

### 🔧 Необходимые компоненты

| Компонент | Кол-во | Описание |
|-----------|--------|----------|
| ESP32 DevKit | 1 | Основной контроллер |
| LED | 1 | Индикатор состояния (встроенный) |
| USB кабель | 1 | Программирование и питание |

### 📐 Схема подключения

```
┌─────────────────────────────────────────────────────────┐
│                      ESP32 DevKit                        │
│                                                          │
│   ┌─────────────────────────────────────────────────┐   │
│   │                                                  │   │
│   │    WiFi: "Siren" ────────► Интернет             │   │
│   │              │                                   │   │
│   │              ▼                                   │   │
│   │    broker.hivemq.com:1883                       │   │
│   │              │                                   │   │
│   │              ▼                                   │   │
│   │    Топик: payments/{merchant_id}                │   │
│   │              │                                   │   │
│   │              ▼                                   │   │
│   │    LED_BUILTIN ◄── По сумме платежа            │   │
│   │    (5000 = ВКЛ, 10000 = ВЫКЛ)                   │   │
│   │                                                  │   │
│   └─────────────────────────────────────────────────┘   │
│                                                          │
└─────────────────────────────────────────────────────────┘
```

### ⚙️ Настройка

Настройки WiFi:
```cpp
const char* ssid = "Siren";           // Имя WiFi
const char* password = "00152010";    // Пароль WiFi
```

Настройки MQTT:
```cpp
const char* mqtt_server = "broker.hivemq.com";
const char* mqtt_topic  = "payments/68ffc803d2d01cc2d62db3a4";
```

Управление LED (по сумме):
```cpp
if (amount == "5000") {
  digitalWrite(LED_BUILTIN, HIGH);    // 5000 сум = LED включён
}
else if (amount == "10000") {
  digitalWrite(LED_BUILTIN, LOW);     // 10000 сум = LED выключен
}
```

### 📚 Библиотеки

| Библиотека | Версия | Назначение |
|------------|--------|------------|
| WiFi | Built-in | WiFi подключение |
| PubSubClient | 2.8+ | MQTT клиент |

### 🚀 Установка

1. Установите Arduino IDE или PlatformIO
2. Добавьте поддержку платы ESP32
3. Установите библиотеку `PubSubClient`
4. Измените настройки WiFi и MQTT
5. Загрузите код на ESP32

### 📊 Формат MQTT сообщения

Система ожидает JSON сообщения в формате:
```json
{
  "status": "paid",
  "amount": 5000
}
```

---

## 📁 Struktura loyiha / Project Structure / Структура проекта

```
Payme_QR_ESP32/
├── Payme_QR_ESP32.ino    # Asosiy kod / Main code / Основной код
└── README.md             # Hujjatlar / Documentation / Документация
```

---

## 🔗 Tizim komponentlari / System Components / Компоненты системы

### Backend Server (Node.js)
To'lov webhook'larini qabul qiladi va MQTT xabarlarini yuboradi.
Receives payment webhooks and publishes MQTT messages.
Принимает вебхуки платежей и публикует MQTT сообщения.

### ESP32 Client
MQTT mavzusiga obuna bo'lib, to'lov xabarlarini qabul qiladi.
Subscribes to MQTT topic and receives payment messages.
Подписывается на MQTT топик и получает сообщения о платежах.

---

## 📝 Litsenziya / License / Лицензия

MIT License - Batafsil ma'lumot uchun [LICENSE](LICENSE) faylini ko'ring.
MIT License - See [LICENSE](LICENSE) file for details.
MIT Лицензия - См. файл [LICENSE](LICENSE) для подробностей.

---

## 👨‍💻 Muallif / Author / Автор

**myseringan**

- GitHub: [@myseringan](https://github.com/myseringan)
