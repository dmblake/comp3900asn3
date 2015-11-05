#include "gps-utils.h"


void main_gps_loop(gps_data_t *data_ptr) {
    for (;;) {
        if (!gps_waiting(data_ptr, 5000000)) {
            fprintf(stdout, "Timeout on GPS\n");
            return;
        }
        if (gps_read(data_ptr) == -1) {
            fprintf(stderr, "Error reading the GPS.\n");
        } else {
            print_gps_data(data_ptr); 
        }
    }
}
