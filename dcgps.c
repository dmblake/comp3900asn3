/*
 * SOURCE FILE: dcgps.c
 * PROGRAM: DCGPS
 * FUNCTIONS: int main(int argc, char *argv[])
 * DATE: Nov 2, 2015
 * REVISIONS: v1
 * DESIGNER: Dylan & Allen
 * PROGRAMMER: Dylan
 *
 * NOTES: Allocates resources for the GPS device and information data structure.
 */
#include "dcgps.h"

static struct fixsource_t source;
static gps_data_t *data_ptr;

/*
 * FUNCTION: main
 * DATE: Nov 2, 2015
 * REVISION: v1
 * DESIGNER: Dylan & Allen
 * PROGRAMMER: Dylan
 * INTERFACE: int main (int argc, char *argv[])
 *              int argc : not used in this program
 *              char *argv[] : not used in this program
 * RETURNS: 0 upon success, -1 if there is an error
 *
 * NOTES: main driver for the DCGPS program
 */
int main(int argc, char *argv[]) {
    int errCode;
    unsigned int flags = WATCH_ENABLE;
    // malloc structure
    data_ptr = malloc(sizeof(gps_data_t));
    if (!data_ptr) {
        printf("Error allocating memory.\n");
        return -1;
    }
    // open the socket connection to the gpsd daemon
    // gps_open returns 0 upon success, -1 on failure
    if ((errCode = gps_open(source.server, source.port, data_ptr))) {
        printf("Failed to open GPS.\n");
        printf("%s\n", gps_errstr(errCode));
        return -1;
    }
    // if successful
    else {
        if (source.device != NULL) {
            flags |= WATCH_DEVICE;
        }
        gps_stream(data_ptr, flags, source.device);
    }
    // enter loop
    main_gps_loop(data_ptr);
    // free resources
    gps_close(data_ptr);
    gps_stream(data_ptr, WATCH_DISABLE, NULL);
    free(data_ptr);
    return 0;
}
