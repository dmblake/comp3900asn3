#ifndef DCGPS_H
#define DCGPS_H

typedef struct fixsource_t {
    char *spec;
    char *server;
    char *port;
    char *device;
} fixsource_t;
typedef struct gps_data_t gps_data_t;
#include <gps.h>
#include <stdio.h>
#include <stdlib.h>
#include "gps-utils.h"
#endif
