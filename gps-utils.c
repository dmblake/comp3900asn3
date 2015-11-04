#include "gps-utils.h"
#include "gpsprint.h"


void main_gps_loop(gps_data_t *data_ptr) {
    for (;;) {
        if (!gps_waiting(data_ptr, 5000000)) {
            return;
        }
        if (gps_read(data_ptr) == -1) {
            fprintf(stderr, "Error reading the GPS.\n");
        } else {
            print_gps_data(data_ptr);
            
        }
    }
    // print loop
    print_gps_data(data_ptr);
}
