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
    window *win_prev = NULL;

    create_window(&win, w.y, w.x);
    create_window(&win_prev, w.y, w.x);
    
    window_fill_color(win, COLOR_BLACK);

    hide_cursor();
    
    unsigned int i = 0;
    while (1)
    {
        window_set_pixel(win, 2, 2, COLOR_RED);
        render_window(win, win_prev);
        copy_window(win, &win_prev);
        if (i++ > 1000)
            break;
    }

    getchar();

    destroy_window(win);

    erase_screen();
    reset_cursor();
    show_cursor();

    return 0;
}