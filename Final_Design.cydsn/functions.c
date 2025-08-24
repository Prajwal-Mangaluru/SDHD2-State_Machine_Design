/**
 * @file functions.c
 * @brief Implementation of hardware abstraction and support functions.
 */

#include "functions.h"

// Global variable definitions
State state = IDLE;
uint16_t adcBuffer[NUM_OF_SAMPLES];
volatile uint8_t buttonPressed = 0;
uint8_t sampleCount = 0;
volatile uint8_t uart_s_received = 0;
volatile uint8_t uart_o_received = 0;

/**
 * @brief ISR for button press.
 * 
 * Sets buttonPressed flag and clears interrupt.
 */
CY_ISR(Button_ISR_Handler)
{
    buttonPressed = 1;
    isr_Button_ClearPending();
    Button_ClearInterrupt();
}

/**
 * @brief ISR for UART.
 * 
 * Sets uart_s_received and uart_o_received flag and clears interrupt.
 */
CY_ISR(UART_ISR_Handler)
{
    uint8_t rxChar = UART_LOG_GetChar();

    if (rxChar == 's')
        uart_s_received = 1;
    else if (rxChar == 'o')
        uart_o_received = 1;

    isr_UART_ClearPending();
}


/**
 * @brief Samples ADC and stores values in adcBuffer.
 * 
 * Uses blocking method to wait for each conversion to complete.
 */
void sampleADC()
{
    uint16_t output;
    for (int i = 0; i < NUM_OF_SAMPLES; i++)
    {
        ADC_StartConvert();
        while (!ADC_IsEndConversion(ADC_RETURN_STATUS));  /**< Wait until conversion finishes */
        output = ADC_GetResult16();
        adcBuffer[i] = output;
    }
}

/**
 * @brief Sends the ADC buffer over UART.
 * 
 * Each 16-bit sample is sent as two bytes: LSB followed by MSB.
 */
void uartSendBuffer()
{
    for (int i = 0; i < NUM_OF_SAMPLES; i++)
    {
        UART_LOG_PutChar(adcBuffer[i] & 0xFF);         /**< Send LSB */
        UART_LOG_PutChar((adcBuffer[i] >> 8) & 0xFF);  /**< Send MSB */
    }
}

/**
 * @brief Controls the state of status LEDs.
 * 
 * @param red     Red LED state (0 or 1)
 * @param orange  Orange LED state (0 or 1)
 * @param green   Green LED state (0 or 1)
 */
void updateLEDs(uint8_t red, uint8_t orange, uint8_t green)
{
    led_red_Write(red);
    led_orange_Write(orange);
    led_green_Write(green);
}

/**
 * @brief Initializes all hardware components.
 * 
 * Starts DAC, ADC, UART, button interrupt, and turns off all LEDs.
 */
void initializeHardware()
{
    WaveDAC8_1_Start();      /**< Start waveform generator (DAC) */
    UART_LOG_Start();        /**< Initialize UART communication */
    ADC_Start();             /**< Start ADC peripheral */
    isr_Button_StartEx(Button_ISR_Handler);  /**< Attach ISR */
    isr_UART_StartEx(UART_ISR_Handler); /**< Attach ISR */
    updateLEDs(0, 0, 0);     /**< Turn off all LEDs initially */
}

/**
 * @brief Clears all pending bytes in UART RX buffer.
 */
void flushRxBuffer()
{
    while(UART_LOG_GetRxBufferSize())
    {
        UART_LOG_GetChar();  /**< Discard unread character */
    }
}

/* [] END OF FILE */
