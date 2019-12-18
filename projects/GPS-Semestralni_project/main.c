#include <stdlib.h>         // itoa() function
#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <string.h>
#include <math.h>
#include "timer.h"
#include "uart.h"
#include "nokia5110.h"
#include "gpio.h"
#include "GPS_parsing.h"


#define UART_BAUD_RATE 9600
#define INT_PIN PD2
#define GPS_enable PD4


char znak;
volatile uint8_t i = 0;
volatile uint8_t konec = 0;
volatile uint8_t vyhledavam = 1;
volatile uint8_t pokracuj = 1;

char NMEA[72];
char *NMEA_parse[6];

double lat; double lon; 
char lat_h; char lon_h;
double time;




int main(void)
{

    EICRA = 0b00000000;   
	  EIMSK = 0b00000001;

    DDRD &= ~_BV(INT_PIN);
    DDRD |= _BV(GPS_enable);
    PORTD |= _BV(GPS_enable);

    TIM_config_prescaler(TIM1, TIM_PRESC_1024);
    TIM_config_interrupt(TIM1, TIM_OVERFLOW_ENABLE);

    uart_init(UART_BAUD_SELECT(UART_BAUD_RATE, F_CPU));
    nokia_lcd_init();

    sei();


    while(1){
        
         while (!(UCSR0A & (1<<RXC0))){

            znak = uart_getc();

            if (znak == '$'){

                while(1){
                    
                    while (!(UCSR0A & (1<<RXC0)));
                    NMEA[i] = uart_getc();
                    i++;

                    if(i==70){
                        pokracuj = 0;
                        break;
                    }             

                }


                NMEA[71] = '\0';
                i = 0;
                
                
                if (strstr(NMEA,"GPGGA") != NULL){

                    char* token; 
                    char* rest = NMEA;
                    while ((token = strtok_r(rest, ",", &rest))){

                        NMEA_parse[i] = token;
                        i++;
       
                    }

                    lat = atof(NMEA_parse[2]);   
                    lat_h = *NMEA_parse[3];
                    lon = atof(NMEA_parse[4]);   
                    lon_h = *NMEA_parse[5];
                    time = atof(NMEA_parse[1]);


                    konec = 1;
                    i = 0;
                    vyhledavam = 0;
                    NMEA[0] = '\0';
                    while (pokracuj != 1);
                    break;

                }

                else{

                    //konec = 1;
                    i = 0;
                    NMEA[0] = '\0';
                    vyhledavam = 1;
                    while (pokracuj != 1);
                    break;
                    
                }

            }    

        }

        //if (konec == 1){konec = 0; break;}

    }



    // for (;;) {
    // }    
    
    nokia_lcd_write_string("konec", 1); 
    nokia_lcd_render();
    
    return (0);
}



ISR(TIMER1_OVF_vect)
{
    nokia_lcd_clear();

    if (vyhledavam == 1){
        nokia_lcd_write_string("Lat.:Searching ", 1);   
        nokia_lcd_set_cursor(0, 8);
        nokia_lcd_write_string("Lon.:Searching", 1);
        nokia_lcd_set_cursor(0, 16);
        nokia_lcd_write_string("Time:Searching", 1);

        nokia_lcd_render();
    }

    else {
        nokia_lcd_write_string("Lat.: ", 1);
        latitude_parse_print(lat,lat_h);     
        nokia_lcd_set_cursor(0, 8);
        nokia_lcd_write_string("Lon.: ", 1); 
        longitude_parse_print(lon,lon_h);
        nokia_lcd_set_cursor(0, 16);
        nokia_lcd_write_string("Time: ", 1); 
        time_parse_print(time);
        }

        vyhledavam = 1;
        pokracuj = 1;
        return;
}


ISR(INT0_vect){

    TIM_config_interrupt(TIM1, TIM_OVERFLOW_DISABLE);    
    PORTD &= ~_BV(GPS_enable);  
    uart_puts(NMEA_parse[2]);
    PORTD |= _BV(GPS_enable); 
    TIM_config_interrupt(TIM1, TIM_OVERFLOW_ENABLE);  

 
}

