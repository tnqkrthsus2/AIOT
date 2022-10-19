#include <U8g2lib.h>
#include "DHT.h"
#include <SoftPWM.h>
U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0,U8X8_PIN_NONE);

#define LAMP 17
#define PUMP 16
#define DHTPIN A1
#define DHTTYPE DHT22
#define SOILHUMI A6
SOFTPWM_DEFINE_CHANNEL(A3);
//핀 지정

DHT dht(DHTPIN, DHTTYPE);
//파일에서 가져오기
uint32_t DataCaptureDelay_1 = 2000;
//2000밀리는 2초, 온/습도의 측정 딜레이
uint32_t DataCaptureDelay_2 = 3000;
//3000밀리는 3초, 토양 습도의 측정 딜레이
uint32_t DataCapture_ST_1 = 0;
uint32_t DataCapture_ST_2 = 0;
uint32_t TimeCompare;
uint32_t StartTime = 0;

float Temp;
float Humi;
int Soilhumi = 0;

int Hour = 0;
int Minute = 5;
int Second = 0;
//변수 선언
uint32_t TimeSum = (uint32_t)((Hour*60+Minute)*60*Second)*1000;
//TimeSum을 통해 밀리세컨드 계산 -> 1분에 대한 밀리세컨드 계산
int FAN_status = 0;
int PUMP_status = 0;
int LAMP_status = 0; 
//팬,펌프,LED 상태 선언

void setup() {
  Serial.begin(9600);
  //9600으로 잡기
  pinMode(SOILHUMI,INPUT);
  //핀모드 input으로 설정
  pinMode(PUMP, OUTPUT);
  //pump를 출력 모드로 변경
  pinMode(LAMP, OUTPUT);
  //lamp 출력 모드로 변경
  dht.begin();
  u8g2.begin();
  SoftPWM.begin(490);
  DataCapture_ST_1 = millis();
  DataCapture_ST_2 = millis();
}

void loop() {
  //시작 시작 기록
  if ((millis() - DataCapture_ST_1) > DataCaptureDelay_1) {
  //millis()는 현재 시간
    Humi = dht.readHumidity();
    Temp = dht.readTemperature();
    //온도와 습도 2초 간격으로 측정
    DataCapture_ST_1 = millis();
  if ((millis() - DataCapture_ST_2) > DataCaptureDelay_2) {
    Soilhumi = map(analogRead(SOILHUMI),0,1023,100,0);
    //아날로그 신호를 디지털 테이터 값으로 변경
    //토양 습도 3초 간격으로 측정
    DataCapture_ST_2 = millis();     
  if (isnan(Humi) || isnan(Temp) || isnan(Soilhumi)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
    //만약 읽는거 실패할 경우 다시 오류문 출력하고 다시 측정
        }
  //OLEDdraw()를 실행한다
      }
  if (Temp >= 29){
    SoftPWM.set(100);
    FAN_status = 1;
      }
  else if (Temp <= 20){
    SoftPWM.set(0);
    FAN_status = 0;
      }
  else {
    SoftPWM.set(65);
    FAN_status = 1;
      } 
    }
  if ((Soilhumi >= 30) & Soilhumi < 60) {digitalWrite(PUMP,HIGH); PUMP_status = 1;}
  else {
    digitalWrite(PUMP,LOW); 
    PUMP_status = 0;}
  //조건문을 통해 펌프 속도 조절

  TimeCompare = (millis() - StartTime) / TimeSum;
  if (TimeCompare % 5 == 0){
    digitalWrite(LAMP,LOW); // 너무 밝아서 무조건 꺼지게 변경
    LAMP_status = 1;}
    //짝수일때 Lamp를 킨다
   else {
    digitalWrite(LAMP,LOW);
    LAMP_status = 0;}
    //홀수일때 lamp를 끈다
OLEDdraw();
}

void OLEDdraw() {
  u8g2.clearBuffer();
//화면에 매트릭스를 초기화
  u8g2.setFont(u8g2_font_ncenB08_te);
//폰트 설정
  u8g2.drawStr(1,15,"Temp.");
  u8g2.setCursor(85,15);
  u8g2.print(Temp);
  u8g2.drawStr(114,15,"\xb0");
  u8g2.drawStr(119,15,"C");
  u8g2.drawStr(1,26,"Humidity");
  u8g2.setCursor(85,26); u8g2.print(Humi);
  u8g2.drawStr(119,26,"%");
  u8g2.drawStr(1,37,"Soil Humidity");
  u8g2.setCursor(85,37); u8g2.print(Soilhumi);
  u8g2.drawStr(119,37,"%");
  u8g2.drawStr(1,48,"status");
  u8g2.setCursor(1,59); u8g2.print(FAN_status);
  u8g2.setCursor(10,59); u8g2.print(PUMP_status);
  u8g2.setCursor(19,59); u8g2.print(LAMP_status);
  //모듈 작동 상태 0,1로 표시
  u8g2.sendBuffer();
  //행렬을 led로 보내라
}