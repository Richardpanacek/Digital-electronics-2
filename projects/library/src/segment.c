#include <util/delay.h>
#include "gpio.h"
#include "segment.h"

/* Define ------------------------------------------------------------*/
/* Variables ---------------------------------------------------------*/
/* Active low digit 0 to 9 */
uint8_t segment_digit[] = {
   //DPgfedcba
    0b11000000,      // Digit 0
    0b11111001,      // Digit 1
    0b10100100,      // Digit 2
    0b10110000,      // Digit 3
    0b10011001,      // Digit 4
    0b10010010,      // Digit 5
    0b10000010,      // Digit 6
    0b11111000,      // Digit 7
    0b10000000,      // Digit 8
    // TODO: Set segments for other digits
    0b10011000};     // Digit 9     desetina tecka g f e d c b a

/* Active high position 0 to 3 */
uint8_t segment_position[] = {
    0b00001000,   // Position 0
    0b00000100,   // Position 1
    0b00000010,   // Position 2
    0b00000001};  // Position 3

/* Functions ---------------------------------------------------------*/
void SEG_putc(uint8_t digit,
              uint8_t position)
{
    uint8_t i;

    /* Read values from look-up tables */
    digit    = segment_digit[digit];
    position = segment_position[position];

    /* Put 1st byte to serial data */
    for (i = 0; i < 8; i++) {
        // TODO: Test and send 8 individual "digit" bits
        uint8_t pom = 0x00;
        pom |= _BV (7-i);
        if((digit & pom) == 0)
        {
            GPIO_write(&PORTB, SEGMENT_DATA, 0);
        }
        else GPIO_write(&PORTB, SEGMENT_DATA, 1);
        SEG_toggle_clk();
    }
    /* Put 2nd byte to serial data */
    for (i = 0; i < 8; i++) {
        // TODO: Test and send 8 individual "position" bits
        uint8_t pom = 0x00;
        pom |= _BV (7-i);
        if((position & pom) == 0)
        {
            GPIO_write(&PORTB, SEGMENT_DATA, 0);
        }
        else GPIO_write(&PORTB, SEGMENT_DATA, 1);
        SEG_toggle_clk();
    }

    /* TODO: Generate 1 us latch pulse */
    GPIO_write(&PORTD, SEGMENT_LATCH, 0);
    _delay_us(1);
    GPIO_write(&PORTD, SEGMENT_LATCH, 1);
    _delay_us(1);
}

/*--------------------------------------------------------------------*/
void SEG_toggle_clk(void)
{
    /* TODO: Generate 2 us clock period */
     GPIO_write(&PORTD, SEGMENT_CLK, 0);
    _delay_us(1);
    GPIO_write(&PORTD, SEGMENT_CLK, 1);
    _delay_us(1);
}

