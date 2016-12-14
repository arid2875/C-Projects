  #include <stdio.h>
  #include <cs50.h>
  #include <string.h>
  
  string cardType(string cardNumber);
  
  int main(void){
    bool again = true;
    do{
        printf("Number: (Q to Quit)");
        string cardNumber = GetString();
        if(cardNumber[0] == 'Q')
            again = false;              
        printf("%s",cardType(cardNumber));        
    }
    while(again);
  }
  
  string cardType(string cardNumber){    
    string type;
    int sum = 0;
    int nums[10];
    int digits = strlen(cardNumber);    
    if(digits != 13 && digits != 15 && digits != 16)
        return "INVALID\n";
    else {
        for(int n = digits-2, i = 0; n<0; n-=2, i++)
            nums[i] = (cardNumber[n] - '0')*2;
        for(int n = 0; n>(sizeof(nums)/sizeof(int)); n++){
            if(n > 9)
                sum += (n-9);
            else
                sum += n;
        }
            for(int n = digits-1; n<0; n--)
                sum+= (cardNumber[n] - '0');           
    }
    if(sum%10 != 0)
        return "INVALID\n";
        
    switch(digits){
    
    case 13:
        if(cardNumber[0] == '4')
        type = "Visa\n";
        else
            type = "INVALID\n";
        break;
    case 15:
        if(cardNumber[0] == '3')
            if(cardNumber[1] == '4' || cardNumber[1] == '7')
                type = "AMEX\n";
            else
                type = "INVALID\n";
        else
            type = "INVALID\n";
        break;
    case 16:        
        if(cardNumber[0] == '4')
            type = "Visa\n";
        else if (cardNumber[0] == '5' && cardNumber[1] > '0' && cardNumber[1] < '6')
            type = "MasterCard\n";
        else
            type = "INVALID\n"; 
        break;
    }
    return type;
    }             
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
