# PCA9555 rp2040 driver
## Brief 
Easy to use driver for PCA9555(I2C) to use with rp2040. Written in C++

## Sample Code
```c++
/**
 * @file main.c
 * @author Mudit Sharma
 * @brief 
 * @version 0.1
 * @date 2022-07-26
 */

#include <stdio.h>
#include "pico/stdlib.h"
#include "bsp/board.h"
#include "pico/binary_info.h"
#include "hardware/i2c.h"
#include "pca9555.h"

enum
{
    LEVEL_LOW = 1,
    LEVEL_HIGH = 2,
    EDGE_FALL = 3,
    EDGE_RISE = 4
};

void read_val();

pca9555 *int1_p;

/**
 * @brief Interrupt callback function
 *
 * @param gpio
 * @param events
 */
void irq_callback(uint gpio, uint32_t events)
{
    uint16_t readout;
    switch (gpio)
    {
    case 8:
        readout = int1_p->read_input();
        printf("%x \n", readout);

        break;
    default:
        break;
    }
}

int main()
{
    stdio_init_all();

#if !defined(i2c_default) || !defined(PICO_DEFAULT_I2C_SDA_PIN) || !defined(PICO_DEFAULT_I2C_SCL_PIN)
#warning i2c/bus_scan example requires a board with I2C pins
    puts("Default I2C pins were not defined");
#else
    // This example will use I2C0 on the default SDA and SCL pins (GP4, GP5 on a Pico)
    i2c_init(i2c_default, 100 * 1000);
    gpio_set_function(PICO_DEFAULT_I2C_SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(PICO_DEFAULT_I2C_SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(PICO_DEFAULT_I2C_SDA_PIN);
    gpio_pull_up(PICO_DEFAULT_I2C_SCL_PIN);
    // Make the I2C pins available to picotool
    bi_decl(bi_2pins_with_func(PICO_DEFAULT_I2C_SDA_PIN, PICO_DEFAULT_I2C_SCL_PIN, GPIO_FUNC_I2C));
    printf("i2c config \n");
#endif

    // Instance declaration
    // i2c address of io expander set to 0x20 (A0, A1, A2 -> GND)
    // GPIO interrupt pin set to 8
    pca9555 exp1(0x20, 8);
    
    int1_p = &exp1;

    // Attach callback function to the callback function pointer
    gpio_irq_callback_t callback = &irq_callback;

    config_ports_t config_ports;
    // All pins set to input
    config_ports.config_port0.all = ALL_INPUT;
    config_ports.config_port1.all = ALL_INPUT;

    exp1.pin_mode(&config_ports);

    printf("config done \n");

    // enable irq with callback
    gpio_set_irq_enabled_with_callback(8, GPIO_IRQ_LEVEL_LOW, true, callback);

    while (1)
    {
    }

    return 0;
}
}
```
