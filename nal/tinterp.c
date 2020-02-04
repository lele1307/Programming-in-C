#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <math.h>
#include <assert.h>

#include "interp.h"

/* Test Function */
void testbasic(void);
void testInputFile(Program *prog);
char *creatstr(char *str);

void inte_test1(void);
bool STRCMP(char *target1,char *target2);
bool TESTPRINT(Program *p,int index);
bool TESTPRINT_Plain(char *rawstr);
bool TESTPRINT_ROT13(char *rawstr);
bool TESTSETNUM(Program *p,int index);
bool TESTSETSTR(Program *p,int index);
bool TESTRND(Program *p,int index);
bool TESTINC(Program *p,int index);
bool TESTINNUM(Program *p,int index,double num);
bool TESTIN2STR_IN(Program *p,int index);
bool TESTIN2STR_IN_Single(Program *p,int index,char *input);
int TESTJUMP(Program *p,int index);

void inte_test2(void);
void inte_test3(void);
void inte_test4(void);
int TESTIF_RECORD(Program *p,int index);
bool TESTIF_CHECK(Program *p);
bool TESTIF_SET(Program *p);
bool TESTIFGREATER(Program *p);
bool TESTIFEQUAL(Program *p);

int main(int argc,char **argv)
{
    if (argc==2)
    {
        ProgramArr prog;
        prog.num = 0;
        printf("============TEST STR=============\n");
        testbasic();
        inte_test1();
        inte_test2();
        inte_test4();
        /* inte_test3(); */
        printf("\n============TEST END=============\n");
        printf("============INTERP STR===========\n");
        prog.p[prog.num] = init_P();
        srand((unsigned)time(NULL));
        InputFile(argv[1],prog.p[prog.num],prog);
        PROG(prog.p[prog.num],prog);
        printf("============INTERP END===========\n");
        printf("Parsed OK\n");
        printf("=================================\n");
        /* printSTRUCT(prog); */
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
void testbasic(void)
{
    ProgramArr p;
    Program *prog;
    char *rawstr;
    char *name,*rot;
    char *strcon;
    int i,t;
    /* TEST initial Program */
    prog = init_P();
    assert(prog!=NULL);
    assert(prog->num==0);
    assert(prog->arrnum==0);
    assert(prog->ifposition==0);
    assert(prog->which==0);

    /* TEST_SAMEVALNAME */
    prog->arrnum = 2;
    strcpy(prog->arr[0].name,"A");
    strcpy(prog->arr[0].val,"Hello World666!");
    prog->arr[0].num = 0;
    strcpy(prog->arr[1].name,"ASDA");
    strcpy(prog->arr[1].val,"Hello");
    prog->arr[1].num = 1;
    t = TEST_SAMEVALNAME(prog,"ASDA");
    assert(t==1);
    t = TEST_SAMEVALNAME(prog,"A");
    assert(t==0);
    t = TEST_SAMEVALNAME(prog,"B");
    assert(t==-1);

    /* TEST InputFile Function */
    InputFile("inte_allright.nal",prog,p);
    /* printSTRUCT(prog); */
    testInputFile(prog);

    /* TEST creatstr and Getname Function */
    rawstr = creatstr("$A");
    i = strcmp(rawstr,"$A");
    assert(i==0);
    i = strcmp(rawstr,"$B");
    assert(i!=0);

    name = Getname(rawstr);
    i = strcmp(name,"A");
    assert(i==0);
    i = strcmp(name,"$B");
    assert(i!=0);
    free(name);
    free(rawstr);

    /* TEST GetSTRCON and ROT Function */
    rawstr = creatstr("#Uryyb Jbeyq111!#");
    strcon = GetSTRCON(rawstr);
    rot = ROT(strcon);
    i = strcmp(strcon,"Uryyb Jbeyq111!");
    assert(i==0);
    i = strcmp(strcon,"Uryyb Jbeyq111!!!");
    assert(i!=0);
    i = strcmp(rot,"Hello World666!");
    assert(i==0);
    i = strcmp(rot,"#Uryyb Jbeyq111!#");
    assert(i!=0);
    free(rot);
    free(strcon);
    free(rawstr);

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
char *creatstr(char *str)
{
    char *rawstr;
    rawstr = (char*)calloc(STR,sizeof(char));
    if (rawstr==NULL)
    {
        ERROR("Creatstr error!!\n");
    }
    strcpy(rawstr,str);
    return rawstr;
}

void inte_test1(void)
{
    ProgramArr p;
    Program *prog;
    prog = init_P();
    InputFile("inte_test1.nal",prog,p);
    /* TEST SETNUM Function */
    assert(TESTSETNUM(prog,12)==true);
    assert(TESTSETNUM(prog,15)==true);
    assert(TESTSETNUM(prog,18)==true);
    assert(TESTSETNUM(prog,21)==false);
    assert(TESTSETNUM(prog,24)==false);
    assert(TESTSETNUM(prog,27)==false);
    assert(TESTSETNUM(prog,30)==false); 
    /* TEST SETSTR Function */
    assert(TESTSETSTR(prog,3)==true); 
    assert(TESTSETSTR(prog,6)==true); 
    assert(TESTSETSTR(prog,9)==true); 
    assert(TESTSETSTR(prog,33)==false); 
    assert(TESTSETSTR(prog,36)==false); 
    assert(TESTSETSTR(prog,39)==false); 
    /* TEST PRINT Function */
    assert(TESTPRINT(prog,0)==false);
    assert(TESTPRINT(prog,41)==true);
    assert(TESTPRINT(prog,43)==true);
    assert(TESTPRINT(prog,45)==true);
    assert(TESTPRINT(prog,47)==true);
    assert(TESTPRINT(prog,49)==true);
    assert(TESTPRINT(prog,51)==true);
    assert(TESTPRINT(prog,53)==true);
    assert(TESTPRINT(prog,55)==true);
    assert(TESTPRINT(prog,57)==true);
    assert(TESTPRINT(prog,59)==false);
    assert(TESTPRINT(prog,61)==false);
    /* TEST RND Function */
    assert(TESTRND(prog,65)==true);
    assert(TESTRND(prog,69)==true);
    /* TEST INC Function */
    assert(TESTINC(prog,73)==true);
    assert(TESTINC(prog,77)==false);
    /* TEST INNUM Function */
    assert(TESTINNUM(prog,81,1.00)==true);
    assert(TESTINNUM(prog,85,85.00)==true);
    /* TEST TESTIN2STR_IN && TESTIN2STR_IN_Single Function */
    assert(TESTIN2STR_IN(prog,91)==true);
    assert(STRCMP(prog->arr[8].name,"STR1")==true);
    assert(STRCMP(prog->arr[9].name,"STR2")==true);
    /* TEST JUMP Function */
    assert(TESTJUMP(prog,93)==0);
    assert(TESTJUMP(prog,93)!=1);

    /* printSTRUCT(prog); */
    prog_free(&prog);
}
bool TESTPRINT(Program *p,int index)
{
    char *name;
    int t;
    p->cw = index;
    if (p->wds[p->cw][0]=='%')
    {
        name = Getname(p->wds[p->cw]);
        t = TEST_SAMEVALNAME(p,name);
        free(name);
        if (t!=-1)
        {
            return true;
        }
        else
        {
            return false;
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
            return true;
        }
        else
        {
            return false;
        }
    }
    else if (p->wds[p->cw][0]=='\"')
    {
        if(TESTPRINT_Plain(p->wds[p->cw])==true){
            return true;
        }
    }
    else if (p->wds[p->cw][0]=='#')
    {
        if(TESTPRINT_ROT13(p->wds[p->cw])==true){
            return true;
        }
    }
    else if (isdigit(p->wds[p->cw][0]))
    {
        return true;
    }
    return false;
}
bool TESTPRINT_Plain(char *rawstr)
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
            /* printf("\n"); */
            i=i+2;
        }
    }
    free(str); 
    return true;   
}
bool TESTPRINT_ROT13(char *rawstr)
{
    char *str,*newstr;
    str = GetSTRCON(rawstr);
    newstr = ROT(str);
    TESTPRINT_Plain(newstr);
    free(str);   
    free(newstr); 
    return true;
}
bool STRCMP(char *target1,char *target2)
{
    if(strsame(target1,target2)){
        return true;
    }
    else
    {
        return false;
    }
}
bool TESTSETNUM(Program *p,int index)
{
    char *name,*valname;
    int t,valt;
    p->cw = index;
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
                FREE_STR(name);
                return true;
            }
            else
            {
                /* ERROR("Cannot assign values to variable!!\n"); */
                FREE_STR(name);
                return false;
            }
        }
        else if (p->wds[p->cw][0]=='#'||p->wds[p->cw][0]=='\"'||p->wds[p->cw][0]=='$')
        {
            /* ERROR("Cannot assign values to variable!!\n"); */
            FREE_STR(name);
            return false;
        }
        else
        {
            strcpy(p->arr[t].val,p->wds[p->cw]);
            FREE_STR(name);
            return true;
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
                /* ERROR("Cannot assign non set variable to variable!!\n"); */
                FREE_STR(name);
                return false;
            }
        }
        else if (p->wds[p->cw][0]=='#'||p->wds[p->cw][0]=='\"'||p->wds[p->cw][0]=='$')
        {
            /* ERROR("Cannot assign values to variable!!\n"); */
            FREE_STR(name);
            return false;
        }
        else
        {
            strcpy(p->arr[p->arrnum].val,p->wds[p->cw]);
        }
        strcpy(p->arr[p->arrnum].name,name);
        p->arr[p->arrnum].num = p->arrnum;
        p->arrnum++;
        FREE_STR(name);
        return true;
    }
}
bool TESTSETSTR(Program *p,int index)
{
    char *newstr,*rotnewstr;
    char *name,*valname;
    int t,valt;
    p->cw = index;
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
                FREE_STR(name);
                return true;
            }
            else
            {
                /* ON_ERROR("Cannot assign non set variable to variable!!\n"); */
                FREE_STR(name);
                return false;
            }
            
        }
        else if (p->wds[p->cw][0]=='\"')
        {
            newstr = GetSTRCON(p->wds[p->cw]);
            strcpy(p->arr[t].val,newstr);
            free(newstr);
            FREE_STR(name);
            return true;
        }
        else if (p->wds[p->cw][0]=='#')
        {
            newstr = GetSTRCON(p->wds[p->cw]);
            rotnewstr = ROT(newstr);
            strcpy(p->arr[t].val,rotnewstr);
            free(newstr);
            free(rotnewstr);
            FREE_STR(name);
            return true;
        }
        else if (p->wds[p->cw][0]=='%'||isdigit(p->wds[p->cw][0]))
        {
            /* ON_ERROR("Cannot assign values to variable!!\n"); */
            FREE_STR(name);
            return false;
        }
    }
    else
    {
        if (p->wds[p->cw][0]=='$')
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
                /* ON_ERROR("Cannot assign non set variable to variable!!\n"); */
                FREE_STR(name);
                return false;
            }
        }
        else if (p->wds[p->cw][0]=='%'||isdigit(p->wds[p->cw][0]))
        {
            /* ON_ERROR("Cannot assign values to variable!!\n"); */
            FREE_STR(name);
            return false;
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
        FREE_STR(name);
        return true;
    }
    return false;
}
bool TESTRND(Program *p,int index){
    int r;
    int len;
    char *name,*result;
    int t;
    p->cw = index;
    r = rand()%100;
    /* printf("rand:%d\n",r); */
    p->cw = p->cw-1;
    len = strlen(p->wds[p->cw]);
    /* printf("%s %d\n",p->wds[p->cw],len); */
    name = Getname(p->wds[p->cw]);
    p->cw = p->cw+1;

    result = (char*)calloc(STR,sizeof(char));
    if (result==NULL)
    {
        ERROR("RND error!!\n");
        FREE_STR(name);
        return false;
    }
    /* printf("name:%s\n",name); */
    sprintf(result,"%d",r);
    /* printf("result:%s\n",result); */
    t = TEST_SAMEVALNAME(p,name);
    /* printf("t:%d\n",t); */
    if (t!=-1)
    {
        strcpy(p->arr[t].val,result);
        FREE_STR(name);
        FREE_STR(result);
        return true;
    }
    else
    {
        strcpy(p->arr[p->arrnum].name,name);
        strcpy(p->arr[p->arrnum].val,result);
        p->arr[p->arrnum].num = p->arrnum;
        p->arrnum++;
        FREE_STR(name);
        FREE_STR(result);
        return true;
    }
    return false;
}
bool TESTINC(Program *p,int index)
{
    int len,t;
    double r;
    char *name;
    p->cw = index;
    p->cw = p->cw-1;
    len = strlen(p->wds[p->cw]);
    name = Getname(p->wds[p->cw]);
    t = TEST_SAMEVALNAME(p,name);
    free(name);
    p->cw = p->cw+1;
    if (t!=-1)
    {
        r = atof(p->arr[t].val)+1;
        sprintf(p->arr[t].val,"%.2f",r);
        return true;
    }
    return false;
}
bool TESTINNUM(Program *p,int index,double num)
{
    int t;
    double r;
    char *name;
    p->cw = index;
    p->cw = p->cw-1;
    name = Getname(p->wds[p->cw]);
    /*  printf("Please set a number for %s: ",name);
    scanf("%lf",&r); */
    r = num;
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
    return true;
}
bool TESTIN2STR_IN(Program *p,int index)
{
    char str[STR] = "hello";
    p->cw = index;
    p->cw = p->cw-3;
    TESTIN2STR_IN_Single(p,p->cw,str);
    assert(TESTIN2STR_IN_Single(p,p->cw,str)==true);
    p->cw = p->cw+2;
    TESTIN2STR_IN_Single(p,p->cw,str);
    assert(TESTIN2STR_IN_Single(p,p->cw,str)==true);
    p->cw = p->cw+1;
    return true;
}
bool TESTIN2STR_IN_Single(Program *p,int index,char *input)
{
    int t;
    int len;
    char *name;
    char str[STR];
    p->cw = index;
    name = Getname(p->wds[p->cw]);
    /* printf("1STR:%s\n",name); */
    t = TEST_SAMEVALNAME(p,name);
    /* printf("Please input %s: ",name);
    scanf("%s",str); */
    strcpy(str,input);
    len = strlen(str);
    /* printf("len:%d\n",len); */
    if (t!=-1)
    {
        strcpy(p->arr[t].val,str);
        free(name);
        return true;
    }
    else
    {
        strcpy(p->arr[p->arrnum].name,name);
        strcpy(p->arr[p->arrnum].val,str);
        p->arr[p->arrnum].num = p->arrnum;
        p->arrnum++;
        free(name);
        return true;
    }
    free(name);
    return false;
}
int TESTJUMP(Program *p,int index)
{
    int jumpindex;
    p->cw = index;
    jumpindex = atoi(p->wds[p->cw]);
    /* printf("jumpindex:%d\n",jumpindex); */
    p->cw = jumpindex-1;
    return jumpindex;
}

void inte_test2(void)
{
    ProgramArr p;
    Program *prog;
    prog = init_P();
    InputFile("inte_test2.nal",prog,p);
    /* PROG(prog); */

    assert(TESTSETSTR(prog,3)==true); 
    assert(TESTSETNUM(prog,6)==true);

    assert(TESTIF_RECORD(prog,12)==12);
    assert(TESTIF_CHECK(prog)==true);
    assert(prog->which==1);
    assert(STRCMP(prog->strcon[0],prog->strcon[1])==true);
    assert(TESTIFEQUAL(prog)==true);
    

    assert(TESTIF_RECORD(prog,19)==19);
    assert(TESTIF_CHECK(prog)==true);
    assert(prog->which==-1);
    assert(prog->numcon[0]>prog->numcon[1]);
    assert(TESTIFGREATER(prog)==true);

    assert(TESTIF_RECORD(prog,37)==37);
    assert(TESTIF_CHECK(prog)==true);
    assert(prog->which==-1);
    assert(prog->numcon[0]<prog->numcon[1]);
    assert(TESTIFGREATER(prog)==false);

    assert(TESTIF_RECORD(prog,48)==48);
    assert(TESTIF_CHECK(prog)==true);
    assert(prog->which==1);
    assert(STRCMP(prog->strcon[0],prog->strcon[1])==false);
    assert(TESTIFEQUAL(prog)==false);

    /*     printSTRUCT(prog);
    printf("\ncheckcon1:%s\n",prog->con[0]);
    printf("checkcon2:%s\n",prog->con[1]); 
    printf("checknum1:%f\n",prog->numcon[0]);
    printf("checknum2:%f\n",prog->numcon[1]);
    printf("check1:%s\n",prog->strcon[0]);
    printf("check2:%s\n",prog->strcon[1]); 
    printf("which:%d\n",prog->which);  */
    prog_free(&prog);
}
void inte_test3(void)
{
    ProgramArr prog;
    int i;
    prog.num = 0;
    prog.p[prog.num] = init_P();
    InputFile("inte_test2.nal",prog.p[prog.num],prog);
    PROG(prog.p[prog.num],prog);
    /*     assert(STRCMP("C",prog->arr[2].name));
    assert(STRCMP("IN new file",prog->arr[2].val));
    assert(STRCMP("TEST",prog->arr[3].name));
    assert(STRCMP("0",prog->arr[3].val)); */
    for ( i = 0; i <= prog.num; i++)
    {
        printf("~~~~~~~~~~~~~~%d~~~~~~~~~~~~\n",i);
        printSTRUCT(prog.p[prog.num]);
    }
    Progarr_free(prog);
}
void inte_test4(void)
{
    ProgramArr p;
    Program *prog;
    prog = init_P();
    InputFile("inte_test4.nal",prog,p);
    
    assert(TESTSETSTR(prog,3)==true); 
    assert(TESTSETNUM(prog,6)==true);
    /*TEST IF_CHECK ERROR CONS*/
    assert(TESTIF_RECORD(prog,12)==12);
    assert(TESTIF_CHECK(prog)==false);
    assert(TESTIF_RECORD(prog,21)==21);
    assert(TESTIF_CHECK(prog)==false);
    assert(TESTIF_RECORD(prog,30)==30);
    assert(TESTIF_CHECK(prog)==false);
    assert(TESTIF_RECORD(prog,39)==39);
    assert(TESTIF_CHECK(prog)==false);
    assert(TESTIF_RECORD(prog,48)==48);
    assert(TESTIF_CHECK(prog)==false);
    assert(TESTIF_RECORD(prog,58)==58);
    assert(TESTIF_CHECK(prog)==false);

    /*     printSTRUCT(prog);
    printf("\ncheckcon1:%s\n",prog->con[0]);
    printf("checkcon2:%s\n",prog->con[1]); 
    printf("checknum1:%f\n",prog->numcon[0]);
    printf("checknum2:%f\n",prog->numcon[1]);
    printf("check1:%s\n",prog->strcon[0]);
    printf("check2:%s\n",prog->strcon[1]); 
    printf("which:%d\n",prog->which);  */
    prog_free(&prog);
}
int TESTIF_RECORD(Program *p,int index)
{
    p->cw = index;
    p->cw = p->cw-3;
    strcpy(p->con[0],p->wds[p->cw]);
    p->cw = p->cw+2;
    strcpy(p->con[1],p->wds[p->cw]);
    p->cw = p->cw+1;
    p->ifposition = p->cw;
    return p->ifposition;
}
bool TESTIF_CHECK(Program *p)
{
    if (p->con[CON1][0]=='$'||p->con[CON1][0]=='\"'||p->con[CON1][0]=='#')
    {
        if (p->con[CON2][0]=='$'||p->con[CON2][0]=='\"'||p->con[CON2][0]=='#')
        {
            p->which = 1;
            TESTIF_SET(p);
            return true;
        }
        else
        {
            /* ERROR("IF conditions cannot compare!!!!"); */
            return false;
        }
    }
    else if (p->con[CON1][0]=='%'||isdigit(p->con[CON1][0]))
    {
        if (p->con[CON1][0]=='%'||isdigit(p->con[CON1][0]))
        {
            p->which = -1;
            TESTIF_SET(p);
            return true;
        }
        else
        {
            /* ERROR("IF conditions cannot compare!!!!"); */
            return false;
        }
    }
    return false;
}
bool TESTIF_SET(Program *p)
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
                return false;
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
                return false;
            }
            
        }
        else if (isdigit(p->con[i][0]))
        {
            p->numcon[i] = atof(p->con[i]);
        }
    }
    return true;
}
bool TESTIFGREATER(Program *p)
{
    int cleft=0,cright=0;
    p->cw = p->ifposition+1;
    /* printf("ifgra:%d %s\n",p->cw,p->wds[p->cw]); */
    if (p->which == 1)
    {
        if (strcmp(p->strcon[CON1],p->strcon[CON2])>0)
        {
            p->cw = p->cw+1;
            /* INSTRS(p); */
            return true;
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
            /* INSTRS(p); */
            return false;
        }
    }
    else if (p->which== -1)
    {
        if (p->numcon[CON1] > p->numcon[CON2])
        {
            p->cw = p->cw+1;
            /* INSTRS(p); */
            return true;
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
            /* INSTRS(p); */
            return false;
        }
    }
    p->which = 0;
    return false;
}
bool TESTIFEQUAL(Program *p)
{
    int cleft=0,cright=0;
    p->cw = p->ifposition+1;
    /* printf("ifgra:%d %s\n",p->cw,p->wds[p->cw]);  */
    if (p->which == 1)
    {
        if (strcmp(p->strcon[CON1],p->strcon[CON2])==0)
        {
            p->cw = p->cw+1;
            /* INSTRS(p); */
            return true;
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
            /* INSTRS(p); */
            return false;
        }
    }
    else if (p->which== -1)
    {
        if (fabs(p->numcon[0]-p->numcon[1])<EPSILON)
        {
            p->cw = p->cw+1;
            /* INSTRS(p); */
            return true;
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
            /* INSTRS(p); */
            return false;
        }
    }
    p->which = 0;
    return false;
}


