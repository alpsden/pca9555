add_library(PCA9555 INTERFACE)

target_sources(PCA9555 INTERFACE
  ${CMAKE_CURRENT_LIST_DIR}/pca9555.cpp
)

#edit as per your stdio output setup
pico_enable_stdio_usb(PCA9555 1)
pico_enable_stdio_uart(PCA9555 0)

target_include_directories(PCA9555 INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)

target_link_libraries(PCA9555 INTERFACE pico_stdlib hardware_i2c)