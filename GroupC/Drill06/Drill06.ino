// TimedAction.h
#ifndef TIMEDACTION_H
#define TIMEDACTION_H

//#include "arduino.h"

#define NO_PREDELAY 0

class TimedAction {

  public:
    TimedAction(unsigned long interval,void (*function)());
    TimedAction(unsigned long prev,unsigned long interval,void (*function)());

  void reset();
  void disable();
  void enable();
  void check();

  void setInterval( unsigned long interval );

  private:
    bool active;
    unsigned long previous;
    unsigned long interval;
    void (*execute)();

};

#endif


// TimedAction.cpp
TimedAction::TimedAction(unsigned long intervl,void (*function)()){
    active = true;
  previous = 0;
  interval = intervl;
  execute = function;
}

/*
|| <<constructor>>
*/
TimedAction::TimedAction(unsigned long prev,unsigned long intervl,void (*function)()){
    active = true;
  previous = prev;
  interval = intervl;
  execute = function;
}

void TimedAction::reset(){
    previous = millis();
}

void TimedAction::disable(){
    active = false;
}

void TimedAction::enable(){
  active = true;
}

void TimedAction::check(){
  if ( active && (millis()-previous >= interval) ) {
    previous = millis();
    execute();
  }
}

void TimedAction::setInterval( unsigned long intervl){
  interval = intervl;
}


//Start here
#include <TimedAction.h>

char y[8]= {};
String input;
int str_len;
int x=str_len-1;
void serialPrint(char y[8],int str_len)
{
  for(int i=0;i<str_len;i++)//i think 8 chg to x
  {
    Serial.println(char(y[i])); //array need forloop
  }
  y[x]=" ";//we cut one by one bushi,
  x--;

}

TimedAction action2 = TimedAction(1000, serialPrint);

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  if(Serial.available()>0)
    input=char(Serial.read());
  str_len = input.length() + 1;
  input.toCharArray(y,str_len);
  action2.check();
}
