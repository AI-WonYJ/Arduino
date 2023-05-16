
unsigned long time;

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <FastLED.h>
#include <TM1637Display.h>

#define switchPin  12 // 스위치 핀 번호
#define buzzerPin  10 // 부저 핀 번호
#define wirePin    2 // 와이어 핀 번호
#define successPin 3
#define LED_PIN    7
#define NUM_LEDS   96

LiquidCrystal_I2C lcd(0x27, 16, 2);
int Brightness = 2;
unsigned long previousTime, currentTime;      // 현재시간, 현재시간(ms)
int timeValue;      
CRGB leds[NUM_LEDS];

void setup() {
  Serial.begin(9600); 
  pinMode(switchPin, INPUT); // 스위치 핀을 입력으로 설정
  pinMode(buzzerPin, OUTPUT); // 부저 핀을 출력으로 설정
  pinMode(wirePin, INPUT_PULLUP); // 와이어 핀을 내부 풀업 저항과 함께 입력으로 설정
   // I2C LCD를 초기화 합니다..
  lcd.init();
  // I2C LCD의 백라이트를 켜줍니다.
  lcd.backlight();
  lcd.clear();
  FastLED.addLeds<WS2812, 7, GRB>(leds, NUM_LEDS);
  for(int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB(0, 0, 0);
  }
  FastLED.show();
  delay(100);
  for(int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB(Brightness, 0, 0);
    FastLED.show(); 
  }
  for(int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB(0, Brightness, 0);
    FastLED.show(); 
  }
  for(int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB(0, 0, Brightness);
    FastLED.show(); 
  }
  for(int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB(Brightness, Brightness, Brightness);
    FastLED.show(); 
  }
  for(int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB(0, 0, 0);
  }
  FastLED.show();
  delay(200);
  
  digitalWrite(buzzerPin, HIGH); // 삐 소리 출력
  delay(100);
  digitalWrite(buzzerPin, LOW); // 삐 소리 출력
}

void loop() {
  if (digitalRead(switchPin) == HIGH) { // 스위치가 눌렸을 때
    
    digitalWrite(buzzerPin, HIGH); // 삐 소리 출력
    lcd.clear();
    for(int i = 0; i < NUM_LEDS; i++) {
      leds[i] = CRGB(Brightness, 0, 0);
    }
    FastLED.show(); 
    lcd.setCursor(0,0);                // 0번째 줄 0번째 셀부터 입력하게 합니다.
    lcd.print("Ready Buzz");        // 문구를 출력합니다.
    delay(300);
    digitalWrite(buzzerPin, LOW); // 부저 끄기
    while (digitalRead(switchPin) != HIGH) {
      continue;
    }
    lcd.clear();
    lcd.setCursor(0,0);                // 0번째 줄 0번째 셀부터 입력하게 합니다.
    lcd.print("Start Buzz");        // 문구를 출력합니다.
    for(int i = 0; i < NUM_LEDS; i++) {
      leds[i] = CRGB(0, 0, 0);
    }
    FastLED.show();
    delay(500);
    
    for(int i = 40; i < 64; i++) {
      leds[i] = CRGB(Brightness, 0, 0);
    }
    FastLED.show();
    delay(1000);
    for(int i = 24; i < 40; i++) {
      leds[i] = CRGB(Brightness, 0, 0);
    }
    for(int i = 64; i < 80; i++) {
      leds[i] = CRGB(Brightness, 0, 0);
    }
    FastLED.show();
    delay(1000);
    for(int i = 0; i < 24; i++) {
      leds[i] = CRGB(Brightness, 0, 0);
    }
    for(int i = 80; i < NUM_LEDS; i++) {
      leds[i] = CRGB(Brightness, 0, 0);
    }
    FastLED.show();
    delay(1000);

    for(int i = 0; i < NUM_LEDS; i++) {
      leds[i] = CRGB(0, Brightness, 0);
    }
    FastLED.show(); 
    // 와이어 게임 실행
    digitalWrite(buzzerPin, HIGH); // 삐 소리 출력
    delay(500);
    digitalWrite(buzzerPin, LOW); // 삐 소리 출력
    lcd.clear();
    previousTime = millis();
    int start = millis();
    int status = 0;
    int count = 0;
    while (digitalRead(successPin) != HIGH) { // 스위치가 눌렸을 때 게임 스타트
      digitalWrite(buzzerPin, LOW); // 삐 소리 출력
      currentTime = millis();                    // 현재 시간값을 측정
      if(currentTime - previousTime >= 10) {     // 현재 시간값을 0.01s마다 10씩 증가시킴
        previousTime = currentTime;
        timeValue = currentTime / 10;            // 0.01s 마다 10씩 증가된 숫자를 10으로 나누어 줌.
      
        Serial.println(currentTime - start);
        }

      if (digitalRead(wirePin) == HIGH) {
        digitalWrite(buzzerPin, HIGH); // 삐 소리 출력
        delay(100);
        count += 1;
        while (digitalRead(wirePin) == HIGH) {
          continue;
        }
        if (count == 3) {
          Serial.println("Fail");
          for(int i = 0; i < NUM_LEDS; i++) {
              leds[i] = CRGB(0, Brightness, 0);
          }
          status = 1;
          FastLED.show(); 
          lcd.clear();
          lcd.setCursor(0, 1);                // 0번째 줄 0번째 셀부터 입력하게 합니다.
          lcd.print("fail");        // 문구를 출력합니다.
          delay(400);
          break;
        }
      }
    }
    if (status == 0) {
      for(int i = 0; i < NUM_LEDS; i++) {
        leds[i] = CRGB(0, 0, Brightness);
      }
      FastLED.show(); 
    }
    else if (status == 1) {
      for(int i = 0; i < NUM_LEDS; i++) {
        leds[i] = CRGB(Brightness, 0, 0);
      }
      FastLED.show(); 
    }
    digitalWrite(buzzerPin, HIGH); // 삐 소리 출력
    delay(500);
    digitalWrite(buzzerPin, LOW); // 삐 소리 출력

    int time_int = currentTime - start;
    String str1 = String(time_int);
    String str2 = "ms";
    // lcd.clear();
    lcd.setCursor(0,0);                // 0번째 줄 0번째 셀부터 입력하게 합니다.
    lcd.print(str1 + str2);        // 문구를 출력합니다.
    while (digitalRead(switchPin) != HIGH) {
      continue;
    }
    delay(400);







    lcd.clear();
      lcd.setCursor(0,0);                // 0번째 줄 0번째 셀부터 입력하게 합니다.
      lcd.print("END Buzz");        // 문구를 출력합니다.
    // delay(2000);
  }
  else {
    digitalWrite(buzzerPin, LOW); // 부저 끄기
    for(int i = 0; i < NUM_LEDS; i++) {
      leds[i] = CRGB(Brightness, Brightness, Brightness);
      FastLED.show(); 
      lcd.clear();
    }
    for(int i = 0; i < NUM_LEDS; i++) {
      leds[i] = CRGB(0, 0, 0);
      FastLED.show(); 
      lcd.clear();
    }
  }
}