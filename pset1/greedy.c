#include <stdio.h>
#include <math.h>
#include <cs50.h>

int main(void)
{  
     _Bool again = true;
    float amountOwed = 0.0;
    int totalCoins;
    
    do
    {               
        while(amountOwed <= 0)
        {
            totalCoins = 0;
            printf("\n\nHow much change is owed? (e.g. 9.50) ");
            amountOwed = GetFloat()*100;
        }   
        while(amountOwed > 0)
        {  
            if(amountOwed>=25)
            {
                amountOwed -= 25;
                totalCoins++;
            }
            else if(amountOwed >=10)
            {
                amountOwed -= 10;
                totalCoins++;
            }
            else if(amountOwed >= 5)
            {
                amountOwed -= 5;
                totalCoins++;
            }
            else
            {
                amountOwed -= 1;
                totalCoins++;            
            }
        }        
        printf("\n\nThe total coins required is %i\n\n",totalCoins);
        printf("\n\nWould you like to do another? (Y/N) ");
        if(GetChar() == 'N')
            again = false;
    }
    while(again);     
}
