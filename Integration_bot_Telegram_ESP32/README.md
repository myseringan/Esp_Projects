# 🌐 ESP32bot  
**Умное IoT-устройство для мониторинга расстояния с веб-интерфейсом Wi-Fi и HTTPS-отправкой данных**  
**Smart IoT distance monitor with Wi-Fi web interface and HTTPS data upload**  
**Wi-Fi veb interfeysi va HTTPS ma’lumot yuboruvchi masofani o‘lchovchi IoT qurilma**

---

## 🇷🇺 Описание проекта

**ESP32bot** — это автономное устройство на базе **ESP32**, которое измеряет расстояние при помощи ультразвукового датчика и отправляет данные на удалённый сервер по защищённому HTTPS-каналу.  
Для удобства предусмотрен **встроенный веб-интерфейс**, через который можно задать или изменить Wi-Fi-настройки, не перепрошивая микроконтроллер.

### ⚙️ Основные функции

- 📡 Измерение расстояния (ультразвуковой сенсор HC-SR04)  
- 🔐 Передача данных на HTTPS-сервер каждые 10 секунд  
- 🌐 Настройка Wi-Fi через встроенный веб-интерфейс  
- ♻️ Автоматическое восстановление соединения и перезагрузка при обрыве  
- 💾 Сохранение Wi-Fi-данных в энергонезависимой памяти (Preferences)  
- ⚙️ Поддержка двойного режима: STA + AP (одновременно клиент и точка доступа)

### 🧩 Используемое оборудование

| Компонент | Назначение |
|-----------|-------------|
| ESP32 | Основной микроконтроллер |
| HC-SR04 | Ультразвуковой датчик расстояния |
| Wi-Fi (встроенный) | Для связи с сервером и настройки |
| Питание 5 В / USB | Электропитание устройства |

### 🖥️ Веб-интерфейс

При первом запуске ESP32 создаёт сеть **ESP32-Config**.  
Подключись к ней и открой в браузере `192.168.4.1` — откроется страница для ввода SSID и пароля Wi-Fi.  
После сохранения устройство перезагрузится и подключится к заданной сети.

---

## 🇬🇧 Project Description

**ESP32bot** is an autonomous **ESP32-based IoT device** that measures distance using an ultrasonic sensor and uploads data securely via HTTPS to a remote server.  
It features a built-in **Wi-Fi setup web interface** that allows changing Wi-Fi credentials without reflashing.

### ⚙️ Features

- 📡 Distance measurement (HC-SR04 ultrasonic sensor)  
- 🔐 Sends data to HTTPS server every 10 s  
- 🌐 Built-in web interface for Wi-Fi configuration  
- ♻️ Auto reconnect and restart on Wi-Fi loss  
- 💾 Saves credentials using ESP32 Preferences API  
- ⚙️ Dual mode support: STA + AP simultaneously

### 🧩 Hardware Components

| Component | Purpose |
|-----------|----------|
| ESP32 | Main microcontroller |
| HC-SR04 | Ultrasonic distance sensor |
| Wi-Fi | Connectivity and configuration |
| Power supply | 5 V / USB source |

### 🖥️ Web Interface

On first boot, ESP32 starts an access point **ESP32-Config**.  
Connect to it and open `192.168.4.1` in your browser — you’ll see a form to enter Wi-Fi SSID and password.  
After saving, the device reboots and connects to your network.

---

## 🇺🇿 Loyihaning tavsifi

**ESP32bot** — bu **ESP32** mikrokontrolleri asosidagi mustaqil IoT qurilma bo‘lib, ultratovush sensoridan foydalangan holda masofani o‘lchaydi va ma’lumotlarni HTTPS orqali serverga yuboradi.  
Qurilmada **Wi-Fi sozlash uchun ichki veb interfeys** mavjud — shuning uchun Wi-Fi ma’lumotlarini qayta dasturlamasdan o‘zgartirish mumkin.

### ⚙️ Asosiy funksiyalar

- 📡 Masofani o‘lchash (HC-SR04 ultratovush sensori)  
- 🔐 Har 10 soniyada HTTPS orqali ma’lumot yuborish  
- 🌐 Wi-Fi sozlash uchun ichki veb interfeys  
- ♻️ Aloqa uzilganda avtomatik qayta ulanish va qayta yuklash  
- 💾 Wi-Fi ma’lumotlarini xotirada saqlash (Preferences)  
- ⚙️ Ikkita rejim: STA + AP (mijoz va nuqta bir vaqtning o‘zida)

### 🧩 Qurilma qismlari

| Qism | Maqsad |
|------|---------|
| ESP32 | Asosiy mikrokontroller |
| HC-SR04 | Ultratovush masofa sensori |
| Wi-Fi | Aloqa va sozlash |
| Quvvat manbai | 5 V / USB manba |

### 🖥️ Veb interfeys

Qurilma birinchi marta ishga tushganda **ESP32-Config** tarmog‘ini yaratadi.  
Unga ulanib, brauzerda `192.168.4.1` manzilini oching — Wi-Fi SSID va parolni kiritish oynasi paydo bo‘ladi.  
Sozlamalarni saqlagach, qurilma qayta yuklanadi va tarmoqqa ulanadi.

---

## 📡 API и сервер / API and Server / API va server

ESP32 отправляет HTTPS-POST-запрос на указанный сервер:
```cpp
String server_ip = "ip твоего сервера";
int server_port = 443;
