# Payme QR ESP32 Payment System 💳

![ESP32](https://img.shields.io/badge/ESP32-Payment%20System-red)
![MQTT](https://img.shields.io/badge/Protocol-MQTT-green)
![Payme](https://img.shields.io/badge/Integration-Payme%20QR-blue)
![WiFi](https://img.shields.io/badge/Connectivity-WiFi-orange)

## 🌍 Multi-language README
- [English](#english) | [Русский](#русский) | [O'zbek](#ozbek)

---

## English

### 💰 Smart Payment Notification System with Payme QR

ESP32-based payment monitoring system that receives real-time payment notifications from Payme QR via MQTT protocol and triggers physical actions based on payment amounts.

### ✨ Key Features

- **🔔 Real-time Payment Alerts**
  - Instant MQTT notifications
  - JSON message parsing
  - Payment status monitoring
  - Amount-based actions

- **📡 Wireless Communication**
  - WiFi connectivity
  - MQTT protocol implementation
  - HiveMQ public broker
  - Automatic reconnection

- **💡 Physical Feedback**
  - Built-in LED indicators
  - Custom actions per amount
  - Visual payment confirmation
  - Hardware triggers

### 🛠 Technical Specifications

#### Hardware Components
- **Controller**: ESP32
- **Indicator**: Built-in LED
- **Communication**: WiFi 2.4GHz
- **Protocol**: MQTT over TCP

#### Software Integration
- **Payment Provider**: Payme QR
- **MQTT Broker**: HiveMQ (public)
- **Message Format**: JSON
- **Security**: Merchant ID authentication

### 📦 Configuration

#### WiFi Settings
```cpp
const char* ssid = "Your_WiFi_SSID";
const char* password = "Your_WiFi_Password";
```

#### MQTT Configuration
```cpp
const char* mqtt_server = "broker.hivemq.com";
const char* mqtt_topic = "payments/your_merchant_id";
```

### 🚀 Setup & Installation

#### 1. Hardware Setup
- Connect ESP32 to power
- Built-in LED will be used for indicators
- No additional components required

#### 2. Software Configuration
```cpp
// Update these values in the code:
const char* ssid = "Your_WiFi_SSID";
const char* password = "Your_WiFi_Password";
const char* mqtt_topic = "payments/your_actual_merchant_id";
```

#### 3. Library Dependencies
```cpp
#include <WiFi.h>
#include <PubSubClient.h>
```

### 🎮 Operation Modes

#### Payment Monitoring
- **Topic**: `payments/merchant_id`
- **Format**: JSON messages
- **Fields**: status, amount
- **Frequency**: Real-time

#### LED Indicators
- **5000 amount**: LED ON
- **10000 amount**: LED OFF
- **Customizable**: Modify for your needs

### 📊 Message Format

#### Example JSON Payload
```json
{
  "status": "paid",
  "amount": 5000
}
```

#### Parsed Information
- **Status**: Payment state (paid, pending, failed)
- **Amount**: Transaction amount in units
- **Actions**: LED control based on amount

### 🔧 Customization

#### Modify Amount Triggers
```cpp
if (amount == "5000") {
    digitalWrite(LED_BUILTIN, HIGH);  // Turn LED ON
}
else if (amount == "10000") {
    digitalWrite(LED_BUILTIN, LOW);   // Turn LED OFF
}
// Add more conditions as needed
```

#### Additional Actions
- Connect relays for device control
- Add buzzer for audio alerts
- Implement LCD display for status
- Send SMS notifications

### 🌐 Network Configuration

#### MQTT Broker Options
- **Public**: HiveMQ (broker.hivemq.com)
- **Private**: Custom MQTT server
- **Cloud**: AWS IoT, Azure IoT Hub
- **Local**: Mosquitto on Raspberry Pi

#### Security Considerations
- Use unique merchant IDs
- Consider private MQTT brokers
- Implement SSL/TLS encryption
- Add authentication credentials

### 🐛 Troubleshooting

**Common Issues:**
- **WiFi connection failed**: Check SSID/password
- **MQTT not connecting**: Verify broker address
- **No messages received**: Check merchant ID
- **LED not working**: Verify GPIO pin assignment

**Debug Information:**
- Serial output at 115200 baud
- Connection status messages
- Raw JSON message display
- Payment details logging

---

## Русский

### 💰 Умная система уведомлений о платежах с Payme QR

Система мониторинга платежей на базе ESP32, которая получает уведомления о платежах от Payme QR через протокол MQTT и выполняет физические действия в зависимости от суммы платежа.

### ✨ Основные возможности

- **🔔 Уведомления о платежах в реальном времени**
  - Мгновенные MQTT уведомления
  - Парсинг JSON сообщений
  - Мониторинг статуса платежей
  - Действия на основе суммы

- **📡 Беспроводная связь**
  - Подключение по WiFi
  - Реализация протокола MQTT
  - Публичный брокер HiveMQ
  - Автоматическое переподключение

- **💡 Физическая обратная связь**
  - Светодиодные индикаторы
  - Пользовательские действия по сумме
  - Визуальное подтверждение платежа
  - Аппаратные триггеры

### 📦 Конфигурация

#### Настройки WiFi
```cpp
const char* ssid = "Ваш_WiFi_SSID";
const char* password = "Ваш_WiFi_Пароль";
```

#### Конфигурация MQTT
```cpp
const char* mqtt_server = "broker.hivemq.com";
const char* mqtt_topic = "payments/ваш_merchant_id";
```

### 🚀 Использование

#### Индикаторы LED
- **Сумма 5000**: LED ВКЛ
- **Сумма 10000**: LED ВЫКЛ
- **Настраиваемо**: Измените под свои нужды

#### Формат сообщений
```json
{
  "status": "paid",
  "amount": 5000
}
```

---

## O'zbek

### 💰 Payme QR bilan Aqlli To'lov Bildirishnoma Tizimi

ESP32 asosidagi to'lov monitoring tizimi, MQQT protokoli orqali Payme QR dan real vaqtda to'lov bildirishnomalarini qabul qiladi va to'lov miqdoriga asoslangan jismoniy harakatlarni amalga oshiradi.

### ✨ Asosiy xususiyatlar

- **🔔 Real vaqtda to'lov bildirishnomalari**
  - Tezkor MQTT bildirishnomalar
  - JSON xabarlarni tahlil qilish
  - To'lov holati monitoringi
  - Miqdorga asoslangan harakatlar

- **📡 Simsiz aloqa**
  - WiFi ulanishi
  - MQTT protokoli amalga oshirish
  - HiveMQ ochiq broker
  - Avtomatik qayta ulanish

- **💡 Jismoniy feedback**
  - O'rnatilgan LED indikatorlari
  - Miqdorga mos maxsus harakatlar
  - To'lovni vizual tasdiqlash
  - Uskuna trigerlar

### 📦 Konfiguratsiya

#### WiFi sozlamalari
```cpp
const char* ssid = "Sizning_WiFi_SSID";
const char* password = "Sizning_WiFi_Parol";
```

#### MQTT konfiguratsiyasi
```cpp
const char* mqtt_server = "broker.hivemq.com";
const char* mqtt_topic = "payments/sizning_merchant_id";
```

### 🚀 Foydalanish

#### LED indikatorlari
- **5000 miqdor**: LED YONIQ
- **10000 miqdor**: LED O'CHIQ
- **Sozlanishi mumkin**: O'z ehtiyojlaringizga moslang

#### Xabar formati
```json
{
  "status": "paid",
  "amount": 5000
}
```

---

## 👨‍💻 Author

**Temur Eshmurodov**

## 📄 License

This project is open source. Feel free to use and modify for your needs.

---

<div align="center">

**💳 Smart Payments Made Simple with ESP32! 💳**

</div>
