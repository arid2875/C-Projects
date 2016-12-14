#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <unistd.h>
#define _XOPEN_SOURCE

//main program
int main(int argc, string argv[]){
	
	//local functions and variables
	string crypt(string salt, string key);
	char salt[3];
	char word[10];
	FILE *fp = fopen("/usr/share/dict/words", "r");
	
	//only allow one command line arguement
	if(argc !=2){
		printf("Need ONE command line arguement!!");
		exit(1);
	}	
	//get cypher from command line
	string cypher = argv[1];	
	//copy salt from cypher to salt array and set 3rd element to 0
	strncpy(salt,cypher,2);
	salt[2] = 0;
	
	//check for file	
	if(fp == NULL){
      perror("File Not Found");
      return(-1);
    }
    
    //keep going til you run out of words
    while(fgets(word,10,fp)!=NULL){
    	word[strlen(word)-1] = '\0';
    	//if were at the end, tell user and quit
    	if(feof(fp)){
      		printf("End of File");
      		exit(0);
    	}
    	//see if current word is the password    	    	   		    
    	else if(strcmp(crypt(word,salt),cypher)==0){
    		    printf("%s\n", word);
    		    exit(0);   		
    		}		    		
        }
        fclose(fp);

    
}    
       


