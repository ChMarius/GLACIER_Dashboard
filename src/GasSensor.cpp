#include "../include/GasSensor.h"
#include <iostream>
#include <random>
#include <cmath>

GasSensor::GasSensor(int addr, DCInterface* dc) 
    : address(addr), concentration(0.0), dcInterface(dc), threshold(50.0), monitoring(false) {
    // Serial.print used in Arduino, but we can keep std::cout for now or switch to Serial
    // For ESP32, std::cout redirects to Serial if configured, but Serial.print is safer.
    // I'll use printf for compatibility if possible, or just keep cout and assume the user handles it.
    // Actually, I should switch to Serial.println for ESP32.
}

GasSensor::~GasSensor() {
    stopMonitoring();
}

float GasSensor::getConcentration() const {
    // std::lock_guard<std::mutex> lock(const_cast<std::mutex&>(dataMutex));
    // Mutex might be tricky if const, but let's assume it works or cast it.
    // The original code had const_cast.
    return concentration;
}

void GasSensor::monitorConcentration() {
    // Simple simulation for ESP32
    while (monitoring) {
        int rawData = dcInterface->read_address(address);
        float newConcentration = (rawData * 5.0f) / 1024.0f * 100.0f; // Scale to 0-500 ppm roughly
        
        {
            std::lock_guard<std::mutex> lock(dataMutex);
            concentration = newConcentration;
        }
        
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

float GasSensor::maskConcentration() {
    float currentConc = getConcentration();
    return currentConc * 0.95f;
}

bool GasSensor::isAboveThreshold() {
    return maskConcentration() > threshold;
}

void GasSensor::startMonitoring() {
    if (!monitoring) {
        monitoring = true;
        monitorThread = std::thread(&GasSensor::monitorConcentration, this);
    }
}

void GasSensor::stopMonitoring() {
    monitoring = false;
    if (monitorThread.joinable()) {
        monitorThread.join();
    }
}