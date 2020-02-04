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
enum bool {false,true};
typedef enum bool Bool;

Node *MakeNode(char c);
void InsertRandom(Node *t,Node *n);
char *PrintTree(Node *t);
int treeDepth(Node *root);
Bool CompareTree(Node *root1,Node *root2);

int main(void)
{
    char c;
    int r1=0,r2=0;
    Node *head1 = MakeNode('A');
    Node *head2 = MakeNode('A');
    Node *n1;
    Node *n2;

    srand(time(NULL));
    for ( c ='B'; c < 'G'; c++)
    {
        n1 = MakeNode(c);
        InsertRandom(head1,n1);
    }
    printf("%s\n",PrintTree(head1));
    r1 = treeDepth(head1);
    printf("DEPTH1:%d\n",r1);

    for ( c ='B'; c < 'G'; c++)
    {
        n2 = MakeNode(c);
        InsertRandom(head2,n2);
    }
    printf("%s\n",PrintTree(head2));
    r2 = treeDepth(head1);
    printf("DEPTH2:%d\n",r2);

    if(CompareTree(head1,head2)==true){
        printf("Both trees are identical.\n");
    }
    else
    {
        printf("Both trees are not identical.\n");
    }
    

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
Bool CompareTree(Node *root1,Node *root2)
{
    if (root1==NULL && root2==NULL)
    {
        return false;
    }
    if (root1!=NULL && root2!=NULL)
    {
        return( root1->c == root2->c && 
                CompareTree(root1->left,root2->left) && 
                CompareTree(root1->right,root2->right) );
    }
    return true;
}
