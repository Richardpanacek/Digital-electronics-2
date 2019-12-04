
#include <stdlib.h>             // itoa() function
#include <avr/io.h>
#include <avr/interrupt.h>
#include "timer.h"
#include "lcd.h"
#include "uart.h"

/* Typedef -----------------------------------------------------------*/
/* Define ------------------------------------------------------------*/
#define UART_BAUD_RATE 9600

/* Variables ---------------------------------------------------------*/
/* Function prototypes -----------------------------------------------*/

/* Functions ---------------------------------------------------------*/
/**
 *  Brief:  Main program. Read ADC result and transmit via UART.
 *  Input:  None
 *  Return: None
 */
int main(void)
{
    // LCD display
    lcd_init(LCD_DISP_ON);
    lcd_puts("LCD testing");

    /* ADC
     * TODO: Configure ADC reference, clock source, enable ADC module, 
     *       and enable conversion complete interrupt 
    ADMUX |= _BV(REFS0);    //vyber reference napeti pro adc
    ADMUX &= ~_BV(REFS1);   //vyber reference napeti pro adc
    ADMUX &= ~_BV(MUX3) & ~_BV(MUX2) & ~_BV(MUX1) & ~_BV(MUX0);   //vyber ADC vstupu
    ADCSRA |= _BV(ADEN);    //povoleni ADC
    ADCSRA |= _BV(ADIE);    //povoleni preruseni
    ADCSRA |= _BV(ADPS2) | _BV(ADPS1) | _BV(ADPS0);*/

    // UART: asynchronous, 8-bit data, no parity, 1-bit stop
    uart_init(UART_BAUD_SELECT(UART_BAUD_RATE, F_CPU));

    // Enables interrupts by setting the global interrupt mask
    sei();

    // Put string to ringbuffer for transmitting via UART.
    uart_puts("UART testing\r\n"); //n posune na dalsi radek, a r na zacatek radku

    // Infinite loop
    for (;;) {
    }

    // Will never reach this
    return (0);
}

/**
 *  Brief: Timer1 overflow interrupt routine. Start ADC conversion.
 */
ISR(TIMER1_OVF_vect)
{
    // TODO: Start ADC conversion
    ADCSRA |= _BV(ADSC);     //zahaji ADC konverzi
}

/**
 *  Brief: ADC complete interrupt routine. Update LCD and UART 
 *         transmiter.
 */
ISR(ADC_vect)
{
    uint16_t value = 0;
    char uart_string[128];

	// Read 10-bit ACD value
    value = ADC;
    // TODO: Update LCD and UART transmiter
    itoa(value, uart_string, 10);        //vypise cislo v 10 soustave
    lcd_gotoxy(1, 1);                    //2 radek 2 sloupec
    lcd_puts(uart_string);

    uart_puts(uart_string);     //odesle promennou do uart, 
    //zapni program Putty SSH Client, otevri session a usb0, okno ukazuje dig hodnotu tlacitek  
    uart_puts("\r\n");//pise na dalsi radek

    lcd_gotoxy(1, 0); //pise v zavislosti na podmince pokud je DIG hodnota...
    if (value < 50)
        {
        lcd_puts("RIGHT");
        }
    else if (value > 50 && value < 150)
        {
        lcd_puts("UP");
        }
    else if (value > 150 && value < 300)
        {
        lcd_puts("DOWN");
        }
    else if (value > 300 && value < 450)
        {
        lcd_puts("LEFT");
        }
    else if (value > 450 && value < 750)
        {
        lcd_puts("SELECT");
        }
}