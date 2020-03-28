
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
