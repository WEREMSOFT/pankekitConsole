

/* SevSeg Counter Example
 
 Copyright 2014 Dean Reading
 
 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at 
 http://www.apache.org/licenses/LICENSE-2.0
 
 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
 
 
 This example demonstrates a very simple use of the SevSeg library with a 4
 digit display. It displays a counter that counts up, showing deci-seconds.
 */

#include "SevSeg.h"
#include "Bounce2.h"

SevSeg sevseg; //Instantiate a seven segment controller object

static const unsigned int STATE_READY = 0;
static const unsigned int STATE_RUNNING = 1;
static const unsigned int STATE_PAUSED = 2;
static const unsigned int STATE_LAP = 3;

unsigned int state = STATE_READY;

byte button_start_stop_pin = A0;
byte button_lap_reset_pin = A1;
  
static unsigned long timer = millis();
static unsigned long timerPaused = millis();
static unsigned long elapsedTimeInMiliseconds = 0;
static unsigned long timeToShowMinutes = 0;
static unsigned long timeToShowSeconds = 0;
static unsigned long timeToShowDecSeconds = 0;

boolean justPressedReset = false;
boolean justPressedStart = false;

Bounce button_start_stop = Bounce(); 

// Instantiate another Bounce object
Bounce button_lap_reset = Bounce(); 

  
void setup() {
  byte numDigits = 6;   
  byte digitPins[] = {0, 1, 2, 3, 4, 5};
  //                    a  b  c  d   e   f   g
  byte segmentPins[] = {6, 7, 8, 9, 11, 10, 12, 13};
/*
a 6
b 10
c 11
d 9
e 8
f 7
g 12
  */

  pinMode(button_start_stop_pin,INPUT_PULLUP);  // button pins are inputs
  // enable internal pullup; buttons start in high position; logic reversed
  button_start_stop.attach(button_start_stop_pin);
  button_start_stop.interval(100); // interval in ms
  
  pinMode(button_lap_reset_pin,INPUT_PULLUP);  // button pins are inputs
  // enable internal pullup; buttons start in high position; logic reversed
  button_lap_reset.attach(button_lap_reset_pin);
  button_lap_reset.interval(100); // interval in ms
  
  sevseg.begin(COMMON_ANODE, numDigits, digitPins, segmentPins);
  sevseg.setBrightness(100);

  passToStateReady();
}

int lastStateStart = LOW;

bool checkButtonStartClick()
{
<<<<<<< HEAD
  int dRead = digitalRead(button_start_stop);
  bool returnValue = false;
  if(dRead == HIGH && lastStateStart==LOW)
  {
    returnValue = true;
  }
  
  lastStateStart = dRead;
  return returnValue;
=======
  button_start_stop.update();
  int value = button_start_stop.read();

  // Turn on the LED if either button is pressed :
 if ( value == LOW && !justPressedStart)
  {
    justPressedStart = true;
    return true;
  }else
  {
    justPressedStart = false;
    return false;
  }
>>>>>>> origin/master
}

int lastStateStop = LOW;

boolean checkButtonResetClick()
{
<<<<<<< HEAD
  int dRead = digitalRead(button_lap_reset);
  bool returnValue = false;
  if(dRead == HIGH && lastStateStop == LOW)
  {
    returnValue = true;
=======
   button_lap_reset.update();
  int value = button_lap_reset.read();

  // Turn on the LED if either button is pressed :
  if ( value == LOW && !justPressedReset)
  {
    justPressedReset = true;
    return true;
  }else
  {
    justPressedReset = false;
    return false;
>>>>>>> origin/master
  }
  
  lastStateStop = dRead;
  return returnValue;
}

void loop() {
  switch(state)
  {
    case STATE_READY:
      processStateReady();
      break;
    case STATE_RUNNING:
      processStateRunning();
      break;
    case STATE_PAUSED:
      processStatePaused();
      break;
  }
  updateDisplay();
}

void passToStateLap()
{
  state = STATE_LAP;
}

void processStateLap()
{
  if(checkButtonResetClick())
  {
    passToStateRunningNoReset();
  }
}

void passToStatePaused()
{
  state = STATE_PAUSED;
  timerPaused = millis();
}

void processStatePaused()
{
  if(checkButtonStartClick())
  {
<<<<<<< HEAD
    timer =+ millis() - timerPaused;
    passToStateRunning();
=======
    timer += millis() - timerPaused;
    passToStateRunningNoReset();
>>>>>>> origin/master
  }
  if(checkButtonResetClick())
  {
    passToStateReady();
  }
}

void passToStateRunningNoReset()
{
  state = STATE_RUNNING;
}

void passToStateReady()
{
  state = STATE_READY;
  timerPaused = 0;
  elapsedTimeInMiliseconds = 0;
  timeToShowMinutes = 0;
  timeToShowSeconds = 0;
  timeToShowDecSeconds = 0;
  timer = 0;
}

void processStateReady()
{
  if(checkButtonStartClick())
  {
    passToStateRunning();
  }
}

void passToStateRunning()
{
  state = STATE_RUNNING;
  timerPaused = 0;
  timer = millis();
  elapsedTimeInMiliseconds = 0;
  timeToShowMinutes = 0;
  timeToShowSeconds = 0;
  timeToShowDecSeconds = 0;
}

void processStateRunning()
{
  elapsedTimeInMiliseconds = millis() - timer;
  //minutos 
  timeToShowMinutes = (elapsedTimeInMiliseconds / 60000) * 10000;
  elapsedTimeInMiliseconds = elapsedTimeInMiliseconds % 60000;

  timeToShowSeconds = (elapsedTimeInMiliseconds / 1000) * 100;
  elapsedTimeInMiliseconds = elapsedTimeInMiliseconds % 1000;
  
  timeToShowDecSeconds = (elapsedTimeInMiliseconds / 10);
  if(checkButtonStartClick())
  {
    passToStatePaused();
  }
}

void updateDisplay()
{
  sevseg.setNumber(timeToShowMinutes + timeToShowSeconds + timeToShowDecSeconds, 1);
  //sevseg.setNumber(123456, 1);
  
  sevseg.refreshDisplay(); // Must run repeatedly
}

/// END ///
