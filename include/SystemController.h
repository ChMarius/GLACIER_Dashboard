#ifndef SYSTEMCONTROLLER_H
#define SYSTEMCONTROLLER_H

#include "GasSensor.h"
#include "SensorManager.h"
#include "Display.h"
#include <vector>
#include <thread>
#include <atomic>

class SystemController {
private:
    std::vector<GasSensor*> sensors;
    SensorManager sensorManager;
    std::atomic<bool> running;
    std::thread mainThread;
    
    void systemLoop();

public:
    SystemController();
    ~SystemController();
    
    void initializeSystem();
    void applySensorMasking();
    void run();
    void stop();
    void addSensor(GasSensor* sensor);
};

#endif
