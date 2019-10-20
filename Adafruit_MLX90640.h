/*!
 *  @file Adafruit_MLX90640.h
 *
 * 	I2C Driver for MLX90640 24x32 IR Thermal Camera
 *
 * 	This is a library for the Adafruit MLX90640 breakout:
 * 	https://www.adafruit.com/products/4407
 *
 * 	Adafruit invests time and resources providing this open source code,
 *  please support Adafruit and open-source hardware by purchasing products from
 * 	Adafruit!
 *
 *
 *	BSD license (see license.txt)
 */

#ifndef _ADAFRUIT_MLX90640_H
#define _ADAFRUIT_MLX90640_H

#include "Arduino.h"
#include <Wire.h>
#include <Adafruit_I2CDevice.h>

#define MLX90640_I2CADDR_DEFAULT 0x33

/*!
 *    @brief  Class that stores state and functions for interacting with
 *            the MLX90640 sensor
 */
class Adafruit_MLX90640 {
 public:
    Adafruit_MLX90640();
    boolean begin(uint8_t i2c_addr = MLX90640_I2CADDR_DEFAULT,
		  TwoWire *wire = &Wire);

    int getCurrMode() {
      return MLX90640_GetCurMode(MLX90640_I2CADDR_DEFAULT);
    }
 private:
    Adafruit_I2CDevice *i2c_dev;
};
#endif
