#include "../include/SystemController.h"
#include <chrono>

SystemController::SystemController() : running(false) {
}

SystemController::~SystemController() {
    stop();
}

void SystemController::initializeSystem() {
    sensorManager.calibrateSensors();
    for (auto sensor : sensors) {
        sensor->startMonitoring();
    }
}

void SystemController::applySensorMasking() {
    // Logic placeholder
}

void SystemController::systemLoop() {
    while (running) {
        sensorManager.checkAllSensors();
        Display::showAllSensors(sensors);
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

void SystemController::run() {
    if (!running) {
        running = true;
        initializeSystem();
        applySensorMasking();
        mainThread = std::thread(&SystemController::systemLoop, this);
    }
}

void SystemController::stop() {
    if (running) {
        running = false;
        if (mainThread.joinable()) {
            mainThread.join();
        }
        for (auto sensor : sensors) {
            sensor->stopMonitoring();
        }
    }
}

void SystemController::addSensor(GasSensor* sensor) {
    sensors.push_back(sensor);
    sensorManager.addSensor(sensor);
}
