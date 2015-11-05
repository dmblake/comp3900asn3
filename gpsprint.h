#ifndef GPSPRINT_H
#define GPSPRINT_H
#include <stdio.h>
#include <math.h>
#include <gps.h>
#include <string.h>
#include "dcgps.h"
#include "gpsdclient.h"

#define MAXCHANNELS 72
#define MAX_POSSIBLE_SATS (MAXCHANNELS-2)

void print_gps_data(gps_data_t *data_ptr);
#endif
