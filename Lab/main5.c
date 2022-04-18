#include "BigChars.h"
#include "SC.h"
#include "myReadkey.h"
#include <signal.h>
#include <unistd.h>
#include <sys/time.h>

void bigCharPrint(int index);
static struct Bigchars number[] = {{1717976064, 3958374},
								   {1010315264, 3158064},
								   {1010842624, 8258050},
								   {2120252928, 8282238},
								   {2120640000, 6316158},
								   {1040350720, 4079680},
								   {35789824, 1974814},
								   {811630080, 396312},
								   {1013332992, 3958374},
								   {2087074816, 3956832}};

void printIC(int x, int y, int index)
{
	mt_gotoXY(x, y);
	printf("+");
	for (int k = 0; k < 4; k++)
	{
		mt_gotoXY(x + 4 - k, y);
		printf("%d", index % 10);
		index /= 10;
	}
}

void printAC(int x, int y, int index)
{
	mt_gotoXY(x, y);
	printf("+");
	int tmpRam = RAM[index];
	for (int k = 0; k < 4; k++)
	{
		mt_gotoXY(x + 4 - k, y);
		printf("%d", tmpRam % 10);
		tmpRam /= 10;
	}
}

void printRam(int x, int y, int index)
{
	mt_gotoXY(x, y);
	printf("+");
	int tmpRam = RAM[index];
	for (int k = 0; k < 4; k++)
	{
		mt_gotoXY(x + 4 - k, y);
		printf("%d", tmpRam % 10);
		tmpRam /= 10;
	}
}

void interface()
{
	mt_clear();
	bc_box(1, 1, 61, 12);
	mt_gotoXY(30, 1);
	printf("Memory");
	int index = 0, tmpRam = 0;
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
	printf("+0000");

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

	bc_box(1, 13, 46, 10);
	int bigCh[2];
	bigCh[0] = 2115508224;
	bigCh[1] = 1579134;
	int y = 14, x = 2;
	bc_printbigchar(bigCh, x, y, red, cl_default);

	index = 0;
	bigCharPrint(index);

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

void bigCharPrint(int index)
{
	int bigCh[2];
	int tmpRam = RAM[index];
	int x = 38, y = 14;
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
}

static int runX = 2, runY = 2, runCount = 0;

void steap(int x, int y)
{
	mt_gotoXY(x, y);
	bigCharPrint((y - 2) * 10 + (x - 2) / 6);
	printIC(72, 5, (y - 2) * 10 + (x - 2) / 6);
	printAC(72, 2, (y - 2) * 10 + (x - 2) / 6);
	mt_gotoXY(x, y);
}

void signalhandler(int signo)
{
	if (runCount >= 100)
	{
		alarm(0);
		runCount = 0;
		runX = 2;
		runY = 2;
		return;
	}
	steap(runX, runY);
	runX += 6;
	if (runX > 56)
	{
		runX = 2;
		runY++;
	}
	runCount++;
}

int main()
{
	setbuf(stdout, 0);
	sc_memoryInit();
	interface();
	int key = -1;
	int x = 2, y = 2, accumulator = 0, instructionCounter = 0;
	struct itimerval nval, oval;

	signal(SIGALRM, signalhandler);

	nval.it_interval.tv_sec = 1;
	nval.it_interval.tv_usec = 0;
	nval.it_value.tv_sec = 1;
	nval.it_value.tv_usec = 0;

	mt_gotoXY(x, y);
	while (key != 13)
	{
		if (rk_readkey(&key) == -1)
		{
			mt_clear();
			printf("Error term\n");
			return 0;
		}
		if (key == KEY_up && y > 2)
		{
			y--;
			steap(x, y);
		}
		else if (key == KEY_down && y < 11)
		{
			y++;
			steap(x, y);
		}
		else if (key == KEY_right && x < 56)
		{
			x += 6;
			steap(x, y);
		}
		else if (key == KEY_left && x > 2)
		{
			x -= 6;
			steap(x, y);
		}
		else if (key == KEY_enter)
		{
			printf("+    ");
			mt_gotoXY(x + 1, y);
			scanf("%4d", &(RAM[(y - 2) * 10 + (x - 2) / 6]));
			bigCharPrint((y - 2) * 10 + (x - 2) / 6);
			printIC(72, 5, (y - 2) * 10 + (x - 2) / 6);
			printAC(72, 2, (y - 2) * 10 + (x - 2) / 6);
			mt_gotoXY(x, y);
		}
		else if (key == KEY_r)
		{
			runX = 2;
			runY = 2;
			runCount = 0;
			setitimer(ITIMER_REAL, &nval, &oval);
		}
		else if (key == KEY_q)
		{
			runCount = 100;
		}
		else if (key == KEY_t)
		{
			runCount = 99;
			runX = x + 6;
			if (runX > 56)
			{
				runX = 2;
				runY = y + 1;
			}
			else
			{
				runY = y;
			}
			y = runY;
			x = runX;
			setitimer(ITIMER_REAL, &nval, &oval);
		}
		else if (key == KEY_l)
		{
			sc_memoryInit();
			sc_memoryLoad("Ram.bin");
			interface();
		}
		else if (key == KEY_s)
		{
			sc_memorySave("Ram.bin");
		}
		else if (key == KEY_i)
		{
			sc_memoryInit();
			interface();
		}
		else if (key == KEY_f5)
		{
			mt_gotoXY(72, 2);
			printf("+    ");
			mt_gotoXY(73, 2);
			scanf("%d", &accumulator);
			mt_gotoXY(x, y);
			RAM[(y - 2) * 10 + (x - 2) / 6] = accumulator;
			printRam(x, y, (y - 2) * 10 + (x - 2) / 6);
			mt_gotoXY(x, y);
			bigCharPrint((y - 2) * 10 + (x - 2) / 6);
			mt_gotoXY(x, y);
		}
		else if (key == KEY_f6)
		{
			mt_gotoXY(72, 5);
			printf("+    ");
			mt_gotoXY(73, 5);
			scanf("%d", &instructionCounter);
			if (instructionCounter > 99)
			{
				instructionCounter = 0;
				printIC(72, 5, 0);
			}
			y = instructionCounter / 10 + 2;
			x = (instructionCounter % 10) * 6 + 2;
			bigCharPrint((y - 2) * 10 + (x - 2) / 6);
			mt_gotoXY(x, y);
		}
	}

	return 0;
}