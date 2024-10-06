#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "graphics.h"

void create_window(window **win, uint16_t rows, uint16_t cols)
{
    (*win) = malloc(sizeof(window));
    (*win)->rows = rows;
    (*win)->cols = cols;
    (*win)->frag_chars = malloc(sizeof(frag_char) * rows * cols);
    
    for (int i = 0; i < rows * cols; i++)
    {
        frag_char fr_ch = {{COLOR_BLACK}, {COLOR_BLACK}};
        (*win)->frag_chars[i] = fr_ch;
    }
}

void destroy_window(window *win)
{
    // free(win->frag_chars);
    free(win);
}

// static inline window_index_t window_index
// (uint16_t row, uint16_t col, window* win)
// {
//     return col + (row * win->cols);
// }

void display_window(window *win)
{
    uint32_t display_chars_count = FRAG_CHAR_CHARS * (win->rows) * (win->cols);
    char display_chars[display_chars_count + 1];
    display_chars[0] = '\0';

    window_coord_t i = 0;
    for (window_coord_t y = 0; y < win->rows; y++)
    {
        for (window_coord_t x = 0; x < win->cols; x++)
        {
            frag_char *fr_ch = &win->frag_chars[i];
            frag_char_chars_t fr_ch_chs;
            snprintf(fr_ch_chs, FRAG_CHAR_CHARS,
                     "\x1b[3%d;4%dm%s", 
                     fr_ch->upper.color, 
                     fr_ch->lower.color,
                     CHAR_UPPER_BLOCK);
            strcat(display_chars, fr_ch_chs);
            i++;
        }
    }

    printf("%s", display_chars);
}