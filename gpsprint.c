/*
 * SOURCE FILE: gpsprint.c
 * PROGRAM: DCGPS
 * FUNCTIONS:  void print_gps_data(gps_data_t *data_ptr, WINDOW* locdata, WINDOW* satdata)
                char *deg_to_str(double f) 
 * DATE: Nov 2, 2015
 * REVISIONS: v2
 * DESIGNER: Dylan & Allen
 * PROGRAMMER: Dylan & Allen
 *
 * NOTES: Allocates resources for the GPS device and information data structure.
 */
#include "gpsprint.h"

/*
 * FUNCTION: print_gps_data
 * DATE: Nov 2, 2015
 * REVISION: v2
 * DESIGNER: Dylan & Allen
 * PROGRAMMER: Dylan (reading from the data structure) & Allen (filling the curses windows with data)
 * INTERFACE: void print_gps_data(gps_data_t *data_ptr, WINDOW* locdata, WINDOW* satdata)
 *              gps_data_t *data_ptr : structure that holds data
 *              WINDOW* locdata : curses window to hold location data
 *              WINDOW* satdata : curses window to hold satellite data
 * RETURNS: void
 *
 * NOTES: Reads from the provided data structure and prints the information to the screen.
 */
void print_gps_data(gps_data_t *data_ptr, WINDOW* locdata, WINDOW* satdata) {
    int i, j;
    bool usedflags[MAXCHANNELS];
    wclear(locdata);
    wclear(satdata);
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
                mvwprintw(satdata, i, 0, "%3d\t%02d\t%03d\t%02d  %c",
                        data_ptr->PRN[i],
                        data_ptr->elevation[i],
                        data_ptr->azimuth[i],
                        (int)data_ptr->ss[i],
                        ( usedflags[i] ? 'Y' : 'N'));
                wrefresh(satdata);
            }
        }
    }
    else {
        mvwprintw(satdata, 0, 0, "No satellites.");
        wrefresh(satdata);
    }
    if (data_ptr->fix.mode >= MODE_2D && isnan(data_ptr->fix.time) == 0) {
        time_t seconds =  (time_t)data_ptr->fix.time;
        mvwprintw(locdata, 0, 0, "%d", seconds);
        wrefresh(locdata);
    } else {
        mvwprintw(locdata, 0, 0, "n/a");
        wrefresh(locdata);
    }

    if (data_ptr->fix.mode >= MODE_2D && isnan(data_ptr->fix.time) == 0) {
        time_t seconds =  (time_t)data_ptr->fix.time;
        mvwprintw(locdata, 2, 0, "%s", ctime(&seconds));
        wrefresh(locdata);
    } else {
        mvwprintw(locdata, 2, 0, "n/a");
        wrefresh(locdata);
    }

    if (data_ptr->fix.mode >= MODE_2D && isnan(data_ptr->fix.latitude) == 0) {
        mvwprintw(locdata, 4, 0, "%s %c", deg_to_str(fabs(data_ptr->fix.latitude)), (data_ptr->fix.latitude < 0) ? 'S' : 'N');
        wrefresh(locdata);

    } else {
        mvwprintw(locdata, 4, 0, "n/a");
        wrefresh(locdata);
    }
    if (data_ptr->fix.mode >= MODE_2D && isnan(data_ptr->fix.longitude) == 0) {
        mvwprintw(locdata, 6, 0, "%s %c", deg_to_str(fabs(data_ptr->fix.longitude)), (data_ptr->fix.longitude < 0) ? 'W' : 'E');
        wrefresh(locdata);
    } else {
        mvwprintw(locdata, 6, 0, "n/a");
        wrefresh(locdata);
    }
}
 

/*
 * FUNCTION: deg_to_str
 * DATE: Nov 5, 2015
 * REVISION: v1
 * DESIGNER: Dylan
 * PROGRAMMER: Dylan
 * INTERFACE: char *deg_to_str(double f)
 *              double f : value to convert to string format
 * RETURNS: a string formatted version of the value
 *
 * NOTES: Takes a double from the gps_data_t structure and converts it to a human readable degree minute' second" format
 */
char *deg_to_str(double f) {
    static char str[40];
    int sec, deg, min;
    double fsec, fdeg, fmin;

    if (f < 0 || f > 360) {
        strlcpy(str, "nan", sizeof(str));
        return str;
    }

    fmin = modf(f, &fdeg);
    deg = (int)fdeg;

    fsec = modf(fmin * 60, &fmin);
    min = (int)fmin;
    sec = (int) (fsec * 10000.0);
    snprintf(str, sizeof(str), "%3d %02d' %02d\"", deg, min, sec);

    return str;
}


