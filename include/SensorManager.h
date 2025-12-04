#ifndef SENSORMANAGER_H
#define SENSORMANAGER_H

#include "GasSensor.h"
#include <vector>
#include <memory>

class SensorManager {
private:
    std::vector<GasSensor*> sensors;
    
public:
    void calibrateSensors();
    void reactivateSensors();
    void triggerSafetyAlert(bool alert);
    void addSensor(GasSensor* sensor);
    void checkAllSensors();
    void listSensors() const;
};

#endif
