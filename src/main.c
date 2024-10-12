#include <stdio.h>
#include <stdint.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <termios.h>

#include "graphics.h"
#include "utils.h"

int main (int argc, char *argv[])
{
    vec2 w = get_console_size();
    
    window *win = NULL;
    window *win_prev = NULL;

    create_window(&win, w.y, w.x);
    create_window(&win_prev, w.y, w.x);

    window_fill_color(win, COLOR_BLACK);

    hide_cursor();

    raw_mode_enable();

    window_index_t cursor_x = 0;
    window_index_t cursor_y = 0;
    uint64_t i = 0;
    while (1)
    {
        escaped_char ec;
        getchar_escaped(&ec);

        if (ec.str[0] == 'q')
        {
            break;
        }
        else if (ec.n == 3)
        {
            char cmd = ec.str[2];
            switch (cmd)
            {
                case 'A':
                    cursor_y -= 1; break;
                case 'B':
                    cursor_y += 1; break;
                case 'C':
                    cursor_x += 1; break;
                case 'D':
                    cursor_x -= 1; break;
                default: break;
            }
        }

        free(ec.str);

        window_set_pixel(win, cursor_x, cursor_y, COLOR_RED);
        render_window(win, win_prev);
        printf("\x1b[H\n\n\n\n%llu", i);
        copy_window(win, win_prev);
        window_set_pixel(win, cursor_x, cursor_y, COLOR_BLACK);

        i++;
    }

    raw_mode_disable();

    destroy_window(win);

    erase_screen();
    reset_cursor();
    show_cursor();

    return 0;
}