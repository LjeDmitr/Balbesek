#pragma once
#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>

enum colors
{
	black = 30,
	red = 31,
	green = 32,
	blue = 34,
	magenta = 35,
	light_blue = 37,
	cl_default = 39
};

void mt_clear();
int mt_gotoXY(int x, int y);
int mt_getscreensize(int *rows, int *cols);
int mt_setfgcolor(enum colors color);
int mt_setbgcolor(enum colors color);
