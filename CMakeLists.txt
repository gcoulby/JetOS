# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

# Initialize pico_sdk from installed location
# (note this can come from environment, CMake cache etc)
set(PICO_SDK_PATH "/home/gcoul/pico/pico-sdk")

set(PICO_BOARD pico CACHE STRING "Board type")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(jet-os C CXX ASM)

# Initialize the Raspberry Pi Pico SDK
pico_sdk_init()

# Add the main executable
add_executable(jet-os main.c cli.c Interpretter.c command.c vram.c)

# Additional configuration for main executable
pico_set_program_name(jet-os "jet-os")
pico_set_program_version(jet-os "0.1")
pico_enable_stdio_uart(jet-os 1)
target_link_libraries(jet-os pico_stdlib pico_multicore)

# Add subdirectories
add_subdirectory(gfx)

pico_add_extra_outputs(jet-os)
