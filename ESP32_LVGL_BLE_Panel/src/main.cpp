#include <Arduino.h>
#include <lvgl.h>
#include <ui.h>
#include <TFT_eSPI.h>
#include <tft_draw.h>
#include <BLEDevice.h>
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>
#include <ble_service.h>
TFT_eSPI tft;
bool flag_button_start = true;
bool flag_button_stop = true;
bool deviceConnected = false;
int LED_BUILTIN = 2;
unsigned long timer = 0;
std::string value = "";
static lv_color_t buf1[320 * 20];
void setup() {
ble_begin();
lv_init();
tft.init();
tft.setRotation(0);
tft.setSwapBytes(true);
tft.fillScreen(TFT_WHITE);
static lv_disp_draw_buf_t draw_buf;
lv_disp_draw_buf_init(&draw_buf, buf1, NULL, 320 * 20);
static lv_disp_drv_t disp_drv;
lv_disp_drv_init(&disp_drv);
disp_drv.hor_res = 320;
disp_drv.ver_res = 480;
disp_drv.flush_cb = my_disp_flush;
disp_drv.draw_buf = &draw_buf;
lv_disp_drv_register(&disp_drv);
ui_init();
lv_obj_add_flag(ui_Image1, LV_OBJ_FLAG_HIDDEN);
lv_obj_add_flag(ui_Image3, LV_OBJ_FLAG_HIDDEN);
lv_obj_add_flag(ui_Image4, LV_OBJ_FLAG_HIDDEN);
}

void loop() {
  static uint32_t last_ms = 0;
  uint32_t now_ms = millis();
  uint32_t diff = now_ms - last_ms;
  if (diff > 0) {
      lv_tick_inc(diff);
      last_ms = now_ms;
  }
  lv_timer_handler();  
  if (millis() - timer > 1000){
  if (deviceConnected == true) {
    lv_obj_add_flag(ui_Image2, LV_OBJ_FLAG_HIDDEN);
    lv_obj_clear_flag(ui_Image1, LV_OBJ_FLAG_HIDDEN);
    lv_label_set_text(ui_Label1, "Connect");
    if (value == "ON") {
      lv_obj_clear_flag(ui_Image3, LV_OBJ_FLAG_HIDDEN);
    }
    if (value == "OFF") {
      lv_obj_clear_flag(ui_Image4, LV_OBJ_FLAG_HIDDEN);
    }
    }
  if (deviceConnected == false){
    lv_obj_add_flag(ui_Image1, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui_Image3, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui_Image4, LV_OBJ_FLAG_HIDDEN);
    lv_obj_clear_flag(ui_Image2, LV_OBJ_FLAG_HIDDEN);
    lv_label_set_text(ui_Label1, "Disconnect");
    }
    timer = millis();
  }
}