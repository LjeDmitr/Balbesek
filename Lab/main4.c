#include "BigChars.h"
#include "SC.h"
#include "myReadkey.h"

void interface()
{
	mt_clear();
	bc_box(1, 1, 61, 12);
	sc_memoryInit();
	mt_gotoXY(30, 1);
	printf("Memory");
	int index = 0, tmpRam = 0;
	RAM[index] = 3506;
	for (int i = 1; i <= 10; i++)
	{
		for (int j = 0; j < 60; j += 6)
		{
			if (RAM[index] >= 9999)
			{
				mt_gotoXY(j + 2, i + 1);
				printf("+9999 ");
			}
			else
			{
				mt_gotoXY(j + 2, i + 1);
				printf("+");
				tmpRam = RAM[index];
				for (int k = 0; k < 4; k++)
				{
					mt_gotoXY(j + 6 - k, i + 1);
					printf("%d", tmpRam % 10);
					tmpRam /= 10;
				}
			}
			index++;
		}
	}
	bc_box(64, 1, 22, 3);

	mt_gotoXY(70, 1);
	printf("accumulator");
	mt_gotoXY(72, 2);
	printf("+9999");

	bc_box(64, 4, 22, 3);
	mt_gotoXY(67, 4);
	printf("instructionCounter\n");
	mt_gotoXY(72, 5);
	printf("+0000\n");

	bc_box(64, 7, 22, 3);
	mt_gotoXY(71, 7);
	printf("Operation\n");
	mt_gotoXY(71, 8);
	printf("+00 : 00\n");

	bc_box(64, 10, 22, 3);
	mt_gotoXY(73, 10);
	printf("Flags\n");
	mt_gotoXY(72, 11);
	printf("O E V M\n");

	struct Bigchars number[] = {{1717976064, 3958374},
								{1010315264, 3158064},
								{1010842624, 8258050},
								{2120252928, 8282238},
								{2120640000, 6316158},
								{1040350720, 4079680},
								{35789824, 1974814},
								{811630080, 396312},
								{1013332992, 3958374},
								{2087074816, 3956832}};

	bc_box(1, 13, 46, 10);
	int bigCh[2];
	bigCh[0] = 2115508224;
	bigCh[1] = 1579134;
	int y = 14, x = 2;
	bc_printbigchar(bigCh, x, y, red, cl_default);

	index = 0;
	tmpRam = RAM[index];
	x = 38;
	for (int i = 0; i < 4; i++)
	{
		bigCh[0] = number[tmpRam % 10].value1;
		bigCh[1] = number[tmpRam % 10].value2;
		bc_printbigchar(bigCh, x, y, red, cl_default);
		tmpRam /= 10;
		x -= 9;
	}

	mt_setfgcolor(cl_default);
	mt_setbgcolor(cl_default);
	mt_gotoXY(51, 13);
	printf("Keys: \n");
	mt_gotoXY(50, 14);
	printf("l - load\n");
	mt_gotoXY(50, 15);
	printf("s - save\n");
	mt_gotoXY(50, 16);
	printf("r - run\n");
	mt_gotoXY(50, 17);
	printf("t - step\n");
	mt_gotoXY(50, 18);
	printf("i - reset\n");
	mt_gotoXY(50, 19);
	printf("F5 - accumulator\n");
	mt_gotoXY(50, 20);
	printf("F6 - instructionCounter\n");
	bc_box(49, 13, 37, 10);
	printf("\n");
}

int main()
{
	interface();
	int key = -1;
	int x = 2, y = 2;
	int count_n = 0;
	char buf[30];
	mt_gotoXY(x, y);
	while (key != 13)
	{
		if (rk_readkey(&key) == -1)
		{
			printf("Error term\n");
			return 0;
		}
		if (key == KEY_up && y > 2)
		{
			y--;
			count_n = sprintf(buf, "\E[%d;%dH", y, x);
			write(STDIN_FILENO, buf, count_n);
		}
		else if (key == KEY_down && y < 11)
		{
			y++;
			count_n = sprintf(buf, "\E[%d;%dH", y, x);
			write(STDIN_FILENO, buf, count_n);
		}
		else if (key == KEY_right && x < 60)
		{
			x += 6;
			count_n = sprintf(buf, "\E[%d;%dH", y, x);
			write(STDIN_FILENO, buf, count_n);
		}
		else if (key == KEY_left && x > 2)
		{
			x -= 6;
			count_n = sprintf(buf, "\E[%d;%dH", y, x);
			write(STDIN_FILENO, buf, count_n);
		}
		else if (key == KEY_enter)
		{
			write(STDIN_FILENO, "     ", 5);
			count_n = sprintf(buf, "\E[%d;%dH", y, x);
			write(STDIN_FILENO, buf, count_n);
			count_n = sprintf(buf, "+", y, x);
			write(STDIN_FILENO, buf, count_n);
		}
		else if (key == KEY_l)
		{
			rk_mytermrestore();
		}
		else if (key == KEY_s)
		{
			rk_mytermsave();
		}
		else if (key == KEY_f5)
		{
		}
		// rk_mytermregime(1, 0, 0, 0, 0);
	}

	return 0;
}