#include "myTerm.h"

void mt_clear()
{
    printf("\E[H\E[2J");
}

int mt_gotoXY(int x, int y)
{
    int rows, cols;

    mt_getscreensize(&rows, &cols);
    if ((y < rows) && (x < cols) && (x >= 0) && (y >= 0))
    {
        printf("\E[%d;%dH", y, x);
        return 0;
    }
    else
    {
        return 1;
    }
}

int mt_getscreensize(int *rows, int *cols)
{
    struct winsize w;

    if (!ioctl(STDOUT_FILENO, TIOCGWINSZ, &w))
    {
        *rows = w.ws_row;
        *cols = w.ws_col;
        return 0;
    }
    else
    {
        return 1;
    }
}

int mt_setfgcolor(enum colors color)
{
    printf("\E[%dm", color);
    return 0;
}

int mt_setbgcolor(enum colors color)
{
    printf("\E[%dm", color + 10);
    return 0;
}