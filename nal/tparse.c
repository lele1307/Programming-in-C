#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#include "parse.h"

int main(int argc,char **argv)
{
    if (argc==2)
    {
        Program *prog;
        /* printf("FILE NAME: %s\n",argv[1]); */
        test();
        prog = init_P();
        InputFile(argv[1],prog);
        /* testprint(prog); */
        PROG(prog);
        printf("=======================\n");
        printf("Parsed OK\n");
        printf("=======================\n");
        prog_free(&prog);
    }
    else
    {
        printf("ERROR!!! You should input right file name. \n");
        exit(2);
    }
    return 0;
}
/*Read 'parseread.nal' test function file */
void test(void)
{
    Program *prog;
    /* TEST initial Program */
    prog = init_P();
    assert(prog!=NULL);
    assert(prog->cw==0);

    /* TEST InputFile Function */
    InputFile("parse_allright.nal",prog);
    /* testprint(prog); */
    testInputFile(prog);

    /* TEST PROG Function Using .nal file */
    PROG(prog);

    /* TEST prog_free Function */
    prog_free(&prog);
    assert(prog==NULL);
}
void testInputFile(Program *prog)
{
    int i,j;
    i = strcmp(prog->wds[0],"{");
    j = strcmp(prog->wds[0],"=");
    assert(i==0);
    assert(j!=0);
}
