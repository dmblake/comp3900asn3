/*
 * SOURCE FILE: gps-utils.c
 * PROGRAM: DCGPS
 * FUNCTIONS:   void main_gps_loop(gps_data_t)
 *              WINDOW* create_newwin(int, int, int, int)
                void initialize_windows(WINDOW *, WINDOW *, WINDOW *, WINDOW*)
 * DATE: Nov 2, 2015
 * REVISIONS: v2
 * DESIGNER: Dylan & Allen
 * PROGRAMMER: Dylan & Allen
 *
 * NOTES: Allocates resources for the GPS device and information data structure.
 */
#include "gps-utils.h"

/*
 * FUNCTION: main_gps_loop
 * DATE: Nov 2, 2015
 * REVISION: v2
 * DESIGNER: Dylan & Allen
 * PROGRAMMER: Dylan (GPS reading and error checking) & Allen (curses window creation)
 * INTERFACE: main_gps_loop(gps_data_t *data_ptr)
 *              gps_data_t *data_ptr : structure to fill with GPS data
 * RETURNS: void
 *
 * NOTES: Sets up the curses window and opens the GPS for reading.
 */
void main_gps_loop(gps_data_t *data_ptr) {
    int errno;
    // init windows
    initscr();
    cbreak();
    noecho();
    timeout(10);
    refresh(); 
    WINDOW* mainwin = create_newwin(20, 77, 0, 0);
    mvwprintw(mainwin, 0, 2, "DCGPS");
    mvwprintw(mainwin, 19, 60, "Press q to exit");
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
            return;
        }
        if ((errno = gps_read(data_ptr)) == -1) {
            endwin();
            fprintf(stderr, "Error reading the GPS.\n");
            fprintf(stdout, "%s\n", gps_errstr(errno));
            return;
        } else if(getch() == 'q') {
            endwin();
            return; 
        } else {
            print_gps_data(data_ptr, locdata, satdata); 
        }
    }
    endwin();
}

/*
 * FUNCTION: create_newwin
 * DATE: Nov 7, 2015
 * REVISION: v1
 * DESIGNER: Allen
 * PROGRAMMER: Allen
 * INTERFACE: WINDOW* create_newwin(int height, int width, int starty, int startx)
 *              int height : height of the window
 *              int width : width of the window
 *              int starty : y position of the window
 *              int startx : x position of the window
 * RETURNS: a pointer to the window that was created
 *
 * NOTES: Creates a new curses window with the given parameters and draws the border around it.
 */
WINDOW* create_newwin(int height, int width, int starty, int startx) {
    WINDOW *local_win;
    local_win = newwin(height, width, starty, startx);
    box(local_win, 0 , 0);
    wrefresh(local_win);
    return local_win;
}

/*
 * FUNCTION: initialize_windows
 * DATE: Nov 7, 2015
 * REVISION: v1
 * DESIGNER: Allen
 * PROGRAMMER: Allen
 * INTERFACE: void initialize_windows(WINDOW *locwin, WINDOW *locdata, WINDOW *satwin, WINDOW* satdata)
 *              WINDOW *locwin : the location window
 *              WINDOW *locdata : the location data field
 *              WINDOW *satwin : the satellite window
 *              WINDOW* satdata : the satellite data fields
 * RETURNS: void
 *
 * NOTES: Sets up the text for the curses windows such as headers and data fields.
 */
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
