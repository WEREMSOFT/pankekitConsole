#include <LinkedList.h>

/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the Uno and
  Leonardo, it is attached to digital pin 13. If you're unsure what
  pin the on-board LED is connected to on your Arduino model, check
  the documentation at http://www.arduino.cc

  This example code is in the public domain.

  modified 8 May 2014
  by Scott Fitzgerald
 */

LinkedList<int> pins1 = LinkedList<int>();
LinkedList<int> pins2 = LinkedList<int>();

int pins[] = {2, 3, 4, 5};

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin 13 as an output.
  int i = 0;
  for(i = 0; i < sizeof(pins); i++)
  {
     pinMode(pins[i], OUTPUT);
  }
  randomSeed(analogRead(0));
}

// the loop function runs over and over again forever
void loop() {
  unsigned int valor = random(0, 4);
  digitalWrite(pins[valor], HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(200);  

  turnOffAll();
  delay(200);  
}

void turnOffAll()
{
  int i = 0;
  for(i = 0; i < sizeof(pins); i++)
  {
     digitalWrite(i, LOW);
  }
}

