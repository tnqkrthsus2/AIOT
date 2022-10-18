#define PUMP 16
#define SOILHUMI A6

int Soilhumi = 0;
//Soilhumi 선언

void setup() {
  Serial.begin(9600);
  //9600으로 잡기
  pinMode(SOILHUMI,INPUT);
  //핀모드 input으로 설정
  pinMode(PUMP, OUTPUT);
  //pump를 출력 모드로 변경
}

void loop() {
  Soilhumi = map(analogRead(SOILHUMI),0,1023,100,0);
  if (Soilhumi >= 60) digitalWrite(PUMP,LOW);
  else if (Soilhumi < 30) digitalWrite(PUMP,HIGH);
  //조건문을 통해 펌프 속도 조절
  delay(2000);
}
//2초 간격으로 펌프의 속도를 변경
