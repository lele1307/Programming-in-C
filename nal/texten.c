#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <math.h>
#include <assert.h>

#include "interp.h"
#include "exten.h"

int main(int argc,char **argv)
{
    if (argc==2)
    {
        ProgramArr prog;
        prog.num = 0;
        printf("============TEST STR=============\n");
        test();
        /*testbasic();
        inte_test1();
        inte_test2();
        inte_test4();
        inte_test3(); */
        printf("============TEST END=============\n");
        printf("============INTERP STR===========\n");
        prog.p[prog.num] = init_P();
        srand((unsigned)time(NULL));
        InputFile(argv[1],prog.p[prog.num],prog);
        PROG_EXTEN(prog.p[prog.num],prog);
        printf("============INTERP END===========\n");
        printf("Parsed OK\n");
        printf("=================================\n");
        printSTRUCT(prog.p[prog.num]);
        Progarr_free(prog);
        /* prog_free(&prog.p[prog.num]); */
    }
    else
    {
        printf("ERROR!!! You should input right file name. \n");
        exit(2);
    }
    return 0;
}
