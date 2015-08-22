#include <Max3421e.h>
#include <Usb.h>
#include <AndroidAccessory.h>

#define D_IN1 2
#define D_IN2 3
#define D_IN3 4
#define D_IN4 5
#define D_IN5 6
#define D_IN6 7
#define D_IN7 8
#define D_IN8 9
#define D_IN9 10

#define READ_PINS 9

#define START_BYTE 0x7f
#define MSG_SIZE 10

#define DEBUG 0  

AndroidAccessory acc("nozomi",
                     "SchoolFestivalController",
                     "Android Open Accessory basic implementation",
                     "1.0",
                     "http://bonboru.bglb.jp",
                     "0000000123456789");
                     
int pinArray[READ_PINS] = {
  D_IN1,
  D_IN2,
  D_IN3,
  D_IN4,
  D_IN5,
  D_IN6,
  D_IN7,
  D_IN8,
  D_IN9
};

void initPins() {
 int index = 0;
 for (index = 0; index < READ_PINS; index++) {
    pinMode(pinArray[index], INPUT);
    // setting pull up
    digitalWrite(pinArray[index], HIGH);
 }
}

void setup() {
 Serial.begin(115200);
 Serial.println("Start");
 initPins();
 acc.powerOn();
}

void loop() {
  byte msg[MSG_SIZE];
  int index = 0;
  int data = 0;
    
#if DEBUG > 0
    Serial.println("start");
#endif

    for (index = 0; index < READ_PINS; index++) {
      data = digitalRead(pinArray[index]);
      msg[index + 1] = data == HIGH ? 0 : 1;
#if DEBUG > 0
      Serial.print(pinArray[index]);
      Serial.print(":");
      Serial.print(data);
      Serial.print(":");
      Serial.println(msg[index + 1]);
#endif
    }

  if (acc.isConnected()) {
    msg[0] = START_BYTE;
    for (index = 0; index < READ_PINS; index++) {
      data = digitalRead(pinArray[index]);
      msg[index + 1] = data == HIGH ? 0 : 1;
    }
#if DEBUG > 0
    Serial.println("end");
#endif
    acc.write(msg, MSG_SIZE);
  } else {
    int index = 0;
    for (index = 0; index < READ_PINS; index++) {
      digitalWrite(pinArray[index], LOW); 
    }
  }
}



