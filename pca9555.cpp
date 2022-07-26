#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "pico/stdio.h"
#include "pca9555.h"

pca9555::pca9555(uint8_t address, uint8_t int_pin_num)
{
  this->address = address;

  if (int_pin_num > 0)
  {
    this->int_pin_num = int_pin_num;
    gpio_init(int_pin_num);
    gpio_set_dir(int_pin_num, false);
    gpio_is_pulled_up(int_pin_num);
  }

  else
  {
    this->int_pin_num = 0;
  }
}

void pca9555::pin_mode(config_ports_t *config_ports)
{
  I2CSetValue(address, cp_0, config_ports->config_port0.all);
  I2CSetValue(address, cp_1, config_ports->config_port1.all);
}

void pca9555::set_polarity(polarity_ports_t *pol_ports)
{
  I2CSetValue(address, pi_0, pol_ports->polarity_port0.all);
  I2CSetValue(address, pi_1, pol_ports->polarity_port1.all);
}

uint16_t pca9555::read_input()
{
  return I2CGetValue(address, ip_0);
}

uint16_t pca9555::I2CGetValue(uint8_t address, uint8_t reg)
{
  uint8_t _inputData[2];
  word_u words_;

  _error = i2c_write_blocking(i2c_default, address, &reg, 1, false);
  _error = i2c_read_blocking(i2c_default, address, (uint8_t *)&_inputData, 2, false);

  words_.byte[0] = _inputData[0];
  words_.byte[1] = _inputData[1];

  return words_.word;
}

/**
 * @name I2CSetValue(uint8_t address, uint8_t reg, uint8_t value)
 * @param address Address of I2C chip
 * @param reg    register to write to
 * @param value    value to write to register
 * Write the value given to the register set to selected chip.
 */
void pca9555::I2CSetValue(uint8_t address, uint8_t reg, uint8_t value)
{
  //
  // write output register to chip
  //
  _error = i2c_write_blocking(i2c_default, address, &reg, 1, false);   // setup direction registers
  _error = i2c_write_blocking(i2c_default, address, &value, 1, false); // pointer to configuration register address 0
}