#include "Dron.h"

void loop(Dron &dron);



extern "C" void app_main(void)
{

     Dron dron;
    dron.Init();
    // 3. Equivalente a loop()
    while (true)
    {
        loop(dron);
    };


    // 3. Equivalente a loop()
}



void loop(Dron &dron)
{
    dron.Fly();
    
}