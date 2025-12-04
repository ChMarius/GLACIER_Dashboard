#include "../include/I2CInterface.h"
#include <iostream>
#include <random>
#include <thread>
#include <chrono>

I2CInterface::I2CInterface(int bus, int address) : i2cBus(bus), deviceAddress(address) {
    // In a real ESP32 implementation, we would initialize Wire here
    // Wire.begin();
}

int I2CInterface::read_address(int address) {
    // For simulation purposes, we'll return random data
    // In a real implementation, this would perform actual I2C reads using Wire
    
    // Simple random generation that works on ESP32
    int value = rand() % 1024;
    
    // Simulate I2C read delay
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    
    return value;
}

void I2CInterface::write_address(int address, int data) {
    // For simulation purposes, we'll just print the write operation
    // In a real implementation, this would perform actual I2C writes using Wire
    
    // Simulate I2C write delay
    std::this_thread::sleep_for(std::chrono::milliseconds(5));
}