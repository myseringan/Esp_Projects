# PHOTO_TO_TFT_SHOW

## English

This project allows you to display a JPEG image on a TFT display connected to an ESP32‑based board (for example, the LilyGO T‑Connect Pro). It includes conversion of the image into a compatible format and example code built with PlatformIO.

### Features
- Converts a .jpg file into a format suitable for TFT display on ESP32.
- Example firmware project using PlatformIO.
- Works with common display libraries (e.g., TFT_eSPI).
- Easy to adapt for your own image and board configuration.

### Requirements
- ESP32‑based development board (e.g., LilyGO T‑Connect Pro)
- TFT display module supported by your board and library
- PlatformIO environment configured for your board
- A JPEG image you want to display

### Usage
1. Replace the `image.jpg` (or your own image) in the folder.
2. Run the conversion tool (if provided) or convert the image manually into the required format (e.g., C array, RAW bitmap).
3. Update the example code with your image data and screen pin/config settings.
4. Build and upload the firmware via PlatformIO to your board.
5. On startup, the image will be displayed on the screen.

---

## Русский

Этот проект позволяет отобразить JPEG‑изображение на TFT‑дисплее, подключённом к плате на базе ESP32 (например, LilyGO T‑Connect Pro). Включает конвертацию изображения в совместимый формат и пример прошивки на PlatformIO.

### Возможности
- Конвертация файла .jpg в формат, подходящий для вывода на TFT‑дисплей на ESP32.
- Пример проекта прошивки с использованием PlatformIO.
- Совместимость с распространёнными библиотеками дисплеев (например, TFT_eSPI).
- Легко адаптируется под своё изображение и конфигурацию платы.

### Требования
- Плата на базе ESP32 (например, LilyGO T‑Connect Pro)
- TFT‑дисплей, поддерживаемый вашей платой и библиотекой
- Среда PlatformIO, настроенная под вашу плату
- JPEG‑изображение, которое вы хотите отобразить

### Использование
1. Замените файл `image.jpg` (или вставьте своё изображение) в папке.
2. Запустите инструмент конвертации (если он есть) или вручную конвертируйте изображение в нужный формат (например, C‑массив, RAW‑bitmap).
3. Обновите пример кода, указав данные изображения и настройки экрана (пины, библиотеку).
4. Сборка и загрузка прошивки через PlatformIO на вашу плату.
5. При включении устройства изображение будет отображено на экране.

---

## Uzbek (Ўзбекча)

Ushbu loyiha ESP32 asosidagi plata (masalan, LilyGO T‑Connect Pro) bilan ulanilgan TFT displeyda JPEG tasvirni ko‘rsatishga imkon beradi. Unda rasmni mos formatga o‘tkazish va PlatformIO bilan tuzilgan namuna dastur mavjud.

### Xususiyatlari
- .jpg faylini ESP32 uchun TFT displeyga mos formatga o‘tkazish.
- PlatformIO bilan namuna firmware loyihasi.
- Ko‘p ishlatiladigan displey kutubxonalari bilan mos (masalan, TFT_eSPI).
- O‘z tasviringiz va plata sozlamalaringizga osongina moslashadi.

### Talablar
- ESP32 asosidagi rivojlantirish plata (masalan, LilyGO T‑Connect Pro)
- Sizning plata va kutubxonangiz tomonidan qo‘llab‑quvvatlanadigan TFT displey
- Sizning plata uchun sozlangan PlatformIO muhiti
- Ko‘rsatmoqchi bo‘lgan JPEG tasvir

### Foydalanish
1. Loyihada `image.jpg` (yoki sizning tasvir) faylini almashtiring.
2. Konvertatsiya asbobini ishga tushiring (agar mavjud bo‘lsa) yoki tasvirni zarur formatga (masalan C massiv, RAW bitmap) qo‘l bilan o‘tkazing.
3. Namuna kodini o‘zgartiring — tasvir ma’lumotlari va ekran sozlamalarini belgilang (pinlar, kutubxona).
4. PlatformIO orqali firmware’ni qurib, plataningizga joylang.
5. Qurilma yoqilganda, tasvir ekranda ko‘rinadi.

