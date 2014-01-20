#ifndef Morse_h
#define Morse_h

#include "Arduino.h"

class Morse {
 public:
  Morse(int pin, int delay);
  void dot();
  void dash();
  void elementPause();
  void letterPause();
  void wordPause();
  void h();
  void k();
  void l();
  void o();
  void s();
  void t();
  void v();
 private:
  int _pin;
  int _delay;
};

#endif
