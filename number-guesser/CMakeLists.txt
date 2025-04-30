cmake_minimum_required(VERSION 3.22)

# User is free to modify the file as much as necessary

# Setup compiler settings
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)

# Define the build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()

# Set the project name
set(CMAKE_PROJECT_NAME number-guesser)

# Include toolchain file
include("cmake/gcc-arm-none-eabi.cmake")

# Enable compile command to ease indexing with e.g. clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

# Core project settings
project(${CMAKE_PROJECT_NAME})

# Enable CMake support for ASM and C languages
enable_language(C ASM)
message("Build type: " ${CMAKE_BUILD_TYPE})

# Find all user sources automatically
file(GLOB USER_SOURCES "Src/*.c")
file(GLOB USER_HEADERS "Inc/*.h")

# Add STM32CubeMX generated sources
add_subdirectory(cmake/stm32cubemx)

# Create an executable object
add_executable(${CMAKE_PROJECT_NAME}
    ${USER_SOURCES}
        Inc/keypad.h
        Src/keypad.c
        Src/dwt.c
        Inc/dwt.h   # Add all user C files
)

# Link directories setup
target_link_directories(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined library search paths (if needed)
)

# Add include paths
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
    Inc              # User headers folder
)

# Add project symbols (macros)
target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined symbols (optional)
)

# Add linked libraries
target_link_libraries(${CMAKE_PROJECT_NAME}
    stm32cubemx
)

# BIN GENERATION
add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD
    COMMAND arm-none-eabi-objcopy -O binary
            $<TARGET_FILE:${CMAKE_PROJECT_NAME}>
            ${CMAKE_BINARY_DIR}/${CMAKE_PROJECT_NAME}.bin
    COMMENT "Generating ${CMAKE_PROJECT_NAME}.bin binary for flashing..."
)

add_custom_target(flash
        COMMAND openocd
        -f interface/stlink.cfg
        -f target/stm32f4x.cfg
        -c "init"
        -c "reset halt"
        -c "flash write_image erase ${CMAKE_BINARY_DIR}/${CMAKE_PROJECT_NAME}.bin 0x08000000"
        -c "verify_image ${CMAKE_BINARY_DIR}/${CMAKE_PROJECT_NAME}.bin 0x08000000"
        -c "reset"
        -c "exit"
        DEPENDS ${CMAKE_PROJECT_NAME}
        COMMENT "Flashing firmware to STM32 using OpenOCD..."
)


add_custom_target(erase
        COMMAND openocd
        -f interface/stlink.cfg
        -f target/stm32f4x.cfg
        -c "init"
        -c "reset halt"
        -c "flash erase_sector 0 0 last"
        -c "reset"
        -c "exit"
        COMMENT "Erasing STM32 flash memory using OpenOCD..."
)