#ifndef BLE_SERVICE_H
#define BLE_SERVICE_H

#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>
extern int LED_BUILTIN;
// Настройки BLE
#define DEVICE_NAME "ESP32_BLE_Server"
#define SERVICE_UUID "12345678-1234-1234-1234-123456789abc"
#define CHARACTERISTIC_UUID "abcd1234-5678-1234-5678-abcdef123456"

// Глобальные переменные
extern BLECharacteristic *pCharacteristic;
extern bool deviceConnected;
extern std::string value;
// Колбэк для обработки записей в характеристику
class MyCallbacks : public BLECharacteristicCallbacks {
  void onWrite(BLECharacteristic *pChar) override;
};

// Инициализация BLE сервера
void ble_begin();

#endif
