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
    DCInterface* DC;
    float Bretensrc;  // Threshold value
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
    float getThreshold() const { return Bretensrc; }
    void setThreshold(float threshold) { Bretensrc = threshold; }
    
    float maskConcentration();
    bool pAboverThreadsdc();  // Check if above threshold
    void startMonitoring();
    void stopMonitoring();
};

#endif