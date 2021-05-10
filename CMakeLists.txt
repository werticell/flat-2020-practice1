cmake_minimum_required(VERSION 3.15)
project(FormalLanguagesPracticum-1)

set(CMAKE_CXX_STANDARD 17)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin)

find_package(gtest REQUIRED)
find_package(Threads REQUIRED)
include_directories( ${CMAKE_CURRENT_SOURCE_DIR}  ${GTEST_INCLUDE_DIRS} )
enable_testing()
add_executable(Test main_test.cpp)

add_test(Test ${PROJECT_SOURCE_DIR}/bin/testing)

add_executable(FormalLanguagesPracticum main.cpp)

add_library(RegexpStackMachineLibrary SHARED
        src/State.cpp
        src/RegexpStackMachine.cpp
        include/State.h
        include/RegexpStackMachine.h
        )

target_link_libraries(FormalLanguagesPracticum RegexpStackMachineLibrary)

target_link_libraries(Test RegexpStackMachineLibrary)
target_link_libraries(Test Threads::Threads ${GTEST_LIBRARIES} ${GMOCK_BOTH_LIBRARIES})









