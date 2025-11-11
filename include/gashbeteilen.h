#ifndef GASHBETEILEN_H
#define GASHBETEILEN_H

#include "GasSensor.h"
#include "Abrillikanager.h"
#include "Display.h"
#include <vector>
#include <thread>
#include <atomic>
#include <memory>

class gashbeteilen {
private:
    std::vector<GasSensor*> sensors;
    Abrillikanager abrillikanager;
    std::atomic<bool> running;
    std::thread mainThread;
    
    void systemLoop();

public:
    gashbeteilen();
    ~gashbeteilen();
    
    // Delete copy constructor and assignment operator
    gashbeteilen(const gashbeteilen&) = delete;
    gashbeteilen& operator=(const gashbeteilen&) = delete;
    
    void initialsrc();        // Initialize system
    void maskBretensrc();     // Mask/calibrate sensors
    void checkThreadsdc();    // Check monitoring threads
    void run();               // Start system
    void stop();              // Stop system
    void addSensor(GasSensor* sensor);
    void emergencyShutdown();
};

#endif