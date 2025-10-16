cmake_minimum_required(VERSION 3.13)

set(PICO_BOARD pico_w)

# --- SDK paths ---
set(PICO_SDK_PATH "C:/Users/aydil/.pico-sdk/sdk/2.2.0")
include(${PICO_SDK_PATH}/pico_sdk_init.cmake)

# set(PICO_EXTRAS_PATH "C:/Users/aydil/Documents/Pico-v1.5.1/pico-extras")
# include(${PICO_EXTRAS_PATH}/external/pico_extras_import.cmake OPTIONAL)

project(picohttps)

# Initialize the SDK AFTER project() is declared
pico_sdk_init()

# --- Executable ---
add_executable(picohttps
    main.c
)

# --- Preprocessor defines ---
target_compile_definitions(picohttps PRIVATE
    PICO_STDIO_USB_CONNECT_WAIT_TIMEOUT_MS=3000
    # PICOHTTPS_WIFI_PASSWORD=\"$ENV{PICOHTTPS_WIFI_PASSWORD}\"
)

# --- Includes ---
target_include_directories(picohttps PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}

    # lwIP core + apps
    ${PICO_SDK_PATH}/lib/lwip/src/include
    ${PICO_SDK_PATH}/lib/lwip/src/apps/altcp_tls

    # cyw43 Wi-Fi driver (from extras)
    ${PICO_EXTRAS_PATH}/src/rp2_common/pico_cyw43_driver/include
)

# --- Link libraries ---
target_link_libraries(picohttps
    pico_stdlib
    pico_stdio_usb
    pico_cyw43_arch_lwip_threadsafe_background
    pico_lwip_mbedtls
    pico_mbedtls
)

# --- Outputs ---
pico_add_extra_outputs(picohttps)

# --- Export compile commands for IntelliSense ---
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
