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
        frag_char fc = {{COLOR_BLACK}, {COLOR_BLACK}};
        (*win)->frag_chars[i] = fc;
    }
}

void destroy_window(window *win)
{
    free(win);
}

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
            frag_char *fc = &win->frag_chars[i];
            frag_char_chars_t fcc;
            snprintf(fcc, FRAG_CHAR_CHARS,
                     "\x1b[3%d;4%dm%s", 
                     fc->upper.color, 
                     fc->lower.color,
                     CHAR_UPPER_BLOCK);
            strcat(display_chars, fcc);
            i++;
        }
    }

    printf("%s", display_chars);
}

static inline window_index_t window_index
(window *win, window_coord_t row, window_coord_t col)
{
    return col + (row * win->cols);
}

void window_set_pixel
(window *win, window_coord_t x, window_coord_t y, color_t c)
{
    if (!window_check_pixel_bounds(win, x, y))
        return;

    frag_char *fc = &(win->frag_chars[window_index(win, y / 2, x)]);
    if (y % 2 == 0)
        fc->upper.color = c;
    else
        fc->lower.color = c;
}

int window_check_pixel_bounds
(window *win, window_coord_t x, window_coord_t y)
{
    if (x < 0 || y < 0)
        return 0;
    if (x >= win->cols)
        return 0;
    if (y / 2 >= win->rows)
        return 0;
    return 1;
}