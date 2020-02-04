#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

struct board
{
    char b[10];
    int index;
    int father;
};
typedef struct board Board;
struct stackelem
{
    Board i;
    struct stackelem *prev;
};
typedef struct stackelem Elem;
struct thestack
{
    Elem *tp;
};
typedef struct thestack Stack;

void InitBoard(char *s,Board *boards);
void InitialiseStack(Stack *s);
void Push_Board(Stack *s, Board n);
Board Pop_Board(Stack *s);
int main(int argc,char **argv){
    Stack s;
    Board initial[1];
    Board *curr;
    char goal[]={"12345678 "};
    char newstr[4][10];
    if (argc==2)
    {
        printf("Your input number string is '%s'.\n", argv[1]);
        printf("--------------------START---------------------\n");
        InitBoard(argv[1],initial);
        InitialiseStack(&s);
        Push_Board(&s,initial[0]);
        curr=(Board*)malloc(sizeof(Board));
        if(!curr)
        {
            printf("error malloc！\n");
            exit(1); 
        }
        curr[0]=Pop_Board(&s);
        printf("%s\n",curr[0].b);
        printf("%d\n",curr[0].index);
        printf("%d\n",curr[0].father); 
        
        printf("\n--------------------END---------------------\n"); 
    }
    else
    {
        printf("ERROR: Incorrect usage, try e.g. %s '513276 48'\n", argv[0]);
    }
    return 0;
}
void InitBoard(char *s,Board *boards)
{
    strcpy(boards[0].b,s);
    boards[0].index = 0;
    boards[0].father = 0;
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
        /* PrintBoard(cType[0]); */
        j++;
        /* printf("-------LEFT--------\n"); */
    }
    if(col!=2)/*RIGHT*/
    {
        strcpy(cType[1],p);
        Swap(&(cType[1][index]),&(cType[1][index+1]));
        strcpy(newstr[j],cType[1]);
        /* PrintBoard(cType[1]); */
        j++;
        /* printf("-------RIGHT--------\n"); */
    }
    if(row!=0)/*UP*/
    {
        strcpy(cType[2],p);
        Swap(&(cType[2][index]),&(cType[2][index-3]));
        strcpy(newstr[j],cType[2]);
        /* PrintBoard(cType[2]); */
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
int Compare_add	(char *str,Board *boards,int index,int father)
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
            /* printf("%s\n",newstr[i]); */
            if(Compare_add(newstr[i],boards,n,m)==0)
            {
                n++;
                if(strcmp(newstr[i],goal)==0)
                {
                    /* PrintBoard(boards[n].b); */
                    return 1;
                }
            }
        }
        m++;
    }
    return 0;    
}
void InitialiseStack(Stack *s)
{
    s->tp = (Elem *)calloc(1, sizeof(Elem));
    s->tp->prev = NULL;
}
void Push_Board(Stack *s, Board n)
{
    Elem *e;
    e = (Elem *)calloc(1, sizeof(Elem));
    e->prev = s->tp;
    s->tp->i = n;
    s->tp = e;
}
Board Pop_Board(Stack *s)
{
    s->tp = s->tp->prev;
    assert(s->tp!=NULL);
    return s->tp->i;
}
