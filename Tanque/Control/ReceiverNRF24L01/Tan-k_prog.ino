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


#define LedALR A1           //Salida led indicadora de que hay un problema
#define LedOKA A0           //Salida led indicadora de que está todo OKAY

#define pulsosDER 5          //Motor derecho visto desde el frente
#define pulsosIZQ 6          //Motor izquierdo visto desde el frente
#define dirDER 7            //dirección del motor derecho
#define dirIZQ 4            //dirección del motor izquierdo
#define DRV8825 1           //Tipo de interfas del motor

#define Fault 8           //Entrada por si hay algún problema con los DRV8825

#define buzzer 3           //Salida del Parlante indicador
#define NTC1 A2           //Entrada para sensar temperaturas o alguna LDR
#define NTC2 A3           //Entrada para sensar temperaturas o alguna LDR


//Variable con la dirección del canal que se va a leer
byte direccion[5] ={'c','a','n','a','l'}; 

//creamos el objeto radio (NRF24L01)
RF24 radio(CE_PIN, CSN_PIN);

//vector para los datos recibidos
float datos[7];
int auxiliar;

AccelStepper motorIZQ = AccelStepper(DRV8825, pulsosIZQ, dirIZQ);         //Creamos la instancia motor Izquierdo
AccelStepper motorDER = AccelStepper(DRV8825, pulsosDER, dirDER);         //Creamos la instancia motor Derecho



 void revisarAlerta(int, int, AccelStepper, AccelStepper);
 void activarAlerta(int, AccelStepper, AccelStepper);
 void desactivarAlerta(int, AccelStepper, AccelStepper);

void setup()
{
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

  motorIZQ.setMaxSpeed(1000);       //Definimos la velocidad maxima del motor izq
  motorDER.setMaxSpeed(1000);       //Definimos la velocidad maxima del motor der
  motorIZQ.setSpeed(850);
  motorDER.setSpeed(850);
}
 
void loop() {
  motorIZQ.setSpeed(850);
  motorDER.setSpeed(850);
 uint8_t numero_canal;
 //if ( radio.available(&numero_canal) )
 if ( radio.available() )
 {    
       digitalWrite(LedOKA, true);
       //Leemos los datos y los guardamos en la variable datos[]
       radio.read(datos,sizeof(datos));       
       //reportamos por el puerto serial los datos recibidos
       Serial.print("valor de eje X= " );
       Serial.print(datos[0]);
       Serial.print("valor de eje Y= " );
       Serial.print(datos[1]);
       Serial.print("Estado del Boton 1= " );
       Serial.print(datos[2]);
       Serial.print("Estado del Boton 2= " );
       Serial.print(datos[3]);
       Serial.print("Estado del Boton 3= " );
       Serial.print(datos[4]);
       Serial.print("Estado del Boton 4= " );
       Serial.println(datos[6]);

       revisarAlerta(Fault, LedALR, motorDER, motorIZQ);
       
       auxiliar = datos[0];
       if ((auxiliar > -6) && (auxiliar < 6)){
          motorIZQ.setSpeed(auxiliar*(-200));
          motorDER.setSpeed(auxiliar*(-200));
       }else{
          activarAlerta(LedALR, motorDER, motorIZQ);
       }
       auxiliar = datos[1];
       if ((auxiliar>-6) && (auxiliar <6)){
          motorIZQ.setSpeed(auxiliar*200);
          motorDER.setSpeed(auxiliar*(-200));
       }else{
          activarAlerta(LedALR, motorDER, motorIZQ);
       }
       revisarAlerta(Fault, LedALR, motorDER, motorIZQ);
 }
 else
 {
     Serial.println("No hay datos de radio disponibles");
     delay(500);
     digitalWrite(LedOKA, false);
     digitalWrite(LedALR, true);
     delay(500);
 }
 motorIZQ.runSpeed();
 motorDER.runSpeed();
 //delay(1000);
}



void revisarAlerta(int fault, int LedALR, AccelStepper motorDER, AccelStepper motorIZQ){
   if (!digitalRead(fault)){
       activarAlerta(LedALR, motorDER, motorIZQ);
    }else{
       desactivarAlerta(LedALR, motorDER, motorIZQ);
    }
}

void activarAlerta(int LedALR, AccelStepper motorDER, AccelStepper motorIZQ){
    digitalWrite(LedALR, true);
    motorIZQ.stop();
    motorDER.stop();
}

void desactivarAlerta(int LedALR, AccelStepper motorDER, AccelStepper motorIZQ){
    digitalWrite(LedALR, false);
    motorIZQ.runSpeed();
    motorDER.runSpeed(); 
}
