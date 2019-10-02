/*
 * ---------------------------------------------------------------------
 * Author:      Tomas Fryza
 *              Dept. of Radio Electronics, Brno Univ. of Technology
 * Created:     2018-09-27
 * Last update: 2019-07-16
 * Platform:    ATmega328P, AVR 8-bit Toolchain 3.6.2
 * ---------------------------------------------------------------------
 * Description: Blink a LED with delay function.
 * TODO: Verify functionality of LED blinker.
 * NOTE: Macro _BV converts a bit number into a byte value (see AVR Libc
 * Reference Manual).
 */

/* Includes ----------------------------------------------------------*/
#include <avr/io.h>
#include <util/delay.h>

/* Typedef -----------------------------------------------------------*/
/* Define ------------------------------------------------------------*/
#define LED_PIN     PB5     //pB...takze ddrB
#define LED_PIN2     PB1    //je na 9 pod SCL,SDA... z 9 drat do radku s diodou napr 30, hlidej polaritu diody, pak rezistor z nej drat na minus sloupec 
#define BTN     PD2         //drat z PD2 to je 2 na tlacitko a z tlacitka zpet na spolecnou zem do sloupce minus, ktery vede dratem na pin GND 
#define BLINK_DELAY 250     //blikani po 250 ms

/* Variables ---------------------------------------------------------*/
/* Function prototypes -----------------------------------------------*/

/* Functions ---------------------------------------------------------*/
/**
  * Brief:  Main program. Blink a LED with delay function.
  * Input:  None
  * Return: None
  */
int main(void)
{
    /* Set output pin */
    DDRB |= _BV(LED_PIN);           /* DDRB = DDRB or (0010 0000) */ //smerový registr
    DDRB |= _BV(LED_PIN2);
    DDRD &= _BV(BTN);
    PORTD |= _BV(BTN);

    /* Turn LED off */
    PORTB &= ~_BV(LED_PIN);         /* PORTB = PORTB and (0010 0000) */ //vystupni registr
    PORTB |= _BV(LED_PIN2);
    /* Infinite loop */
    for (;;)
    {
      if(bit_is_clear(PIND, BTN))  //zmacknute tlacitko ma mensi odpor nez mikrokontroler na tom je pak 0 a zacne blikani
      {                            //nezmacknute tlacitko zanecha LED pin9 na posledni hodnote to je ON/OFF 
        /* Invert LED and delay */
        PORTB ^= _BV(LED_PIN);      /* PORTB = PORTB xor (0010 0000) */
        PORTB ^= _BV(LED_PIN2);
        _delay_ms(BLINK_DELAY);     /* Wait for several milisecs */
      }
    }                              //uloz CTRL+S a do terminalu: make flash pro nahrani

    return (0);
}
