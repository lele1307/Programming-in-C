#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "fmvm.h"
#define H 134298
#define W 150
#define N 3
void test();
void Inputfile(char **Key,char **Val);
void BuildMap(mvm *m1,mvm *m2,char **Key,char **Val,int n);
void FreeArr(char **Key,char **Val);
int FindPound(char *str);
char *FindKey(mvm *m1,char *find,int n);
void FindVal(char **Val,char **Key,char *find,mvm *m2);
void ShowResult(char **av,int num);
int main(int argc,char **argv)
{
    char *Key[H];
    char *Val[H];
    int i,j;
    int n;
    int flag;
    int num;
    mvm *m1;
    mvm *m2;
    /* mvmcell *head; */
    char *k;
    char **av;
    Inputfile(Key,Val);
    flag = 0;
    for (j = 0; j < argc; j++)
    {
        if (strcmp(argv[j],"-n")==0)
        {
            flag = 1;
        }
    }
    /* printf("flag:%d\n",flag); */
    m1 = mvm_init();
    m2 = mvm_init();
    if (flag==0 && argc>1) /*There is not '-n'.*/
    {
        n = 3;
        /*printf("n:%d\n",n); */
        BuildMap(m1,m2,Key,Val,n);
        for ( i = 1; i < argc; i++)
        {
            printf("INPUTWORD:%s ",argv[i]);
            k=FindKey(m1,argv[i],n);
            printf("(%s):\n",k);
            av = mvm_multisearch(m2,k,&num);
            ShowResult(av,num);
            free(k);
            free(av);
        }
    }
    else if(flag==1 && argc>N)
    {
        n = atoi(argv[2]);
        /*printf("n:%d\n",n); */
        BuildMap(m1,m2,Key,Val,n);
        for ( i = 3; i < argc; i++)
        {
            printf("INPUTWORD:%s ",argv[i]);
            k=FindKey(m1,argv[i],n);
            printf("(%s):\n",k);
            av = mvm_multisearch(m2,k,&num);
            ShowResult(av,num);
            free(k);
            free(av);
        }
    }
    else
    {
        printf("ERROR\n");
    } 
    mvm_free(&m1);
    mvm_free(&m2);
    FreeArr(Key,Val);
    return 0;
}
void Inputfile(char **Key,char **Val){
    int i; /*WhichLine*/
    int PoundLen;
    int Strlen;
    int NexLen;
    char fileg[W];
    FILE *fpRead;
    /* Read file name IN */
    if((fpRead=fopen("cmudict.txt","r"))==NULL){
        printf("Cannot open file, please check the file name!\n");
        exit(1);
    }
    /* Add to array */
    for (i=0; i<H; i++){
        fgets(fileg,W,fpRead);
        Strlen = strlen(fileg);
        /* printf("%d\n",Strlen); */
        PoundLen = FindPound(fileg);
        /* printf("%d\n",PoundLen); */
        NexLen = Strlen-PoundLen-2;
        /* printf("%d\n",NexLen); */
        Key[i]=(char*)calloc((PoundLen+N),sizeof(char));
        if (Key[i]==NULL)
        {
            ON_ERROR("KEYarr_ERROR!\n");
        }
        strncpy(Key[i],fileg,PoundLen);
        Val[i]=(char*)calloc((NexLen+N),sizeof(char));
        if (Val[i]==NULL)
        {
            ON_ERROR("Valarr_ERROR!\n");
        }
        strncpy(Val[i],fileg+PoundLen,NexLen);
/*         printf("%d |%s|%s|\n",i,Key[i],Val[i]);
        printf("---------------------\n");  */
    }
    fclose(fpRead);
}
void BuildMap(mvm *m1,mvm *m2,char **Key,char **Val,int n)
{
    int i,j,k=0;
    int valindex=0,len,vallen;
    char *str;
    for ( i = 0; i < H; i++)
    {
        mvm_insert(m1,Key[i],Val[i]);
        len = strlen(Val[i]);
       /*  printf("lenVal:%d %s\n",len,Val[i]); */
        for (j=len-1;j>=0 && k!=n ;j--)
        {
            /* printf("%c",Val[index][j]); */
            if(Val[i][j]==' '||Val[i][j]=='#'){
                k++;
                valindex = j;
            }
            /* printf("K:%d valindex:%d\n",k,valindex); */
        }
        if (k<n)
        {
            /* printf("kcmpstr:%s\n",Val[i]); */
            mvm_insert(m2,Val[i],Key[i]);
        }
        else
        {
            vallen = len-valindex-1;
            str = (char*)calloc(vallen+N,sizeof(char));
            if (str == NULL)
            {
                ON_ERROR("FindKey_error");
            }
            strncpy(str,Val[i]+valindex+1,vallen);
            mvm_insert(m2,str,Key[i]);
            /* printf("cmpstr:%s\n",str); */
            free(str);
        }
        k=0;
        /* printf("-------------------\n"); */
    }

}
void FreeArr(char **Key,char **Val){
    int i;
    for ( i = 0; i < H; i++)
    {
        free(Key[i]);
        free(Val[i]);
    }
}
int FindPound(char *str){
    int i;
    int indexPound;
    for ( i = 0; str[i]!=0; i++)
    {
        if (str[i]=='#')
        {
            indexPound = i;
        }
    }
    return indexPound;
}
char *FindKey(mvm *m1,char *find,int n)
{
    int j,k=0;
    int valindex=0,len,vallen;
    char *data,*str;
    data = mvm_search(m1,find);
    /* printf("%s\n",data); */
    len = strlen(data);
    for (j=len-1;j>=0 && k!=n ;j--)
    {
        /* printf("%c",Val[index][j]); */
        if(data[j]==' '||data[j]=='#'){
            k++;
            valindex = j;
        }
    }
    if (k<n)
    {
        printf("The number of phonemes_ERROR!\n");
        exit(0);
    }
    vallen = len-valindex-1;
    str = (char*)calloc(vallen+1,sizeof(char));
    if (str == NULL)
    {
        ON_ERROR("FindKey_error");
    }
/*  printf("len:%d\n",len);
    printf("valindex:%d\n",valindex);
    printf("vallen:%d\n",vallen);
    printf("|%s|\n",Val[index]); */
    strncpy(str,data+valindex+1,vallen);
    return str;
}
void ShowResult(char **av,int num)
{
    int i;
    for ( i = 0; i < num; i++)
    {
        printf("%s ",av[i]);
    }
    printf("\n");
}
void test()
{
    int i;
    char *str = "UNDERPRIVILEDGED#AH2 N D ER0 P R IH1 V L IH0 JH D";
    char *animals[5] = {"cat", "dog", "bird", "horse", "frog"};
    printf("----------test start----------\n");
    i = FindPound(str);
    assert(i==16);
    ShowResult(animals,5);
    /* mvm_insert(m1,"frog","croak");  */
    printf("----------test end----------\n");
}

