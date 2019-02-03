#include "LowPower.h"
#include <Sim800L.h>
#include <SoftwareSerial.h>               

#define RX  10
#define TX  11
#define resetPin 8

const int wakeSwitch = 2;
const int waterPinOne = 3;
const int sleepTogglePin = 4;
const int waterPinTwo = 7;
const int waterPinThree = 9;
const int waterPinFour = 12;
const int waterPinFive = 13;
bool error;

int lastState =0;

Sim800L GSM(RX, TX, resetPin);

void wakeUp()
{
    // Just a handler for the pin interrupt.
}

void printLevel(){
    Serial.print("   ");
    Serial.print(!digitalRead(waterPinOne));
    Serial.print(!digitalRead(waterPinTwo));
    Serial.print(!digitalRead(waterPinThree));
    Serial.print(!digitalRead(waterPinFour));
    Serial.println(!digitalRead(waterPinFive));
}

void sendMessage(char message[161]){
  Serial.print(" SENDING SMS ");
  error=GSM.sendSms("phone number here", message);
  if(error){
    Serial.print(" SMS Fail ");
  }else{
    Serial.print(" SMS Sent ");
  }
}


void setup()
{
    pinMode(wakeSwitch, INPUT_PULLUP);
    pinMode(sleepTogglePin, OUTPUT);

    pinMode(waterPinOne, INPUT_PULLUP);
    pinMode(waterPinTwo, INPUT_PULLUP);
    pinMode(waterPinThree, INPUT_PULLUP);
    pinMode(waterPinFour, INPUT_PULLUP);
    pinMode(waterPinFive, INPUT_PULLUP);

    
    Serial.begin(57600);
    GSM.begin(4800);

    
    Serial.print(" SENDING SMS ");
    error=GSM.sendSms("8165365490", "Starting Up");
    if(error){
      Serial.print(" SMS Fail ");
    }else{
      Serial.print(" SMS Sent ");
    }
}

void loop() 
{
    if(digitalRead(wakeSwitch) == LOW && digitalRead(waterPinOne) == HIGH){
      lastState = 15;
      attachInterrupt(digitalPinToInterrupt(2), wakeUp, HIGH);
      attachInterrupt(digitalPinToInterrupt(3), wakeUp, LOW);
      Serial.println("asleep");
      sendMessage("DROP unit, going to sleep.");
      delay(100);
      digitalWrite(sleepTogglePin, HIGH);
      LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF); 
      detachInterrupt(0); 
      
      digitalWrite(sleepTogglePin, LOW);
      delay(20);
    }
    

    if(!digitalRead(waterPinFive)){
      Serial.print("Water Level: 4ft");
      if(lastState != 5){
        sendMessage("Water Level: 4ft");
      }
      lastState=5;
      
    }else if(!digitalRead(waterPinFour)){
      Serial.print("Water Level: 3ft");
      if(lastState != 4){
        sendMessage("Water Level: 3ft");
      }
      lastState=4;
      
    }else if(!digitalRead(waterPinThree)){
      Serial.print("Water Level: 2ft");
      if(lastState != 3){
        sendMessage("Water Level: 2ft");
      }
      lastState=3;

    }else if(!digitalRead(waterPinTwo)){
      Serial.print("Water Level: 1ft");
      if(lastState != 2){
        sendMessage("Water Level: 1ft");
      }
      lastState=2;

    }else if(!digitalRead(waterPinOne)){
      Serial.print("Water Level: 3in");
      if(lastState != 1){
        sendMessage("Water Level: 3in");
      }
      lastState=1;
      
    }else{
      Serial.print("Water Level: 0ft");
      if(lastState != 0){
        sendMessage("Water Level: 0ft");
      }
      lastState=0;
    }
    printLevel();
    
    delay(100);
}
