#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

#define N 100

int isogram(char *s);

int main(void){
    char str[100];
    scanf("%s",str);
    isogram(str);
/*     assert(isogram("programming") == 0);
    assert(isogram("housewarmings") == 0);
    assert(isogram("abductions") == 1);
    assert(isogram("housewarming") == 1);
    assert(isogram("hydromagnetics") == 1);
    assert(isogram("uncopyrightable") == 1);  */
    
return 0;
}

int isogram(char *s){
    int i,j,k;
    k = strlen(s);
    for (i=0; i < k-1; i++){
        for (j=i+1; i < k; j++){
            if(s[i]==s[j]){
                return 0;
                printf("0");
            }else
            {
                printf("1");
            }
            
        }
    }
    return 1;
    
}
