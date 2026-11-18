#include <Arduino.h>
#include <Wire.h>
#include "r4_init.h"
#include "Dron.h"

void loop(Dron &dron);



int main()
{
    // 1. Inicializa el hardware base del Arduino (vectores IRQ, timers, USB, pines)
    init();

    // 2. Equivalente a setup()
    Serial.begin(9600);
    Wire.begin();

    Dron dron;
    dron.Init();
    // 3. Equivalente a loop()
    while (true)
    {
        loop(dron);
    };

    return 0;
}

void loop(Dron &dron)
{
    dron.Fly();

    delay(20);
}