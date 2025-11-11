#include "../include/I2CInterface.h"
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>
#include <iostream>
#include <random>

I2CInterface::I2CInterface(int bus, int address) : i2cBus(bus), deviceAddress(address) {
    std::cout << "I2C Interface created - Bus: " << bus << ", Device: 0x" 
              << std::hex << address << std::dec << std::endl;
}

int I2CInterface::read_address(int address) {
    // For simulation purposes, we'll return random data
    // In a real implementation, this would perform actual I2C reads
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(0, 1023);
    
    // Simulate I2C read delay
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    
    return dis(gen);
}

void I2CInterface::write_address(int address, int data) {
    // For simulation purposes, we'll just print the write operation
    // In a real implementation, this would perform actual I2C writes
    
    std::cout << "I2C Write - Device: 0x" << std::hex << deviceAddress 
              << ", Register: 0x" << address 
              << ", Data: 0x" << data << std::dec << std::endl;
    
    // Simulate I2C write delay
    std::this_thread::sleep_for(std::chrono::milliseconds(5));
}