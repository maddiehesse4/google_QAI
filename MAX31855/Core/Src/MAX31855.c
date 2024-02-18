#include "MAX31855.h"

// Define CS pin (adjust based on your setup)
#define MAX31855_CS_GPIO_Port GPIOA
#define MAX31855_CS_Pin GPIO_PIN_4

// Function to read temperature from MAX31855
float MAX31855_ReadTemperature(SPI_HandleTypeDef *hspi) {
    uint8_t data[4] = {0};
    uint32_t tempRaw;

    // Ensure CS is high before starting
    HAL_GPIO_WritePin(MAX31855_CS_GPIO_Port, MAX31855_CS_Pin, GPIO_PIN_SET);

    // Pull CS low to initiate communication
    HAL_GPIO_WritePin(MAX31855_CS_GPIO_Port, MAX31855_CS_Pin, GPIO_PIN_RESET);

    // Read 4 bytes from MAX31855
    HAL_SPI_Receive(hspi, data, 4, 100);

    // Pull CS high to end communication
    HAL_GPIO_WritePin(MAX31855_CS_GPIO_Port, MAX31855_CS_Pin, GPIO_PIN_SET);

    // Process raw data
    tempRaw = (data[0] << 24) | (data[1] << 16) | (data[2] << 8) | data[3];

    // Check for fault
    if (tempRaw & 0x00010000) {
        return -999; // Simple error handling
    }

    // Convert raw data to temperature
    // The 14 MSBs represent the temperature in C (right-shift 18 bits)
    // Each bit is 0.25C
    if (tempRaw & 0x80000000) {
        // Handle negative temperatures
        tempRaw = ~tempRaw + 1; // Two's complement
        return (float)(tempRaw >> 18) * -0.25;
    } else {
        return (float)(tempRaw >> 18) * 0.25;
    }
}
