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
    win->frag_chars[1].lower.color = COLOR_RED;
    display_window(win);
    destroy_window(win);

    return 0;
}