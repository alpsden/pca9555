#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "pico/stdio.h"
#include "pca9555.h"

/**
 * @brief Construct a new pca9555::pca9555 object
 *
 * @param address
 * @param int_pin_num set to zero if polling
 */
pca9555::pca9555(uint8_t address, uint8_t int_pin_num)
{
  this->address = address;

  if (int_pin_num > 0)
  {
    this->int_pin_num = int_pin_num;
    gpio_init(int_pin_num);
    gpio_set_dir(int_pin_num, false);
    gpio_is_pulled_up(int_pin_num);

    printf("hello from constructor %d\n", this->address);
  }

  else
  {
    int_pin_num = 0;
  }
}

/**
 * @brief Set pins as input or output
 *
 * @param config_ports
 */
void pca9555::pin_mode(config_ports_t *config_ports)
{
  uint8_t reg_config[2] = {config_ports->config_port0.all, config_ports->config_port1.all};
  twi_write(this->address, cp_0, reg_config, 2);
  read_input(); // to clear interrupts (if any)
}

/**
 * @brief Set pins as input or output
 *
 * @param config_ports
 */
void pca9555::set_output(output_ports_t *output_ports)
{
  uint8_t reg_config[2] = {output_ports->config_port0.all, output_ports->config_port1.all};
  twi_write(this->address, cp_0, reg_config, 2);
  read_input();
}

/**
 * @brief set polarity of the pins
 *
 * @param pol_ports
 */
void pca9555::set_polarity(polarity_ports_t *pol_ports)
{
  uint8_t pol_config[2] = {pol_ports->polarity_port0.all, pol_ports->polarity_port1.all};
  twi_write(address, pi_0, pol_config, 2);
}

/**
 * @brief read value of the input regs
 *
 * @return uint16_t
 */
uint16_t pca9555::read_input()
{
  return twi_read(address, ip_0);
}

/**
 * @name twi_read(uint8_t address, uint8_t reg)
 * @param address
 * @param reg
 * @return uint16_t
 */
uint16_t pca9555::twi_read(uint8_t address, uint8_t reg)
{
  uint8_t _inputData[2];
  word_u words_;
  _error = i2c_write_blocking(i2c_default, address, &reg, 1, true);
  _error = i2c_read_blocking(i2c_default, address, (uint8_t *)&_inputData, 2, false);
  // printf("%d", _error);
  words_.byte[0] = _inputData[0];
  words_.byte[1] = _inputData[1];

  return words_.word;
}

/**
 * @name twi_write(uint8_t address, uint8_t reg, uint8_t value, uint8_t len)
 * @param address Address of I2C chip
 * @param reg    register to write to
 * @param value    value to write to register
 * @param len length of data being sent
 * Write the value given to the register set to selected chip.
 */
void pca9555::twi_write(uint8_t address, uint8_t reg, uint8_t *value, uint8_t len)
{
  //
  // write output register to chip
  //
  uint8_t err;
  uint8_t _reg = reg;
  err = i2c_write_blocking(i2c_default, address, &_reg, 1, false);   // setup direction registers
  err = i2c_write_blocking(i2c_default, address, value, len, false); // pointer to configuration register address 0
}