#ifndef TFT_DRAW
#define TFT_DRAW
#include <TFT_eSPI.h>
extern TFT_eSPI tft;
#include <lvgl.h>
#include <ui.h>
void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p);
#endif