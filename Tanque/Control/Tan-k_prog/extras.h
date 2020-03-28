#ifndef EXTRAS_H // if x.h hasn't been included yet...
#define EXTRAS_H //   #define this so the compiler knows it has been included

#include <DS1307RTC.h>
#include <Time.h>
#include <TimeLib.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <AccelStepper.h>
#include <Wire.h>
#include <SD.h>

#include "extras.h"

void revisarAlerta(int, int, AccelStepper, AccelStepper);
void activarAlerta(int , AccelStepper, AccelStepper);
void desactivarAlerta(int, AccelStepper, AccelStepper);
void pruebaSerial(float[]);
void moverMotores(AccelStepper, AccelStepper);

#endif