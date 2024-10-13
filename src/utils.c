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
    struct termios conf;
    tcgetattr(STDIN_FILENO, &conf);
    conf.c_lflag &= ~(ECHO | ICANON);
    conf.c_cc[VMIN] = 0;  // this is poggers, non-blocking input,
    conf.c_cc[VTIME] = 0; // but needs to get reset? could be bad
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &conf);
}

void raw_mode_disable()
{
    struct termios conf;
    tcgetattr(STDIN_FILENO, &conf);
    conf.c_lflag &= (ECHO | ICANON);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &conf);
}

int was_kbhit()
{
   struct timeval tv = { 0L, 0L };
   fd_set fds;
   FD_ZERO(&fds);
   FD_SET(0, &fds);
   return select(1, &fds, NULL, NULL, &tv);
}

char _getchar()
{
    char ch;
    read(STDIN_FILENO, &ch, 1);
    return ch;
}

void getchar_escaped(escaped_char *ec)
{
    char c0 = _getchar();
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
        char c1 = _getchar();
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
            char c2 = _getchar();
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