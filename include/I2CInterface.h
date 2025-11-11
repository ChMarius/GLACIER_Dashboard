#ifndef I2CINTERFACE_H
#define I2CINTERFACE_H

#include "DCInterface.h"

class I2CInterface : public DCInterface {
private:
    int i2cBus;
    int deviceAddress;
    
public:
    I2CInterface(int bus, int address);
    virtual ~I2CInterface() = default;
    
    virtual int read_address(int address) override;
    virtual void write_address(int address, int data) override;
    
    int getBus() const { return i2cBus; }
    int getDeviceAddress() const { return deviceAddress; }
};

#endif