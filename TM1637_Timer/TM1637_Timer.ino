extern volatile unsigned long timer0_millis;   // millis() 리셋을 위한 변수

#include <Arduino.h>
#include <TM1637Display.h>

// Module connection pins (Digital Pins)aa
#define CLK 9
#define DIO 8
#define Switch 12
#define Wire 11

unsigned long previousTime, currentTime;      // 현재시간, 현재시간(ms)
int timeValue;
uint8_t data[] = { 0x00, 0x00, 0x00, 0x00 };  // 초기 출력값 0000 
int seg3, seg2, seg1, seg0;

int start = 0;
int wire_touch = 0;

TM1637Display display(CLK, DIO);

void setup() {
  display.setBrightness(15);                  // 0 ~ 15 (15가 가장 밝음)
  // display.setBrightness(0x0f);
  pinMode(Switch, INPUT);
  pinMode(Wire, INPUT);

  Serial.begin(9600); 
}

void loop() {
  // if (digitalRead(Switch) == HIGH) {
  //   start = 1;
  // }
  // if (start == 1) {
    while(digitalRead(Switch) != LOW) {
      currentTime = millis();                    // 현재 시간값을 측정

      if(currentTime - previousTime >= 10) {     // 현재 시간값을 0.01s마다 10씩 증가시킴
        previousTime = currentTime;
        timeValue = currentTime / 10;            // 0.01s 마다 10씩 증가된 숫자를 10으로 나누어 줌.
                                                //   (결과적으로 0.01s마다 1씩 증가된 숫자가 timeValue에 저장됨)  
    
        seg0 = (timeValue / 1000) % 10;          // 현재 시간값 4자리에서 1000의 자리 숫자 저장
        seg1 = (timeValue / 100) % 10;           // 현재 시간값 4자리에서 100의 자리 숫자 저장
        seg2 = (timeValue / 10) % 10;            // 현재 시간값 4자리에서 10의 자리 숫자 저장
      seg3 = timeValue % 10;                   // 현재 시간값 4자리에서 1의 자리 숫자 저장

        data[0]=display.encodeDigit(seg0);       // 첫번째 Segment에 1000의 자리 숫자 배열
        data[1]=display.encodeDigit(seg1);       // 두번째 Segment에 100의 자리 숫자 배열
        data[2]=display.encodeDigit(seg2);       // 세번째 Segment에 10의 자리 숫자 배열
        data[3]=display.encodeDigit(seg3);       // 네번째 Segment에 1의 자리 숫자 배열

        display.setSegments(data);
        Serial.println(timeValue);
      }

      if(currentTime>=1000000) {                  // 1,000,000ms(1000초) 후 millis() 리셋
        timer0_millis = 0;
        previousTime = 0;
      }
    }
  // }
}