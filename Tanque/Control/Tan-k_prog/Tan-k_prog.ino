#include <DS1307RTC.h>
#include <Time.h>
#include <TimeLib.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <AccelStepper.h>
#include <Wire.h>
#include <SD.h>

#define CS 2

#define LedALR A1 //Salida led indicadora de que hay un problema
#define LedOKA A0 //Salida led indicadora de que está todo OKAY

#define pulsosDER 5 //Motor derecho visto desde el frente
#define pulsosIZQ 6 //Motor izquierdo visto desde el frente
#define dirDER 7    //dirección del motor derecho
#define dirIZQ 4    //dirección del motor izquierdo
#define DRV8825 1   //Tipo de interfas del motor

#define Fault 8 //Entrada por si hay algún problema con los DRV8825

#define buzzer 3 //Salida del Parlante indicador
#define NTC1 A2  //Entrada para sensar temperaturas o alguna LDR
#define NTC2 A3  //Entrada para sensar temperaturas o alguna LDR

int ejeX;
int ejeY;
int coef;
const int velMax = 1000;
const int cteVel = 200;

AccelStepper motorIZQ = AccelStepper(DRV8825, pulsosIZQ, dirIZQ); //Creamos la instancia motor Izquierdo
AccelStepper motorDER = AccelStepper(DRV8825, pulsosDER, dirDER); //Creamos la instancia motor Derecho

int relojito = 0;

//Declaremos los pines CE y el CSN
#define CE_PIN 9
#define CSN_PIN 10

//Variable con la dirección del canal que se va a leer
byte direccion[5] = {'t', 'a', 'n', '-', 'k'};

//creamos el objeto radio (NRF24L01)
RF24 radio(CE_PIN, CSN_PIN);

//vector para los datos recibidos
float datos[7];
float newdatos[7];

void setup(){
   //inicializamos el NRF24L01
   radio.begin();
   //inicializamos el puerto serie
   Serial.begin(9600);
   //Abrimos el canal de Lectura
   radio.openReadingPipe(1, direccion);
   //empezamos a escuchar por el canal
   radio.startListening();

   pinMode(Fault, INPUT);
   pinMode(buzzer, OUTPUT);
   pinMode(LedOKA, OUTPUT);
   pinMode(LedALR, OUTPUT);
   digitalWrite(LedOKA, false);
   digitalWrite(LedALR, false);

   motorIZQ.setMaxSpeed(velMax); //Definimos la velocidad maxima del motor izq
   motorDER.setMaxSpeed(1000); //Definimos la velocidad maxima del motor der

   motorIZQ.setSpeed(0);
   motorDER.setSpeed(0);
}

void loop(){
   if (relojito % 2000 == 0){
      relojito = 1;
      if (radio.available()){
         motorIZQ.runSpeed();
         motorDER.runSpeed();
         digitalWrite(LedOKA, true);
         digitalWrite(LedALR, false);

         //Leemos los datos y los guardamos en la variable datos[]
         radio.read(datos, sizeof(datos));

         ejeX = datos[0];
         ejeY = datos[1];
  
         if (abs(ejeX) + abs(ejeY) <= 5){
            if (ejeY > 0){
                if (ejeX > 0){
                    motorIZQ.setSpeed((ejeY + ejeX)*cteVel);
                    motorDER.setSpeed((ejeY)*cteVel*(-1));
                }else{
                    motorIZQ.setSpeed((ejeY)*cteVel);
                    motorDER.setSpeed((ejeY - ejeX)*cteVel*(-1));
                }
            }else{
                if (ejeX > 0){
                    motorIZQ.setSpeed((ejeY - ejeX)*cteVel*(-1));
                    motorDER.setSpeed((ejeY)*cteVel);
                }else{
                    motorIZQ.setSpeed((ejeY)*cteVel);
                    motorDER.setSpeed((ejeY + ejeX)*cteVel*(-1));
                }
            }
         }         
         motorIZQ.runSpeed();
         motorDER.runSpeed();
         revisarAlerta(Fault, LedALR, motorIZQ, motorDER);
      }else{
         for (int i = 0; i < 2; i++){

            delay(150);
            digitalWrite(LedOKA, false);
            delay(150);
            digitalWrite(LedOKA, true);
         }
      }
    }else{
        motorIZQ.runSpeed();
        motorDER.runSpeed();
        relojito++;
    }
}