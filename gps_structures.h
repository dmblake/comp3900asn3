#ifndef GPS_STRUCTURES_H
#define GPS_STRUCTURES_H
#include <gps.h>

typedef struct fixsource_t
{
    char *spec;
    char *server;
    char *port;
    char *device;
} fixsource_t;

typedef struct gps_data_t gps_data_t;
#endif
