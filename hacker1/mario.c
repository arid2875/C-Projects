#include <stdio.h>
#include <cs50.h>

int main(void){
    int height = 0;
    bool isValidInt = false;
    do{
        printf("Height: (0-23)");
        height = GetInt();
        if(height >=0 && height <=23)
            isValidInt = true;
    }
    while(!isValidInt);
    for(int row = 0; row < height; row++){
            for(int x=row; x<height-1; x++)            
                printf(" ");            
            for(int x=0; x<=row; x++)            
                printf("#");           
            printf("  ");
            for(int x=0; x<=row; x++)            
                printf("#");           
            for(int x=row; x<height-1; x++)            
                printf(" ");           
            printf("\n");
        }
    
    
}

