#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

//Declaremos los pines CE y el CSN
#define CE_PIN 9
#define CSN_PIN 10

#define SW_pin  8
#define Y_pin  A7
#define X_pin  A6

#define boton1  A3           //La entrada analogica la tomo como digital
#define boton2  A2           //La entrada analogica la tomo como digital
#define boton3  A1           //La entrada analogica la tomo como digital     
#define ntc  A0

 
//Variable con la dirección del canal por donde se va a transmitir
byte direccion[5] ={'c','a','n','a','l'};

//creamos el objeto radio (NRF24L01)
RF24 radio(CE_PIN, CSN_PIN);

//vector con los datosValores a enviar
float datosValores[7];
String datosNombre[] = {"Eje X = ",
                        "Eje Y = ",
                        "Boton Joystick = ",
                        "Boton 1 = ",
                        "Boton 2 = ",
                        "Boton 3 = ",
                        "Boton 4 = " };

void setup()
{
  //Configurando el Joystick
  pinMode(SW_pin, INPUT);
  pinMode(boton1, INPUT);
  pinMode(boton2, INPUT);
  pinMode(boton3, INPUT);
  digitalWrite(SW_pin, HIGH);
  
  //Inicializando el NRF24L01 
  radio.begin();
  //Inicializando el puerto serie
  Serial.begin(9600); 
 
  //Abriendo un canal de escritura
  radio.openWritingPipe(direccion);
 
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
 //enviamos los datosValores
 bool ok = radio.write(datosValores, sizeof(datosValores));
  //reportamos por el puerto serial los datosValores enviados 
  if(ok)
  {
    for (int i = 0; i < 7; i++){
      if (datosValores[i] != -1){
       Serial.print(datosNombre[i]);
       Serial.println(datosValores[i]);
      }
    }
  }
  else
  {
     Serial.println("no se ha podido enviar");
  }
  delay(1000);
}
