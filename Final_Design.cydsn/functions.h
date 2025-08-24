/**
 * @file functions.h
 * @brief Header for hardware abstraction and control functions.
 */

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "project.h"

#define NUM_OF_SAMPLES 1024  /**< Number of ADC samples to collect */

/**
 * @brief System states for state machine.
 */
typedef enum { IDLE, SAMPLING, UART_TRANSFER } State;

// Global variables
extern State state;
extern uint16_t adcBuffer[NUM_OF_SAMPLES];
extern volatile uint8_t buttonPressed;
extern volatile uint8_t uart_s_received;
extern volatile uint8_t uart_o_received;
extern uint8_t sampleCount;

// Function declarations
void sampleADC(void);
void uartSendBuffer(void);
void updateLEDs(uint8_t red, uint8_t orange, uint8_t green);
void initializeHardware(void);
void flushRxBuffer(void);
uint8_t waitForUARTChar(uint8_t expectedChar);
CY_ISR_PROTO(Button_ISR_Handler);
CY_ISR_PROTO(UART_ISR_Handler);

#endif // FUNCTIONS_H

/* [] END OF FILE */
