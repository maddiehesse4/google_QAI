/*
 * MAX31855.h
 *
 *  Created on: Feb 17, 2024
 *      Author: meraz
 */
#ifndef MAX31855_H
#define MAX31855_H

#include "main.h" // Include main header for SPI_HandleTypeDef

float MAX31855_ReadTemperature(SPI_HandleTypeDef *hspi);

#endif // MAX31855_H
