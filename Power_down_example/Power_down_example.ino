/* Author = helscream (Omer Ikram ul Haq)
Last edit date = 2015-04-05
Website: http://hobbylogs.me.pn/?p=339
Location: Pakistan
Ver: 0.1 beta --- Start
*/


// BASIC EXAMPLE

#include "Power_down.h"


void setup() {
  Serial.begin(115200);
  Serial.println("Program started ...");
  pinMode(13,OUTPUT);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("Power saving ON ...");
  digitalWrite(13,HIGH);
  delay(100);                  // wait for serial to finish transmitting 
  Power_down(16);
  digitalWrite(13,LOW);
  Power_down(16);
  
  Serial.println("Power saving OFF ...");
  digitalWrite(13,HIGH);
  delay(16000);
  digitalWrite(13,LOW);
  delay(16000);
  
}





