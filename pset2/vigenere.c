#include <stdio.h>
#include <cs50.h>
#include <string.h>

string upper(string s);
string encoder(string keyword, string message);
int main(int argc, string argv[]){
	//function and variable  declarations
	void yell(void);
	int isalpha(int c);    
    int toupper(int c);
    string message;    
    
    if(argc !=2)
   		yell();
   	//if key contains non-alphabetical chars yell, otherwise make key uppercase  	
    string key = argv[1];
    int keylen = strlen(key);
    for(int i = 0; i < keylen; i++){
   		int c = (int)key[i];
   		if(!isalpha(c))
   		    yell();
	    else
	        key[i] = toupper(key[i]);	        
    }
    printf("\n%s\n", key);
    //get a message from the user       		  			
	printf("Please Enter Some Text: ");
	message = GetString();
	int meslen = strlen(message);	   
    
    for(int a = 0, keypos = 0; a < meslen; a++){
        char letter = message[a];
        int increment = (int)key[keypos % (keylen - 1)] - 65;
        //if char isnt a letter then leave it unchanged
        if(!isalpha(letter))
	        printf("%c", letter);	    
        //if char is a letter, increment it
        else{
            int new = ((int)letter + increment);            
            if((int)letter < 91){            
                if(new >90)
                    new -= 26;                                       
            }
            else{
                if((int)new > 122)
                    new -= 26;                
            }
            printf("%c", (char)new);
        }	
    }
    printf("\n");
}

void yell(void){
        printf("Your ONE command line arguement must be an all-alphabetic string!!!!\n");
        exit(1);        
    }


