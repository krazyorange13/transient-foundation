#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "graphics.h"

void erase_screen()
{
    printf(ERASE_SCREEN);
}

void reset_cursor()
{
    printf(RESET_CURSOR);
}

void hide_cursor()
{
    printf(HIDE_CURSOR);
}

void show_cursor()
{
    printf(SHOW_CURSOR);
}

/*
 * frags, chars, windows, oh my!
 */

static inline int frag_char_equal(frag_char *a, frag_char *b)
{
    return a->lower.color == b->lower.color
        && a->upper.color == b->upper.color;
}

void create_window(window **win, window_coord_t rows, window_coord_t cols)
{
    (*win) = malloc(sizeof(window));
    (*win)->rows = rows;
    (*win)->cols = cols;
    (*win)->width = cols;
    (*win)->height = rows * 2;
    (*win)->frag_chars = malloc(sizeof(frag_char) * rows * cols);
    
    for (int i = 0; i < rows * cols; i++)
    {
        frag_char fc = {{COLOR_MAGENTA}, {COLOR_MAGENTA}};
        (*win)->frag_chars[i] = fc;
    }
}

void create_window_pure(window **win, window_coord_t rows, window_coord_t cols)
{
    (*win) = malloc(sizeof(window));
    (*win)->rows = rows;
    (*win)->cols = cols;
    (*win)->frag_chars = malloc(sizeof(frag_char) * rows * cols);
}

void destroy_window(window *win)
{
    free(win);
}

void copy_window(window *src, window *dest)
{
    memcpy(dest->frag_chars, src->frag_chars, 
           sizeof(frag_char) * src->cols * src->rows);
}

void render_window_full(window *win)
{
    reset_cursor();

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

void render_window(window *win, window *win_prev)
{
    reset_cursor();

    uint32_t display_chars_count = FRAG_CHAR_CHARS * (win->rows) * (win->cols);
    char display_chars[display_chars_count + 1];
    display_chars[0] = '\0';

    window_coord_t i = 0;
    int prev_diff = 0;
    for (window_coord_t y = 0; y < win->rows; y++)
    {
        for (window_coord_t x = 0; x < win->cols; x++)
        {
            frag_char *fc = &win->frag_chars[i];
            frag_char *fc_prev = &win_prev->frag_chars[i];
            if (!frag_char_equal(fc, fc_prev))
            {
                frag_char_chars_t fcc;
                if (prev_diff)
                {
                    // maybe do some benchmarking to see if even
                    // further optimized printing is better?
                    frag_char *last_fc = &win->frag_chars[i-1];
                    if (frag_char_equal(fc, last_fc))
                    {
                        snprintf(fcc, FRAG_CHAR_CHARS,
                                "%s",
                                CHAR_UPPER_BLOCK);
                    }
                    else
                    {
                        snprintf(fcc, FRAG_CHAR_CHARS,
                                "\x1b[3%d;4%dm%s", 
                                fc->upper.color, 
                                fc->lower.color,
                                CHAR_UPPER_BLOCK);
                    }
                }
                else
                {
                    snprintf(fcc, FRAG_CHAR_CHARS,
                             "\x1b[%d;%dH\x1b[3%d;4%dm%s", 
                             y+1, x+1,
                             fc->upper.color,
                             fc->lower.color,
                             CHAR_UPPER_BLOCK);
                }
                strcat(display_chars, fcc);
                prev_diff = 1;
            }
            else
            {
                prev_diff = 0;
            }
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

    frag_char *fc = &(win->frag_chars[window_index(win, (y / 2), x)]);
    if (y % 2 == 0)
        fc->upper.color = c;
    else
        fc->lower.color = c;
}

void window_fill_color(window *win, color_t c)
{
    for (window_index_t i = 0; i < win->rows * win->cols; i++)
    {
        frag_char fc = {{c}, {c}};
        win->frag_chars[i] = fc;
    }
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
