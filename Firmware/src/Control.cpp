#include <Control.h>
#include <ArduinoBLE.h>



void Init()
{
    BLEService droneService("19B10000-E8F2-537E-4F6C-D104768A1214");
    BLEByteCharacteristic throttleChar("19B10001-E8F2-537E-4F6C-D104768A1214", BLERead | BLEWrite);
}
