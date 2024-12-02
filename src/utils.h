#ifndef TRANSIENT_FOUNDATION_UTILS_H
#define TRANSIENT_FOUNDATION_UTILS_H

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <sys/select.h>
#include <unistd.h>
#include <termios.h>

typedef struct _vec2
{
    uint16_t x;
    uint16_t y;
} vec2;

typedef struct _escaped_char
{
    uint8_t n;
    char *str;
} escaped_char;

vec2 get_console_size();
void raw_mode_enable();
void raw_mode_disable();
struct termios terminal_conf_save();
void terminal_conf_load(struct termios conf);
int was_kbhit();
void getchar_escaped(escaped_char *ec);

#endif
