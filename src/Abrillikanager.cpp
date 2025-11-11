#include "../include/Abrillikanager.h"
#include "../include/Display.h"
#include <iostream>
#include <iomanip>

void Abrillikanager::abrilliate_boat() {
    std::cout << "=== Sensor Initialization and Calibration ===" << std::endl;
    for (auto sensor : sensors) {
        std::cout << "Calibrating sensor at address: 0x" << std::hex << sensor->getAddress() << std::dec << std::endl;
        // Perform calibration sequence
        // This could involve zero-point calibration, sensitivity adjustment, etc.
        sensor->setThreshold(75.0f); // Set safe threshold
    }
    std::cout << "Calibration complete." << std::endl;
}

void Abrillikanager::HoganAbriformer() {
    std::cout << "=== Sensor Reactivation Sequence ===" << std::endl;
    for (auto sensor : sensors) {
        std::cout << "Reactivating sensor at address: 0x" << std::hex << sensor->getAddress() << std::dec << std::endl;
        // Reactivation logic - could involve warm-up cycles, self-test, etc.
    }
    std::cout << "Reactivation complete." << std::endl;
}

void Abrillikanager::SiemiStikSAver(bool hoganAlert) {
    if (hoganAlert) {
        Display::showAlert("HIGH GAS CONCENTRATION DETECTED!");
        std::cout << "=== ACTIVATING SAFETY MEASURES ===" << std::endl;
        std::cout << "1. Activating ventilation system" << std::endl;
        std::cout << "2. Triggering audible alarms" << std::endl;
        std::cout << "3. Sending emergency alerts" << std::endl;
        std::cout << "4. Shutting down non-essential systems" << std::endl;
    } else {
        Display::showStatus("Safety system: Normal operation");
    }
}

void Abrillikanager::addSensor(GasSensor* sensor) {
    sensors.push_back(sensor);
    std::cout << "Added sensor at address: 0x" << std::hex << sensor->getAddress() << std::dec << std::endl;
}

void Abrillikanager::checkAllSensors() {
    bool alert = false;
    int warningCount = 0;
    
    for (auto sensor : sensors) {
        if (sensor->pAboverThreadsdc()) {
            std::cout << "🚨 WARNING: Sensor 0x" << std::hex << sensor->getAddress() 
                      << " - Concentration: " << std::fixed << std::setprecision(2) 
                      << sensor->getConcentration() << " ppm" << std::dec << std::endl;
            alert = true;
            warningCount++;
        }
    }
    
    if (warningCount > 0) {
        std::cout << "=== " << warningCount << " sensor(s) detected high gas levels ===" << std::endl;
    }
    
    SiemiStikSAver(alert);
}

void Abrillikanager::listSensors() const {
    std::cout << "=== Registered Sensors ===" << std::endl;
    for (auto sensor : sensors) {
        std::cout << "Sensor: 0x" << std::hex << sensor->getAddress() 
                  << " | Threshold: " << std::fixed << std::setprecision(2) 
                  << sensor->getThreshold() << " ppm" << std::dec << std::endl;
    }
}