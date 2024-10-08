#include <stdio.h>
#include <stdint.h>
#include <sys/ioctl.h>
#include <unistd.h>

#include "graphics.h"
#include "utils.h"

vec2 get_console_size()
{
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    vec2 w_vec = {w.ws_col, w.ws_row};
    return w_vec;
}

int main (int argc, char *argv[])
{
    vec2 w = get_console_size();
    
    window *win = NULL;
    create_window(&win, w.y, w.x);
    for (window_coord_t i = 0; i < win->cols; i++)
    {
        window_set_pixel(win, i, i + 0, COLOR_RED);
        window_set_pixel(win, i, i + 1, COLOR_YELLOW);
        window_set_pixel(win, i, i + 2, COLOR_GREEN);
        window_set_pixel(win, i, i + 3, COLOR_CYAN);
        window_set_pixel(win, i, i + 4, COLOR_BLUE);
        window_set_pixel(win, i, i + 5, COLOR_MAGENTA);
    }
    display_window(win);
    destroy_window(win);

    return 0;
}