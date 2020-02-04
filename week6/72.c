#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define NUMARRAY 3628800
struct board
{
    char b[10];
    int index;
    int father;
};
typedef struct board Board;

void test();
int TestStr(char *str);
void InitBoard(char *s,Board boards[NUMARRAY]);
void PrintBoard(char *p);
void Swap(char *x,char *y);
int CreateNewState(char *p,char (*newstr)[10]);
int Compare_add	(char *str,Board *boards,int index,int father);
int SearchResult(Board *boards,char *goal,char newstr[4][10]);
void PrintResult(Board *boards);

int main(int argc,char **argv)
{
    static Board boards[NUMARRAY];
    char goal[]={"12345678 "};
    char newstr[4][10];
    test();
    if (argc==2)
    {
        printf("Your input number string is '%s'.\n", argv[1]);
        if(TestStr(argv[1])%2==0) /*Test build the game board*/
        {
            printf("--------------------START---------------------\n");
            /* Initial Board */
            InitBoard(argv[1],boards);
            /* Create a board and test it until the goal board be settled */
            SearchResult(boards,goal,newstr);
            /* Print Path Board */
            PrintResult(boards);
            printf("\n--------------------END---------------------\n"); 
        }
        else
        {
            printf("Your input number string '%s' can not build 8-Tiles-Game. \n", argv[1]);
        }
    }
    else
    {
        printf("ERROR: Incorrect usage, try e.g. %s '513276 48'\n", argv[0]);
    }
    return 0;
}
void test()
{
    static Board boards[NUMARRAY];
    char newstr[4][10];
    /* int c; */
    InitBoard("123 45786",boards);
    /* assert(strcmp(boards[0].b,"123 45786")==0); */
    assert(boards[0].father==0);
    assert(boards[0].index==0);
    assert(boards[6587].index==0);
    /* TEST: Whether CreateNewState function corresponds to 
    create new states and return the number of creations */
    assert(CreateNewState(" 12345678",newstr)==2);
    assert(CreateNewState("123 45678",newstr)==3);
    assert(CreateNewState("1234 5678",newstr)==4);

    assert(Compare_add(" 23145786",boards,0,0)==0);/* TEST: Different add */
    assert(Compare_add(" 23145786",boards,2,0)==1);/* TEST: Same no add */

    assert(SearchResult(boards," 23145786",newstr)==1); /* TEST: Find same goal */

    assert(TestStr("7125 9836")%2!=0);/* TEST:odd or even */
    assert(TestStr("12345678 ")%2==0);
    
    /* Print Assume Value */
/*     for (c = 0; c < 3; c++)
    {
        printf("CHAR:%s\n",boards[c].b);
        printf("INDEX:%d\n",boards[c].index);
        printf("Father:%d\n",boards[c].father);
    }  
    printf("----------TEST END------------\n"); */
}
int TestStr(char *str)
{
    int i,j,k=1;
    int m=0;
    int len;
    len=strlen(str);
    for ( i = 0; i < len; i++)
    {
        if (str[i]!=' '){
            for ( j = k; j < len; j++)
            {
                if (str[j]!=' '){
                    /* printf("str[i]:%c,str[j]:%c\n",str[i],str[j]); */
                    if(str[i]-str[j]>0){
                        m++;
                    }
                }
            }
            k++;
        }
    }
    /* printf("m:%d\n",m); */
    return m;
}
void InitBoard(char *s,Board *boards)
{
    int i;
    strcpy(boards[0].b,s);
    for ( i = 0; i < NUMARRAY; i++)
    {
        boards[i].index = 0;
    }
    boards[0].index = 0;
    boards[0].father = 0;
}
void PrintBoard(char *p)
{
    int i;
    for ( i = 0; i < 9; i++)
    {
        if (i%3==0)
            printf("\n+-------------+\n");
        printf("|%2c |",p[i]);
    }
    printf("\n+-------------+\n");
}
void Swap(char *x,char *y)
{
    char tmp;
    tmp = *x;
    *x = *y;
    *y = tmp;
}
int CreateNewState(char *p,char (*newstr)[10])
{
    int i,j=0;
    int index;/* ' ' index in board */
    int col,row;
    char cType[4][10]; 
    for ( i = 0; i < 9; i++)
    {
        if(p[i]==' ')
        index = i;
    }
    col = index%3;
    row = index/3;
    /* Find ' ' location and change it */
    if (col!=0) /*LEFT*/
    {
        strcpy(cType[0],p);
        Swap(&(cType[0][index]),&(cType[0][index-1]));
        strcpy(newstr[j],cType[0]);
        j++;
        /* printf("-------LEFT--------\n"); */
    }
    if(col!=2)/*RIGHT*/
    {
        strcpy(cType[1],p);
        Swap(&(cType[1][index]),&(cType[1][index+1]));
        strcpy(newstr[j],cType[1]);
        j++;
        /* printf("-------RIGHT--------\n"); */
    }
    if(row!=0)/*UP*/
    {
        strcpy(cType[2],p);
        Swap(&(cType[2][index]),&(cType[2][index-3]));
        strcpy(newstr[j],cType[2]);
        j++;
        /* printf("-------UP-----------\n"); */
    }
    if(row!=2)/*DOWN*/
    {
        strcpy(cType[3],p);
        Swap(&(cType[3][index]),&(cType[3][index+3]));
        strcpy(newstr[j],cType[3]);
        /* PrintBoard(cType[3]); */
        j++;
        /* printf("-------DOWN----------\n"); */
    }
    return j;
}
int Compare_add(char *str,Board *boards,int index,int father)
{
    int i,r=0;
    for ( i = 0; i < index; i++)
    {
        if(strcmp(boards[i].b,str)==0)
        {
            r = 1;
        }
    }
    if (r==0)
    {
        strcpy(boards[index+1].b,str);
        boards[index+1].index = index+1;
        boards[index+1].father = father;
    }
    return r;
}
int SearchResult(Board *boards,char *goal,char newstr[4][10])
{
    int i,j;
    int m=0,n=0;
    while (strcmp(boards[m].b,goal)!=0)
    { 
        j=CreateNewState(boards[m].b,newstr);
        for ( i = 0; i < j; i++)
        {
            if(Compare_add(newstr[i],boards,n,m)==0)
            {
                n++;
                if(strcmp(newstr[i],goal)==0)
                {
                    return 1;
                }
            }
        }
        m++;
    }
    return 0;    
}
void PrintResult(Board *boards)
{
    int i=1,k=1,count=1;
    int goal_index;
    int *array;
    int arrLen=1;
    
    while(boards[i+1].index!=0)
    { 
        count++;
        i++;
    }
    goal_index=count;
    while (count!=0)
    {
        count=boards[count].father;
        arrLen++;
    }
    count = goal_index;
    /* Create int array store father value */
    array = (int*)malloc(arrLen*sizeof(int));
    if(!array)
    {
        printf("error！\n");
        exit(1); 
    }
    array[0]=goal_index;
    while (count!=0)
    {
        count=boards[count].father;
        array[k]=count;
        k++;
    } 
    for(i=arrLen-1; i>=0; i--)
    {
        PrintBoard(boards[array[i]].b);
    }
    free(array);
}
