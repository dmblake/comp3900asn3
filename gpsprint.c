#include "gpsprint.h"

 void print_gps_data(gps_data_t *data_ptr) {
    int i, j;
    bool usedflags[MAXCHANNELS];
    for (i = 0; i < MAXCHANNELS; i++) {
        usedflags[i] = false;
        for (j = 0; j < data_ptr->satellites_used; j++) {
            if (data_ptr->used[j] == data_ptr->PRN[i]) {
                usedflags[i] = true;
            }
        }
    } 
    // print out information of visible satellites
    if (data_ptr->satellites_visible != 0) {
        for (i = 0; i < MAX_POSSIBLE_SATS; i++) {
            if (i < data_ptr->satellites_visible) {
                fprintf(stdout, "PRN:%3d\tElevation:%02d\tAzimuth:%03d\tSNR:%02d\tUsed:%c\n",
                        data_ptr->PRN[i],
                        data_ptr->elevation[i],
                        data_ptr->azimuth[i],
                        (int)data_ptr->ss[i],
                        ( usedflags[i] ? 'Y' : 'N'));
            }
        }
        if (data_ptr->fix.mode >= MODE_2D && isnan(data_ptr->fix.latitude) == 0) {
            fprintf(stdout, "Latitude: %s%c\n", deg_to_str(deg_ddmmss, fabs(data_ptr->fix.latitude)), (data_ptr->fix.latitude < 0) ? 'S' : 'N');
            fflush(stdout);
        } else {
            fprintf(stdout, "n/a\n");
        }
        if (data_ptr->fix.mode >= MODE_2D && isnan(data_ptr->fix.longitude) == 0) {
            fprintf(stdout, "longitude: %s%c\n", deg_to_str(deg_ddmmss, fabs(data_ptr->fix.longitude)), (data_ptr->fix.longitude < 0) ? 'W' : 'E');
        } else {
            fprintf(stdout, "n/a\n");
        }
    } else {
        fprintf(stdout, "No satellites.\n");
    }
    fprintf(stdout, "----------------------------\n");
 }
