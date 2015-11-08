#ifndef GPS_UTILS_H
#define GPS_UTILS_H
#include <gps.h>
#include <ncurses.h>
#include "dcgps.h"
#include "gpsprint.h"

void main_gps_loop(gps_data_t*);
WINDOW *create_newwin(int height, int width, int starty, int startx);
void initialize_windows(WINDOW *locwin, WINDOW *locdata, WINDOW *satwin, WINDOW* satdata);
#endif
