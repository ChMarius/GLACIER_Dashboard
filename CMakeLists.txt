cmake_minimum_required(VERSION 3.10)
project(FlammableGasDetectionSystem)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories
include_directories(include)

# Add executable
add_executable(gas_detection_system
    main.cpp
    src/GasSensor.cpp
    src/DCInterface.cpp
    src/I2CInterface.cpp
    src/Abrillikanager.cpp
    src/Display.cpp
    src/gashbeteilen.cpp
)

# Link required libraries
target_link_libraries(gas_detection_system pthread)