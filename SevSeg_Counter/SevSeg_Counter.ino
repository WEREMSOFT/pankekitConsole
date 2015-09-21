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

SevSeg sevseg; //Instantiate a seven segment controller object

static const unsigned int STATE_READY = 0;
static const unsigned int STATE_RUNNING = 1;
static const unsigned int STATE_PAUSED = 2;
static const unsigned int STATE_LAP = 3;

unsigned int state = STATE_READY;

byte button_start_stop = A0;
byte button_lap_reset = A1;
  
static unsigned long timer = millis();
static unsigned long timerPaused = millis();
static unsigned long elapsedTimeInMiliseconds = 0;
static unsigned long timeToShowMinutes = 0;
static unsigned long timeToShowSeconds = 0;
static unsigned long timeToShowDecSeconds = 0;
bool just_pressed_start = false;
bool just_pressed_reset = false;
  
void setup() {
  byte numDigits = 6;   
  byte digitPins[] = {5, 4, 3, 2, 1, 0};
  byte segmentPins[] = {6, 7, 8, 9, 10, 11, 12, 13};

  pinMode(button_start_stop, INPUT);  // button pins are inputs
  digitalWrite(button_start_stop, HIGH);  // enable internal pullup; buttons start in high position; logic reversed
  
  pinMode(button_lap_reset, INPUT);  // button pins are inputs
  digitalWrite(button_lap_reset, HIGH);  // enable internal pullup; buttons start in high position; logic reversed

  sevseg.begin(COMMON_ANODE, numDigits, digitPins, segmentPins);
  sevseg.setBrightness(100);

  passToStateReady();
}

bool checkButtonStartClick()
{
  if(digitalRead(button_start_stop) == LOW && !just_pressed_start)
  {
    just_pressed_start = true;
    return true;
  }else
  {
    just_pressed_start = false;
    return false;
  }
 
}

boolean checkButtonResetClick()
{
  if(digitalRead(button_lap_reset) == LOW && !just_pressed_reset)
  {
    just_pressed_reset = true;
    return true;
  }else
  {
    just_pressed_reset = false;
    return false;
  }
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
    timer =+ millis() - timerPaused;
    passToStateRunningNoReset();
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
 // sevseg.setNumber(123456, 1);
  
  sevseg.refreshDisplay(); // Must run repeatedly
}

/// END ///
