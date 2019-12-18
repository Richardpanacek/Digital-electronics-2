#include "GPS_parsing.h"

#include <string.h>
#include <math.h>
#include <stdio.h>
#include "nokia5110.h"


void  latitude_parse_print(volatile double lat, volatile char latitude_hemisphere)
{   
    double fractpart; double intpart;
    int fp; int ip;
    char vypis[50];

    int degrees = lat/100;
    double seconds = (lat/100-degrees)*100;
    seconds /= 60;
    double latitude = seconds + degrees;

    fractpart = modf(latitude, &intpart);
    ip = intpart;
    fp = fractpart*10000;

    if (latitude_hemisphere == 'S'){
        nokia_lcd_write_char('-', 1);
    }

    sprintf(vypis,"%d",ip);
    nokia_lcd_write_string(vypis, 1);
    nokia_lcd_write_char('.', 1);    
    sprintf(vypis,"%d",fp);
    nokia_lcd_write_string(vypis, 1);  

    nokia_lcd_render();  
}


void  longitude_parse_print(volatile double lon, volatile char longitude_hemisphere)
{   
    double fractpart; double intpart;
    int fp; int ip;
    char vypis[50];

    int degrees = lon/100;
    double seconds = (lon/100-degrees)*100;
    seconds /= 60;
    double longitude = seconds + degrees;

    fractpart = modf(longitude, &intpart);
    ip = intpart;
    fp = fractpart*10000;

    if (longitude_hemisphere == 'W'){
        nokia_lcd_write_char('-', 1);
    }

    sprintf(vypis,"%d",ip);
    nokia_lcd_write_string(vypis, 1);
    nokia_lcd_write_char('.', 1);    
    sprintf(vypis,"%d",fp);
    nokia_lcd_write_string(vypis, 1);  

    nokia_lcd_render();  
}


void  time_parse_print(volatile double time){
    char vypis[50];

    int hour = time/10000;
    int min = (time/10000 - hour)*100;
    // int sec = time;
    // sec = sec%10;

    sprintf(vypis,"%d",hour);
    nokia_lcd_write_string(vypis, 1);
    nokia_lcd_write_char(':', 1); 
    sprintf(vypis,"%d",min);
    nokia_lcd_write_string(vypis, 1);
    // nokia_lcd_write_char(':', 1);
    // sprintf(vypis,"%d",sec);
    // nokia_lcd_write_string(vypis, 1);

    nokia_lcd_render(); 
}