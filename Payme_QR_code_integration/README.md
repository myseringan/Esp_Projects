Payme QR ESP32

ESP32 устройство для приёма уведомлений о платежах Payme через QR-коды
ESP32 device for receiving Payme QR payment notifications
ESP32 qurilmasi Payme QR to‘lovlaridan xabarlarni qabul qilish uchun

🇷🇺 Описание проекта

Payme QR ESP32 — это устройство на базе ESP32, которое получает данные о платежах, совершённых через Payme QR-коды.
После оплаты в Serial Monitor выводится статус платежа и сумма.

🇬🇧 Project Description

Payme QR ESP32 is an ESP32-based device that receives notifications about payments made via Payme QR codes.
After a payment, the payment status and amount are displayed in the Serial Monitor.

🇺🇿 Loyihaning tavsifi

Payme QR ESP32 — bu ESP32 mikrokontrolleriga asoslangan qurilma bo‘lib, Payme QR to‘lovlari haqida xabarlarni qabul qiladi.
To‘lov amalga oshirilgach, Serial Monitor’da holat va summa ko‘rsatiladi.

⚙️ Основные функции / Features / Asosiy funksiyalar

📡 Приём уведомлений о платежах Payme QR
🔐 Отображение статуса платежа в Serial Monitor
💰 Отображение суммы оплаты
♻️ Автоматическое подключение к Wi-Fi при перезагрузке

📡 Receive Payme QR payment notifications
🔐 Display payment status in Serial Monitor
💰 Display payment amount
♻️ Automatic Wi-Fi connection on reboot

📡 Payme QR to‘lov xabarlarini qabul qilish
🔐 Serial Monitor’da to‘lov holatini ko‘rsatish
💰 To‘lov summasini ko‘rsatish
♻️ Qayta yuklashda Wi-Fi ga avtomatik ulanadi

🧩 Используемое оборудование / Hardware Components / Qurilma qismlari
Компонент / Component / Qism	Назначение / Purpose / Maqsad
ESP32	Основной микроконтроллер / Main microcontroller / Asosiy mikrokontroller
Wi-Fi (встроенный)	Подключение к сети для приёма уведомлений / Wi-Fi connectivity / Tarmoqqa ulanish
Питание 5V / USB	Электропитание устройства / Power supply / Quvvat manbai
🖥️ Настройка и использование / Setup and Usage / Sozlash va foydalanish

Клонируем репозиторий / Clone repository / Repositni klonlash:

git clone https://github.com/myseringan/Esp_Projects.git
cd Esp_Projects/Payme_QR_code_integration


Открываем Payme_QR_Code.ino в Arduino IDE / Open Payme_QR_Code.ino in Arduino IDE / Payme_QR_Code.ino faylini Arduino IDE’da oching

Настраиваем Wi-Fi / Set Wi-Fi / Wi-Fi sozlash:

const char* ssid = "your_SSID";
const char* password = "your_PASSWORD";


Загружаем скетч на ESP32 / Upload sketch to ESP32 / Sketchni ESP32 ga yuklash

Открываем Serial Monitor / Open Serial Monitor / Serial Monitor’ni oching

После оплаты через Payme QR в Serial Monitor появятся статус платежа и сумма / Payment status and amount will appear after Payme QR payment / Payme QR to‘lovidan so‘ng holat va summa Serial Monitor’da ko‘rsatiladi

📄 Лицензия / License / Litsenziya

MIT License. Подробности в файле LICENSE / MIT License. See LICENSE file / MIT Litsenziyasi. Batafsil LICENSE faylida.
