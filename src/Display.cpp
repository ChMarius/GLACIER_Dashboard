#include "../include/Display.h"

#ifdef ARDUINO
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1

static Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
#else
#include <iostream>
#include <iomanip>
#include <thread>
#include <chrono>
#endif

void Display::init() {
#ifdef ARDUINO
    if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
        // Serial.println(F("SSD1306 allocation failed"));
        for(;;); // Don't proceed, loop forever
    }
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0,0);
    display.println("GLACIER Dashboard");
    display.display();
    delay(2000);
#else
    std::cout << "=== OLED DISPLAY INITIALIZED ===" << std::endl;
    std::cout << "GLACIER Dashboard" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(2));
#endif
}

void Display::showReading(GasSensor* sensor) {
    // Not used directly in current loop
}

void Display::showAllSensors(const std::vector<GasSensor*>& sensors) {
#ifdef ARDUINO
    display.clearDisplay();
    display.setCursor(0,0);
    display.setTextSize(1);
    display.println("Gas Levels:");
    
    for (auto sensor : sensors) {
        display.print("ID: ");
        display.print(sensor->getAddress(), HEX);
        display.print(" ");
        display.print(sensor->getConcentration(), 1);
        display.println(" ppm");
        
        if (sensor->isAboveThreshold()) {
            display.print(" [ALERT]");
        }
        display.println();
    }
    display.display();
#else
    // Clear console (ANSI escape code)
    std::cout << "\033[2J\033[1;1H"; 
    std::cout << "=== DASHBOARD ===" << std::endl;
    std::cout << "Gas Levels:" << std::endl;
    for (auto sensor : sensors) {
        std::cout << "ID: 0x" << std::hex << sensor->getAddress() << std::dec 
                  << " | " << std::fixed << std::setprecision(1) << sensor->getConcentration() << " ppm";
        
        if (sensor->isAboveThreshold()) {
            std::cout << " [ALERT]";
        }
        std::cout << std::endl;
    }
    std::cout << "=================" << std::endl;
#endif
}

void Display::showAlert(const std::string& message) {
#ifdef ARDUINO
    display.clearDisplay();
    display.setCursor(0, 0);
    display.setTextSize(2); // Big text
    display.println("WARNING!");
    display.setTextSize(1);
    display.println(message.c_str());
    display.display();
#else
    std::cout << "\n!!! WARNING: " << message << " !!!\n" << std::endl;
#endif
}

void Display::showStatus(const std::string& status) {
    // Optional status logging
}