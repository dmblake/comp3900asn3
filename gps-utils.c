#include "gps-utils.h"

void main_gps_loop(gps_data_t *data_ptr) {
    initscr();
    cbreak();
    refresh();
    WINDOW* mainwin = create_newwin(20, 77, 0, 0);
    mvwprintw(mainwin, 0, 2, "DCGPS");
    wrefresh(mainwin);
    WINDOW* locwin = create_newwin(18, 40, 1, 1);
    mvwprintw(locwin, 1, 1, "Timestamp:\n\n Time:\n\n Latitude:\n\n Longitude:");
    box(locwin, 0 , 0);
    wrefresh(locwin);
    WINDOW* locdata = create_newwin(16, 26, 2, 13);
    wclear(locdata);
    wrefresh(locdata);
    WINDOW* satwin = create_newwin(18, 35, 1, 41);
    mvwprintw(satwin, 1, 1, "PRN:  Elev:  Azim:  SNR:  Used:");
    wrefresh(satwin);
    WINDOW* satdata = create_newwin(15, 33, 3, 42);
    wclear(satdata);
    wrefresh(satdata);

    for (;;) {
        if (!gps_waiting(data_ptr, 5000000)) {
            endwin();
            fprintf(stdout, "Timeout on GPS\n");
            return;
        }
        if (gps_read(data_ptr) == -1) {
            fprintf(stderr, "Error reading the GPS.\n");
        } else {
            print_gps_data(data_ptr, locdata, satdata); 
        }
    }
    endwin();
}
