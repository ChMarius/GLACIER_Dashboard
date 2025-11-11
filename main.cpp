#include "include/gashbeteilen.h"
#include "include/I2CInterface.h"
#include "include/GasSensor.h"
#include <iostream>
#include <signal.h>
#include <memory>

std::unique_ptr<gashbeteilen> gasSystem;

void signalHandler(int signal) {
    if (gasSystem) {
        gasSystem->stop();
    }
    std::cout << "\nSystem shutdown complete." << std::endl;
    exit(signal);
}

int main() {
    // Setup signal handlers for graceful shutdown
    signal(SIGINT, signalHandler);
    signal(SIGTERM, signalHandler);
    
    std::cout << "=== Flammable Gas Detection System ===" << std::endl;
    std::cout << "Initializing I2C interfaces and sensors..." << std::endl;
    
    try {
        // Create I2C interface (assuming I2C bus 1, device address 0x48)
        DCInterface* i2cInterface = new I2CInterface(1, 0x48);
        
        // Create gas detection system
        gasSystem = std::make_unique<gashbeteilen>();
        
        // Add multiple gas sensors with different addresses
        // These addresses should match your actual gas sensor hardware
        gasSystem->addSensor(new GasSensor(0x50, i2cInterface));  // Sensor 1
        gasSystem->addSensor(new GasSensor(0x51, i2cInterface));  // Sensor 2
        gasSystem->addSensor(new GasSensor(0x52, i2cInterface));  // Sensor 3
        
        // Start the system
        gasSystem->run();
        
        // Keep the system running
        std::cout << "System is now monitoring for flammable gases..." << std::endl;
        std::cout << "Press Ctrl+C to stop the system" << std::endl;
        
        while (true) {
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}