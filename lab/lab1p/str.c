#include <stdio.h>

#define MAXLINE 100

void read_in(char s[]);
char *change(char *s);
int main(){
    char line[MAXLINE];

    printf("\nwhat is your favorite line?");
    read_in(line);
    printf("\n%s\n\n%s\n\n","Here is after being changed:",change(line));
    return 0;

}

void read_in(char s[]){
    int c,i=0;

    while ((c=getchar())!=EOF && c!='\n'){
        s[i++] = c;
    }
    s[i]='\0';
}

char *change(char *s){
    static char new_string[MAXLINE];
    char *p = new_string;

    *p++ ='\t';
    for (; *s!='\0'; ++s){
        if (*s=='e'){
            *p++ = 'E';
        }else if (*s==' '){
            *p++ = '\n';
            *p++ = '\t';
        }else{
            *p++ = *s;
        }
    }
    *p = '\0';
    return new_string;
}