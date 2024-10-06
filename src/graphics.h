#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "utils.h"

/*
 * Half block characters.
 * Used for fitting two pixels into one character.
 */

#define CHAR_UPPER_BLOCK "\u2580"
#define CHAR_LOWER_BLOCK "\u2584"

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

#define FRAG_CHAR_CHARS (2 + (COLOR_CODE_LENGTH - 1) * 2)
typedef char frag_char_chars_t[FRAG_CHAR_CHARS];

// max length of window.frag_chars is uint32_t
// uint16_t * uint16_t = uint32_t
// 2^16 * 2^16 = 2^32

typedef uint16_t window_coord_t;
typedef uint32_t window_index_t;

typedef struct _frag
{
    uint8_t color;
} frag;

typedef struct _frag_char
{
    frag upper;
    frag lower;
} frag_char;

typedef struct _window
{
    uint16_t rows;
    uint16_t cols;
    frag_char *frag_chars;
} window;

void create_window(window **win, uint16_t rows, uint16_t cols);
void destroy_window(window *win);
void display_window(window *win);
// static inline window_index_t window_index
// (uint16_t row, uint16_t col, window* win);

#endif