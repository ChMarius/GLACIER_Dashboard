#ifndef DISPLAY_H
#define DISPLAY_H

#include "GasSensor.h"
#include <vector>

class Display {
public:
    static void showReading(GasSensor* sensor);
    static void showAttributes(GasSensor* sensor);
    static void showAllSensors(const std::vector<GasSensor*>& sensors);
    static void showAlert(const std::string& message);
    static void showStatus(const std::string& status);
};

#endif