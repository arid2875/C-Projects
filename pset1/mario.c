#include <stdio.h>
#include <cs50.h>


int height;    
char again = 'Y';

int main (void)
{    
    
    do
    {
        _Bool isValidInt = false;
        while(!isValidInt)
        {    
            printf("How tall should the tower be? (0-23) ");
            height = GetInt();
            if(height >= 0 && height <= 23)
                isValidInt = true;
        }
        for(int row = 0; row < height; row++)
        {
            for(int x=row; x<height-1; x++)
            {
                printf(" ");             
            }
            for(int x=0; x<row+2; x++)
            {
                printf("#");
            }
            printf("\n");
        }
        printf("Again? (press n to quit)"); 
        again = GetChar();       
    }
    while(again != 'n');
}

