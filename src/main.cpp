#ifndef NATIVE_PLATFORM
#include <Arduino.h>
#endif
#include "SystemController.h"
#include "I2CInterface.h"
#include "GasSensor.h"
#include "Display.h"
#include <thread>
#include <chrono>

SystemController* gasSystem;
DCInterface* i2cInterface;

void setupSystem() {
#ifndef NATIVE_PLATFORM
    Serial.begin(115200);
#endif
    
    // Initialize Display
    Display::init();
    
    // Create I2C interface (Mock or Real)
    i2cInterface = new I2CInterface(1, 0x48);
    
    // Create gas detection system
    gasSystem = new SystemController();
    
    // Add sensors
    gasSystem->addSensor(new GasSensor(0x50, i2cInterface));
    gasSystem->addSensor(new GasSensor(0x51, i2cInterface));
    
    // Start the system
    gasSystem->run();
}

#ifndef NATIVE_PLATFORM
void setup() {
    setupSystem();
}

void loop() {
    // The system runs in its own thread, so we just delay here
    delay(1000);
}
#else
int main() {
    setupSystem();
    
    // Keep main thread alive
    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    return 0;
}
#endif