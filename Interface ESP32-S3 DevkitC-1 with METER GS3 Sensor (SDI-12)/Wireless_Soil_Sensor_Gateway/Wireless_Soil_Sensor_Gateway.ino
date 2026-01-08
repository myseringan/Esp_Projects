#include <SDI12.h>
#include "esp_sleep.h"

const int ENERGY_SAVING = 8;
SDI12 SDI12_pin1 (15);
SDI12 SDI12_pin2 (16);
SDI12 SDI12_pin3 (17);
SDI12 SDI12_pin4 (18);

SDI12* SDI12_data[4] = {
  &SDI12_pin1,
  &SDI12_pin2,
  &SDI12_pin3,
  &SDI12_pin4
};

const char sensor_address[4] = {'1', '2', '3', '4'};

const unsigned long MEAS_CYCLE_INTERVAL_MS = 1200000UL; // если не используем deep sleep, интервал между циклами (ms)
const unsigned long WAKE_DELAY_MS = 2000UL;            // время на пробуждение питания датчиков (ms)
const unsigned long RESPONSE_TIMEOUT_MS = 5000UL;      // таймаут на ответ от шины (ms)
const unsigned long READ_TIMEOUT_MS = 5000UL;          // таймаут чтения данных после D0! (ms)

const bool USE_DEEP_SLEEP = true;      // если true — ESP уходит в deep sleep после цикла
const unsigned long DEEP_SLEEP_TIME_SEC = 3600UL; // время сна в секундах

enum State {
  IDLE,
  WAKE_SENSORS,
  WAIT_WAKE,
  SEND_MEASUREMENT,
  WAIT_MEASUREMENT,
  READ_DATA,
  FINISH_CYCLE
};

State state = IDLE;
unsigned long stateTimer = 0;
unsigned long lastCycleMillis = 0;
int currentSensorIndex = 0;
int measurementWaitSec = 0;
int valuesCount = 0;

void setup() {
  Serial.begin(115200);
  delay(100);
  pinMode(ENERGY_SAVING, OUTPUT);
  digitalWrite(ENERGY_SAVING, HIGH);
  for (int i = 0; i < 4; ++i) {
    SDI12_data[i]->begin();
  }

  lastCycleMillis = millis();
  state = IDLE;

  Serial.println();
  Serial.println("SDI-12 ESP32: launch.");
  if (USE_DEEP_SLEEP) {
    Serial.println("Mode: deep sleep is on.");
  } else {
    Serial.println("Mode: deep sleep disabled, using periodic polling.");
  }
}

String readFromBusWithTimeout(SDI12* bus, unsigned long timeoutMs) {
  unsigned long start = millis();
  String accum = "";
  while (millis() - start < timeoutMs) {
    String s = bus->readString();
    if (s.length() > 0) {
      accum += s;
      if (accum.indexOf('\n') >= 0 || accum.indexOf('\r') >= 0) break;
    }
    delay(50);
  }
  accum.trim();
  return accum;
}

void loop() {
  unsigned long now = millis();

  switch (state) {

    case IDLE:
      if (USE_DEEP_SLEEP) {
        Serial.println("Ready for a new cycle (will use deep sleep after completion).");
        state = WAKE_SENSORS;
      } else {
        if (now - lastCycleMillis >= MEAS_CYCLE_INTERVAL_MS) {
          Serial.println("The interval has expired - we begin the measurement cycle.");
          state = WAKE_SENSORS;
        }
      }
      break;

    case WAKE_SENSORS:
      Serial.println("Turning on the power to the sensors (ENERGY_SAVING LOW)...");
      digitalWrite(ENERGY_SAVING, LOW);
      stateTimer = now;
      state = WAIT_WAKE;
      break;

    case WAIT_WAKE:
      if (now - stateTimer >= WAKE_DELAY_MS) {
        Serial.println("The sensors are powered, I start sending measurement commands one by one.");
        currentSensorIndex = 0;
        state = SEND_MEASUREMENT;
      }
      break;

    case SEND_MEASUREMENT: {
      if (currentSensorIndex >= (int)(sizeof(SDI12_data)/sizeof(SDI12_data[0]))) {
        state = FINISH_CYCLE;
        break;
      }

      SDI12* bus = SDI12_data[currentSensorIndex];
      char addr = sensor_address[currentSensorIndex];

      Serial.print("-> Sensor ");
      Serial.print(currentSensorIndex);
      Serial.print(" (addr ");
      Serial.print(addr);
      Serial.println("): sending M! ...");

      String cmd = String(addr) + "M!";
      bus->sendCommand(cmd);

      String resp = readFromBusWithTimeout(bus, RESPONSE_TIMEOUT_MS);

      if (resp.length() == 0) {
        Serial.println("   Error: No response to M! (timeout). Skipping sensor.");
        currentSensorIndex++;
      } else {
        Serial.print("   Answer: '");
        Serial.print(resp);
        Serial.println("'");
        String clean = resp;
        clean.trim();
        if (clean.length() >= 5 && isDigit(clean.charAt(1)) && isDigit(clean.charAt(2)) && isDigit(clean.charAt(3))) {
          measurementWaitSec = clean.substring(1, 4).toInt();
          if (clean.length() > 4 && isDigit(clean.charAt(4))) {
            valuesCount = clean.substring(4, 5).toInt();
          } else {
            valuesCount = 0;
          }
          Serial.print("   The sensor asks you to wait ");
          Serial.print(measurementWaitSec);
          Serial.println(" sec.");
          stateTimer = now;
          state = WAIT_MEASUREMENT;
        } else {
          Serial.println("   Incorrect response format for M!. Skipping the sensor.");
          currentSensorIndex++;
        }
      }
      break;
    }

    case WAIT_MEASUREMENT:
      if ((unsigned long)(now - stateTimer) >= (unsigned long)measurementWaitSec * 1000UL) {
        state = READ_DATA;
      }
      break;

    case READ_DATA: {
      SDI12* bus = SDI12_data[currentSensorIndex];
      char addr = sensor_address[currentSensorIndex];
      String cmd = String(addr) + "D0!";
      Serial.print("-> Requesting data:");
      Serial.println(cmd);
      bus->sendCommand(cmd);

      // Сразу читаем; даём больший таймаут на передачу значений
      String resp = readFromBusWithTimeout(bus, READ_TIMEOUT_MS);

      if (resp.length() > 0) {
        Serial.print("   Data received: ");
        Serial.println(resp);
      } else {
        Serial.println("   Error: No data after D0! (timeout).");
      }

      currentSensorIndex++;
      state = SEND_MEASUREMENT;
      break;
    }

    case FINISH_CYCLE:
      Serial.println("The measurement cycle is complete. I am turning off the power to the sensors.");
      digitalWrite(ENERGY_SAVING, HIGH);

      lastCycleMillis = millis();

      if (USE_DEEP_SLEEP) {
        Serial.print("I go into deep sleep ");
        Serial.print(DEEP_SLEEP_TIME_SEC);
        Serial.println(" sec. (ESP32 will reboot after waking up).");
        esp_sleep_enable_timer_wakeup((uint64_t)DEEP_SLEEP_TIME_SEC * 1000000ULL);
        delay(100);
        esp_deep_sleep_start();
      } else {
        Serial.println("Waiting for the next interval...");
        state = IDLE;
      }
      break;
  }

  delay(10);
}