#include <Adafruit_MLX90640.h>


/*!
 *    @brief  Instantiates a new MPU6050 class
 */
Adafruit_MLX90640::Adafruit_MLX90640(void) {

}

/*!
 *    @brief  Sets up the hardware and initializes I2C
 *    @param  i2c_address
 *            The I2C address to be used.
 *    @param  wire
 *            The Wire object to be used for I2C connections.
 *    @return True if initialization was successful, otherwise false.
 */
boolean Adafruit_MLX90640::begin(uint8_t i2c_addr, TwoWire *wire) {
  i2c_dev = new Adafruit_I2CDevice(i2c_addr, wire);

  if (!i2c_dev->begin()) {
    return false;
  }
  return true;
}
