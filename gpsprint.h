#ifndef GPSPRINT_H
#define GPSPRINT_H
#include <stdio.h>
#include <math.h>
#include <gps.h>
#include <string.h>
#include <ncurses.h>
#include "dcgps.h"

#define MAXCHANNELS 72
#define MAX_POSSIBLE_SATS (MAXCHANNELS-2)

void print_gps_data(gps_data_t *data_ptr, WINDOW* locwin, WINDOW* satdata);
char *deg_to_str(double f);
#endif
