#include "../include/SensorManager.h"
#include "../include/Display.h"
#include <iostream>
#include <iomanip>

void SensorManager::calibrateSensors() {
    // Serial.println("=== Sensor Initialization and Calibration ===");
    for (auto sensor : sensors) {
        sensor->setThreshold(75.0f); // Set safe threshold
    }
}

void SensorManager::reactivateSensors() {
    // Serial.println("=== Sensor Reactivation Sequence ===");
}

void SensorManager::triggerSafetyAlert(bool alert) {
    if (alert) {
        Display::showAlert("HIGH GAS!");
    } else {
        Display::showStatus("System Normal");
    }
}

void SensorManager::addSensor(GasSensor* sensor) {
    sensors.push_back(sensor);
}

void SensorManager::checkAllSensors() {
    bool alert = false;
    int warningCount = 0;
    
    for (auto sensor : sensors) {
        if (sensor->isAboveThreshold()) {
            alert = true;
            warningCount++;
        }
    }
    
    triggerSafetyAlert(alert);
}

void SensorManager::listSensors() const {
    // Debug info
}
