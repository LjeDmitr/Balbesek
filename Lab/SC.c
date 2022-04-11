#include "SC.h"

const int correct_operations[] = {0x10, 0x11, 0x21, 0x30, 0x31, 0x32, 0x33, 0x40,
                                  0x41, 0x42, 0x43, 0x51, 0x52, 0x53, 0x54, 0x55,
                                  0x56, 0x57, 0x58, 0x59, 0x60, 0x61, 0x62, 0x63,
                                  0x64, 0x65, 0x66, 0x67, 0x68, 0x68, 0x69, 0x70,
                                  0x71, 0x72, 0x73, 0x74, 0x75, 0x76};
const int operations_n = 38;

int cmp(const void *a, const void *b)
{
    if (a > b)
        return 1;
    else if (a == b)
        return 0;
    else
        return -1;
}

void sc_memoryInit()
{
    for (int i = 0; i < MEMORY; i++)
    {
        RAM[i] = 0;
    }
}

int sc_memorySet(int address, int value)
{
    if (address < MEMORY)
    {
        RAM[address] = value;
        return 0;
    }
    sc_regSet(1, M);
    return -1;
}

int sc_memoryGet(int address, int *value)
{
    if (address < MEMORY)
    {
        *value = RAM[address];
        return 0;
    }
    sc_regSet(1, M);
    return -1;
}

int sc_memorySave(char *Filename)
{
    FILE *file;
    file = fopen(Filename, "wb");
    if (file == NULL)
    {
        sc_regSet(1, F);
        return -1;
    }
    fwrite(RAM, sizeof(int), MEMORY, file);

    fclose(file);
    return 0;
}

int sc_memoryLoad(char *Filename)
{
    FILE *file;
    file = fopen(Filename, "rb");
    if (file == NULL)
    {
        sc_regSet(1, F);
        return -1;
    }
    fread(RAM, sizeof(int), MEMORY, file);

    fclose(file);
    return 0;
}

int sc_regInit()
{
    registr = 0;
    return 0;
}

int sc_regSet(int value, int k)
{
    if (value == 1)
    {
        registr = SET1(k);
    }
    else if (value == 0)
    {
        registr = SET0(k);
    }
    else
    {
        sc_regSet(1, O);
        return -1;
    }
    return 0;
}

int sc_regGet(int k, int *value)
{
    if (k < 33 && k > 0)
    {
        *value = GETFLAG(k);
        return 0;
    }
    else
    {
        sc_regSet(1, M);
        return -1;
    }
}

int sc_commandEncode(int command, int operand, int *value)
{
    int *command_ptr = NULL;

    command_ptr = bsearch(&command, correct_operations, operations_n, sizeof(int), cmp);

    if (command_ptr != NULL)
    {
        *value = (command << 7) | operand;
        return 0;
    }
    else
    {
        sc_regSet(1, C);
        return -1;
    }
}

int sc_commandDecode(int *operand, int *command, int value)
{
    void *correct_command;
    int check;
    int tmp_command, tmp_operand;

    check = (value >> 14) & 1;
    if (check == 0)
    {
        tmp_command = (value >> 7) & 0x7F;
        tmp_operand = value & 0x7F;
        correct_command = bsearch(&tmp_command, correct_operations, operations_n, sizeof(int), cmp);
        if (correct_command != NULL)
        {
            *command = tmp_command;
            *operand = tmp_operand;
        }
        else
        {
            sc_regSet(1, C);
        }
        return -1;
    }
    else
    {
        sc_regSet(1, C);
        return -1;
    }

    return 0;
}