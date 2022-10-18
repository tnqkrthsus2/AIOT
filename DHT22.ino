#include "DHT.h"
//전처리
#define DHTPIN A1
#define DHTTYPE DHT22

DHT dht(DHTPIN,DHTTYPE);
//파일에서 가져오기
uint32_t DataCaptureDelay = 2000;
//2000밀리는 2초
uint32_t StartTime = 0;
//주석
void setup() {
  Serial.begin(9600);
  //9600의 속도
  dht.begin();
  StartTime = millis();
  // put your setup code here, to run once:

}

void loop() {
  if ((millis() - StartTime) > DataCaptureDelay) {
//millis()는 현재 시간
    float h = dht.readHumidity();
    float t = dht.readTemperature();
  
  if (isnan(h) || isnan(t)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
    //만약 읽는거 실패할 경우 다시 오류문 출력하고 다시 측정
  }
  Serial.print(F("Humidity: "));
  //보통은 하드디스크에서 램을 통해 읽는다. 아두이누의 램의 크기는 무척 작다. 
  //그래서 F를 입력함으로써 데이터를 하드디크에서 램을 안거치고 바로 읽어온다 -> 무척 효율적
  Serial.print(h);
  Serial.print(F("% Temperature: "));
  Serial.print(t);
  Serial.println(F("C"));
  
  StartTime = millis();
  //현재 시간으로 변경
  }
  // put your main code here, to run repeatedly:

}
//millis()를 delay()를 사용하는것은 delay()를 사용하면 그 시간동안 작동 자체가 멈춘다 
//온도 측정 기능 구현
