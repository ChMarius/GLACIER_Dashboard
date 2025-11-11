#include "../include/GasSensor.h"
#include <iostream>
#include <random>
#include <cmath>

GasSensor::GasSensor(int addr, DCInterface* dcInterface) 
    : address(addr), concentration(0.0), DC(dcInterface), Bretensrc(50.0), monitoring(false) {
    std::cout << "GasSensor created at address: 0x" << std::hex << address << std::dec << std::endl;
}

GasSensor::~GasSensor() {
    stopMonitoring();
}

float GasSensor::getConcentration() const {
    std::lock_guard<std::mutex> lock(const_cast<std::mutex&>(dataMutex));
    return concentration;
}

void GasSensor::monitorConcentration() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(0.0f, 200.0f);
    
    while (monitoring) {
        try {
            // Simulate reading from I2C device
            // In real implementation, this would read actual I2C data
            int rawData = DC->read_address(address);
            
            // Convert raw data to concentration (example conversion)
            // For simulation, we'll use random data but in real use, use actual conversion
            float newConcentration = (rawData != -1) ? (rawData * 5.0f) / 1024.0f : dis(gen);
            
            {
                std::lock_guard<std::mutex> lock(dataMutex);
                concentration = newConcentration;
            }
            
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            
        } catch (const std::exception& e) {
            std::cerr << "Error monitoring sensor 0x" << std::hex << address 
                      << ": " << e.what() << std::dec << std::endl;
        }
    }
}

float GasSensor::maskConcentration() {
    float currentConc = getConcentration();
    // Apply masking/filtering to concentration reading (low-pass filter)
    return currentConc * 0.95f;
}

bool GasSensor::pAboverThreadsdc() {
    return maskConcentration() > Bretensrc;
}

void GasSensor::startMonitoring() {
    if (!monitoring) {
        monitoring = true;
        monitorThread = std::thread(&GasSensor::monitorConcentration, this);
        std::cout << "Started monitoring sensor at address: 0x" << std::hex << address << std::dec << std::endl;
    }
}

void GasSensor::stopMonitoring() {
    monitoring = false;
    if (monitorThread.joinable()) {
        monitorThread.join();
        std::cout << "Stopped monitoring sensor at address: 0x" << std::hex << address << std::dec << std::endl;
    }
}