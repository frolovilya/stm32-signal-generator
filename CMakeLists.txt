cmake_minimum_required(VERSION 3.22)

# Compiler settings
set(TOOLCHAIN_PREFIX arm-none-eabi-)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)
set(CMAKE_C_COMPILER_FORCED TRUE)
set(CMAKE_C_COMPILER_ID GNU)
set(CMAKE_C_COMPILER ${TOOLCHAIN_PREFIX}gcc)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_COMPILER_FORCED TRUE)
set(CMAKE_CXX_COMPILER_ID GNU)
set(CMAKE_CXX_COMPILER ${TOOLCHAIN_PREFIX}g++)

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)

set(CMAKE_EXECUTABLE_SUFFIX_CXX ".elf")
set(CMAKE_OBJCOPY ${TOOLCHAIN_PREFIX}objcopy)
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

# Define the default build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()
message("Build type: " ${CMAKE_BUILD_TYPE})

# STM32 CLI
if(NOT PROGRAMMER_CLI)
    set(PROGRAMMER_CLI /opt/ST/STM32CubeCLT_1.18.0/STM32CubeProgrammer/bin/STM32_Programmer_CLI)
endif()
message("Programmer CLI: " ${PROGRAMMER_CLI})

# MCU specific compiler flags
# Configure hardware floating point support for both C and C++ 
set(TARGET_FLAGS "-mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard ")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${TARGET_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${TARGET_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -fdata-sections -ffunction-sections")
if(CMAKE_BUILD_TYPE MATCHES Debug)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -g3")
endif()
if(CMAKE_BUILD_TYPE MATCHES Release)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Os -g0")
endif()
set(CMAKE_CXX_LINK_FLAGS "${TARGET_FLAGS}")
set(CMAKE_CXX_LINK_FLAGS "${CMAKE_CXX_LINK_FLAGS} -T \"${CMAKE_SOURCE_DIR}/src/sys/STM32F446RETx_FLASH.ld\"")
set(CMAKE_CXX_LINK_FLAGS "${CMAKE_CXX_LINK_FLAGS} --specs=nano_c_standard_cpp.specs")
set(CMAKE_CXX_LINK_FLAGS "${CMAKE_CXX_LINK_FLAGS} -Wl,-Map=${CMAKE_PROJECT_NAME}.map -Wl,--gc-sections")
set(CMAKE_CXX_LINK_FLAGS "${CMAKE_CXX_LINK_FLAGS} -Wl,--start-group -lc -lm -Wl,--end-group")
set(CMAKE_CXX_LINK_FLAGS "${CMAKE_CXX_LINK_FLAGS} -Wl,--print-memory-usage")

# Set the project name
set(CMAKE_PROJECT_NAME stm32-wave-generator)

# Core project settings
project(${CMAKE_PROJECT_NAME} VERSION 1.0 LANGUAGES CXX)

enable_language(C CXX ASM)

# Create an executable object type
add_executable(${CMAKE_PROJECT_NAME}
    ./src/Main.cpp

    ./src/sys/syscalls.c
    ./src/sys/sysmem.c
    ./src/sys/system_stm32f4xx.c
    ./src/sys/startup_stm32f446xx.s

    ./src/signals/WaveForm.cpp
    ./src/signals/Frequency.cpp
    ./src/signals/Level.cpp

    ./src/cmd/CommandParser.cpp
    ./src/cmd/Command.cpp

    ./src/peripherals/Peripherals.cpp
    ./src/peripherals/RCCPeripheral.cpp
    ./src/peripherals/UARTPeripheral.cpp
    ./src/peripherals/UART2Peripheral.cpp
    ./src/peripherals/UART3Peripheral.cpp
    ./src/peripherals/DACPeripheral.cpp
    ./src/peripherals/ADCPeripheral.cpp
)

find_path(WELLE_HEADER_PATH Welle.hpp PATHS /usr/local/include)
message("-- Welle Header: " ${WELLE_HEADER_PATH})
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE ${WELLE_HEADER_PATH})

if(USE_USART3)
    message("Using USART3")
    target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE
        USE_USART3
    )
else()
    message("Using USART2")
endif()

target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE
    EMBEDDED
)

add_subdirectory(drivers)

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE
    stm32-drivers
)

# Upload ELF to the device
add_custom_target(flash
    COMMAND ${PROGRAMMER_CLI}
    -c port=swd -w $<TARGET_FILE:${CMAKE_PROJECT_NAME}> -v -rst)
