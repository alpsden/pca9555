
/**
 * @brief pca9555 driver for rp2040
 *
 */

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
    ALL_INPUT = 0B11111111
} config_reg_val_e;

typedef enum
{
    retain,
    inverted,
    ALL_RETAINED = 0B0,
    ALL_INVERTED = 0B11111111
} polarity_reg_val_e;

typedef enum
{
    OUT_LOW,
    OUT_HIGH,
    ALL_LOW = 0B0,
    ALL_HIGH = 0B11111111
} output_port_val_e;

//******************************************************
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

} output_port_t;

typedef struct
{
    output_port_t config_port0;
    output_port_t config_port1;
} output_ports_t;
//*******************************************************

//******************************************************
typedef union
{
    uint8_t all;
    struct __attribute__((packed, aligned(1)))
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
//*******************************************************

//*******************************************************
typedef union
{
    uint8_t all;
    struct __attribute__((packed, aligned(1)))
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
//*********************************************************

typedef union
{
    uint16_t word;
    uint8_t byte[2];
} word_u;

class pca9555
{
private:
    /**
     * @brief Device address
     *
     */
    uint8_t address;

    /**
     * @brief Gpio pin on which interrput occurs
     *
     */
    uint8_t int_pin_num;

    /**
     * @brief I2C read function
     *
     * @param address
     * @param reg
     * @return uint16_t: read val from the regs
     */
    uint16_t twi_read(uint8_t address, uint8_t reg);

    /**
     * @brief i2c write function
     *
     * @param address
     * @param reg
     * @param value
     * @param len
     */
    void twi_write(uint8_t address, uint8_t reg, uint8_t *value, uint8_t len);

public:
    uint8_t _error;

    /**
     * @brief Construct a new pca9555 object
     *
     * @param address: Dev address of the io expander
     * @param int_pin_num: pin number of the interrupt gpio (on the mcu)
     * Set to zero if polling
     */
    pca9555(uint8_t address, uint8_t int_pin_num);

    /**
     * @brief set pins as input or output
     *
     * @param config_ports: Struct defining the pin cofig (for each bank) as input and output
     */
    void pin_mode(config_ports_t *config_ports);

    /**
     * @brief Set the output object
     *
     * @param output_ports Struct to set output port values
     */
    void set_output(output_ports_t *output_ports);

    /**
     * @brief Set the polarity object
     *
     * @param pol_ports: Struct defining the polarity of pins
     */
    void set_polarity(polarity_ports_t *pol_ports);

    /**
     * @brief read values of the input regs
     *
     * @return uint16_t:
     */
    uint16_t read_input();
};

#endif /* CLSPCA9555_H_ */