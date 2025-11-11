// #include "DCInterface.h"
// #include <fcntl.h>
// #include <unistd.h>
// #include <sys/ioctl.h>
// #include <linux/i2c-dev.h>
// #include <iostream>

// I2CInterface::I2CInterface(int bus, int address) : i2cBus(bus), deviceAddress(address) {
// }

// int I2CInterface::read_address(int address) {
//     char filename[20];
//     snprintf(filename, 19, "/dev/i2c-%d", i2cBus);
//     int file = open(filename, O_RDWR);
    
//     if (file < 0) {
//         std::cerr << "Failed to open I2C bus " << i2cBus << std::endl;
//         return -1;
//     }
    
//     if (ioctl(file, I2C_SLAVE, deviceAddress) < 0) {
//         std::cerr << "Failed to acquire bus access or talk to slave" << std::endl;
//         close(file);
//         return -1;
//     }
    
//     // Read from specific register
//     uint8_t reg = address;
//     if (write(file, &reg, 1) != 1) {
//         std::cerr << "Failed to write to I2C device" << std::endl;
//         close(file);
//         return -1;
//     }
    
//     uint8_t data[2] = {0};
//     if (read(file, data, 2) != 2) {
//         std::cerr << "Failed to read from I2C device" << std::endl;
//         close(file);
//         return -1;
//     }
    
//     close(file);
//     return (data[0] << 8) | data[1];
// }

// void I2CInterface::write_address(int address, int data) {
//     char filename[20];
//     snprintf(filename, 19, "/dev/i2c-%d", i2cBus);
//     int file = open(filename, O_RDWR);
    
//     if (file < 0) {
//         std::cerr << "Failed to open I2C bus " << i2cBus << std::endl;
//         return;
//     }
    
//     if (ioctl(file, I2C_SLAVE, deviceAddress) < 0) {
//         std::cerr << "Failed to acquire bus access or talk to slave" << std::endl;
//         close(file);
//         return;
//     }
    
//     uint8_t buffer[3] = {static_cast<uint8_t>(address), 
//                          static_cast<uint8_t>(data >> 8), 
//                          static_cast<uint8_t>(data & 0xFF)};
    
//     if (write(file, buffer, 3) != 3) {
//         std::cerr << "Failed to write to I2C device" << std::endl;
//     }
    
//     close(file);
// }