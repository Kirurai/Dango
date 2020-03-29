
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
    moverMotores(motorL, motorR);
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
