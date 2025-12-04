#ifndef GASSENSOR_H
#define GASSENSOR_H

#include "DCInterface.h"
#include <atomic>
#include <thread>
#include <chrono>
#include <mutex>

class GasSensor {
private:
    int address;
    float concentration;
    DCInterface* dcInterface;
    float threshold;
    std::atomic<bool> monitoring;
    std::thread monitorThread;
    std::mutex dataMutex;
    
    void monitorConcentration();

public:
    GasSensor(int addr, DCInterface* dcInterface);
    ~GasSensor();
    
    // Delete copy constructor and assignment operator
    GasSensor(const GasSensor&) = delete;
    GasSensor& operator=(const GasSensor&) = delete;
    
    float getConcentration() const;
    int getAddress() const { return address; }
    float getThreshold() const { return threshold; }
    void setThreshold(float newThreshold) { threshold = newThreshold; }
    
    float maskConcentration();
    bool isAboveThreshold();
    void startMonitoring();
    void stopMonitoring();
};

#endif