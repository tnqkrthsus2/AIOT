#define PUMP 16

void setup() {
  pinMode(PUMP, OUTPUT)
  //pump를 출력 모드로 변경
}

void loop() {
  digitalWrite(PUMP,HIGH);
  //펌프 속도 조절
  delay(2000);
  digitalWrite(PUMP,LOW);
  delay(2000);
}
//2초 간격으로 펌프의 속도를 변경