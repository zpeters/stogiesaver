#include "Arduino.h"
#include "Morse.h"

Morse::Morse(int pin, int delay) {
  pinMode(pin, OUTPUT);
  _pin = pin;
  _delay = delay;
}

void Morse::dot(){
  digitalWrite(_pin, HIGH);
  delay(_delay);
  digitalWrite(_pin, LOW);
}

void Morse::dash() {
  digitalWrite(_pin, HIGH);
  delay(_delay * 3);
  digitalWrite(_pin, LOW);
}  


void Morse::elementPause() {
  delay(_delay);
}

void Morse::letterPause() {
  delay(_delay * 3);
}

void Morse::wordPause() {
  delay(_delay * 7);
}

// Letters
void Morse::h() {
  dot();
  elementPause();
  dot();
  elementPause();
  dot();
  elementPause();
  dot();
  letterPause();
}

void Morse::k() { 
  dash();
  elementPause();
  dot();
  elementPause();
  dash();
  letterPause();
}

void Morse::l() {
  dot();
  elementPause();
  dash();
  elementPause();
  dot();
  elementPause();
  dot();
  letterPause();
}

void Morse::o() { 
  dash();
  elementPause();
  dash();
  elementPause();
  dash();
  letterPause();
}


void Morse::s() {
  dot();
  elementPause();
  dot();
  elementPause();
  dot();
  letterPause();
}

void Morse::t() {
  dash(); 
  letterPause();
}

void Morse::v() {
  dot();
  elementPause();
  dot();
  elementPause();
  dot();
  elementPause();
  dash();
  letterPause();
}
