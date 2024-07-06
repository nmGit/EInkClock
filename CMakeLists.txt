project("Clock")
enable_language(CXX C ASM)
cmake_minimum_required(VERSION 3.20)

set(CMAKE_BUILD_TYPE Debug CACHE INTERNAL "")

#### Executable #####
add_executable(EInkClock src/generated/eink_clock_2/Core/Src/main.c)

target_link_options(EInkClock PUBLIC -T C:/Users/Noah/Documents/Projects/Electronics/Clock1/src/generated/eink_clock_2/STM32F103C8Tx_FLASH.ld)

add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/src)

##### External #####
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/external)
target_link_libraries(EInkClock PUBLIC NGL)