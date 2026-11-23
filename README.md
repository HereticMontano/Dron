# Drone

This is my second project, and it is more MCU-dependent. I need to learn C++, ESP32, RTOS, and the Bluetooth (BLE) protocol.  
I'm using the Bitcraze frame shape to design the PCB, along with two official components: the motors and propellers.

## Objective
Build a flying drone that can handle input from a controller and hover in one place.

## First step (Schematic)
Create a first draft of the schematic: battery, 3.3V voltage regulator, an ESP32, MOSFETs, motors, and an IMU sensor (GY-87).

## Second step (Desk Prototype)
First, I needed to migrate the driver I wrote for the GY-87 from Arduino libraries to native Espressif ESP-IDF so I can use it in the Drone project.

Using LEDs to simulate the motors:  
![Prototype](assets/Led_Engines.jpeg)