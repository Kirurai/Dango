#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

//Declaremos los pines CE y el CSN
#define CE_PIN 9
#define CSN_PIN 10
 
//Variable con la dirección del canal por donde se va a transmitir
byte direccion[5] ={'t','a','n','-','k'};

//creamos el objeto radio (NRF24L01)
RF24 radio(CE_PIN, CSN_PIN);


#define SW_pin  6
#define Y_pin  A0
#define X_pin  A1

#define boton1  5             //Botón         
#define boton2  4             //Botón          
#define boton3  A3           //La entrada analogica la tomo como digital     
#define ntc  A2           //Sensor de temperatura para las 18650.
    
#define ledOK  8          //Led indicador de emparejamiento del NRF24L01
#define alerta 7           //Led indicador de alerta.

float datosValores[7];


void setup()
{
  //inicializamos el NRF24L01 
  radio.begin();
  //inicializamos el puerto serie
  Serial.begin(9600); 
 
//Abrimos un canal de escritura
 radio.openWritingPipe(direccion);

  //Configurando el Joystick0
  pinMode(SW_pin, INPUT);
  pinMode(boton1, INPUT);
  pinMode(boton2, INPUT);
  pinMode(boton3, INPUT);
  pinMode(ledOK, OUTPUT);
  pinMode(alerta, OUTPUT);
  digitalWrite(alerta, false);
  digitalWrite(ledOK, false);
  
}
 
void loop()
{ 

 //cargamos los datosValores en la variable datosValores[]
 datosValores[0]= analogRead(X_pin);
 datosValores[1]= analogRead(Y_pin);
 datosValores[2]= digitalRead(SW_pin);
 datosValores[3]= digitalRead(boton1);
 datosValores[4]= digitalRead(boton2);
 datosValores[5]= digitalRead(boton3);
 datosValores[6]= analogRead(ntc);
 
 datosValores[0] = (-1)*round(datosValores[0]/100 - 5);
 datosValores[1] = (-1)*round(datosValores[1]/100 - 5);
 
 //enviamos los datos
 bool ok = radio.write(datosValores, sizeof(datosValores));
  //reportamos por el puerto serial los datos enviados 
  if(ok)
  {
     digitalWrite(8, true);
     digitalWrite(7, false);
     Serial.println("Se ha establecido la comunicación.");
  }
  else
  {
     digitalWrite(8, false);
     digitalWrite(7, true);
     Serial.println("no se ha podido enviar");
  }
}
 
