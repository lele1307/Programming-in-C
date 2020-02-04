#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "fmvm.h"

mvm* mvm_init(void)
{
    mvm *np;
    np = (mvm*)calloc(1,sizeof(mvm));
    if (np==NULL)
    {
        ON_ERROR("INIT_ERROR!");
    }
    np->size = 0;
    return np;
}
mvmcell* mvmcell_init(void)
{
    mvmcell *np;
    np = (mvmcell*)calloc(1,sizeof(mvmcell));
    if (np==NULL)
    {
        ON_ERROR("INIT_ERROR!");
    }
    np->datahead = NULL;
    return np;
}
void InsertNode(mvmcell*n,char *value){
    valuenode *P;
    int lenv;
    if (n==NULL)
    {
        ON_ERROR("InsertNode error!!\n");
    }
    lenv = strlen(value);
    P = (valuenode*)calloc(1,sizeof(valuenode)); 
    if (P==NULL)
    {
        ON_ERROR("INSERT_ERROR NULL! p\n");
    }
    /* printf("InsertNode:%d %s\n",lenv,value); */
    P->val = (char *)calloc(lenv+2,sizeof(char));
    if (P->val==NULL)
    {
        ON_ERROR("INSERT_ERROR NULL! p\n");
    } 
    strcpy(P->val,value);
    if (n->datahead==NULL)
    {
        n->datahead=P;
        P->next=NULL;
    }
    else
    {
        /* printf("--------\n"); */
        P->next=n->datahead;
        n->datahead=P;
    }
    n->next=NULL; 
}
void PrintNodeList(valuenode *l){
    printf("\nvalue:");
    do
    {
        printf(" %s",l->val);
        l = l->next;
    } while (l!=NULL);
}
void InsertHashNode(mvmcell *n,char *value,char *key)
{
    int lenk;
    lenk = strlen(key);
    if (n==NULL || key==NULL || value == NULL)
    {
        /* printf("INSERT_ERROR NULL! M\n"); */
        return;
    }
    n->key = (char *)calloc(lenk+2,sizeof(char));
    if (n->key==NULL)
    {
        ON_ERROR("INSERT_ERROR NULL! p\n");
    }
    strcpy(n->key,key);
    printf("InsertHash key:%s\n",n->key);
    InsertNode(n,value);
    n->next=NULL;
}
unsigned int hash(char *key)
{
    unsigned int h;
    if (key==NULL)
    {
        ON_ERROR("int hash error\n");
    }
    h = 0;
    for (; *key; key++)
    {
        h=*key+h*31;
    }
    return h;
}
void mvm_insert(mvm *m, char* key, char* data)
{
    /* printf("======INCERT========\n"); */
    mvmcell *new,*phead;
	unsigned int hashvalue;
    int pos;
    int lenk;
    if (m==NULL || key==NULL || data == NULL)
    {
        return;
    }
    if(m->size >= HASHSIZE)
    {
        printf("out of hash table memory!\n");
        return;
    }
    hashvalue = hash(key);
    pos = hashvalue%HASHSIZE;
    /* printf("position:%d\n",pos); */
    lenk = strlen(key);
    if (m->hashtable[pos]==NULL)
    {
        new=mvmcell_init();    
        assert(new!=NULL);
        new->key = (char *)calloc(lenk+2,sizeof(char));
        if (new->key==NULL)
        {
            ON_ERROR("INSERT_ERROR NULL! p\n");
        }
        strcpy(new->key,key);
        /* printf("InsertHash key:%s\n",new->key); */
        InsertNode(new,data);
        m->hashtable[pos]=new;
        new->next = NULL;
    }
    else
    {
        phead = m->hashtable[pos];
        while (phead!=NULL)
        {
            if(strcmp(phead->key,key) == 0)
            {
                /* printf("%s already exists!\n", key); */
                InsertNode(phead,data);
                return;
            }
            phead = phead->next;
        }
        new=mvmcell_init();    
        assert(new!=NULL);
        new->key = (char *)calloc(lenk+2,sizeof(char));
        if (new->key==NULL)
        {
            ON_ERROR("INSERT_ERROR NULL! p\n");
        }
        strcpy(new->key,key);
        /* printf("InsertHash key:%s\n",new->key); */
        InsertNode(new,data);
        new->next=m->hashtable[pos];
        m->hashtable[pos] = new;
    }
    m->size++;
    /* printf("======INCERT END========\n"); */
}
void mvm_print(mvm *m)
{
    int i;
    mvmcell *phead;
    if (m==NULL)
    {
        ON_ERROR("mvm_print_ERROR NULL!");
    }
    printf("===========content of hash table=================\n");
    for(i = 0; i < HASHSIZE; ++i)
        if(m->hashtable[i])
        {
            phead = m->hashtable[i];
            printf("%d=>", i);
            while(phead)
            {
                printf("%s ", phead->key);
                PrintNodeList(phead->datahead);
                phead = phead->next;
            }
            printf("\n");
        }
    printf("===========End of hash table=================\n");
}
char* mvm_search(mvm* m, char* key)
{
    unsigned int pos,hashvalue;
    mvmcell *phead;
    char *str;
    if (m == NULL || key==NULL)  
    {  
        ON_ERROR("SEARCH_ERROR NULL!\n");
    }
    hashvalue = hash(key);
    pos = hashvalue%HASHSIZE;
    /* printf("findposition:%d\n",pos); */
    phead = m->hashtable[pos];
    while(phead!=NULL)
    {
        if(strcmp(key, phead->key) == 0)
        {
            str = (char *)calloc(MAXLEN,sizeof(char));
            if (str==NULL)
            {
                ON_ERROR("str mvm_insert error!\n");
            }
            while (phead->datahead!=NULL)
            {
                /* valen=strlen(phead->datahead->val); */
                sprintf(str,"%s",phead->datahead->val);
                phead->datahead = phead->datahead->next;
            }
            /* printf("%s\n",str); */
            return str;
        }
        phead = phead->next;
    }
    return NULL;
}
char** mvm_multisearch(mvm* m, char* key,int *n)
{
    unsigned int pos,hashvalue;
    mvmcell *phead;
    valuenode *phead1,*phead2;
    char **argv;
    int i,valen,count;
    if (m == NULL || key == NULL || n == NULL)  
    {  
        ON_ERROR("mvm_multisearch_ERROR NULL!\n");
    } 
    hashvalue = hash(key);
    pos = hashvalue%HASHSIZE;
    /* printf("findposition:%d\n",pos); */
    i=0;
    count=0;
    phead = m->hashtable[pos];
    while(phead)
    {
        /* printf("%s\n",phead->key); */
        if(strcmp(key,phead->key) == 0)
        {
            phead1 = phead->datahead;
            phead2 = phead->datahead;
            while (phead2 !=NULL)  
            {  
                count++; 
                phead2= phead2->next;  
            }
            *n=count;
            /* printf("c:%d\n",count); */
            argv = (char**)calloc(count+1,sizeof(char*)); 
            if (argv == NULL)
            {
                ON_ERROR("mvm_multisearch_ERROR NULL! argv\n");
            }
            while (phead1!=NULL)
            {
                valen=strlen(phead1->val);
                /* printf("valen:%d\n",valen); */
                argv[i] = phead1->val;
                /* printf("%s\n",argv[i]); */
                phead1 = phead1->next;
                i++;
            } ;
            return argv;
        }
        phead = phead->next;
    }
    return NULL;
}
void mvmcell_free(mvmcell* p)
{
    valuenode *c,*tmp;
    c = p->datahead;
    while(c!=NULL)
    {
        tmp = c->next;
        free(c->val);
        free(c);
        c = tmp;
    }
    free(p->key);
    free(p);
    p = NULL;
}
void mvm_free(mvm **p)
{
    int i;
    mvm *phead;
    mvmcell *head,*tmp;
    phead = *p;
    for(i = 0; i < HASHSIZE; ++i)
    {
        if(phead->hashtable[i])
        {
            /* printf("------------------\n"); */
            head = phead->hashtable[i];
            while (head!=NULL)
            {
                tmp = head->next;
                mvmcell_free(head);
                head = tmp;
            }
        }
    }
    free(phead);
    *p=NULL;
}





