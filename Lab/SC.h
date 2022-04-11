#pragma once
#include <stdio.h>
#include <stdlib.h>
#define MEMORY 100
#define GETFLAG(k) (registr >> (k - 1)) & 0x1
#define SET1(K) registr | (1 << (k - 1))
#define SET0(k) registr &(~(1 << (k - 1)))
#define INVERT(k) registr ^ (1 << (k - 1))
#define M 1 //Выход за границы
#define C 2 // Неверная команда
#define P 3 // Переполнение
#define F 4 // Ошибка файла
#define O 5 // Неправильный аргумент
int RAM[MEMORY];
int registr;


int cmp(const void *a, const void *b);
void sc_memoryInit();
int sc_memorySet(int address, int value);
int sc_memoryGet(int address, int *value);
int sc_memorySave(char *Filename);
int sc_memoryLoad(char *Filename);
int sc_regInit();
int sc_regSet(int value, int k);
int sc_regGet(int k, int *value);
int sc_commandEncode(int command, int operand, int *value);
int sc_commandDecode(int *operand, int *command, int value);
