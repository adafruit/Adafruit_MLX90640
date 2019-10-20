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
  
  MLX90640_I2CRead(0, MLX90640_DEVICEID1, 3, serialNumber);

  return true;
}

int Adafruit_MLX90640::MLX90640_I2CRead(uint8_t slaveAddr, uint16_t startAddress, 
					uint16_t nMemAddressRead, uint16_t *data) {
  uint8_t cmd[2];
  cmd[0] = startAddress >> 8;
  cmd[1] = startAddress & 0x00FF;

  if (i2c_dev->write_then_read(cmd, 2, (uint8_t *)data, nMemAddressRead*2, false)) {
    // we now have to swap every two bytes
    for (int i=0; i<nMemAddressRead; i++) {
      data[i] = __builtin_bswap16(data[i]);
    }
    return 0;
  }
  return -1;
}

int Adafruit_MLX90640::MLX90640_I2CWrite(uint8_t slaveAddr, uint16_t writeAddress, uint16_t data) {
  uint8_t cmd[4];
  uint16_t dataCheck;

  cmd[0] = writeAddress >> 8;
  cmd[1] = writeAddress & 0x00FF;
  cmd[2] = data >> 8;
  cmd[3] = data & 0x00FF;

  if (! i2c_dev->write_then_read(cmd, 4, (uint8_t *)&dataCheck, 2, true)) {
    return -1;
  }
  // check echo
  if (dataCheck != data) {
    return -1;
  }
  // OK!
  return 0;
}



mlx90640_mode_t Adafruit_MLX90640::getMode(void) {
  return (mlx90640_mode_t)MLX90640_GetCurMode(0);
}

void Adafruit_MLX90640::setMode(mlx90640_mode_t mode) {
  if (mode == MLX90640_CHESS) {
    MLX90640_SetChessMode(0);
  } else {
    MLX90640_SetInterleavedMode(0);
  }
}


mlx90640_resolution_t Adafruit_MLX90640::getResolution(void) {
  return (mlx90640_resolution_t)MLX90640_GetCurResolution(0);
}

void Adafruit_MLX90640::setResolution(mlx90640_resolution_t res) {
  MLX90640_SetResolution(0, (int)res);
}
