#include "Dron.h"

void loop(Dron &dron);

extern "C" void app_main(void)
{

    Dron dron;
    dron.Init();

    while (true)
    {
        loop(dron);
    };
}

void loop(Dron &dron)
{
    dron.Fly();
}