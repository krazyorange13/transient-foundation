#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "utils.h"

/*
 * Half block characters.
 * Used for fitting two pixels into one character.
 */

#define CHAR_UPPER_BLOCK "\u2580"
// #define CHAR_UPPER_BLOCK "\xE2\x96\x92"
// #define CHAR_UPPER_BLOCK "▀"
// #define CHAR_UPPER_BLOCK " "
#define CHAR_LOWER_BLOCK "\u2584"

/*
 * Misc ANSI escape codes
 */

#define ERASE_SCREEN "\x1b[2J"
#define RESET_CURSOR "\x1b[H"
#define HIDE_CURSOR "\x1b[?25l"
#define SHOW_CURSOR "\x1b[?25h"

void erase_screen();
void reset_cursor();
void hide_cursor();
void show_cursor();

/*
 * ANSI escape code color sequences
 */

#define COLOR_CODE_LENGTH 9
typedef char color_code_t[COLOR_CODE_LENGTH];

#define COLOR_BLACK   0
#define COLOR_RED     1
#define COLOR_GREEN   2
#define COLOR_YELLOW  3
#define COLOR_BLUE    4
#define COLOR_MAGENTA 5
#define COLOR_CYAN    6
#define COLOR_WHITE   7
#define COLOR_DEFAULT 9

#define COLOR_RESET "\x1b[0m"

#define COLOR_CODE_FG_BLACK   "\x1b[30m"
#define COLOR_CODE_FG_RED     "\x1b[31m"
#define COLOR_CODE_FG_GREEN   "\x1b[32m"
#define COLOR_CODE_FG_YELLOW  "\x1b[33m"
#define COLOR_CODE_FG_BLUE    "\x1b[34m"
#define COLOR_CODE_FG_MAGENTA "\x1b[35m"
#define COLOR_CODE_FG_CYAN    "\x1b[36m"
#define COLOR_CODE_FG_WHITE   "\x1b[37m"
#define COLOR_CODE_FG_DEFAULT "\x1b[39m"

#define COLOR_CODE_BG_BLACK   "\x1b[40m"
#define COLOR_CODE_BG_RED     "\x1b[41m"
#define COLOR_CODE_BG_GREEN   "\x1b[42m"
#define COLOR_CODE_BG_YELLOW  "\x1b[43m"
#define COLOR_CODE_BG_BLUE    "\x1b[44m"
#define COLOR_CODE_BG_MAGENTA "\x1b[45m"
#define COLOR_CODE_BG_CYAN    "\x1b[46m"
#define COLOR_CODE_BG_WHITE   "\x1b[47m"
#define COLOR_CODE_BG_DEFAULT "\x1b[49m"

/*
 * frags, chars, windows, oh my!
 */

// (COLOR_CODE_LENGTH - terminator) * 2 + CHAR_UPPER_BLOCK + terminator = 18

#define FRAG_CHAR_CHARS (4 + (COLOR_CODE_LENGTH - 1) * 2)
typedef char frag_char_chars_t[FRAG_CHAR_CHARS];

// max length of window.frag_chars is uint32_t
// uint16_t * uint16_t = uint32_t
// 2^16 * 2^16 = 2^32

typedef uint16_t window_coord_t;
typedef uint32_t window_index_t;

typedef uint8_t color_t;

typedef struct _frag
{
    color_t color;
} frag;

typedef struct _frag_char
{
    frag upper;
    frag lower;
} frag_char;

int frag_char_equal(frag_char *a, frag_char *b);

typedef struct _window
{
    window_coord_t rows;
    window_coord_t cols;
    frag_char *frag_chars;
} window;

void create_window(window **win, window_coord_t rows, window_coord_t cols);
void create_window_pure(window **win, window_coord_t rows, window_coord_t cols);
void destroy_window(window *win);
void copy_window(window *src, window **dest);
void render_window_full(window *win);
void render_window(window *win, window* win_prev);
static inline window_index_t window_index
(window *win, window_coord_t row, window_coord_t col);
void window_set_pixel
(window *win, window_coord_t x, window_coord_t y, color_t c);
void window_fill_color(window *win, color_t c);
int window_check_pixel_bounds
(window *win, window_coord_t x, window_coord_t y);

#endif