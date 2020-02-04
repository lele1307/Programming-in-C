#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <math.h>
#include <assert.h>

#include "interp.h"
#include "exten.h"

void test(void){
    printf("GOOD\n");
}
void PROG_EXTEN(Program *p,ProgramArr progarr)
{
    int i,cright=0,cleft=0;
    for ( i = 0; i <= p->num; i++)
    {
        if (strsame(p->wds[i],"{"))
        {
            cleft++;
        }
        else if (strsame(p->wds[i],"}"))
        {
            cright++;
        }
    }
    if (cleft!=cright)
    {
        ERROR(" STRUCT '{' and '}' is not pairing!");
        FREE(progarr);
    }
    else
    {
        if (!strsame(p->wds[p->cw],"{"))
        {
            ERROR("No { statement?");
            FREE(progarr);
        }    
        p->cw = p->cw+1;
        INSTRS_EXTEN(p,progarr);
    }
}
void INSTRS_EXTEN(Program *p,ProgramArr progarr)
{
    if (strsame(p->wds[p->cw],"}"))
        return;
    INSTRUCT_EXTEN(p,progarr);
    p->cw = p->cw+1;
    INSTRS_EXTEN(p,progarr);
}
void INSTRUCT_EXTEN(Program *p,ProgramArr progarr)
{
    if (strsame(p->wds[p->cw],"PRINT"))
    {
        p->cw = p->cw+1;
        VARCON(p,progarr);
        PRINT(p,progarr);
        printf("\n");
        return;
    }
    else if (strsame(p->wds[p->cw],"PRINTN"))
    {
        p->cw = p->cw+1;
        VARCON(p,progarr);
        PRINT(p,progarr);
        return;
    }
    else if(strsame(p->wds[p->cw],"JUMP"))
    {
        p->cw = p->cw+1;
        NUMCON(p,progarr);
        JUMP(p);
        return;
    }
    else if(strsame(p->wds[p->cw],"FILE"))
    {
        p->cw = p->cw+1;
        STRCON(p,progarr);
        READFILE_EXTEN(p,progarr);
        return;
    }
    else if(strsame(p->wds[p->cw],"ABORT"))
    {
        /* test(p); */
        Progarr_free(progarr);
        ABORT("ABORT END\n");
        return;
    }
    else if(strsame(p->wds[p->cw],"INC"))
    {
        p->cw = p->cw+1;
        INC_RND(p,progarr);
        INC(p,progarr);
        return;
    }
    else if(strsame(p->wds[p->cw],"RND"))
    {
        p->cw = p->cw+1;
        INC_RND(p,progarr);
        RND(p,progarr);
        return;
    }
    else if(strsame(p->wds[p->cw],"INNUM"))
    {
        p->cw = p->cw+1;
        INC_RND(p,progarr);
        INNUM(p);
        return;
    }    
    else if(strsame(p->wds[p->cw],"IN2STR"))
    {
        p->cw = p->cw+1;
        IN2STR(p,progarr);
        IN2STR_IN(p);
        return;
    }
    else if(p->wds[p->cw][0]=='%')
    {
        SET(p,progarr);
        SETNUM(p,progarr);
        return;
    }
    else if(p->wds[p->cw][0]=='$')
    {
        SET(p,progarr);
        SETSTR(p,progarr);
        return;
    }
    else if(strsame(p->wds[p->cw],"IFEQUAL"))
    {
        IFCOND_EXTEN(p,progarr);
        IF_CHECK(p,progarr);
        IFEQUAL_EXTEN(p,progarr);
        return;
    }
    else if(strsame(p->wds[p->cw],"IFGREATER"))
    {
        IFCOND_EXTEN(p,progarr);
        IF_CHECK(p,progarr);
        IFGREATER_EXTEN(p,progarr);
        return;
    }
    else if(strsame(p->wds[p->cw],"LOOP"))
    {
        p->cw = p->cw+1;
        LOOP(p,progarr);
        LOOP_INTE(p,progarr);
        return;
    } 
    else if(strsame(p->wds[p->cw],"BREAK"))
    {
        BREAK(p,progarr);
        return;
    }
    else
    {
        ERROR(" Expecting correct INSTRUCT!! ");
        FREE(progarr);
    }
    
    
}

void LOOP(Program *p,ProgramArr progarr)
{
    if (strsame(p->wds[p->cw],"("))
    {
        p->cw = p->cw+1;
        NUM(p,progarr);
        p->loop = LOOP_REC(p);
        p->cw = p->cw+1;
        if (strsame(p->wds[p->cw],")"))
        {
            p->cw = p->cw+1;
            if(!strsame(p->wds[p->cw],"{"))
            {
                ERROR(" 'LOOP' No { statement? ");
                FREE(progarr);
            }
            p->cw = p->cw+1;
            p->looposition = p->cw;
            while(!strsame(p->wds[p->cw],"}"))
            {
                p->cw++;
            }
            INSTRS_EXTEN(p,progarr);
        }
    }
    else
    {
        ERROR(" Incorrect LOOP format !! ");
        FREE(progarr);
    }
    
}
void NUM(Program *p,ProgramArr progarr)
{
    int len,i;
    len = strlen(p->wds[p->cw]);
    if(isdigit(p->wds[p->cw][0]))
    {
        for ( i = 1; i < len; i++)
        {
            if(!isdigit(p->wds[p->cw][i])){
                ERROR(" Incorrect in NUM! Varible shoule all use number!");
                FREE(progarr);
            }
        }
        return;
    }
    ERROR(" Incorrect NUM format !");
    FREE(progarr);
}
int LOOP_REC(Program *p)
{
    int loop;
    loop = atoi(p->wds[p->cw]);
    return loop;
}
void LOOP_INTE(Program *p,ProgramArr progarr)
{
    int i;
    for ( i = 0; i < p->loop; i++)
    {
        p->cw = p->looposition;
        if(strsame(p->wds[p->cw],"}")){
            ERROR("You should input some instructions in LOOP! ");
            FREE(progarr);
        }
        INSTRS_EXTEN(p,progarr);
    }
}
void BREAK(Program *p,ProgramArr progarr)
{
    p->cw = p->cw+1;
    while (!strsame(p->wds[p->cw],"}"))
    {
        p->cw++;
    }
    p->cw = p->cw+1;
    /* printf("%d %d\n",p->cw,p->num); */
    if (p->cw == p->num){
        FREE(progarr);
    }
    else
    {
        INSTRS_EXTEN(p,progarr); 
    }
}

void READFILE_EXTEN(Program *p,ProgramArr progarr)
{
    char *str;
    progarr.num++;
    str = GetSTRCON(p->wds[p->cw]);
    progarr.p[progarr.num]= init_P();
    InputFile(str,progarr.p[progarr.num],progarr);
    free(str);
    CopyVal(p,progarr.p[progarr.num]);
    /* printSTRUCT(newfile); */
    PROG_EXTEN(progarr.p[progarr.num],progarr);
    CopyVal(progarr.p[progarr.num],p);
    /* printf("FILE Parsed OK\n"); */
    prog_free(&progarr.p[progarr.num]);
    progarr.num--;
}
void IFCOND_EXTEN(Program *p,ProgramArr progarr)
{
    p->cw = p->cw+1;
        IF(p,progarr);
        IF_RECORD(p);
    p->cw = p->cw+1;
    if(!strsame(p->wds[p->cw],"{"))
    {
        ERROR(" 'IF' No { statement? ");
        FREE(progarr);
    }
    p->cw = p->cw+1;
    while(!strsame(p->wds[p->cw],"}"))
    {
        p->cw++;
    }
    INSTRS_EXTEN(p,progarr);
}
void IFGREATER_EXTEN(Program *p,ProgramArr progarr)
{
    int cleft=0,cright=0;
    p->cw = p->ifposition+1;
    /* printf("ifgra:%d %s\n",p->cw,p->wds[p->cw]); */
    if (p->which == 1)
    {
        if (strcmp(p->strcon[CON1],p->strcon[CON2])>0)
        {
            p->cw = p->cw+1;
            INSTRS_EXTEN(p,progarr);
        }
        else
        {
            do
            {   
                if(strsame(p->wds[p->cw],"{")){
                    cleft++;
                }
                else if (strsame(p->wds[p->cw],"}"))
                {
                    cright++;
                }
                p->cw++;
            }while(cleft!=cright);
            p->cw = p->cw-1;
            INSTRS_EXTEN(p,progarr);
        }
    }
    else if (p->which== -1)
    {
        if (p->numcon[CON1] > p->numcon[CON2])
        {
            p->cw = p->cw+1;
            INSTRS_EXTEN(p,progarr);
        }
        else
        {
            do
            {   
                if(strsame(p->wds[p->cw],"{")){
                    cleft++;
                }
                else if (strsame(p->wds[p->cw],"}"))
                {
                    cright++;
                }
                p->cw++;
            }while(cleft!=cright);
            p->cw = p->cw-1;
            INSTRS_EXTEN(p,progarr);
        }
    }
    p->which = 0;
}
void IFEQUAL_EXTEN(Program *p,ProgramArr progarr)
{
    int cleft=0,cright=0;
    p->cw = p->ifposition+1;
    /* printf("ifgra:%d %s\n",p->cw,p->wds[p->cw]);  */
    if (p->which == 1)
    {
        if (strcmp(p->strcon[CON1],p->strcon[CON2])==0)
        {
            p->cw = p->cw+1;
            INSTRS_EXTEN(p,progarr);
        }
        else
        {
            do
            {   
                if(strsame(p->wds[p->cw],"{")){
                    cleft++;
                }
                else if (strsame(p->wds[p->cw],"}"))
                {
                    cright++;
                }
                p->cw++;

            }while(cleft!=cright);

            p->cw = p->cw-1;

            /* printf("ifend:%d %s\n",p->cw,p->wds[p->cw]);
            printf("left:%d right:%d\n",cleft,cright); */
            INSTRS_EXTEN(p,progarr);
        }
    }
    else if (p->which== -1)
    {
        if (fabs(p->numcon[0]-p->numcon[1])<EPSILON)
        {
            p->cw = p->cw+1;
            INSTRS_EXTEN(p,progarr);
        }
        else
        {
            do
            {   
                if(strsame(p->wds[p->cw],"{")){
                    cleft++;
                }
                else if (strsame(p->wds[p->cw],"}"))
                {
                    cright++;
                }
                p->cw++;
            }while(cleft!=cright);
            p->cw = p->cw-1;
            INSTRS_EXTEN(p,progarr);
        }
    }
    p->which = 0;
}
