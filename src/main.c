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
    window *other_win = NULL;

    create_window(&win, w.y, w.x);
    create_window(&win_prev, w.y, w.x);
    create_window(&other_win, w.y, w.x);

    window_fill_color(win, COLOR_BLACK);

    hide_cursor();
    raw_mode_enable();

    window_index_t cursor_x = 0;
    window_index_t cursor_y = 0;

    while (1)
    {
        if (was_kbhit())
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
            else
            {
                char k = ec.str[0];
                switch (k)
                {
                    case 'j':
                        cursor_y += 1; break;
                    case 'k':
                        cursor_y -= 1; break;
                    case 'h':
                        cursor_x -= 1; break;
                    case 'l':
                        cursor_x += 1; break;
                    default: break;
                }
            }

            free(ec.str);
        }

        window_fill_color(win, COLOR_BLACK);
        window_set_pixel(win, cursor_x, cursor_y, COLOR_RED);
        render_window(win, win_prev);
        copy_window(win, win_prev);
    }

    destroy_window(win);

    raw_mode_disable();
    erase_screen();
    reset_cursor();
    show_cursor();

    return 0;
}