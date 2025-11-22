#include "ble_service.h"
#include <lvgl.h>
#include <ui.h>
BLECharacteristic *pCharacteristic = nullptr;
void MyCallbacks::onWrite(BLECharacteristic *pChar) {
  value = pChar->getValue();
  if (!value.empty()) {
    Serial.print("Получено сообщение: ");
    Serial.println(value.c_str());

    if (value == "ON"){lv_obj_add_flag(ui_Image4, LV_OBJ_FLAG_HIDDEN); lv_obj_clear_flag(ui_Image3, LV_OBJ_FLAG_HIDDEN);}
    if (value == "OFF"){lv_obj_add_flag(ui_Image3, LV_OBJ_FLAG_HIDDEN); lv_obj_clear_flag(ui_Image4, LV_OBJ_FLAG_HIDDEN);}
  }
}

class MyServerCallbacks : public BLEServerCallbacks {
  void onConnect(BLEServer* pServer) override {
    deviceConnected = true;
    Serial.println("Клиент подключился!");
  }
  void onDisconnect(BLEServer* pServer) override {
    deviceConnected = false;
    Serial.println("Клиент отключился!");
    pServer->getAdvertising()->start();
    Serial.println("BLE сервер снова рекламируется");
  }
};

void ble_begin() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  BLEDevice::init(DEVICE_NAME);
  BLEServer *pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());
  BLEService *pService = pServer->createService(SERVICE_UUID);

  pCharacteristic = pService->createCharacteristic(
      CHARACTERISTIC_UUID,
      BLECharacteristic::PROPERTY_WRITE | BLECharacteristic::PROPERTY_READ
  );

  pCharacteristic->setCallbacks(new MyCallbacks());
  pCharacteristic->setValue("Ready");
  
  pService->start();
  BLEDevice::startAdvertising();

  Serial.println("BLE сервер готов к приему команд");
}
