#ifndef SEGMENT_H_INCLUDED
#define SEGMENT_H_INCLUDED

#include <avr/io.h>

/* Define ------------------------------------------------------------*/
/** @brief Defines the interface of 7-segment display. */
#define SEGMENT_DATA    PB0
#define SEGMENT_CLK     PD7
#define SEGMENT_LATCH   PD4

/* Function prototypes -----------------------------------------------*/
/**
 *  @brief Xxx.
 *  @param xxx - Xxxx
 *  @param xxx - Xxxx
 *  @retval None
 */
void SEG_putc(uint8_t digit,
              uint8_t position);

/**
 *  @brief Xxx.
 *  @retval None
 */
void SEG_toggle_clk(void);

#endif /* SEGMENT_H_INCLUDED */