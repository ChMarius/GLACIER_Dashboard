// #ifndef DCINTERFACE_H
// #define DCINTERFACE_H

// class DCInterface {
// public:
//     virtual int read_address(int address) = 0;
//     virtual void write_address(int address, int data) = 0;
//     virtual ~DCInterface() = default;
// };

// // I2C Implementation
// class I2CInterface : public DCInterface {
// private:
//     int i2cBus;
//     int deviceAddress;
    
// public:
//     I2CInterface(int bus, int address);
//     virtual int read_address(int address) override;
//     virtual void write_address(int address, int data) override;
// };

// #endif

#ifndef DCINTERFACE_H
#define DCINTERFACE_H

class DCInterface {
public:
    virtual int read_address(int address) = 0;
    virtual void write_address(int address, int data) = 0;
    virtual ~DCInterface() = default;
};

#endif