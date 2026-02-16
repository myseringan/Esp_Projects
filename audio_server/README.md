# 📢 Megaphone Player

**Саноат аудио огоҳлантириш тизими | Industrial Audio Alert System | Промышленная система звукового оповещения**

[![ESP32-P4](https://img.shields.io/badge/ESP32--P4-000000?style=flat&logo=espressif&logoColor=white)](https://www.espressif.com/)
[![ESP-IDF](https://img.shields.io/badge/ESP--IDF-v5.3+-red?style=flat&logo=espressif&logoColor=white)](https://docs.espressif.com/projects/esp-idf/)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)

**Тил танланг | Choose language | Выберите язык:**

[🇺🇿 O'zbekcha](#-ozbekcha) • [🇬🇧 English](#-english) • [🇷🇺 Русский](#-русский)

---

# 🇺🇿 O'zbekcha

## 📋 Тавсиф

Megaphone Player — HTTP API орқали аудио қабул қилувчи ва ижро этувчи тармоқ аудио плеер. Саноат объектларида огоҳлантириш тизимлари учун мўлжалланган.

## ✨ Хусусиятлар

| Хусусият | Тавсиф |
|----------|--------|
| 🌐 Ethernet | RJ-45 тармоқ уланиши |
| 💾 Flash хотира | 13 MB доимий сақлаш |
| 🔄 Hash кеширлаш | Ўзгармаган аудио қайта юкланмайди |
| 🎵 PCM аудио | 44100 Hz, 16-bit, stereo |
| 📡 REST API | HTTP орқали бошқарув |

## 🔧 Компонентлар

| Компонент | Функция |
|-----------|---------|
| ESP32-P4 | Асосий контроллер |
| ES8311 | Аудио кодек |
| Ethernet RJ-45 | Тармоқ уланиши |
| LittleFS | Флеш файл тизими |

## 📡 API Endpoints

| Endpoint | Метод | Тавсиф |
|----------|-------|--------|
| `/health` | GET | Қурилма ҳолати |
| `/update-audio` | POST | Аудио юклаш (binary) |
| `/play-message` | POST | Сақланган аудиони ижро этиш |
| `/check-audio` | POST | Мавжудликни текшириш |

### GET /health

Қурилма ҳолатини қайтаради.

**Жавоб:**
```json
{
  "megaphone_version": "1.0.0"
}
```

### POST /update-audio

Аудио файлни юклайди.

**Headers:**
| Header | Тавсиф |
|--------|--------|
| `Content-Type` | `application/octet-stream` |
| `X-Message-Text` | Хабар матни (калит) |
| `X-Audio-Hash` | Аудио hash (версия) |

**Body:** Raw PCM bytes (44100 Hz, 16-bit, stereo)

**Мисол:**
```bash
curl -X POST http://192.168.1.100:1820/update-audio \
  -H "Content-Type: application/octet-stream" \
  -H "X-Message-Text: ogohlantirish" \
  -H "X-Audio-Hash: abc123def456" \
  --data-binary @audio.raw
```

### POST /play-message

Сақланган аудиони ижро этади.

**Body:**
```json
{
  "message_text": "ogohlantirish",
  "audio_hash": "abc123def456"
}
```

**Мисол:**
```bash
curl -X POST http://192.168.1.100:1820/play-message \
  -H "Content-Type: application/json" \
  -d '{"message_text": "ogohlantirish", "audio_hash": "abc123def456"}'
```

### POST /check-audio

Аудио мавжудлигини текширади.

**Body:**
```json
{
  "message_text": "ogohlantirish",
  "audio_hash": "abc123def456"
}
```

**Жавоб:**
```json
{
  "exists": true
}
```

## 🛠️ Ўрнатиш

### Талаблар
- [ESP-IDF v5.3+](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/get-started/)
- ESP32-P4-WIFI6-DEV-KIT (Waveshare)

### Қурилиш

```bash
# Репозиторияни клонлаш
git clone https://github.com/myseringan/Esp_Projects.git
cd Esp_Projects/Megaphone_Player

# Мақсадни танлаш
idf.py set-target esp32p4

# Қурилиш
idf.py build

# Флешлаш
idf.py -p COM3 flash monitor
```

### Конфигурация

`menuconfig` орқали созлаш:
```bash
idf.py menuconfig
```

| Параметр | Стандарт | Тавсиф |
|----------|----------|--------|
| Server Port | 1820 | HTTP сервер порти |
| Use DHCP | Yes | Автоматик IP олиш |
| Static IP | 192.168.1.100 | Статик IP (DHCP ўчиқ бўлса) |
| Audio Volume | 90 | Товуш баландлиги (0-100) |

## 📁 Проект структураси

```
Megaphone_Player/
├── main/
│   ├── main.c              # Асосий дастур
│   ├── http_server.c       # HTTP сервер
│   ├── http_server.h
│   ├── audio_player.c      # Аудио ижро
│   ├── audio_player.h
│   ├── audio_storage.c     # Flash сақлаш
│   ├── audio_storage.h
│   ├── ethernet.c          # Ethernet драйвер
│   ├── ethernet.h
│   ├── Kconfig.projbuild   # Menuconfig
│   ├── CMakeLists.txt
│   └── idf_component.yml
├── CMakeLists.txt
├── sdkconfig.defaults
├── partitions.csv
└── README.md
```

## 🐍 Python клиент

```bash
python send_audio.py output.wav
```

**Хусусиятлар:**
- WAV → PCM автоматик конвертация
- Hash бўйича кеширлаш
- Мавжудликни текшириш

---

# 🇬🇧 English

## 📋 Description

Megaphone Player is a network audio player that receives and plays audio via HTTP API. Designed for industrial alert systems.

## ✨ Features

| Feature | Description |
|---------|-------------|
| 🌐 Ethernet | RJ-45 network connection |
| 💾 Flash storage | 13 MB persistent storage |
| 🔄 Hash caching | Unchanged audio won't re-upload |
| 🎵 PCM audio | 44100 Hz, 16-bit, stereo |
| 📡 REST API | HTTP-based control |

## 🔧 Components

| Component | Function |
|-----------|----------|
| ESP32-P4 | Main controller |
| ES8311 | Audio codec |
| Ethernet RJ-45 | Network connection |
| LittleFS | Flash file system |

## 📡 API Endpoints

| Endpoint | Method | Description |
|----------|--------|-------------|
| `/health` | GET | Device status |
| `/update-audio` | POST | Upload audio (binary) |
| `/play-message` | POST | Play stored audio |
| `/check-audio` | POST | Check if exists |

### GET /health

Returns device status.

**Response:**
```json
{
  "megaphone_version": "1.0.0"
}
```

### POST /update-audio

Uploads audio file.

**Headers:**
| Header | Description |
|--------|-------------|
| `Content-Type` | `application/octet-stream` |
| `X-Message-Text` | Message text (key) |
| `X-Audio-Hash` | Audio hash (version) |

**Body:** Raw PCM bytes (44100 Hz, 16-bit, stereo)

**Example:**
```bash
curl -X POST http://192.168.1.100:1820/update-audio \
  -H "Content-Type: application/octet-stream" \
  -H "X-Message-Text: alert_message" \
  -H "X-Audio-Hash: abc123def456" \
  --data-binary @audio.raw
```

### POST /play-message

Plays stored audio.

**Body:**
```json
{
  "message_text": "alert_message",
  "audio_hash": "abc123def456"
}
```

**Example:**
```bash
curl -X POST http://192.168.1.100:1820/play-message \
  -H "Content-Type: application/json" \
  -d '{"message_text": "alert_message", "audio_hash": "abc123def456"}'
```

### POST /check-audio

Checks if audio exists.

**Body:**
```json
{
  "message_text": "alert_message",
  "audio_hash": "abc123def456"
}
```

**Response:**
```json
{
  "exists": true
}
```

## 🛠️ Installation

### Requirements
- [ESP-IDF v5.3+](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/get-started/)
- ESP32-P4-WIFI6-DEV-KIT (Waveshare)

### Build

```bash
# Clone repository
git clone https://github.com/myseringan/Esp_Projects.git
cd Esp_Projects/Megaphone_Player

# Set target
idf.py set-target esp32p4

# Build
idf.py build

# Flash
idf.py -p COM3 flash monitor
```

### Configuration

Configure via `menuconfig`:
```bash
idf.py menuconfig
```

| Parameter | Default | Description |
|-----------|---------|-------------|
| Server Port | 1820 | HTTP server port |
| Use DHCP | Yes | Auto IP assignment |
| Static IP | 192.168.1.100 | Static IP (if DHCP off) |
| Audio Volume | 90 | Volume level (0-100) |

## 📁 Project Structure

```
Megaphone_Player/
├── main/
│   ├── main.c              # Main application
│   ├── http_server.c       # HTTP server
│   ├── http_server.h
│   ├── audio_player.c      # Audio playback
│   ├── audio_player.h
│   ├── audio_storage.c     # Flash storage
│   ├── audio_storage.h
│   ├── ethernet.c          # Ethernet driver
│   ├── ethernet.h
│   ├── Kconfig.projbuild   # Menuconfig
│   ├── CMakeLists.txt
│   └── idf_component.yml
├── CMakeLists.txt
├── sdkconfig.defaults
├── partitions.csv
└── README.md
```

## 🐍 Python Client

```bash
python send_audio.py output.wav
```

**Features:**
- WAV → PCM auto conversion
- Hash-based caching
- Existence checking

---

# 🇷🇺 Русский

## 📋 Описание

Megaphone Player — сетевой аудио плеер, принимающий и воспроизводящий аудио через HTTP API. Предназначен для промышленных систем оповещения.

## ✨ Особенности

| Особенность | Описание |
|-------------|----------|
| 🌐 Ethernet | Сетевое подключение RJ-45 |
| 💾 Flash хранилище | 13 MB постоянного хранения |
| 🔄 Hash кеширование | Неизменённое аудио не перезагружается |
| 🎵 PCM аудио | 44100 Hz, 16-bit, stereo |
| 📡 REST API | Управление по HTTP |

## 🔧 Компоненты

| Компонент | Функция |
|-----------|---------|
| ESP32-P4 | Основной контроллер |
| ES8311 | Аудио кодек |
| Ethernet RJ-45 | Сетевое подключение |
| LittleFS | Flash файловая система |

## 📡 API Endpoints

| Endpoint | Метод | Описание |
|----------|-------|----------|
| `/health` | GET | Статус устройства |
| `/update-audio` | POST | Загрузка аудио (binary) |
| `/play-message` | POST | Воспроизведение |
| `/check-audio` | POST | Проверка наличия |

### GET /health

Возвращает статус устройства.

**Ответ:**
```json
{
  "megaphone_version": "1.0.0"
}
```

### POST /update-audio

Загружает аудио файл.

**Headers:**
| Header | Описание |
|--------|----------|
| `Content-Type` | `application/octet-stream` |
| `X-Message-Text` | Текст сообщения (ключ) |
| `X-Audio-Hash` | Hash аудио (версия) |

**Body:** Raw PCM bytes (44100 Hz, 16-bit, stereo)

**Пример:**
```bash
curl -X POST http://192.168.1.100:1820/update-audio \
  -H "Content-Type: application/octet-stream" \
  -H "X-Message-Text: оповещение" \
  -H "X-Audio-Hash: abc123def456" \
  --data-binary @audio.raw
```

### POST /play-message

Воспроизводит сохранённое аудио.

**Body:**
```json
{
  "message_text": "оповещение",
  "audio_hash": "abc123def456"
}
```

**Пример:**
```bash
curl -X POST http://192.168.1.100:1820/play-message \
  -H "Content-Type: application/json" \
  -d '{"message_text": "оповещение", "audio_hash": "abc123def456"}'
```

### POST /check-audio

Проверяет наличие аудио.

**Body:**
```json
{
  "message_text": "оповещение",
  "audio_hash": "abc123def456"
}
```

**Ответ:**
```json
{
  "exists": true
}
```

## 🛠️ Установка

### Требования
- [ESP-IDF v5.3+](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/get-started/)
- ESP32-P4-WIFI6-DEV-KIT (Waveshare)

### Сборка

```bash
# Клонирование репозитория
git clone https://github.com/myseringan/Esp_Projects.git
cd Esp_Projects/Megaphone_Player

# Выбор цели
idf.py set-target esp32p4

# Сборка
idf.py build

# Прошивка
idf.py -p COM3 flash monitor
```

### Конфигурация

Настройка через `menuconfig`:
```bash
idf.py menuconfig
```

| Параметр | По умолчанию | Описание |
|----------|--------------|----------|
| Server Port | 1820 | Порт HTTP сервера |
| Use DHCP | Yes | Автоматическое получение IP |
| Static IP | 192.168.1.100 | Статический IP (если DHCP выкл) |
| Audio Volume | 90 | Громкость (0-100) |

## 📁 Структура проекта

```
Megaphone_Player/
├── main/
│   ├── main.c              # Основное приложение
│   ├── http_server.c       # HTTP сервер
│   ├── http_server.h
│   ├── audio_player.c      # Воспроизведение
│   ├── audio_player.h
│   ├── audio_storage.c     # Flash хранилище
│   ├── audio_storage.h
│   ├── ethernet.c          # Ethernet драйвер
│   ├── ethernet.h
│   ├── Kconfig.projbuild   # Menuconfig
│   ├── CMakeLists.txt
│   └── idf_component.yml
├── CMakeLists.txt
├── sdkconfig.defaults
├── partitions.csv
└── README.md
```

## 🐍 Python клиент

```bash
python send_audio.py output.wav
```

**Возможности:**
- WAV → PCM автоконвертация
- Кеширование по hash
- Проверка наличия

---

## 📄 Лицензия | License | Лицензия

MIT License

---

## 👤 Муаллиф | Author | Автор

**myseringan**

[![GitHub](https://img.shields.io/badge/GitHub-myseringan-181717?style=flat&logo=github)](https://github.com/myseringan)
