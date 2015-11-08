#include "gps-utils.h"

void main_gps_loop(gps_data_t *data_ptr) {
    int errno;
    initscr();
    cbreak();
    refresh();
    WINDOW* mainwin = create_newwin(20, 77, 0, 0);
    mvwprintw(mainwin, 0, 2, "DCGPS");
    wrefresh(mainwin);
    WINDOW* locwin = create_newwin(18, 40, 1, 1);
    WINDOW* locdata = create_newwin(16, 26, 2, 13);
    WINDOW* satwin = create_newwin(18, 35, 1, 41);
    WINDOW* satdata = create_newwin(15, 33, 3, 42);
    initialize_windows(locwin, locdata, satwin, satdata);

    for (;;) {
        if (!(errno = gps_waiting(data_ptr, 5000000))) {
            endwin();
            fprintf(stdout, "Timeout on GPS\n");
            fprintf(stdout, "%s\n", gps_errstr(errno));
            return;
        }
        if ((errno = gps_read(data_ptr)) == -1) {
            fprintf(stderr, "Error reading the GPS.\n");
            fprintf(stdout, "%s\n", gps_errstr(errno));
        } else {
            print_gps_data(data_ptr, locdata, satdata); 
        }
    }
    endwin();
}

WINDOW* create_newwin(int height, int width, int starty, int startx) {
    WINDOW *local_win;
    local_win = newwin(height, width, starty, startx);
    box(local_win, 0 , 0);
    wrefresh(local_win);
    return local_win;
}

void initialize_windows(WINDOW *locwin, WINDOW *locdata, WINDOW *satwin, WINDOW* satdata) {
    mvwprintw(locwin, 1, 1, "Timestamp:\n\n Time:\n\n Latitude:\n\n Longitude:");
    box(locwin, 0 , 0);
    wrefresh(locwin);
    wclear(locdata);
    wrefresh(locdata);
    mvwprintw(satwin, 1, 1, "PRN:\tElev:\tAzim:\tSNR: Used:");
    wrefresh(satwin);
    wclear(satdata);
    wrefresh(satdata);
}
