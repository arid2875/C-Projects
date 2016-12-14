/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>

#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{    
    int min = 0, max = n;
    while(min!=max){
        int diff = max-min; 
        if(value == values[diff/2])
            return true;        
        else if(value > values[diff/2])
            min = (diff)/2;                    
        else
            max = (diff)/2;        
    }
    return false;    
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    bool swapped = true;
    while(swapped){
        swapped = false;
        for(int i = 0, j = 1; i < n; j++, i++){            
            if(values[i] > values[j]){
                int tmp = values[i];
                values[i] = values[j];
                values[j] = tmp;
                swapped = true;
            }
        }
    }
    return;
}
