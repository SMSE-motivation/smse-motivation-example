#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "s2e.h"

// complile with
// gcc -O0 -g state_machine.c -o state_machine 

enum STATE
{
    INIT = 0,
    FIRST,
    SECOND,
    THIRD,
    FORTH,
    FIFTH,
};

int main()
{
    enum STATE state = INIT;

    int opcode;
    int offset = 0;
    while (1)
    {
        //scanf("%d", &opcode);
        s2e_make_symbolic(&opcode,sizeof(opcode),"opcode");
        switch (opcode)
        {
        case 0:
            if (offset > 0)
                s2e_assert(0);
                printf("vulnerable code\n");
                exit(-1);
            break;
        case 1:
            if (state == INIT)
                state = FIRST;
            break;
        case 2:
            if (state == FIRST)
                state = SECOND;
            else
                state = INIT;
            break;
        case 3:
            if (state == SECOND)
                state = THIRD;
            else
                state = INIT;
            break;
        case 4:
            if (state == THIRD)
                state = FORTH;
            else
                state = INIT;
            break;
        case 5:
            if (state == FORTH)
                state = FIFTH;
            else
                state = INIT;
            break;
        default:
            state = INIT;
            break;
        }

        if (state == FIFTH)
            offset = 1;
        else
            offset = 0;
    }

    return 0;
}
