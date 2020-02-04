#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#include "parse.h"
void testprint(Program *prog)
{
    int i;
    printf("-----------STRUCT STR------------\n");
    for ( i = 0; i <prog->num+1; i++)
    {
        printf("%d |%s|\n",i,prog->wds[i]);
    }
    printf("prog->cw:%d\n",prog->cw);
    printf("prog->num:%d\n",prog->num);
    printf("-----------STRUCT END------------\n");
}
Program *init_P(void)
{
    Program *p;
    p = (Program*)calloc(1,sizeof(Program));
    if (p==NULL)
    {
        ON_ERROR("Prog_init error!!\n");
    }
    p->wds = (char **)calloc(MAXNUMTOKENS,sizeof(char*));
    if (p->wds==NULL)
    {
        ON_ERROR("Prog_init error!!\n");
    }
    p->cw = 0;
    p->num = 0;
    return p;
}
void prog_free(Program **p)
{
    int i;
    Program *q;
    q = *p;
    for ( i = 0; i < q->num+1; i++)
    {
        free(q->wds[i]);
    }
    free(q->wds);
    free(q);
    *p = NULL;
}
void InputFile(char *str,Program *prog)
{
    int i,j;
    int m=-1;
    int flag=0,cflag=0,lastcflag=0;
    int hflag=0,hcflag=0,lasthcflag=0;
    int len,count=0;
    FILE *fp;
    char word[100];
    fp = fopen(str,"r");
    if (!fp)
    {
        ERROR("Cannot open the file!!");
        FREE(prog);
    }
    /* printf("============INPUT START===============\n"); */
    while (fscanf(fp,"%s",word)==1)
    {
        count++;
    }
    /* printf("count:%d\n",count); */
    rewind(fp);
    for ( i = 0; i < count; i++)
    {
        fscanf(fp,"%s",word);
        len=strlen(word);
        /* printf("%d %d %s",i,len,word); */
        for ( j = 0; j < len; j++)
        {
            if(word[j]=='\"')
                flag++;
            if (word[j]=='#')
                hflag++;
        }
        /* printf("    flag:%d hflag:%d||",flag,hflag); */
        if (flag%2!=0)
        {
            cflag++;
        }
        if (hflag%2!=0)
        {
            hcflag++;
        }
        /* printf("cflag:%d lastcflag:%d  ",cflag,lastcflag);
        printf("hcflag:%d lasthcflag:%d\n",hcflag,lasthcflag); */
        if (cflag>0&&cflag<=2&&hcflag==0)
        {
            if (lastcflag==0)
            {
                m++;
                prog->num = m;
                /* printf("@1@@ m%d @@@  ",m); */
                prog->wds[m]=(char *)calloc(MAXTOKENSIZE,sizeof(char));
                if (prog->wds[m]==NULL)
                {
                    ON_ERROR("Prog_init error!!\n");
                }
            }
            strcat(prog->wds[m], word);
            if (cflag!=2)
            {
                strcat(prog->wds[m]," ");
            }
        }
        else if (hcflag>0&&hcflag<=2&&cflag==0)
        {
            if (lasthcflag==0)
            {
                m++;
                prog->num = m;
                /* printf("@2@@ m%d @@@  ",m); */
                prog->wds[m]=(char *)calloc(MAXTOKENSIZE,sizeof(char));
                if (prog->wds[m]==NULL)
                {
                    ON_ERROR("Prog_init error!!\n");
                }
            }
            strcat(prog->wds[m], word);
            if (hcflag!=2)
            {
                strcat(prog->wds[m]," ");
            }
        }
        else if(cflag==0&&hcflag==0)
        {
            m++;
            prog->num = m;
            /* printf("@3@@ m%d @@@  ",m); */
            prog->wds[m]=(char *)calloc(MAXTOKENSIZE,sizeof(char));
            if (prog->wds[m]==NULL)
            {
                ON_ERROR("Prog_init error!!\n");
            }
            strcpy(prog->wds[m],word);
        }
        lastcflag=cflag;
        lasthcflag=hcflag;
        flag=0;
        hflag=0;
        if(cflag==2)cflag=0;
        if(hcflag==2)hcflag=0;
    }
    fclose(fp);
    /* printf("============INPUT END===============\n"); */
}
void PROG(Program *p)
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
        ERROR(" STRUCT '{' and '}' is not pairing or Maybe strings lost double−quote or hash.");
        FREE(p);
    }
    else
    {
        if (!strsame(p->wds[p->cw],"{"))
        {
            ERROR("No { statement?");
            FREE(p);
        }    
        p->cw = p->cw+1;
        INSTRS(p);
    }
}
void INSTRS(Program *p)
{
    if (strsame(p->wds[p->cw],"}"))
    {
        return;
    }
    INSTRUCT(p);
    p->cw = p->cw+1;
    INSTRS(p);
}
void INSTRUCT(Program *p)
{
    if (strsame(p->wds[p->cw],"PRINT")||strsame(p->wds[p->cw],"PRINTN"))
    {
        p->cw = p->cw+1;
        VARCON(p);
        return;
    }
    else if(strsame(p->wds[p->cw],"JUMP"))
    {
        p->cw = p->cw+1;
        NUMCON(p);
        return;
    }
    else if(strsame(p->wds[p->cw],"FILE"))
    {
        p->cw = p->cw+1;
        STRCON(p);
        return;
    }
    else if(strsame(p->wds[p->cw],"ABORT"))
    {
        return;
    }
    else if(strsame(p->wds[p->cw],"INC")||strsame(p->wds[p->cw],"RND")||strsame(p->wds[p->cw],"INNUM"))
    {
        p->cw = p->cw+1;
        INC_RND(p);
        return;
    }
    else if (p->wds[p->cw][0]=='%'||p->wds[p->cw][0]=='$')
    {
        SET(p);
        return;
    }
    else if(strsame(p->wds[p->cw],"IFEQUAL")||strsame(p->wds[p->cw],"IFGREATER"))
    {
        p->cw = p->cw+1;
        IF(p);
        p->cw = p->cw+1;
        if(!strsame(p->wds[p->cw],"{"))
        {
            ERROR(" 'IF' No { statement? ");
            FREE(p);
        }
        p->cw = p->cw+1;
        INSTRS(p);
        return;
    }
    else if(strsame(p->wds[p->cw],"IN2STR"))
    {
        p->cw = p->cw+1;
        IN2STR(p);
        return;
    }
    else
    {
        ERROR("Expecting correct INSTRUCT!!");
        FREE(p);
    }
    
    
}

void INC_RND(Program *p)
{
    if (strsame(p->wds[p->cw],"("))
    {
        p->cw = p->cw+1;
        if(p->wds[p->cw][0]=='%'){
            NUMVAR_STRVAR(p);
        }
        else
        {
            ERROR(" Incorrect INC or RND format !! ");
            FREE(p);
        }
        p->cw = p->cw+1;
        if (strsame(p->wds[p->cw],")"))
        {
            return;
        }
    }
    ERROR(" Incorrect INC or RND format !! ");
    FREE(p);
}
void SET(Program *p)
{
    NUMVAR_STRVAR(p);
    p->cw = p->cw+1;
    if(strsame(p->wds[p->cw],"="))
    {
        p->cw = p->cw+1;
        VARCON(p);
        return;
    }
    ERROR(" SET Error!! ");
    FREE(p);
}
void IF(Program *p)
{
    if (strsame(p->wds[p->cw],"("))
    {
        p->cw = p->cw+1;
        VARCON(p);
        p->cw = p->cw+1;
        if (strsame(p->wds[p->cw],","))
        {
            p->cw = p->cw+1;
            VARCON(p);
            p->cw = p->cw+1;
            if (strsame(p->wds[p->cw],")"))
            {
                return;
            }
        }
    }
    else
    {
        ERROR(" Incorrect IFEQUAL or IFGREATER format !! ");
        FREE(p);
    }
}
void IN2STR(Program *p)
{
    if (strsame(p->wds[p->cw],"("))
    {
        p->cw = p->cw+1;
        if (p->wds[p->cw][0]=='$')
        {
            NUMVAR_STRVAR(p);
        }
        else
        {
            ERROR(" Incorrect NUMVAR_STRVAR format in first input string!! ");
            FREE(p);
        }
        p->cw = p->cw+1;
        if (strsame(p->wds[p->cw],","))
        {
            p->cw = p->cw+1;
            if (p->wds[p->cw][0]=='$')
            {
                NUMVAR_STRVAR(p);
            }
            else
            {
                ERROR(" Incorrect NUMVAR_STRVAR format in second input string!! ");
                FREE(p);
            }
            p->cw = p->cw+1;
            if (strsame(p->wds[p->cw],")"))
            {
                return;
            }
        }
    }
    ERROR(" Incorrect NUMVAR_STRVAR format !! ");
    FREE(p);
}
void VARCON(Program *p)
{
    if (p->wds[p->cw][0]=='%'||p->wds[p->cw][0]=='$')
    {
        NUMVAR_STRVAR(p);
        return;
    }
    else
    {
        CON(p);
        return;
    }
    ERROR(" VARCON Error !! ");
    FREE(p);
}
void CON(Program *p)
{
    if (p->wds[p->cw][0]=='\"'||p->wds[p->cw][0]=='#'){
        STRCON(p);
        return;
    }
    else if(isdigit(p->wds[p->cw][0]))
    {
        NUMCON(p);
        return;
    }
    ERROR(" CON Error, nothing be setting !! ");
    FREE(p);
}
void STRCON(Program *p)
{
    int i,len;
    len = strlen(p->wds[p->cw]);
    if(p->wds[p->cw][len-1]=='\"')
    {
        for ( i = 1; i < len-1; i++)
        {
            if(p->wds[p->cw][i]=='\"'){
                ERROR(" Incorrect STRCON format !! There is \" in string.");
                FREE(p);
            }
        }
        return;
    }
    if(p->wds[p->cw][len-1]=='#')
    {
        for ( i = 1; i < len-1; i++)
        {
            if(p->wds[p->cw][i]=='\"'){
                ERROR(" Incorrect STRCON format !! There is # in string.");
                FREE(p);
            }
        }
        return;
    }
    ERROR(" Expecting text string in double−quotes or hashes!! ");
    FREE(p);
}
void NUMCON(Program *p)
{
    int len,i,dotnum=0;
    len = strlen(p->wds[p->cw]);
    for ( i = 0; i < len; i++)
    {
        if (p->wds[p->cw][i]=='.')
        {
            dotnum++;
        }
    }
    if (dotnum > 1)
    {
        ERROR(" Incorrect in NUMCON! There are more than 1 decimal points !");
        FREE(p);
    }
    else if((p->wds[p->cw][0]=='.')||(p->wds[p->cw][len-1]=='.'))
    {
        ERROR(" Incorrect in NUMCON! Decimal point stays in wrong position !");
        FREE(p);
    }
    else
    {
        for ( i = 0; i < len; i++)
        {
            if(isdigit(p->wds[p->cw][i])||p->wds[p->cw][i]=='.'){
            }
            else
            {
                ERROR(" Incorrect in NUMCON! Error Grammar!");
                FREE(p);
            }
        }
        return;
    }
}
void NUMVAR_STRVAR(Program *p)
{
    int len,i;
    len = strlen(p->wds[p->cw]);
    if (p->wds[p->cw][0]=='%'||p->wds[p->cw][0]=='$')
    {
        for ( i = 1; i < len; i++)
        {
            if(!isupper(p->wds[p->cw][i])){
                ERROR(" Incorrect in NUMVAR_STRVAR! Varible shoule use capital letters!");
                FREE(p);
            }
        }
        return;
    }
    ERROR(" Incorrect in NUMVAR_STRVAR! Varible seting format error!");
    FREE(p);
}

