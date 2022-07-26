
#ifndef PCA9555_H_
#define PCA9555_H_

#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "pico/binary_info.h"
#include "hardware/i2c.h"

#define HIGH 1
#define LOW 0
#define INPUT 1
#define OUTPUT 0

/** enum with names of ports */
typedef enum
{
    pin0,
    pin1,
    pin2,
    pin3,
    pin4,
    pin5,
    pin6,
    pin7,
    pin8,
    pin9,
    pin10,
    pin11,
    pin12,
    pin13,
    pin14,
    pin15
} pin_num_e;

enum
{
    io00,
    io01,
    io02,
    io03,
    io04,
    io05,
    io06,
    io07
} io_port_0_e;

enum
{
    io10,
    io11,
    io12,
    io13,
    io14,
    io15,
    io16,
    io17
} io_port_1_e;

enum
{
    ip_0,
    ip_1,
    op_0,
    op_1,
    pi_0,
    pi_1,
    cp_0,
    cp_1
} cmd_byte_e;

typedef enum
{
    output,
    input,
    ALL_OUTPUT = 0,
    ALL_INPUT = 0B11111111,
} config_reg_val_e;

typedef enum
{
    retain,
    inverted,
    ALL_RETAINED = 0,
    ALL_INVERTED = 0B11111111
} polarity_reg_val_e;

typedef union
{
    uint8_t all;
    struct
    {
        uint8_t pin0 : 1;
        uint8_t pin1 : 1;
        uint8_t pin2 : 1;
        uint8_t pin3 : 1;
        uint8_t pin4 : 1;
        uint8_t pin5 : 1;
        uint8_t pin6 : 1;
        uint8_t pin7 : 1;

    } bits;

} config_port_t;

typedef struct
{
    config_port_t config_port0;
    config_port_t config_port1;
} config_ports_t;

typedef union
{
    uint8_t all;
    struct
    {
        uint8_t pin0 : 1;
        uint8_t pin1 : 1;
        uint8_t pin2 : 1;
        uint8_t pin3 : 1;
        uint8_t pin4 : 1;
        uint8_t pin5 : 1;
        uint8_t pin6 : 1;
        uint8_t pin7 : 1;

    } bits;

} polarity_port_t;

typedef struct
{
    polarity_port_t polarity_port0;
    polarity_port_t polarity_port1;
} polarity_ports_t;

typedef union
{
    uint16_t word;
    uint8_t byte[2];
} word_u;

class pca9555
{
private:
    uint8_t address;
    uint8_t int_pin_num;
    uint16_t I2CGetValue(uint8_t address, uint8_t reg);
    void I2CSetValue(uint8_t address, uint8_t reg, uint8_t value);

public:
    uint8_t _error;
    pca9555(uint8_t address, uint8_t int_pin_num);
    void pin_mode(config_ports_t *config_ports);
    void set_polarity(polarity_ports_t *pol_ports);
    uint16_t read_input();
};

#endif /* CLSPCA9555_H_ */