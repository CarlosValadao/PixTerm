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
cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(PICO_BOARD pico_w CACHE STRING "Board type")
include(pico_sdk_import.cmake)
project(PixTerm C CXX ASM)
pico_sdk_init()
add_executable(PixTerm PixTerm.c )

# Modify the below lines to enable/disable output over UART/USB
pico_enable_stdio_uart(PixTerm 0)
pico_enable_stdio_usb(PixTerm 1)

file(MAKE_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/generated)
pico_generate_pio_header(PixTerm ${CMAKE_CURRENT_LIST_DIR}/ws2812.pio OUTPUT_DIR ${CMAKE_CURRENT_LIST_DIR}/generated)
target_sources(PixTerm PRIVATE PixTerm.c inc/ws2812b.c inc/push_button.c 
                                         inc/rgb.c inc/ssd1306.c inc/uart_usb.c
                                         inc/lite5.c inc/ws2812b_motion.c inc/ssd1306_utils.c)
target_link_libraries(PixTerm PRIVATE pico_stdlib hardware_pio
                    hardware_clocks hardware_pwm hardware_timer
                    hardware_i2c hardware_uart)
pico_add_extra_outputs(PixTerm)
