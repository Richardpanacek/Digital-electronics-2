#include <stdlib.h>         // itoa() function
#include <avr/io.h>
#include <avr/interrupt.h>
#include "timer.h"
#include "uart.h"
#include "twi.h"
#include "nokia5110.h"
#include "gpio.h"

/* Define ------------------------------------------------------------*/
#define UART_BAUD_RATE 9600

/* Variables ---------------------------------------------------------
state_t current_state = IDLE_STATE; */


/* Function prototypes -----------------------------------------------*/


/* Functions ---------------------------------------------------------*/
/**
 *  Brief:  Main program. Test all TWI slave addresses and scan 
 *          connected devices.
 *  Input:  None
 *  Return: None
 */
int main(void)
{
    // INIT LCD NOKIA5110
    nokia_lcd_init();
    //nokia_lcd_clear();
    nokia_lcd_write_string("THIS FUCKING", 1); //cislo je velikost pisma
    nokia_lcd_set_cursor(0, 8);
    nokia_lcd_write_string("THIS FUCKING", 1); //cislo je velikost pisma
    nokia_lcd_render();

    uart_init(UART_BAUD_SELECT(UART_BAUD_RATE, F_CPU));

    TIM_config_prescaler(TIM1, TIM_PRESC_8);
    TIM_config_interrupt(TIM1, TIM_OVERFLOW_ENABLE);

    sei();

    uart_puts("\r\nTEST UART");


    // infinite loop
    for (;;) {
    }
    
    return (0);
}

ISR(TIMER1_OVF_vect)
{
    uart_getc();
}