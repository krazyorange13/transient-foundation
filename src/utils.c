#include "utils.h"

vec2 get_console_size()
{
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    vec2 w_vec = {w.ws_col, w.ws_row};
    return w_vec;
}

void raw_mode_enable()
{
    struct termios raw;
    tcgetattr(STDIN_FILENO, &raw);
    raw.c_lflag &= ~(ECHO | ICANON);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

void raw_mode_disable()
{
    struct termios raw;
    tcgetattr(STDIN_FILENO, &raw);
    raw.c_lflag &= (ECHO | ICANON);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

void getchar_escaped(escaped_char *ec)
{
    char c0 = getchar();
    if (c0 == '\n')
    {
        ec->n = 2;
        ec->str = malloc(sizeof(char) * 3);
        ec->str[0] = '\\';
        ec->str[1] = 'n';
        ec->str[2] = '\0';
        return;
    }
    else if (c0 == '\t')
    {
        ec->n = 2;
        ec->str = malloc(sizeof(char) * 3);
        ec->str[0] = '\\';
        ec->str[1] = 't';
        ec->str[2] = '\0';
        return;
    }
    else if (c0 != '\e')
    {
        ec->n = 1;
        ec->str = malloc(sizeof(char) * 2);
        ec->str[0] = c0;
        ec->str[1] = '\0';
        return;
    }
    else
    {
        char c1 = getchar();
        if (c1 != '[')
        {
            ec->n = 2;
            ec->str = malloc(sizeof(char) * 3);
            ec->str[0] = '\\';
            ec->str[1] = c0;
            ec->str[2] = '\0';
            return;
        }
        else
        {
            char c2 = getchar();
            ec->n = 3;
            ec->str = malloc(sizeof(char) * 4);
            ec->str[0] = '\\';
            ec->str[1] = c1;
            ec->str[2] = c2;
            ec->str[3] = '\0';
            return;
        }
    }
}