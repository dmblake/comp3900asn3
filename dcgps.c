#include <gps.h>
#include <stdio.h>
#include <stdlib.h>
#include "gps_structures.h"
#include "gps-utils.h"

#define LOCAL_HOST "127.0.0.1"

static fixsource_t source;
static gps_data_t *data_ptr;

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
