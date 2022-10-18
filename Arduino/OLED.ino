#include <U8g2lib.h>
#include "DHT.h"
U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0,U8X8_PIN_NONE);

#define DHTPIN A1
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);
//파일에서 가져오기
uint32_t DataCaptureDelay = 3000;
//2000밀리는 2초
uint32_t DataCapture_ST = 0;

float Temp;
float Humi;

void setup() {
  dht.begin();
  u8g2.begin();

  DataCapture_ST = millis();
}
void loop() {
  if ((millis() - DataCapture_ST) > DataCaptureDelay) {
//millis()는 현재 시간
    Humi = dht.readHumidity();
    Temp = dht.readTemperature();
  
  if (isnan(Humi) || isnan(Temp)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
    //만약 읽는거 실패할 경우 다시 오류문 출력하고 다시 측정
  }
  OLEDdraw();
  //OLEDdraw()를 실행한다
  DataCapture_ST = millis();
  }
}
void OLEDdraw() {
  u8g2.clearBuffer();
//화면에 매트릭스를 초기화
  u8g2.setFont(u8g2_font_ncenB08_te);
//폰트 설정
  u8g2.drawStr(1,15,"AIBD AIOT");
  u8g2.drawStr(15,36,"Temp.");
  u8g2.setCursor(85,36);
  u8g2.print(Temp);
  u8g2.drawStr(114,36,"\xb0");
  u8g2.drawStr(119,36,"C");

  u8g2.drawStr(15,47,"Humidity");
  u8g2.setCursor(85,36); u8g2.print(Humi);
  u8g2.drawStr(116,47,"%");

  u8g2.sendBuffer();
  //행렬을 led로 보내라
}