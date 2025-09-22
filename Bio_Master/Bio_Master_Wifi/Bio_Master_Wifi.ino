#define BLYNK_TEMPLATE_ID "TMPL6-Qhz9qFz"
#define BLYNK_TEMPLATE_NAME "Bio Master"

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <SoftwareSerial.h>
#include <DNSServer.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = "b-4atMkevFd_1iP5NTRkZr1t_zIO4iS0";

const byte DNS_PORT = 53;
DNSServer dnsServer;
const char *ssid = "Bio Master";
const char *password = "samurai2023";
float val;

int rele;
int ldr;

ESP8266WebServer server(80);

SoftwareSerial arduinoSerial(D2, D3);

const char* loginPage = R"(
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>WiFi Biomaster</title>
    <link rel="stylesheet" href="wfibio.css">
    <style>
        body {
            margin: 0;
            padding: 0;
            font-family: sans-serif;
            background: linear-gradient(#000000, #000000);
        }

        .login-box {
            width: 80%;
            max-width: 400px;
            margin: auto;
            position: absolute;
            top: 50%;
            left: 50%;
            transform: translate(-50%, -50%);
            padding: 40px;
            background: rgba(0, 0, 0, .5);
            box-sizing: border-box;
            box-shadow: 0 15px 25px rgba(0, 0, 0, .6);
            border-radius: 10px;
        }

        .login-box h2 {
            margin: 0 0 30px;
            padding: 0;
            color: #fff;
            text-align: center;
        }

        .user-box {
            position: relative;
            margin-bottom: 30px;
        }

        .user-box input {
            width: 100%;
            padding: 10px 0;
            font-size: 16px;
            color: #fff;
            border: none;
            border-bottom: 1px solid #fff;
            outline: none;
            background: transparent;
        }

        .user-box label {
            position: absolute;
            top: 0;
            left: 0;
            padding: 10px 0;
            font-size: 16px;
            color: #fff;
            pointer-events: none;
            transition: .5s;
        }

        .user-box input:focus~label,
        .user-box input:valid~label {
            top: -20px;
            left: 0;
            color: #03f417;
            font-size: 12px;
        }

        input[type="submit"] {
            position: relative;
            display: inline-block;
            padding: 10px 20px;
            color: #28de32;
            font-size: 16px;
            text-decoration: none;
            text-transform: uppercase;
            overflow: hidden;
            transition: .5s;
            margin-top: 40px;
            letter-spacing: 4px;
            cursor: pointer;
            background: none;
            border: 2px solid #28de32;
            border-radius: 5px;
        }

        input[type="submit"]:hover {
            background: #28de32;
            color: #fff;
        }

        @media only screen and (min-width: 768px) {
            .login-box {
                width: 400px;
            }
        }
    </style>
</head>
<body>
    <div class="login-box">
        <h2>Настройка Wi-Fi</h2>
        <form action="/save" method="post">
            <div class="user-box">
                <input type="text" name="ssid" required="">
                <label>SSID</label>
            </div>
            <div class="user-box">
                <input type="password" name="password" required="">
                <label>Password</label>
            </div>
            <input type="submit" value="Сохранить">
        </form>
    </div>
</body>
</html>
)";

void handleRoot() {
  server.send(200, "text/html", loginPage);
}

void handleSave() {
  String ssidValue = server.arg("ssid");
  String passwordValue = server.arg("password");

  // Попытка подключения к новой Wi-Fi-сети
  WiFi.begin(ssidValue.c_str(), passwordValue.c_str());

  String waitingMessage = R"(
    <html>
    <head>
     <meta charset="UTF-8">
      <style>
        body {
          margin: 50px;
          padding: 100px;
          font-family: sans-serif;
          background: linear-gradient(#ffffff, #ffffff);
        }

        h1 {
          color: #000000;
          text-align: center;
        }

        .spinner {
          display: flex;
          justify-content: center;
          align-items: center;
        }

        .lds-ring {
          display: inline-block;
          position: relative;
          width: 80px;
          height: 80px;
        }

        .lds-ring div {
          box-sizing: border-box;
          display: block;
          position: absolute;
          width: 64px;
          height: 64px;
          margin: 8px;
          border: 8px solid #0000007f;
          border-radius: 50%;
          animation: lds-ring 1.2s cubic-bezier(0.5, 0, 0.5, 1) infinite;
          border-color: #0000007f transparent transparent transparent;
        }

        @keyframes lds-ring {
          0% {
            transform: rotate(0deg);
          }
          100% {
            transform: rotate(360deg);
          }
        }
      </style>
    </head>
    <body>
      <h1>Подключение к Wi-Fi...</h1>
      <div class="spinner">
        <div class="lds-ring"><div></div><div></div><div></div><div></div></div>
      </div>

      <script>
        setTimeout(function() {
          document.location.href = "/result";
        }, 7000); // Перенаправляем на страницу результата через 30 секунд
      </script>
    </body>
    </html>
  )";
  server.send(200, "text/html", waitingMessage);
}
void handleResult() {
  String message;

  if (WiFi.status() == WL_CONNECTED) {
    message = R"(
      <html>
      <head>
       <meta charset="UTF-8">
        <style>
          body {
            margin: 50px;
            padding: 100px;
            font-family: sans-serif;
            background: linear-gradient(#ffffff, #ffffff);
          }

          h1 {
            color: #000000;
            text-align: center;
          }

          .fa-check-circle {
            font-size: 150px; /* Увеличил размер символа check */
            display: flex;
            justify-content: center;
            align-items: center;
            text-align: center;
            color: #ffffff;
            border-radius: 50%;
            background-color: #2bff00;
            width: 200px;
            height: 200px;
            margin: auto;
            margin-top: 20px;
          }
        </style>
      </head>
      <body>
        <h1>Подключено к Wi-Fi</h1>
        <div class="fa-check-circle">&#10003;</div>
      </body>
      </html>
    )";
    server.send(200, "text/html", message);
    delay(3000);
    WiFi.softAPdisconnect(true);
  } else {
    message = R"(
      <html>
      <head>
       <meta charset="UTF-8">
        <style>
          body {
            margin: 50px;
            padding: 100px;
            font-family: sans-serif;
            background: linear-gradient(#ffffff, #ffffff);
          }

          h1 {
            color: #000000;
            text-align: center;
          }

          .fa-times-circle {
            font-size: 150px; /* Увеличил размер символа cross */
            display: flex;
            justify-content: center;
            align-items: center;
            text-align: center;
            color: #ffffff;
            border-radius: 50%;
            background-color: #ff0000;
            width: 200px;
            height: 200px;
            margin: auto;
            margin-top: 20px;
          }
        </style>
      </head>
      <body>
        <h1>Не удалось подключиться к Wi-Fi. Проверьте учетные данные.</h1>
        <div class="fa-times-circle">&#10007;</div>
      </body>
      </html>
    )";
  }

  server.send(200, "text/html", message);
}
BLYNK_WRITE (V4) {
  rele = param.asInt();
  char datarele = 'R';
  arduinoSerial.write(datarele);
  arduinoSerial.print(rele);
}
BLYNK_WRITE (V5) {
  ldr = param.asInt();
  char dataldr = 'L';
  arduinoSerial.write(dataldr);
  arduinoSerial.print(ldr);
}

void setup() {
  Serial.begin(115200);
  arduinoSerial.begin(9600);
  
  WiFi.softAP(ssid, password);
  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);
  dnsServer.start(DNS_PORT, "*", WiFi.softAPIP());
  server.onNotFound(handleRoot);
  server.on("/save", HTTP_POST, handleSave); // Добавляем обработчик для "/save"
  server.on("/result", HTTP_GET, handleResult);
  server.begin();
  Blynk.config(auth);
}

void loop() {
  dnsServer.processNextRequest();
  server.handleClient();
  Blynk.run();
  if (arduinoSerial.available() > 0) {
    char data1 = arduinoSerial.read();
    val = arduinoSerial.parseFloat();
    switch (data1) {
      case 'T': Serial.print(val);Serial.println("°C");Blynk.virtualWrite(V1, val);
      break;
      case 'H': Serial.print(val);Serial.println("%");Blynk.virtualWrite(V2, val);
      break;
      case 'S': Serial.print(val);Serial.println("%");Blynk.virtualWrite(V3, val);
      break;
      case 'I': Blynk.virtualWrite(V6, val);
      break;
    }
  }
}
