#define LV_CONF_INCLUDE_SIMPLE 1
#include <lvgl.h>
#include "ui.h"
#include "DHT.h"
#include "TFT_eSPI.h"

TFT_eSPI tft;
#define DHTPIN 22
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);
char buf2[10];
char buf3[10];
static lv_color_t buf1[320 * 60];

void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p) {
    uint32_t w = (area->x2 - area->x1 + 1);
    uint32_t h = (area->y2 - area->y1 + 1);

    tft.startWrite();
    tft.setAddrWindow(area->x1, area->y1, w, h);
    tft.pushColors((uint16_t*)color_p, w * h, true);
    tft.endWrite();

    lv_disp_flush_ready(disp);
}

// Явная C-функция-обёртка для анимации
static void arc_anim_exec(void * a, int32_t v) {
    lv_arc_set_value((lv_obj_t*)a, v);
}

void setup () {
  Serial.begin(115200);
  lv_init();
  tft.begin();
  tft.setRotation(0);
  dht.begin();
  static lv_disp_draw_buf_t draw_buf;
  lv_disp_draw_buf_init(&draw_buf, buf1, NULL, 320 * 60);

  static lv_disp_drv_t disp_drv;
  lv_disp_drv_init(&disp_drv);

  disp_drv.hor_res = 320;
  disp_drv.ver_res = 480;

  disp_drv.flush_cb = my_disp_flush;
  disp_drv.draw_buf = &draw_buf;

  lv_disp_drv_register(&disp_drv);

  ui_init();
  lv_label_set_text(ui_Label2, " ");  // пробел
  lv_label_set_text(ui_Label3, " ");

  // Небольшая проверка: установим дуги в 0 и 100 при старте, чтобы увидеть реакцию
  lv_arc_set_value(ui_Arc3, 0);
  lv_arc_set_value(ui_Arc4, 0);
  lv_obj_invalidate(ui_Arc3);
  lv_obj_invalidate(ui_Arc4);
  delay(200);
  lv_arc_set_value(ui_Arc3, 100);
  lv_arc_set_value(ui_Arc4, 100);
  lv_obj_invalidate(ui_Arc3);
  lv_obj_invalidate(ui_Arc4);
}

void loop () {
  // ВАЖНО: LVGL требует инкремента тика (lv_tick_inc) реальным прошедшим временем,
  // иначе таймеры/анимации не обновляются.
  static uint32_t last_ms = 0;
  uint32_t now_ms = millis();
  uint32_t diff = now_ms - last_ms;
  if (diff > 0) {
      lv_tick_inc(diff);
      last_ms = now_ms;
  }

  lv_timer_handler();
  updateDHT();
  delay(10); // небольшой sleep
}

void updateDHT() {
    static uint32_t last = 0;
    if (millis() - last < 2000) return;
    last = millis();

    float tf = dht.readTemperature();
    float hf = dht.readHumidity();

    if (isnan(tf) || isnan(hf)) {
        Serial.println("DHT read failed");
        return;
    }

    Serial.print("T: "); Serial.print(tf);
    Serial.print(" H: "); Serial.println(hf);

    updateArcs(tf, hf);
}

void updateArcs(float t, float h) {
    int it = (int)round(t);
    int ih = (int)round(h);

    // Отладочная информация
    int curT = lv_arc_get_value(ui_Arc3);
    int curH = lv_arc_get_value(ui_Arc4);
    Serial.printf("updateArcs target %d %d, current %d %d\n", it, ih, curT, curH);

    // Прямое присвоение --> смотрим, отрисуется ли изменение немедленно.
    // Это тест: если это работает — объект реагирует, а проблема в анимации/тайках.
    lv_arc_set_value(ui_Arc3, it);
    lv_arc_set_value(ui_Arc4, ih);
    lv_obj_invalidate(ui_Arc3);
    lv_obj_invalidate(ui_Arc4);

    // Небольшая пауза чтобы визуально увидеть прямое изменение (можно убрать позже)
    delay(30);

    // Попытка анимировать от текущего значения к целевому (используем локальные anim, не static)
    lv_anim_t animT;
    lv_anim_init(&animT);
    lv_anim_set_var(&animT, ui_Arc3);
    lv_anim_set_values(&animT, curT, it);
    lv_anim_set_time(&animT, 500); // 0.5 сек
    lv_anim_set_exec_cb(&animT, arc_anim_exec);
    lv_anim_start(&animT);

    lv_anim_t animH;
    lv_anim_init(&animH);
    lv_anim_set_var(&animH, ui_Arc4);
    lv_anim_set_values(&animH, curH, ih);
    lv_anim_set_time(&animH, 500); // 0.5 сек
    lv_anim_set_exec_cb(&animH, arc_anim_exec);
    lv_anim_start(&animH);

    // Обновляем Label
    snprintf(buf2, sizeof(buf2), "%d°C", it);
    lv_label_set_text(ui_Label2, buf2);

    snprintf(buf3, sizeof(buf3), "%d%%", ih);
    lv_label_set_text(ui_Label3, buf3);
}