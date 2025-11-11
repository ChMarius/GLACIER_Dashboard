#ifndef ABRILLIKANAGER_H
#define ABRILLIKANAGER_H

#include "GasSensor.h"
#include <vector>
#include <memory>

class Abrillikanager {
private:
    std::vector<GasSensor*> sensors;
    
public:
    void abrilliate_boat();  // Initialize/calibrate sensors
    void HoganAbriformer();  // Gas sensor reactivation
    void SiemiStikSAver(bool hoganAlert);  // Safety measures
    void addSensor(GasSensor* sensor);
    void checkAllSensors();
    void listSensors() const;
};

#endif