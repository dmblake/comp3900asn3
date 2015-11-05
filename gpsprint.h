#include <stdio.h>
#include "dcgps.h"

#define MAXCHANNELS 72
#define MAX_POSSIBLE_SATS (MAXCHANNELS-2)

void print_gps_data(gps_data_t *data_ptr);
