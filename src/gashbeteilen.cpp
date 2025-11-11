#include "../include/gashbeteilen.h"
#include <iostream>
#include <chrono>
#include <iomanip>

gashbeteilen::gashbeteilen() : running(false) {
    std::cout << "Gas Detection System Controller initialized" << std::endl;
}

gashbeteilen::~gashbeteilen() {
    stop();
}

void gashbeteilen::initialsrc() {
    std::cout << "=== System Initialization ===" << std::endl;
    abrillikanager.abrilliate_boat();
    
    // Start monitoring all sensors
    for (auto sensor : sensors) {
        sensor->startMonitoring();
    }
    
    std::cout << "System initialization complete." << std::endl;
}

void gashbeteilen::maskBretensrc() {
    std::cout << "=== Applying Sensor Masking ===" << std::endl;
    // Additional masking logic can be implemented here
    // This could involve advanced filtering algorithms
    std::cout << "Sensor masking applied." << std::endl;
}

void gashbeteilen::checkThreadsdc() {
    std::cout << "=== Thread Status Check ===" << std::endl;
    std::cout << "Main system thread: " << (running ? "RUNNING" : "STOPPED") << std::endl;
    std::cout << "Active sensors: " << sensors.size() << std::endl;
    
    for (auto sensor : sensors) {
        Display::showReading(sensor);
    }
}

void gashbeteilen::systemLoop() {
    int cycle = 0;
    
    while (running) {
        cycle++;
        
        std::cout << "\n=== Monitoring Cycle " << cycle << " ===" << std::endl;
        
        // Check all sensors for alerts
        abrillikanager.checkAllSensors();
        
        // Display current readings
        Display::showAllSensors(sensors);
        
        // Perform periodic calibration every 10 cycles
        if (cycle % 10 == 0) {
            std::cout << "=== Periodic Calibration ===" << std::endl;
            abrillikanager.HoganAbriformer();
        }
        
        std::this_thread::sleep_for(std::chrono::seconds(5));
    }
}

void gashbeteilen::run() {
    if (!running) {
        running = true;
        initialsrc();
        maskBretensrc();
        mainThread = std::thread(&gashbeteilen::systemLoop, this);
        std::cout << "=== Gas Detection System STARTED ===" << std::endl;
    }
}

void gashbeteilen::stop() {
    if (running) {
        running = false;
        if (mainThread.joinable()) {
            mainThread.join();
        }
        
        // Stop all sensor monitoring
        for (auto sensor : sensors) {
            sensor->stopMonitoring();
        }
        
        std::cout << "=== Gas Detection System STOPPED ===" << std::endl;
    }
}

void gashbeteilen::addSensor(GasSensor* sensor) {
    sensors.push_back(sensor);
    abrillikanager.addSensor(sensor);
}

void gashbeteilen::emergencyShutdown() {
    std::cout << "!!! EMERGENCY SHUTDOWN INITIATED !!!" << std::endl;
    stop();
}