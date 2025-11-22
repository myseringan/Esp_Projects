#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include "DHT.h"

// ---------- ПИНЫ (измените при необходимости) ----------
#define TFT_MOSI  26  // SDA на модуле
#define TFT_SCLK  27  // SCK на модуле
#define TFT_MISO  19  // MISO (необязательно, но ставим стандартный)
#define TFT_CS    13   // CS (chip select)
#define TFT_DC    12  // A0 на модуле -> DC
#define TFT_RST   14  // RST (если нет пина RST на модуле, можно поставить -1 и подключить RST к 3.3V)

#define DHTPIN    25    // DATA pin DHT11
#define DHTTYPE   DHT11

// ---------- Объекты ----------
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);
DHT dht(DHTPIN, DHTTYPE);

// ---------- Параметры интерфейса ----------
const uint16_t SCR_W = 128;
const uint16_t SCR_H = 160;

// Основные зоны
const int TITLE_Y = 6;
const int TEMP_BOX_Y = 26;
const int TEMP_BOX_H = 56;

// Thermometer zone
const int THERM_X = 8;
const int THERM_Y = TEMP_BOX_Y + 4;
const int THERM_W = 18;
const int THERM_H = 78;

// Sparkline zone
const int SPARK_X = 36;
const int SPARK_Y = 106;
const int SPARK_W = 88;
const int SPARK_H = 40;

// Animation / timing
const unsigned long READ_INTERVAL = 2000; // ms для DHT11
const unsigned int FRAME_MS = 300;         // ~25 FPS
const float SMOOTH_ALPHA = 0.08f;         // экспоненциальное сглаживание отображаемого значения
const unsigned int NUMERIC_ANIM_MS = 420; // длительность скольжения цифры (ms)

// Sparkline buffer
const int SPARK_SAMPLES = SPARK_W;
float spark[SPARK_SAMPLES];
int sparkPos = 0;

// Показания и анимационные переменные
float measuredTemp = 0;
float dispTemp = 0;
float prevTempForAnim = 0;
unsigned long lastRead = 0;

// Для скольжения большой цифры
bool numericAnimating = false;
unsigned long numericAnimStart = 0;
float numericAnimFrom = 0;
float numericAnimTo = 0;

// Вспомогательные цвета
uint16_t colBg, colTitle, colBox, colText, colAccent, colThermBg;

void drawBorderAndLayout() {

  tft.setTextSize(1);
  tft.setTextColor(colTitle);
  tft.setCursor(6, TITLE_Y);
  tft.print("DHT11 Temp");

  // термометр рамка
  tft.drawRect(THERM_X - 1, THERM_Y - 1, THERM_W + 2, THERM_H + 2, colBox);

  // подписи
  tft.setTextSize(1);
  tft.setTextColor(colText);
  tft.setCursor(THERM_X, THERM_Y + THERM_H + 4);
  tft.print("Temp");
  tft.setCursor(SPARK_X, SPARK_Y + SPARK_H + 4);
  tft.print("History");
}

float clampf(float v, float a, float b) { if (v < a) return a; if (v > b) return b; return v; }

// easing (cubic out)
float easeOutCubic(float t) {
  t = clampf(t, 0.0f, 1.0f);
  t = t - 1.0f;
  return 1.0f + t * t * t;
}

// Анимированная смена большого числа (скольжение)
void drawTempNumericAnimated(float fromVal, float toVal, float progress) {
  int boxX = 28;
  int boxY = TEMP_BOX_Y + 8;
  int boxW = SCR_W - boxX - 6;
  int boxH = TEMP_BOX_H - 20;

  char bufFrom[16], bufTo[16];
  snprintf(bufFrom, sizeof(bufFrom), "%.1fC", fromVal);
  snprintf(bufTo, sizeof(bufTo), "%.1fC", toVal);

  uint8_t txtSize = 3;
  tft.setTextSize(txtSize);
  int16_t x1,y1; uint16_t w,h;
  tft.getTextBounds(bufFrom, 0, 0, &x1, &y1, &w, &h);

  int cx = boxX + (boxW - w) / 2;
  int cy = boxY + (boxH - h) / 2;

  int dir = (toVal >= fromVal) ? -1 : 1; // to > from -> slide up (dir -1)
  float e = easeOutCubic(progress);

  int oldY = cy + int(dir * (e * (h + 6)));
  int newY = cy + int(dir * ((e - 1.0f) * (h + 6)));

  // очищаем зону
  tft.fillRect(boxX, boxY, boxW, boxH, colBg);

  // новый (акцент)
  tft.setTextColor(colAccent);
  tft.setCursor(cx, newY);
  tft.print(bufTo);
}

void drawTempStatic(float val) {
  int boxX = 28;
  int boxY = TEMP_BOX_Y + 8;
  int boxW = SCR_W - boxX - 6;
  int boxH = TEMP_BOX_H - 20;

  char buf[16];
  snprintf(buf, sizeof(buf), "%.1fC", val);

  uint8_t txtSize = 3;
  tft.setTextSize(txtSize);
  int16_t x1,y1; uint16_t w,h;
  tft.getTextBounds(buf, 0, 0, &x1, &y1, &w, &h);
  int cx = boxX + (boxW - w) / 2;
  int cy = boxY + (boxH - h) / 2;

  tft.fillRect(boxX, boxY, boxW, boxH, colBg);
  tft.setTextColor(colAccent);
  tft.setCursor(cx, cy);
  tft.print(buf);
}

void drawThermometer(float temp) {
  const float MIN_T = -10.0f, MAX_T = 50.0f;
  float clamped = clampf(temp, MIN_T, MAX_T);
  float frac = (clamped - MIN_T) / (MAX_T - MIN_T);
  int fillH = (int)(frac * THERM_H);

  // очистка внутренней области
  tft.fillRect(THERM_X, THERM_Y, THERM_W, THERM_H, colThermBg);

  for (int i = 0; i < THERM_H; ++i) {
    int drawY = THERM_Y + THERM_H - 1 - i;
    uint16_t color;
    if (i < fillH) {
      float p = (float)i / max(1, THERM_H - 1);
      uint8_t r = (uint8_t)clampf(10 + 245 * p, 0, 255);
      uint8_t g = (uint8_t)clampf(10 + 200 * (1.0f - fabs(p - 0.5f)), 0, 255);
      uint8_t b = (uint8_t)clampf(200 * (1.0f - p), 0, 255);
      color = tft.color565(r,g,b);
    } else {
      color = colThermBg;
    }
    tft.drawFastHLine(THERM_X, drawY, THERM_W, color);
  }


  char buf[12];
  snprintf(buf, sizeof(buf), "%.1fC", temp);
  tft.setTextSize(1);
  tft.setTextColor(colText);
  tft.fillRect(THERM_X + THERM_W + 6, THERM_Y + THERM_H/2 - 8, 48, 18, colBg);
  tft.setCursor(THERM_X + THERM_W + 6, THERM_Y + THERM_H/2 - 6);
  tft.print(buf);
}

void drawSparklineFull() {
  tft.fillRect(SPARK_X, SPARK_Y, SPARK_W, SPARK_H, colBg);

  float minv = 9999, maxv = -9999;
  for (int i=0;i<SPARK_SAMPLES;i++) {
    if (!isnan(spark[i])) {
      if (spark[i] < minv) minv = spark[i];
      if (spark[i] > maxv) maxv = spark[i];
    }
  }
  if (minv == 9999) return;
  if (fabs(maxv - minv) < 0.05f) maxv = minv + 0.05f;

  for (int i=0;i<SPARK_W-1;i++) {
    int idx1 = (sparkPos + i) % SPARK_SAMPLES;
    int idx2 = (sparkPos + i + 1) % SPARK_SAMPLES;
    float v1 = spark[idx1];
    float v2 = spark[idx2];
    int y1 = SPARK_Y + SPARK_H - (int)((v1 - minv) / (maxv - minv) * SPARK_H);
    int y2 = SPARK_Y + SPARK_H - (int)((v2 - minv) / (maxv - minv) * SPARK_H);
    tft.drawLine(SPARK_X + i, y1, SPARK_X + i + 1, y2, tft.color565(100,255,120));
  }
}

void setup() {
  Serial.begin(115200);
  delay(50);

  // цвета
  colBg     = tft.color565(8,10,12);
  colTitle  = tft.color565(220,220,220);
  colBox    = tft.color565(120,120,120);
  colText   = tft.color565(200,200,200);
  colAccent = tft.color565(255,200,80);
  colThermBg= tft.color565(40,40,45);

  // SPI init
  SPI.begin(TFT_SCLK, TFT_MISO, TFT_MOSI);

  // TFT init
  tft.initR(INITR_BLACKTAB);
  tft.setRotation(1);
  tft.setTextWrap(false);

  // DHT init
  dht.begin();

  // init spark buffer
  for (int i=0;i<SPARK_SAMPLES;i++) spark[i] = NAN;
  sparkPos = 0;

  // initial draw
  drawBorderAndLayout();
  drawSparklineFull();

  lastRead = millis() - READ_INTERVAL; // чтобы сразу прочитать
  measuredTemp = dispTemp = 0.0f;
  prevTempForAnim = 0.0f;

}

void loop() {
  unsigned long now = millis();

  // Чтение DHT с интервалом
  if (now - lastRead >= READ_INTERVAL) {
    lastRead = now;
    float t = dht.readTemperature();
    if (!isnan(t)) {
      measuredTemp = t;

      // sparkline: добавляем
      spark[sparkPos] = t;
      sparkPos = (sparkPos + 1) % SPARK_SAMPLES;

      // запуск числовой анимации при заметном изменении  
      if (fabs(measuredTemp - prevTempForAnim) >= 0.2f) {
        numericAnimating = true;
        numericAnimStart = now;
        numericAnimFrom = prevTempForAnim;
        numericAnimTo = measuredTemp;
        prevTempForAnim = measuredTemp;
      } else {
        prevTempForAnim = measuredTemp;
      }
    } else {
      Serial.println("DHT read failed");
    }
  }

  // Сглаживание отображаемого значения
  dispTemp += (measuredTemp - dispTemp) * SMOOTH_ALPHA;

  // Обновление анимации большого числа
  if (numericAnimating) {
    tft.fillScreen(ST7735_BLACK);
    unsigned long dt = now - numericAnimStart;
    float prog = clampf((float)dt / (float)NUMERIC_ANIM_MS, 0.0f, 1.0f);
    drawTempNumericAnimated(numericAnimFrom, numericAnimTo, prog);
    if (prog >= 1.0f) numericAnimating = false;
  } else {
    drawTempStatic(dispTemp);
  }

  // Обновляем термометр и sparkline
  drawThermometer(dispTemp);
  drawSparklineFull();
  delay(FRAME_MS);
  
}