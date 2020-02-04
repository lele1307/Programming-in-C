#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <string.h>

#define STRSIZE 5000
struct node{
    char c;
    struct node *left;
    struct node *right;
};
typedef struct node Node;

Node *MakeNode(char c);
void InsertRandom(Node *t,Node *n);
char *PrintTree(Node *t);
int treeDepth(Node *root);
int main(void)
{
    char c;
    int r=0;
    Node *head = MakeNode('A');
    Node *n;

    srand(time(NULL));
    for ( c ='B'; c < 'G'; c++)
    {
        n = MakeNode(c);
        InsertRandom(head,n);
    }
    printf("%s\n",PrintTree(head));
    r = treeDepth(head);
    printf("DEPTH:%d\n",r);
    return 0;
}
Node *MakeNode(char c)
{
    Node *n = (Node *)calloc(1,sizeof(Node));
    assert(n!=NULL);
    n->c = c;
    return n;
}
void InsertRandom(Node *t,Node *n)
{
    if (rand()%2==0)
    {
        if (t->left == NULL)
        {
            t->left=n;
        }
        else
        {
            InsertRandom(t->left,n);
        }
    }
    else
    {
        if (t->right == NULL)
        {
            t->right=n;
        }
        else
        {
            InsertRandom(t->right,n);
        }
    }
}
char *PrintTree(Node *t)
{
    char *str;
    assert((str=calloc(STRSIZE,sizeof(char)))!=NULL);
    if (t==NULL)
    {
        strcpy(str,"*");
        return str;
    }
    sprintf(str,"%c(%s)(%s)",t->c,PrintTree(t->left),PrintTree(t->right));
    return str;
}
int treeDepth(Node *root)
{   
    int left,right; 
    if (root==NULL)
    {
        return 0;
    }
    
    left = treeDepth(root->left);
    right = treeDepth(root->right);

    return left>right?left+1:right+1;
}
