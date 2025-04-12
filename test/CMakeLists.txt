cmake_minimum_required(VERSION 3.22)

if (NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif()
message("Build type: " ${CMAKE_BUILD_TYPE})
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(-Wall -Wextra -pedantic -Werror)

project(SignalGeneratorTests VERSION 1.0 LANGUAGES CXX)

add_executable(${CMAKE_PROJECT_NAME}
    TestModule.cpp

    mocks/DACPeripheralMock.cpp

    FrequencyTest.cpp
    ../src/signals/Frequency.cpp
)

find_package(Boost 1.87.0 REQUIRED COMPONENTS unit_test_framework)
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE ${Boost_INCLUDE_DIRS})
target_link_libraries(${CMAKE_PROJECT_NAME} Boost::unit_test_framework)
