#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

struct node
{   
    char b[10];
    int index;
    int father;
    struct node *next;
};
typedef struct node Node;

void test();
Node *AllocateNode(char *str,int index,int father);
void PrintList(Node *l);
void PrintBoard(char *p);
void Swap(char *x,char *y);
int CreateNewState(char *p,char (*newstr)[10]);
int Compare(char *str,Node *l);
int SearchResult(Node *l,Node *start,Node *current,char *goal,char newstr[4][10]);
void PrintResult(Node *l,Node *start,int index);
void freeNode(Node *start);
int TestStr(char *str);

int main(int argc,char **argv)
{
    Node *start,*current;
    char goal[]={"12345678 "};
    char newstr[4][10];
    int c;
    if (argc==2)
    {
        test();
        printf("Your input number string is '%s'.\n", argv[1]);
        if(TestStr(argv[1])%2==0)
        {
            printf("--------------------START---------------------\n");
            /* Initial Board */
            start = current = AllocateNode(argv[1],0,0);
            /* Create a board and test it until the goal board be settled */
            c = SearchResult(start,start,current,goal,newstr);
            /* Print Path Board */
            PrintBoard(argv[1]);
            PrintResult(start,start,c);
            /* Free Memory */
            freeNode(start);
            printf("\n--------------------END---------------------\n"); 
        }else{
            printf("Your input number string '%s' can not build 8-Tiles-Game\n", argv[1]);
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
    Node *start,*current;
    char goal[]={"12345678 "};
    char newstr[4][10];
    start = current = AllocateNode("123 45678",0,0);

    current->next = AllocateNode("1234 5678",1,0);
    current = current->next;

    current->next = AllocateNode(goal,2,1);
    current = current->next; 

    /* PrintList(start); */  /* This function can print all board from linked list.*/
    assert(Compare("123 45678",start)==1);
    assert(Compare("12345678 ",start)==1);
    assert(Compare("1234567 8",start)==0);

    /* TEST: Whether CreateNewState function corresponds to 
    create new states and return the number of creations */
    assert(CreateNewState(" 12345678",newstr)==2);
    assert(CreateNewState("123 45678",newstr)==3);
    assert(CreateNewState("1234 5678",newstr)==4);

    assert(TestStr("7125 9836")%2!=0);/* TEST:odd or even */
    assert(TestStr("12345678 ")%2==0);
    /* printf("--------------TEST END-------------\n"); */
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
Node *AllocateNode(char *str,int index,int father)
{
    Node *p;
    p=(Node*)malloc(1*sizeof(Node));
    if (p==NULL)
    {
        printf("Can not Allocate node\n");
        exit(1);
    }
    strcpy(p->b,str);
    p->index = index;
    p->father = father;
    p->next = NULL;
    return p;
    fflush(stdin);
}
void PrintList(Node *l)
{
    printf("\n");
    do
    {
        printf("STR: %s\n",l->b);
        printf("Board_father: %d\n",l->father);
        printf("Board_index: %d\n",l->index);
        l = l->next;
    } while (l!=NULL);
    printf("----------PrintList END--------\n");
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
int Compare(char *str,Node *l)
{
    int r=0;
    while (l!=NULL){
        /* printf("l.b:%s\n",l->b); */
        if(strcmp(l->b,str)==0)
        {
            r = 1;
        }
        l=l->next;
    }
    return r;
}
int SearchResult(Node *l,Node *start,Node *current,char *goal,char newstr[4][10])
{
    int i,j;
    int m=0,n=0;
    do{
        j=CreateNewState(l->b,newstr);
        /* printf("j:%d\n",j); */
        for ( i = 0; i < j; i++)
        {
           /*  printf("newstr[i]:%s\n",newstr[i]); */
            if(Compare(newstr[i],start)==0)
            {
                n++;
                current->next = AllocateNode(newstr[i],n,m);
                current = current->next;
                if(strcmp(newstr[i],goal)==0)
                {
                    return n;
                }
            }
        }
        m++;
        l=l->next;
    }while(l!=NULL);
    return 0;    
}
void PrintResult(Node *l,Node *start,int index)
{
    int i,goal_index,j=0,k;
    char **str;
    int arrLen=0;
    goal_index = index;
    do{
        l=start;
        for ( i = 0; i < index+1; i++)
        {
            if(l->index == index){
                index = l->father;
            }
            l = l->next;
        }
        arrLen++;
    }while (index!=0);
    
    k=arrLen;
    str = (char**)malloc(arrLen*sizeof(char*));
    if(!str)
    {
        printf("error！\n");
        exit(1); 
    }
    do{
        l=start;
        for ( i = 0; i < goal_index+1; i++)
        {
            if(l->index == goal_index){
                str[j] = (char*)malloc(arrLen*sizeof(char));
                strcpy(str[j],l->b);
                goal_index = l->father;
            }
            l = l->next;
        }
        j++;
    }while (goal_index!=0);
    for ( i = k-1; i >= 0; i--)
    {
        PrintBoard(str[i]);
    }
    free(str);
}
void freeNode(Node *start)
{
    Node *find;
    while (start!=NULL)
    {
        find = start;
        start = start->next;
        free(find);
    }  
}
