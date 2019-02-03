// **** INCLUDES *****
#include "LowPower.h"

// Use pin 2 as wake up pin
const int wakeSwitch = 2;
const int sleepTogglePin = 4;

const int waterPinOne = 3;
const int waterPinTwo = 7;
const int waterPinThree = 9;
const int waterPinFour = 11;
const int waterPinFive = 13;


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

void setup()
{
    // Configure wake up pin as input.
    // This will consumes few uA of current.
    pinMode(wakeSwitch, INPUT_PULLUP);
    pinMode(sleepTogglePin, OUTPUT);

    pinMode(waterPinOne, INPUT_PULLUP);
    pinMode(waterPinTwo, INPUT_PULLUP);
    pinMode(waterPinThree, INPUT_PULLUP);
    pinMode(waterPinFour, INPUT_PULLUP);
    pinMode(waterPinFive, INPUT_PULLUP);

    
    Serial.begin(57600);
}

void loop() 
{
    if(digitalRead(wakeSwitch) == HIGH && digitalRead(waterPinOne) == HIGH){
      attachInterrupt(digitalPinToInterrupt(2), wakeUp, LOW);
      attachInterrupt(digitalPinToInterrupt(3), wakeUp, LOW);
      Serial.println("asleep");
      delay(100);
      digitalWrite(sleepTogglePin, HIGH);
      LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF); 
      detachInterrupt(0); 
      
      digitalWrite(sleepTogglePin, LOW);
      delay(20);
    }

    if(!digitalRead(waterPinFive)){
      Serial.print("Water Level: 4ft");
      
    }else if(!digitalRead(waterPinFour)){
      Serial.print("Water Level: 3ft");
      
    }else if(!digitalRead(waterPinThree)){
      Serial.print("Water Level: 2ft");
      
    }else if(!digitalRead(waterPinTwo)){
      Serial.print("Water Level: 1ft");
      
    }else if(!digitalRead(waterPinOne)){
      Serial.print("Water Level: 3in");
      
    }else{
      Serial.print("Water Level: 0ft");
    }
    printLevel();
    
    delay(100);
}
