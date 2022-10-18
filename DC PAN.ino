#include <SoftPWM.h>

SOFTPWM_DEFINE_CHANNEL(A3);
//A3핀 사용

void setup() {
  SoftPWM.begin(490);
}

void loop() {
  SoftPWM.set(100);
  //최대전압으로 팬 돌리기
  delay(2000);
  SoftPWM.set(0);
  //팬 끄기
  delay(2000);
}
