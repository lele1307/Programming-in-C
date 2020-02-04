#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "mvm.h"
#define MAXLEN 300
#define SPECIALC 5

mvm* mvm_init(void)
{
    mvm *new;
    new = (mvm *)calloc(1,sizeof(mvm));   
    if(new == NULL)
    {
        ON_ERROR("INIT_ERROR!");
    }
    new->head=NULL;
    new->numkeys = 0;
    return new;
}
int mvm_size(mvm* m)
{
    int size;
    if (m==NULL)
    {
        return 0;
    }
    size = m->numkeys;
    return size;
}
void mvm_insert(mvm* m, char* key, char* data)
{
    int keyl,datal;
    mvmcell *p;
    if (m==NULL || key==NULL || data == NULL)
    {
        /* printf("INSERT_ERROR NULL! M\n"); */
        return;
    }
    p = (mvmcell*)calloc(1,sizeof(mvmcell)); 
    if (p==NULL)
    {
        ON_ERROR("INSERT_ERROR NULL! p\n");
    }
    keyl = strlen(key);
    datal = strlen(data);
    p->key = (char *)calloc(keyl+2,sizeof(char)); 
    if (p->key==NULL)
    {
        ON_ERROR("INSERT_ERROR NULL! p\n");
    }
    p->data = (char *)calloc(datal+2,sizeof(char)); 
    if (p->data==NULL)
    {
        ON_ERROR("INSERT_ERROR NULL! p\n");
    }
    strcpy(p->data,data);
    strcpy(p->key,key);
    if (m->head==NULL)
    {
        /* printf("--------aaa------\n"); */
        m->head=p;
        p->next = NULL;
    }
    else
    {
        p->next=m->head;
        m->head=p;
    } 
    m->numkeys++;
/*     free(p->data);
    free(p->key);
    free(p); */
}
char* mvm_print(mvm* m)
{
    int lenAll,s1,s2;
    char *str,*ss;
    mvmcell *p;
    if (m==NULL)
    {
        ON_ERROR("mvm_print_ERROR NULL!");
    }
    p=m->head;

    str = (char *)calloc(MAXLEN,sizeof(char));
    do
    {
        s1=strlen(p->key);
        s2=strlen(p->data);
        lenAll = s1+s2+SPECIALC;
        ss = (char *)calloc(lenAll+2,sizeof(char));
        sprintf(ss,"[%s](%s) ",p->key,p->data);    
        strcat(str,ss);
        free(ss);
        p = p->next;
    }while (p!=NULL);
    /* printf("numkeys:%d\n",m->numkeys); */
    /* printf("%s\n",str); */
    return str;
    
}
void mvm_delete(mvm* m, char* key)
{
    mvmcell *pb,*pf;
    if (m==NULL || key==NULL || strcmp(key,"")==0)
    {
        /* printf("mvm_delete_ERROR NULL! M\n"); */
        return;
    }
    pb = m->head;
    if (m->head==NULL)
    {
        ON_ERROR("mvm_delete_ERROR NULL! 111\n");
    }
    while(strcmp(pb->key,key)!=0 && pb->next!=NULL)
    {
        pf=pb;
        pb=pb->next;
    }
    if(strcmp(pb->key,key)==0)
    {
        if(pb == m->head)
        {
            m->head = pb->next;
        }
        else
        {
            pf->next = pb->next;
        }
        free(pb->data);
        free(pb->key);
        free(pb);
        m->numkeys--;
    }
    else
    {
        printf("delNULL\n");
    }
}
char* mvm_search(mvm* m, char* key)
{
    mvmcell *p;
    p=m->head;
    if (m == NULL)  
    {  
        ON_ERROR("SEARCH_ERROR NULL!\n");
    }
    if (p == NULL)
    {
        ON_ERROR("SEARCH_ERROR NULL!\n");
    }
    while (p != NULL)  
    {  
        if (strcmp(p->key,key)==0)  
        {  
            return p->data;
        }  
        p = p->next;  
    }
    return NULL;  
}
char** mvm_multisearch(mvm* m, char* key, int *n)
{
    int i=0,count=0;
    char **argv=NULL;
    mvmcell *head1,*head2;
    head1 = m->head;
    head2 = m->head;
    if (m == NULL || key == NULL || n == NULL)  
    {  
        ON_ERROR("mvm_multisearch_ERROR NULL!\n");
    } 
    if (head1 == NULL)
    {
        ON_ERROR("mvm_multisearch_ERROR NULL! head\n");
    }
    while (head1 != NULL)  
    {  
        if (strcmp(head1->key,key)==0)  
        {  
            count++;
        }  
        head1= head1->next;  
    }
    *n = count;
    argv = (char**)calloc(count,sizeof(char*)); 
    if (argv == NULL)
    {
        ON_ERROR("mvm_multisearch_ERROR NULL! argv\n");
    }
    while (head2 != NULL)  
    {  
        if (strcmp(head2->key,key)==0)  
        {  
            argv[i] = head2->data;
            i++;
        }  
        head2= head2->next;  
    }
    return argv;
}
void mvm_free(mvm **p)
{
    mvm *a;
    mvmcell *c;
    mvmcell *tmp;
    a = *p;
    c = a->head;
    while(c!=NULL)
    {
        tmp = c->next;
        free(c->data); 
        free(c->key);
        free(c);
        c = tmp;
    }
    free(a);
    *p = NULL;
} 
