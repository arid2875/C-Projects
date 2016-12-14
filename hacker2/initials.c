#include <stdio.h>
#include <cs50.h>
#include <string.h>

int main(void){
    int isalpha(int c);
    int toupper(int c);    
    string s = GetString();
    for(int i = 0, j = strlen(s); i < j; i++){
        if(isalpha(s[i])){
            if(i == 0)
                printf("%c", (char)toupper(s[i]));
            else if((int)s[i-1] == 32)
                printf("%c", (char)toupper(s[i]));    
        }  
    }
    printf("\n");
    exit(0);
}
