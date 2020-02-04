#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
int anagramD(char s1[], char s2[]);
int anagram(char s1[], char s2[]);
void test();

int main (int argc,char **argv) {
    if( argc==3 ){
        test();
        printf("Your test word is '%s' and '%s'\n", argv[1],argv[2]);
        if(anagramD(argv[1],argv[2])==1){
            anagram(argv[1],argv[2]);
        }
    }else{
        printf("ERROR: Incorrect usage, try e.g. %s elvis lives", argv[0]);
    }
    return 0;
}
int anagramD(char s1[], char s2[]){
    int i;
    int n  = strlen(s1);
    int n1 = strlen(s2);
    if( n != n1) {    
        printf("%s and %s are not anagrams! \n", s1, s2);
        return 0;
    }else{
        for(i=0; i<n; i++){
            if(s1[i]==s2[i]){
                printf("Strings are not D-anagrams! \n");
                return 0;
            }
        }
    }
    return 1;

}
int anagram(char s1[], char s2[]){
    char temp;
    int i, j;
    int n  = strlen(s1);
    /* if( n != n1) {    
        printf("%s and %s are not anagrams! \n", s1, s2);
        return 0;
    }else{ */
        /* sort both strings first */
        for (i = 0; i < n-1; i++) {
            for (j = i+1; j < n; j++) {
                if (s1[i] > s1[j]) {
                    temp  = s1[i];
                    s1[i] = s1[j];
                    s1[j] = temp;
                }
                if (s2[i] > s2[j]) {
                    temp  = s2[i];
                    s2[i] = s2[j];
                    s2[j] = temp;
                }
            }
        }
        /* Compare both strings character by character */
        for(i = 0; i<n; i++) {
            if(s1[i] != s2[i]) {    
                printf("Strings are not anagrams! \n");
                return 0;
            }
        }
        printf("Strings are anagrams! \n");
        return 1;
    
}
void test(){
    assert(anagramD("elvis", "lives") == 0);
    assert(anagramD("dreads", "sadder") == 1);
    assert(anagramD("replays", "parsley") == 1);
    assert(anagramD("listen", "silent") == 0);
    assert(anagramD("orchestra", "carthorse") == 1);
}


