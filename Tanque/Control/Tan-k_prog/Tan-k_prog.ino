#include <DS1307RTC.h>
#include <Time.h>
#include <TimeLib.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <AccelStepper.h>
#include <Wire.h>
#include <SD.h>

//Declaremos los pines CE y el CSN
#define CE_PIN 9
#define CSN_PIN 10
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

//Variable con la dirección del canal que se va a leer
byte direccion[5] = {'c', 'a', 'n', 'a', 'l'};

//creamos el objeto radio (NRF24L01)
RF24 radio(CE_PIN, CSN_PIN);

//vector para los datos recibidos
float datos[7];
float newdatos[7];
int auxiliar;
const int cambioVel = 200;

AccelStepper motorIZQ = AccelStepper(DRV8825, pulsosIZQ, dirIZQ); //Creamos la instancia motor Izquierdo
AccelStepper motorDER = AccelStepper(DRV8825, pulsosDER, dirDER); //Creamos la instancia motor Derecho

int relojito = 0;

void revisarAlerta(int, int, AccelStepper, AccelStepper);
void activarAlerta(int, AccelStepper, AccelStepper);
void desactivarAlerta(int, AccelStepper, AccelStepper);
boolean comparar(float[], float[]);
void moverMotores(AccelStepper, AccelStepper);
void pruebaSerial(float[]);

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

   motorIZQ.setMaxSpeed(1000); //Definimos la velocidad maxima del motor izq
   motorDER.setMaxSpeed(1000); //Definimos la velocidad maxima del motor der

   motorIZQ.setSpeed(0);
   motorDER.setSpeed(0);
}

void loop(){
   if (relojito % 2000 == 0){
      relojito = 1;
      if (radio.available()){
         moverMotores(motorIZQ, motorDER);
         digitalWrite(LedOKA, true);
         digitalWrite(LedALR, false);

         //Leemos los datos y los guardamos en la variable datos[]
         radio.read(datos, sizeof(datos));
         revisarAlerta(Fault, LedALR, motorIZQ, motorDER);
         auxiliar = datos[0];

         if ((auxiliar > -6) && (auxiliar < 6)){
            motorIZQ.setSpeed(auxiliar * cambioVel * (-1));
            motorDER.setSpeed(auxiliar * cambioVel * (-1));
         }else{
            activarAlerta(LedALR, motorIZQ, motorDER);
         }

         moverMotores(motorIZQ, motorDER);
         auxiliar = datos[1];

         if ((auxiliar > -6) && (auxiliar < 6)){
            motorIZQ.setSpeed(auxiliar * cambioVel);
            motorDER.setSpeed(auxiliar * cambioVel * (-1));
         }else{
            activarAlerta(LedALR, motorIZQ, motorDER);
         }

         moverMotores(motorIZQ, motorDER);
         revisarAlerta(Fault, LedALR, motorIZQ, motorDER);
      }else{
         for (int i = 0; i < 2; i++)
         {

            delay(150);
            digitalWrite(LedOKA, false);
            delay(150);
            digitalWrite(LedOKA, true);
         }
      }
   //pruebaSerial(datos);
}else{
   moverMotores(motorIZQ, motorDER);
   relojito++;
}
}

boolean comparar(float datos[], float newdatos[])
{
   for (int i = 0; i <= 7; i++)
   {
      if (datos[i] != newdatos[i])
      {
         return false;
      }
   }
   Serial.println();
   Serial.print("NewDatos: ");
   for (int i = 0; i < 7; i++)
   {
      Serial.print(newdatos[i]);
      Serial.print(" / ");
   }
   Serial.println();
   Serial.println("Dentro del While");
   return true;
}

void revisarAlerta(int fault, int LedALR, AccelStepper motorL, AccelStepper motorR)
{
   if (!digitalRead(fault))
   {
      activarAlerta(LedALR, motorL, motorR);
   }
   else
   {
      desactivarAlerta(LedALR, motorL, motorR);
   }
}

void activarAlerta(int LedALR, AccelStepper motorL, AccelStepper motorR)
{
   digitalWrite(LedOKA, false);
   for (int i = 0; i < 2; i++)
   {
      delay(150);
      digitalWrite(LedALR, false);
      delay(150);
      digitalWrite(LedALR, true);
   }
   motorL.stop();
   motorR.stop();
}

void desactivarAlerta(int LedALR, AccelStepper motorL, AccelStepper motorR)
{
   digitalWrite(LedALR, false);
   digitalWrite(LedOKA, true);
   motorL.runSpeed();
   motorR.runSpeed();
}
void pruebaSerial(float datos[])
{
   Serial.print("Datos: ");
   for (int i = 0; i < 7; i++)
   {
      Serial.print(datos[i]);
      Serial.print(" / ");
   }
}
void moverMotores(AccelStepper motorL, AccelStepper motorR)
{
   motorL.runSpeed();
   motorR.runSpeed();
}
