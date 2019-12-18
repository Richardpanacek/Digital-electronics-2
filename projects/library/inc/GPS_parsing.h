#ifndef  GPS_parsing
#define  GPS_parsing

#include <string.h>
#include <math.h>
#include <stdio.h>
#include "nokia5110.h"

void  latitude_parse_print(volatile double latitude, volatile char latitude_hemisphere);
void  longitude_parse_print(volatile double longitude, volatile char longitude_hemisphere);
void  time_parse_print(volatile double time);


#endif
