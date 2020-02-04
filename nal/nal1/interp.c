#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <math.h>
#include <assert.h>

#include "interp.h"

void printSTRUCT(Program *prog)
{
    int i,j;
    printf("-----------STRUCT PRINT STR------------\n");
    for ( i = 0; i <prog->num+1; i++)
    {
        printf("%d |%s|\n",i,prog->wds[i]);
    }
    printf("prog->cw:%d\n",prog->cw);
    printf("prog->num:%d\n",prog->num);
    printf("prog->arrnum:%d\n",prog->arrnum);
    /* printf("prog->con1:%s\n",prog->con[0]);
    printf("prog->con2:%s\n",prog->con[1]); */
    printf("prog->ifposition:%d\n",prog->ifposition);
    if (prog->arrnum>0)
    {
        printf("-----------VAL ARR STR------------\n");
        for ( j = 0; j <prog->arrnum; j++)
        {
            printf("%d |%s|",prog->arr[j].num,prog->arr[j].name);
            printf("|%s|\n",prog->arr[j].val);
        }
        printf("prog->arrnum:%d\n",prog->arrnum);
        printf("-----------VAL ARR END------------\n");
    }
    
    printf("-----------STRUCT PRINT END------------\n");
}
Program *init_P(void)
{
    Program *p;
    p = (Program*)calloc(1,sizeof(Program));
    if (p==NULL)
    {
        ERROR("Prog_init error!!\n");
    }
    p->wds = (char **)calloc(MAXNUMTOKENS,sizeof(char*));
    if (p->wds==NULL)
    {
        ERROR("Prog_init error!!\n");
    }
    p->cw = 0;
    p->num = 0;
    p->arrnum = 0;
    p->ifposition = 0;
    p->which = 0;
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
    *p=NULL;
}
void Progarr_free(ProgramArr prog){
    int i;
    for ( i = 0; i <= prog.num; i++)
    {
        prog_free(&prog.p[i]);
    }
}
void InputFile(char *str,Program *prog,ProgramArr progarr)
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
        FREE(progarr);
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
        if (cflag>0 && cflag<=2 && hcflag==0)
        {
            if (lastcflag==0)
            {
                m++;
                prog->num = m;
                /* printf("@1@@ m%d @@@  ",m); */
                prog->wds[m]=(char *)calloc(MAXTOKENSIZE,sizeof(char));
                if (prog->wds[m]==NULL)
                {
                    ERROR("Prog_init error!!\n");
                    FREE(progarr);
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
                    ERROR("Prog_init error!!\n");
                    FREE(progarr);
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
                ERROR("Prog_init error!!\n");
                FREE(progarr);
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
    /* printf("============INPUT END=================\n"); */
}

void PROG(Program *p,ProgramArr progarr)
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
        INSTRS(p,progarr);
    }
}
void INSTRS(Program *p,ProgramArr progarr)
{
    if (strsame(p->wds[p->cw],"}"))
        return;
    INSTRUCT(p,progarr);
    p->cw = p->cw+1;
    INSTRS(p,progarr);
}
void INSTRUCT(Program *p,ProgramArr progarr)
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
        READFILE(p,progarr);
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
        IFCOND(p,progarr);
        IF_CHECK(p,progarr);
        IFEQUAL(p,progarr);
        return;
    }
    else if(strsame(p->wds[p->cw],"IFGREATER"))
    {
        IFCOND(p,progarr);
        IF_CHECK(p,progarr);
        IFGREATER(p,progarr);
        return;
    }
    else
    {
        ERROR(" Expecting correct INSTRUCT!! ");
        FREE(progarr);
    }
    
    
}
void INC_RND(Program *p,ProgramArr progarr)
{
    if (strsame(p->wds[p->cw],"("))
    {
        p->cw = p->cw+1;
        if(p->wds[p->cw][0]=='%'){
            NUMVAR_STRVAR(p,progarr);
        }
        else
        {
            ERROR(" Incorrect INC or RND format !! ");
            FREE(progarr);
        }
        p->cw = p->cw+1;
        if (strsame(p->wds[p->cw],")"))
        {
            return;
        }
    }
    ERROR(" Incorrect INC or RND format !! ");
    FREE(progarr);
}
void SET(Program *p,ProgramArr progarr)
{
    NUMVAR_STRVAR(p,progarr);
    p->cw = p->cw+1;
    if(strsame(p->wds[p->cw],"="))
    {
        p->cw = p->cw+1;
        VARCON(p,progarr);
        return;
    }
    ERROR(" SET Error!! ");
    FREE(progarr);
}
void IF(Program *p,ProgramArr progarr)
{
    if (strsame(p->wds[p->cw],"("))
    {
        p->cw = p->cw+1;
        VARCON(p,progarr);
        p->cw = p->cw+1;
        if (strsame(p->wds[p->cw],","))
        {
            p->cw = p->cw+1;
            VARCON(p,progarr);
            p->cw = p->cw+1;
            if (strsame(p->wds[p->cw],")"))
            {
                return;
            }
        }
    }
    ERROR(" Incorrect IFEQUAL or IFGREATER format !! ");
    FREE(progarr);
}
void IN2STR(Program *p,ProgramArr progarr)
{
    if (strsame(p->wds[p->cw],"("))
    {
        p->cw = p->cw+1;
        if (p->wds[p->cw][0]=='$')
        {
            NUMVAR_STRVAR(p,progarr);
        }
        else
        {
            ERROR(" Incorrect NUMVAR_STRVAR format in first input string!! ");
            FREE(progarr);
        }
        p->cw = p->cw+1;
        if (strsame(p->wds[p->cw],","))
        {
            p->cw = p->cw+1;
            if (p->wds[p->cw][0]=='$')
            {
                NUMVAR_STRVAR(p,progarr);
            }
            else
            {
                ERROR(" Incorrect NUMVAR_STRVAR format in second input string!! ");
                FREE(progarr);
            }
            p->cw = p->cw+1;
            if (strsame(p->wds[p->cw],")"))
            {
                return;
            }
        }
    }
    ERROR(" Incorrect NUMVAR_STRVAR format !! ");
    FREE(progarr);
}
void VARCON(Program *p,ProgramArr progarr)
{
    if (p->wds[p->cw][0]=='%'||p->wds[p->cw][0]=='$')
    {
        NUMVAR_STRVAR(p,progarr);
        return;
    }
    else
    {
        CON(p,progarr);
        return;
    }
    ERROR(" VARCON Error !! ");
    FREE(progarr);
}
void CON(Program *p,ProgramArr progarr)
{
    if (p->wds[p->cw][0]=='\"'||p->wds[p->cw][0]=='#'){
        STRCON(p,progarr);
        return;
    }
    else if(isdigit(p->wds[p->cw][0]))
    {
        NUMCON(p,progarr);
        return;
    }
    ERROR(" CON Error, nothing be setting !! ");
    FREE(progarr);
}
void STRCON(Program *p,ProgramArr progarr)
{
    int i,len;
    len = strlen(p->wds[p->cw]);
    if(p->wds[p->cw][len-1]=='\"')
    {
        for ( i = 1; i < len-1; i++)
        {
            if(p->wds[p->cw][i]=='\"'){
                ERROR(" Incorrect STRCON format !! There is \" in string.");
                FREE(progarr);
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
                FREE(progarr);
            }
        }
        return;
    }
    ERROR(" Expecting text string in double−quotes or hashes!! ");
    FREE(progarr);
}
void NUMCON(Program *p,ProgramArr progarr)
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
        FREE(progarr);
    }
    else if((p->wds[p->cw][0]=='.')||(p->wds[p->cw][len-1]=='.'))
    {
        ERROR(" Incorrect in NUMCON! Decimal point stays in wrong position !");
        FREE(progarr);
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
                FREE(progarr);
            }
        }
        return;
    }
}
void NUMVAR_STRVAR(Program *p,ProgramArr progarr)
{
    int len,i;
    len = strlen(p->wds[p->cw]);
    if (p->wds[p->cw][0]=='%'||p->wds[p->cw][0]=='$')
    {
        for ( i = 1; i < len; i++)
        {
            if(!isupper(p->wds[p->cw][i])){
                ERROR(" Incorrect in NUMVAR_STRVAR! Varible shoule use capital letters!");
                FREE(progarr);
            }
        }
        return;
    }
    ERROR(" Incorrect in NUMVAR_STRVAR! Varible seting format error!");
    FREE(progarr);
}

int TEST_SAMEVALNAME(Program *p,char *str)
{
    int j;
    if (p->arrnum>0)
    {
        for ( j = 0; j <p->arrnum; j++)
        {
            if (strcmp(str,p->arr[j].name)==0)
            {
                return j;
            }
        }
    }
    return -1;
}
char *Getname(char *rawstr)
{
    char *name;
    int len;
    len = strlen(rawstr);
    name = (char*)calloc(STR,sizeof(char));
    if (name==NULL)
    {
        ERROR("RND error!!\n");
    }
    strncpy(name,rawstr+1,len-1);
    return name;
}
char *GetSTRCON(char *str)
{
    char *newstr;
    int len;
    len = strlen(str);
    newstr = (char*)calloc(STR,sizeof(char));
    if (newstr==NULL)
    {
        ERROR("RND error!!\n");
    }
    strncpy(newstr,str+1,len-2);
    return newstr;
}
char *ROT(char *str)
{
    char *newstr;
    int i,len;
    len = strlen(str);
    newstr = (char*)calloc(STR,sizeof(char));
    if (newstr==NULL)
    {
        ERROR("READFILE error!!\n");
    }
    for ( i = 0; i < len; i++)
    {
        if (islower(str[i]))
        {
            if (str[i]<'n')
            {
                newstr[i]=str[i]+ROTC;
            }
            else{
                newstr[i]=str[i]-ROTC;
            }
        }
        else if (isupper(str[i]))
        {
            if (str[i]<'N')
            {
                newstr[i]=str[i]+ROTC;
            }
            else{
                newstr[i]=str[i]-ROTC;
            }
        }
        else if (isdigit(str[i]))
        {
            if (str[i]<'5')
            {
                newstr[i]=str[i]+ROTD;
            }
            else{
                newstr[i]=str[i]-ROTD;
            }
        }
        else
        {
            newstr[i]=str[i];
        }
    }
    /* printf("ROT:%s\n",newstr); */
    return newstr;
}

void PRINT(Program *p,ProgramArr progarr)
{
    char *name;
    int t;
    if (p->wds[p->cw][0]=='%')
    {
        name = Getname(p->wds[p->cw]);
        t = TEST_SAMEVALNAME(p,name);
        free(name);
        if (t!=-1)
        {
            printf("%s",p->arr[t].val);
        }
        else
        {
            ERROR("PRINT:There is not set % varible.\n");
            FREE(progarr);
        }
    }
    else if (p->wds[p->cw][0]=='$')
    {
        name = Getname(p->wds[p->cw]);
        t = TEST_SAMEVALNAME(p,name);
        free(name);
        /* printf("%s",p->arr[t].val); */
        if (t!=-1)
        {
            printf("%s",p->arr[t].val);
        }
        else
        {
            ERROR("PRINT:There is not set $ varible.\n");
            FREE(progarr);
        }
    }
    else if (p->wds[p->cw][0]=='\"')
    {
        PRINT_Plain(p->wds[p->cw],progarr);
    }
    else if (p->wds[p->cw][0]=='#')
    {
        PRINT_ROT13(p->wds[p->cw],progarr);
    }
    else
    {
        printf("%s",p->wds[p->cw]);
    }
}
void PRINT_Plain(char *rawstr,ProgramArr progarr)
{
    char *str;
    int i,len;
    if(rawstr[0]!='\"')
    {
        len = strlen(rawstr);
        str = (char*)calloc(STR,sizeof(char));
        if (str==NULL)
        {
            ERROR("PRINT_Plain error!!\n");
            FREE(progarr);
        }
        strcpy(str,rawstr);
    }
    else
    {
        str = GetSTRCON(rawstr);
        len = strlen(str);
    }
    for ( i = 0; i < len; i++)
    {
        if (str[i]=='\\'&& str[i+1]=='n')
        {
            printf("\n");
            i=i+2;
        }
        printf("%c",str[i]);
    }
    free(str);    
}
void PRINT_ROT13(char *rawstr,ProgramArr progarr)
{
    char *str,*newstr;
    str = GetSTRCON(rawstr);
    newstr = ROT(str);
    PRINT_Plain(newstr,progarr);
    free(str);   
    free(newstr); 
}

void JUMP(Program *p)
{
    int jumpindex;
    jumpindex = atoi(p->wds[p->cw]);
    /* printf("jumpindex:%d\n",jumpindex); */
    p->cw = jumpindex-1;
}
void READFILE(Program *p,ProgramArr progarr)
{
    char *str;
    progarr.num++;
    str = GetSTRCON(p->wds[p->cw]);
    progarr.p[progarr.num]= init_P();
    InputFile(str,progarr.p[progarr.num],progarr);
    free(str);
    CopyVal(p,progarr.p[progarr.num]);
    /* printSTRUCT(newfile); */
    PROG(progarr.p[progarr.num],progarr);
    CopyVal(progarr.p[progarr.num],p);
    /* printf("FILE Parsed OK\n"); */
    prog_free(&progarr.p[progarr.num]);
    progarr.num--;
}
void CopyVal(Program *p,Program *target){
    int i;
    target->arrnum = p->arrnum;
    for ( i = 0; i < p->arrnum; i++)
    {
        strcpy(target->arr[i].name,p->arr[i].name);
        strcpy(target->arr[i].val,p->arr[i].val);
        target->arr[i].num = p->arr[i].num;
    }
    /* printf("newfile->arrnum:%d\n",target->arrnum); */
}
void RND(Program *p,ProgramArr progarr)
{
    int r;
    int len;
    char *name,*result;
    int t;
    r = rand()%100;
    /* printf("rand:%d\n",r); */
    p->cw = p->cw-1;
    len = strlen(p->wds[p->cw]);
    /* printf("%s %d\n",p->wds[p->cw],len); */
    name = Getname(p->wds[p->cw]);
    result = (char*)calloc(STR,sizeof(char));
    if (result==NULL)
    {
        ERROR("RND error!!\n");
        FREE(progarr);
    }
    /* printf("name:%s\n",name); */
    sprintf(result,"%d",r);
    /* printf("result:%s\n",result); */
    t = TEST_SAMEVALNAME(p,name);
    /* printf("t:%d\n",t); */
    if (t!=-1)
    {
        strcpy(p->arr[t].val,result);
    }
    else
    {
        strcpy(p->arr[p->arrnum].name,name);
        strcpy(p->arr[p->arrnum].val,result);
        p->arr[p->arrnum].num = p->arrnum;
        p->arrnum++;
    }
    free(name);
    free(result);
    p->cw = p->cw+1;
}
void INC(Program *p,ProgramArr progarr)
{
    int len,t;
    double r;
    char *name;
    p->cw = p->cw-1;
    len = strlen(p->wds[p->cw]);
    name = Getname(p->wds[p->cw]);
    /* printf("name:%s\n",name); */
    t = TEST_SAMEVALNAME(p,name);
    free(name);
    /* printf("t:%d\n",t); */
    if (t!=-1)
    {
        r = atof(p->arr[t].val)+1;
        /* printf("result:%.2f\n",r); */
        sprintf(p->arr[t].val,"%.2f",r);
    }
    else
    {
        ERROR("There is no setting varible to add!!");
        FREE(progarr);
    }
    p->cw = p->cw+1;
}
void SETNUM(Program *p,ProgramArr progarr)
{
    char *name,*valname;
    int t,valt;
    p->cw = p->cw-2;
    /* printf("%s\n",p->wds[p->cw]); */
    name = Getname(p->wds[p->cw]);
    /* printf("name:%s\n",name); */
    t = TEST_SAMEVALNAME(p,name);
    p->cw = p->cw+2;
    if (t!=-1)
    {
        if (p->wds[p->cw][0]=='%')
        {
            valname = Getname(p->wds[p->cw]);
            valt = TEST_SAMEVALNAME(p,valname);
            free(valname);
            if (valt!=-1)
            {
                strcpy(p->arr[t].val,p->arr[valt].val);
            }
            else
            {
                ERROR("Cannot assign values to variable!!\n");
                FREE_STR(name);
                FREE(progarr);
            }
        }
        else if (p->wds[p->cw][0]=='#'||p->wds[p->cw][0]=='\"')
        {
            ERROR("Cannot assign values to variable!!\n");
            FREE_STR(name);
            FREE(progarr);
        }
        else
        {
            strcpy(p->arr[t].val,p->wds[p->cw]);
        }
    }
    else
    {
        if (p->wds[p->cw][0]=='%')
        {
            valname = Getname(p->wds[p->cw]);
            valt = TEST_SAMEVALNAME(p,valname);
            free(valname);
            if (valt!=-1)
            {
                strcpy(p->arr[p->arrnum].val,p->arr[valt].val);
            }
            else
            {
                ERROR("Cannot assign non set variable to variable!!\n");
                FREE_STR(name);
                FREE(progarr);
            }
        }
        else if (p->wds[p->cw][0]=='#'||p->wds[p->cw][0]=='\"'||p->wds[p->cw][0]=='$')
        {
            ERROR("Cannot assign values to variable!!\n");
            FREE_STR(name);
            FREE(progarr);
        }
        else
        {
            strcpy(p->arr[p->arrnum].val,p->wds[p->cw]);
        }
        strcpy(p->arr[p->arrnum].name,name);
        p->arr[p->arrnum].num = p->arrnum;
        p->arrnum++;
    }
    FREE_STR(name);
}
void SETSTR(Program *p,ProgramArr progarr)
{
    char *newstr,*rotnewstr;
    char *name,*valname;
    int t,valt;
    p->cw = p->cw-2;
    name = Getname(p->wds[p->cw]);
    /* printf("name:%s\n",name); */
    t = TEST_SAMEVALNAME(p,name);
    p->cw = p->cw+2;
    if (t!=-1)
    {
        if (p->wds[p->cw][0]=='$')
        {
            valname = Getname(p->wds[p->cw]);
            valt = TEST_SAMEVALNAME(p,valname);
            free(valname);
            /* printf("valname:%s %d\n",valname,valt); */
            if (valt!=-1)
            {
                strcpy(p->arr[t].val,p->arr[valt].val);
            }
            else
            {
                ERROR("Cannot assign non set variable to variable!!\n");
                FREE_STR(name);
                FREE(progarr);
            }
            
        }
        else if (p->wds[p->cw][0]=='\"')
        {
            newstr = GetSTRCON(p->wds[p->cw]);
            strcpy(p->arr[t].val,newstr);
            free(newstr);
        }
        else if (p->wds[p->cw][0]=='#')
        {
            newstr = GetSTRCON(p->wds[p->cw]);
            rotnewstr = ROT(newstr);
            strcpy(p->arr[t].val,rotnewstr);
            free(newstr);
            free(rotnewstr);
        }
        else if (p->wds[p->cw][0]=='%'||isdigit(p->wds[p->cw][0]))
        {
            ERROR("Cannot assign values to variable!!\n");
            FREE_STR(name);
            FREE(progarr);
        }
    }
    else
    {
        if (p->wds[p->cw][0]=='$')
        {
            valname = Getname(p->wds[p->cw]);
            valt = TEST_SAMEVALNAME(p,valname);
            if (valt!=-1)
            {
                strcpy(p->arr[p->arrnum].val,p->arr[valt].val);
            }
            else
            {
                ERROR("Cannot assign non set variable to variable!!\n");
                FREE_STR(name);
                FREE(progarr);
            }
            free(valname);
        }
        else if (p->wds[p->cw][0]=='%'||isdigit(p->wds[p->cw][0]))
        {
            ERROR("Cannot assign values to variable!!\n");
            FREE_STR(name);
            FREE(progarr);
        }
        else if (p->wds[p->cw][0]=='\"')
        {
            newstr = GetSTRCON(p->wds[p->cw]);
            strcpy(p->arr[p->arrnum].val,newstr);
            free(newstr);
        }
        else if (p->wds[p->cw][0]=='#')
        {
            newstr = GetSTRCON(p->wds[p->cw]);
            rotnewstr = ROT(newstr);
            strcpy(p->arr[p->arrnum].val,rotnewstr);
            free(newstr);
            free(rotnewstr);
        }
        strcpy(p->arr[p->arrnum].name,name);
        p->arr[p->arrnum].num = p->arrnum;
        p->arrnum++;
    }
    FREE_STR(name);
}
void INNUM(Program *p)
{
    int t;
    double r;
    char *name;
    p->cw = p->cw-1;
    name = Getname(p->wds[p->cw]);
    printf("Please set a number for %s: ",name);
    scanf("%lf",&r);
    /* printf("%s %f\n",name,r); */
    t = TEST_SAMEVALNAME(p,name);
    if (t!=-1)
    {
        sprintf(p->arr[t].val,"%.2f",r);
    }
    else
    {
        strcpy(p->arr[p->arrnum].name,name);
        sprintf(p->arr[p->arrnum].val,"%.2f",r);
        p->arr[p->arrnum].num = p->arrnum;
        p->arrnum++;
    }
    free(name);
    p->cw = p->cw+1;
}
void IN2STR_IN(Program *p)
{
    p->cw = p->cw-3;
    IN2STR_IN_Single(p);
    p->cw = p->cw+2;
    IN2STR_IN_Single(p);
    p->cw = p->cw+1;
}
void IN2STR_IN_Single(Program *p)
{
    int t;
    int len;
    char *name;
    char str[STR];
    name = Getname(p->wds[p->cw]);
    /* printf("1STR:%s\n",name); */
    t = TEST_SAMEVALNAME(p,name);
    /* printf("Please set %s: ",name); */
    scanf("%s",str);
    len = strlen(str);
    /* printf("len:%d\n",len); */
    if (t!=-1)
    {
        strcpy(p->arr[t].val,str);
    }
    else
    {
        strcpy(p->arr[p->arrnum].name,name);
        strcpy(p->arr[p->arrnum].val,str);
        p->arr[p->arrnum].num = p->arrnum;
        p->arrnum++;
    }
    free(name);
}

void IF_RECORD(Program *p)
{
    p->cw = p->cw-3;
    strcpy(p->con[0],p->wds[p->cw]);
    p->cw = p->cw+2;
    strcpy(p->con[1],p->wds[p->cw]);
    p->cw = p->cw+1;
    p->ifposition = p->cw;
/*     printf("\ncheckcon1:%s\n",p->con[0]);
    printf("checkcon2:%s\n",p->con[1]); */
}
void IFCOND(Program *p,ProgramArr progarr)
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
    INSTRS(p,progarr);
}
void IF_CHECK(Program *p,ProgramArr progarr)
{
    if (p->con[CON1][0]=='$'||p->con[CON1][0]=='\"'||p->con[CON1][0]=='#')
    {
        if (p->con[CON2][0]=='$'||p->con[CON2][0]=='\"'||p->con[CON2][0]=='#')
        {
            IF_SET(p,progarr);
            p->which = 1;
        }
        else
        {
            ERROR("IF conditions cannot compare!!!!");
            FREE(progarr);
        }
    }
    else if (p->con[CON1][0]=='%'||isdigit(p->con[CON1][0]))
    {
        if (p->con[CON1][0]=='%'||isdigit(p->con[CON1][0]))
        {
            IF_SET(p,progarr);
            p->which = -1;
        }
        else
        {
            ERROR("IF conditions cannot compare!!!!");
            FREE(progarr);
        }
    }
    else
    {
        ERROR("IF conditions cannot compare!!!!");
        FREE(progarr);
    }
}
void IF_SET(Program *p,ProgramArr progarr)
{
    int i,t;
    char *name;
    char *newcon,*changecon;
    for ( i = 0; i < IFCON; i++)
    {
        if (p->con[i][0]=='\"')
        {
            newcon = GetSTRCON(p->con[i]);
            strcpy(p->strcon[i],newcon);
            free(newcon);
        }
        else if (p->con[i][0]=='#')
        {
            newcon = GetSTRCON(p->con[i]);
            changecon = ROT(newcon);
            /* printf("#changecon:%s\n",changecon); */
            strcpy(p->strcon[i],changecon);
            free(newcon);
            free(changecon);
        }
        else if (p->con[i][0]=='$')
        {
            name = Getname(p->con[i]);
            /* printf("%s\n",name); */
            t = TEST_SAMEVALNAME(p,name);
            free(name);
            /* printf("t:%d\n",t); */
            if (t!=-1)
            {
                strcpy(p->strcon[i],p->arr[t].val);
            }
            else
            {
                ERROR("There is no value in this condition !!\n");
                FREE(progarr);
            }
        }
        else if (p->con[i][0]=='%')
        {
            name = Getname(p->con[i]);
            t = TEST_SAMEVALNAME(p,name);
            free(name);
            if (t!=-1)
            {
                p->numcon[i] = atof(p->arr[t].val);
            }
            else
            {
                ERROR("There is no value in this condition !!\n");
                FREE(progarr);
            }
            
        }
        else if (isdigit(p->con[i][0]))
        {
            p->numcon[i] = atof(p->con[i]);
        }
        else
        {
            ERROR("The wrong condition format !!\n");
            FREE(progarr);
        }
        
    }
    /*     printf("-------------\n");
    printf("checknum1:%f\n",p->numcon[0]);
    printf("checknum2:%f\n",p->numcon[1]);
    printf("check1:%s\n",p->strcon[0]);
    printf("check2:%s\n",p->strcon[1]); 
    printf("-------------\n"); */
}
void IFGREATER(Program *p,ProgramArr progarr)
{
    int cleft=0,cright=0;
    p->cw = p->ifposition+1;
    /* printf("ifgra:%d %s\n",p->cw,p->wds[p->cw]); */
    if (p->which == 1)
    {
        if (strcmp(p->strcon[CON1],p->strcon[CON2])>0)
        {
            p->cw = p->cw+1;
            INSTRS(p,progarr);
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
            INSTRS(p,progarr);
        }
    }
    else if (p->which== -1)
    {
        if (p->numcon[CON1] > p->numcon[CON2])
        {
            p->cw = p->cw+1;
            INSTRS(p,progarr);
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
            INSTRS(p,progarr);
        }
    }
    p->which = 0;
}
void IFEQUAL(Program *p,ProgramArr progarr)
{
    int cleft=0,cright=0;
    p->cw = p->ifposition+1;
    /* printf("ifgra:%d %s\n",p->cw,p->wds[p->cw]);  */
    if (p->which == 1)
    {
        if (strcmp(p->strcon[CON1],p->strcon[CON2])==0)
        {
            p->cw = p->cw+1;
            INSTRS(p,progarr);
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
            INSTRS(p,progarr);
        }
    }
    else if (p->which== -1)
    {
        if (fabs(p->numcon[0]-p->numcon[1])<EPSILON)
        {
            p->cw = p->cw+1;
            INSTRS(p,progarr);
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
            INSTRS(p,progarr);
        }
    }
    p->which = 0;
}





