/**
 * @file main.c
 * @brief Main control loop for state-based ADC sampling and UART communication.
 * 
 * This file contains the main loop that manages ADC sampling based on button input
 * and transfers data over UART upon host command. LED indicators show the current state.
 */

#include "project.h"
#include "functions.h"


/**
 * @brief Entry point of the program.
 * 
 * Initializes hardware and handles state machine logic:
 * - IDLE: Waiting for button press.
 * - SAMPLING: ADC data acquisition.
 * - UART_TRANSFER: Send ADC data via UART.
 */
int main(void)
{
    CyGlobalIntEnable;
    initializeHardware();

    for(;;)
    {
        switch(state)
        {
            case IDLE:
                updateLEDs(1, 0, 0);         /**< Red LED: IDLE */
                sampleCount = 0;
                buttonPressed = 0;
                flushRxBuffer();             /**< Clear UART RX buffer */
                
                if(buttonPressed == 1)
                {
                    CyDelay(300);            /**< Debounce delay */
                    state = SAMPLING;
                }
                break;

            case SAMPLING:
                updateLEDs(0, 1, 0);         /**< Orange LED: Sampling */
                sampleADC();                 /**< Acquire 1024 ADC samples */
                
                if (uart_s_received)         /**< If 's' received from matlab */
                {
                    uart_s_received = 0;
                    state = UART_TRANSFER;
                }

                else
                {
                    state = IDLE;           /**< Timeout: revert to IDLE */
                }
                break;

            case UART_TRANSFER:
                updateLEDs(0, 0, 1);         /**< Green LED: UART Transfer */
                uartSendBuffer();            /**< Send ADC samples over UART */
                sampleCount++;
                
                if (uart_o_received)         /**< If 'o' received from matlab */
                {
                    uart_o_received = 0;
                    if (sampleCount >= 10)
                        state = IDLE;
                    else
                        state = SAMPLING;
                }
                else
                {
                    state = IDLE;
                }
                break;
        }
    }
}
