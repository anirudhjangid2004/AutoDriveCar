# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Initialise pico_sdk from installed location
# (note this can come from environment, CMake cache etc)

# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.1.0)
set(toolchainVersion 13_3_Rel1)
set(picotoolVersion 2.1.0)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
set(PICO_BOARD pico_w CACHE STRING "Board type")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(MotorDriverRMCS2303 C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Add executable. Default name is the project name, version 0.1

add_executable(MotorDriverRMCS2303 MotorDriverRMCS2303.c RMCS2303drive.cpp)

pico_set_program_name(MotorDriverRMCS2303 "MotorDriverRMCS2303")
pico_set_program_version(MotorDriverRMCS2303 "0.1")

# Modify the below lines to enable/disable output over UART/USB
pico_enable_stdio_uart(MotorDriverRMCS2303 0)
pico_enable_stdio_usb(MotorDriverRMCS2303 1)

# Add the standard library to the build
target_link_libraries(MotorDriverRMCS2303
        pico_stdlib
        pico_time
        pico_binary_info
        pico_stdio
        hardware_uart)

# Add the standard include files to the build
target_include_directories(MotorDriverRMCS2303 PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
)

# Add any user requested libraries
target_link_libraries(MotorDriverRMCS2303 
        
        )

pico_add_extra_outputs(MotorDriverRMCS2303)

