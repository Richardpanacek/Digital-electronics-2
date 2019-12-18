#include "gpio.h"
/*  Functions  ---------------------------------------------------------*/
void  GPIO_config_output(volatile  uint8_t *reg_name , uint8_t  pin_num)
{
    
    // Body of the  function
    *reg_name  |= _BV(pin_num);
    }

 void GPIO_write(volatile uint8_t *reg_name,uint8_t pin_num,uint8_t pin_val) 
 {
    
    
    if (pin_val == PIN_LOW)
    {
        *reg_name  &= ~_BV(pin_num);
    }
    else 
    {
            *reg_name  |= _BV(pin_num);
    }
    
    }  
void GPIO_toggle(volatile uint8_t *reg_name,uint8_t pin_num)
{
    
    // Body of the  function
    *reg_name  ^= _BV(pin_num);
    } 
 void GPIO_config_input_nopull(volatile uint8_t *ddr_name , volatile uint8_t *port_name, uint8_t pin_num)
 {
    
    // Body of the  function
    *port_name  &= ~_BV(pin_num);
    *ddr_name  &= ~_BV(pin_num);

    }   
void GPIO_config_input_pullup(volatile uint8_t *ddr_name , volatile uint8_t *port_name,uint8_t pin_num)
{
    
    // Body of the  function
    *ddr_name  &= ~_BV(pin_num);
    *port_name  |= _BV(pin_num);

    } 
 uint8_t GPIO_read(volatile uint8_t *reg_name, uint8_t pin_num)
{
    //return bit_is_clear(*reg_name, pin_num);
    return ((*reg_name & _BV(pin_num)) >> pin_num);
} 