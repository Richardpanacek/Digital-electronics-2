
/*
 * ---------------------------------------------------------------------
 * Author:      Tomas Fryza
 *              Dept. of Radio Electronics, Brno Univ. of Technology
 * Created:     2018-10-16
 * Last update: 2019-10-25
 * Platform:    ATmega328P, 16 MHz, AVR 8-bit Toolchain 3.6.2
 * ---------------------------------------------------------------------
 * Description:
 *    Decimal counter with data output on LCD display.
 * 
 * Note:
 *    Modified version of Peter Fleury's LCD library with R/W pin 
 *    connected to GND. Newline symbol "\n" is not implemented, use
 *    lcd_gotoxy() function instead.
 */

/* Includes ----------------------------------------------------------*/
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>             // itoa() function
#include "timer.h"
#include "lcd.h"

/* Typedef -----------------------------------------------------------*/
/* Define ------------------------------------------------------------*/
/* Variables ---------------------------------------------------------*/
/* Function prototypes -----------------------------------------------*/

/* Functions ---------------------------------------------------------*/
/**
 *  Brief:  Main program. Shows decimal values ​​on LCD display.
 *  Input:  None
 *  Return: None
 */





int main(void)
{
    /* LCD display
     * TODO: See Peter Fleury's online manual for LCD library 
     * http://homepage.hispeed.ch/peterfleury/avr-software.html
     * Initialize display and test different types of cursor */
    lcd_init(LCD_DISP_ON);

    // Display string without auto linefeed
    //lcd_puts("LCD testing");

    // TODO: Display variable value in decimal, binary, and hexadecimal

    //itoa(value, lcd_string, 16);    //nasledujici 4 radky prevedou value na 16-kovou 
    lcd_gotoxy(0, 1);               //pise na 1(0)-ty sloupec a 2(1)-ty radek
    lcd_putc('$');                  // putc bere char a to jsou jedny uvona kurzor ukaze dolar
    lcd_gotoxy(6, 1);
    lcd_putc('0');                      //dohromady vypise 0b....cislo
    lcd_putc('b');
    //lcd_puts(lcd_string);           //displej ukaze 1f
    /* Timer1
     * TODO: Configure Timer1 clock source and enable overflow 
     *       interrupt */
    TIM_config_prescaler(TIM1, TIM_PRESC_64);         //timer 1 nejel
    TIM_config_interrupt(TIM1, TIM_OVERFLOW_ENABLE);

    /* TODO: Design at least two user characters and store them in 
     *       the display memory */
    uint8_t  lcd_user_symbols [8*2] = {0x00,
  0x1F,
  0x0E,
  0x04,
  0x0E,
  0x0A,
  0x15,
  0x1B};
    lcd_command(1<<LCD_CGRAM);
    for (uint8_t i = 0; i < 16; i++)
        {
        lcd_data(lcd_user_symbols[i]);
        }       
        lcd_clrscr ();
        lcd_putc (0x00);

    // Enables interrupts by setting the global interrupt mask
    sei();

    // Infinite loop
    for (;;) {
    }
    
  
    // Will never reach this

    return (0);
}

/**
 *  Brief: Timer1 overflow interrupt routine. Increment counter value.
 */
ISR(TIMER1_OVF_vect)        //timer 1 nejel
{
    static uint8_t value = 31;     //to je 1f v 16-kove
    char lcd_string [9];
    // TODO: Increment counter value form 0 to 255
    value++;
    itoa(value, lcd_string, 10);        //vypise cislo v 10
    lcd_gotoxy(9, 0);
    lcd_puts(lcd_string); 

    itoa(value, lcd_string, 16);        //vypise cislo v 16
    lcd_gotoxy(1, 1);
    lcd_puts(lcd_string); 
    
    itoa(value, lcd_string, 2);         //vypise cislo v 2
    lcd_gotoxy(8, 1);
    lcd_puts(lcd_string); 
    
}