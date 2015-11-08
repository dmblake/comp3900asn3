#include "gpsprint.h"

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


