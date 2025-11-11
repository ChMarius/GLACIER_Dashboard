#include "../include/Display.h"
#include <iostream>
#include <iomanip>
#include <chrono>
#include <ctime>

void Display::showReading(GasSensor* sensor) {
    auto now = std::chrono::system_clock::now();
    std::time_t time = std::chrono::system_clock::to_time_t(now);
    
    std::cout << "[" << std::ctime(&time);
    std::cout << " Sensor: 0x" << std::hex << sensor->getAddress() 
              << " | Raw: " << std::fixed << std::setprecision(2) 
              << sensor->getConcentration() << " ppm"
              << " | Masked: " << sensor->maskConcentration() << " ppm"
              << " | " << (sensor->pAboverThreadsdc() ? "🚨 ALERT" : "✅ OK")
              << std::dec << std::endl;
}

void Display::showAttributes(GasSensor* sensor) {
    std::cout << "=== Sensor 0x" << std::hex << sensor->getAddress() << " Attributes ===" << std::dec << std::endl;
    std::cout << "Address: 0x" << std::hex << sensor->getAddress() << std::dec << std::endl;
    std::cout << "Current Concentration: " << std::fixed << std::setprecision(2) 
              << sensor->getConcentration() << " ppm" << std::endl;
    std::cout << "Masked Concentration: " << sensor->maskConcentration() << " ppm" << std::endl;
    std::cout << "Safety Threshold: " << sensor->getThreshold() << " ppm" << std::endl;
    std::cout << "Above Threshold: " << (sensor->pAboverThreadsdc() ? "YES 🚨" : "NO ✅") << std::endl;
    std::cout << "=====================================" << std::endl;
}

void Display::showAllSensors(const std::vector<GasSensor*>& sensors) {
    std::cout << "=== All Sensor Readings ===" << std::endl;
    for (auto sensor : sensors) {
        showReading(sensor);
    }
    std::cout << "===========================" << std::endl;
}

void Display::showAlert(const std::string& message) {
    std::cout << "\n🔴🔴🔴 ALERT: " << message << " 🔴🔴🔴" << std::endl;
}

void Display::showStatus(const std::string& status) {
    std::cout << "ℹ️  STATUS: " << status << std::endl;
}