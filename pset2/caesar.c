#include <stdio.h>
#include <cs50.h>
#include <string.h>

int main(int argc, string argv[]){
    string s;
    int cypher = -1;
    void yell(void);
    char encoder(int letter, int cypher);
    if(argv[1] == NULL || argv[0] < 0 || argc > 2)
        yell();        
    cypher = atoi(argv[1]); 
    if(cypher <= 0)
        yell();   
    else{   
        //printf("Cypher is %i, please enter some text.\n", cypher);   
        s = GetString();
        //printf("\nYour encrypted text is:\n");
        
        for(int i = 0, j = strlen(s); i < j; i++){
            int letter = (int)s[i];
            //printf("%i", letter);
            if(letter < 65 || letter > 122){
                printf("%c", s[i]);
            }
            else if(letter > 90 && letter < 97){
                printf("%c", s[i]);
            }
            else
                printf("%c", encoder(letter,cypher));
        }        
        //printf("\n\n");       
        return 0;
    }
}
    
    
 
    
    char encoder(int letter, int cypher){
        int increment = cypher%26;        
        int new = letter + increment;
        if(letter < 91){            
            if(new >90){
                new -= 26;
            }
            return (char)new;        
        }
        else{
            if(new > 122){
                new -= 26;
            }
            return (char)new;        
        }        
    }
    void yell(void){
        printf("Your ONE command line arguement must be a positive non-zero integer!!!\n");
        exit(1);        
    }
