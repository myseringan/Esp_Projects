# Megaphone Player

ESP32-P4 Audio Server for industrial alert systems.

---

## 🇬🇧 English

### Description
Megaphone Player is a network audio player based on ESP32-P4. It receives audio via HTTP API and plays it through a speaker. Audio files are stored in flash memory and persist after reboot.

### Features
- ✅ Ethernet connection (RJ-45)
- ✅ Persistent audio storage (13 MB flash)
- ✅ Hash-based caching (no re-upload if unchanged)
- ✅ HTTP REST API
- ✅ PCM audio playback (44100 Hz, 16-bit, stereo)

### API Endpoints

| Endpoint | Method | Description |
|----------|--------|-------------|
| `/health` | GET | Get device status |
| `/update-audio` | POST | Upload audio file |
| `/play-message` | POST | Play stored audio |
| `/check-audio` | POST | Check if audio exists |

### Upload Audio

```bash
curl -X POST http://<IP>:1820/update-audio \
  -H "Content-Type: application/octet-stream" \
  -H "X-Message-Text: alert_message" \
  -H "X-Audio-Hash: abc123" \
  --data-binary @audio.raw
```

### Play Audio

```bash
curl -X POST http://<IP>:1820/play-message \
  -H "Content-Type: application/json" \
  -d '{"message_text": "alert_message", "audio_hash": "abc123"}'
```

### Check Audio Exists

```bash
curl -X POST http://<IP>:1820/check-audio \
  -H "Content-Type: application/json" \
  -d '{"message_text": "alert_message", "audio_hash": "abc123"}'
```

Response: `{"exists": true}` or `{"exists": false}`

### Python Client

```bash
python send_audio.py output.wav
```

---

## 🇷🇺 Русский

### Описание
Megaphone Player — сетевой аудиоплеер на базе ESP32-P4. Получает аудио по HTTP API и воспроизводит через динамик. Аудиофайлы хранятся во flash-памяти и сохраняются после перезагрузки.

### Возможности
- ✅ Подключение по Ethernet (RJ-45)
- ✅ Постоянное хранение аудио (13 МБ flash)
- ✅ Кэширование по hash (повторная загрузка не требуется)
- ✅ HTTP REST API
- ✅ Воспроизведение PCM (44100 Гц, 16-бит, стерео)

### API Endpoints

| Endpoint | Метод | Описание |
|----------|-------|----------|
| `/health` | GET | Статус устройства |
| `/update-audio` | POST | Загрузка аудио |
| `/play-message` | POST | Воспроизведение |
| `/check-audio` | POST | Проверка наличия |

### Загрузка аудио

```bash
curl -X POST http://<IP>:1820/update-audio \
  -H "Content-Type: application/octet-stream" \
  -H "X-Message-Text: сообщение" \
  -H "X-Audio-Hash: abc123" \
  --data-binary @audio.raw
```

### Воспроизведение

```bash
curl -X POST http://<IP>:1820/play-message \
  -H "Content-Type: application/json" \
  -d '{"message_text": "сообщение", "audio_hash": "abc123"}'
```

### Проверка наличия

```bash
curl -X POST http://<IP>:1820/check-audio \
  -H "Content-Type: application/json" \
  -d '{"message_text": "сообщение", "audio_hash": "abc123"}'
```

Ответ: `{"exists": true}` или `{"exists": false}`

### Python клиент

```bash
python send_audio.py output.wav
```

---

## 🇺🇿 O'zbekcha

### Tavsif
Megaphone Player — ESP32-P4 asosidagi tarmoq audio pleyeri. HTTP API orqali audio qabul qiladi va karnay orqali ijro etadi. Audio fayllar flash xotirada saqlanadi va qayta yuklashdan keyin ham saqlanib qoladi.

### Imkoniyatlar
- ✅ Ethernet ulanishi (RJ-45)
- ✅ Doimiy audio saqlash (13 MB flash)
- ✅ Hash asosida keshlash (o'zgarishsiz qayta yuklash kerak emas)
- ✅ HTTP REST API
- ✅ PCM audio ijrosi (44100 Hz, 16-bit, stereo)

### API Endpoints

| Endpoint | Metod | Tavsif |
|----------|-------|--------|
| `/health` | GET | Qurilma holati |
| `/update-audio` | POST | Audio yuklash |
| `/play-message` | POST | Ijro etish |
| `/check-audio` | POST | Mavjudligini tekshirish |

### Audio yuklash

```bash
curl -X POST http://<IP>:1820/update-audio \
  -H "Content-Type: application/octet-stream" \
  -H "X-Message-Text: xabar" \
  -H "X-Audio-Hash: abc123" \
  --data-binary @audio.raw
```

### Ijro etish

```bash
curl -X POST http://<IP>:1820/play-message \
  -H "Content-Type: application/json" \
  -d '{"message_text": "xabar", "audio_hash": "abc123"}'
```

### Mavjudligini tekshirish

```bash
curl -X POST http://<IP>:1820/check-audio \
  -H "Content-Type: application/json" \
  -d '{"message_text": "xabar", "audio_hash": "abc123"}'
```

Javob: `{"exists": true}` yoki `{"exists": false}`

### Python mijoz

```bash
python send_audio.py output.wav
```

---

## Hardware

- **Board:** ESP32-P4-WIFI6-DEV-KIT (Waveshare)
- **Audio Codec:** ES8311
- **Connection:** Ethernet (RJ-45)
- **Storage:** 13 MB LittleFS

## Build

```bash
idf.py set-target esp32p4
idf.py build
idf.py -p COM3 flash monitor
```

## License

MIT License
