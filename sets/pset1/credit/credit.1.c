#include <stdio.h>
#include <cs50.h>
#include <math.h>


int count_digits(long number);
long calc_check(long number);
long digits;
long checksum;



int main()
{
  
   long number;

    //get digits
    do
    {
        number = get_long("Number: ");
    }while(number < 0);
   
   
    //find count of digits
    digits = count_digits(number);
    
    //calculate checksum
    checksum = calc_check(number);
    
    //check checksum
    if(checksum % 10 != 0)
    {
        printf("INVALID\n");
        return 1;
    }
    
    int starting_number = number/pow(10,(digits-2));
    printf("%i", starting_number);


   
    return 0;
}


int count_digits(long number)
{
    digits = number;
    int count = 0;
    while(digits > 0)
     {
         digits = digits / 10;
         count++;
     }
     return count;
}



long calc_check(long number)
{
    //convert to array and multiply every other digit by two, then add those digits
    long sum = 0;
    long divisor;
    int j = 0;
    long a_number[digits];
    for(int i = 1; i < digits; i += 2)
    {
        divisor = pow(10, i);
        a_number[j] = (number/divisor) % 10;
        a_number[j] *= 2.0;
        
        if (a_number[j] > 9)
        {
            sum += a_number[j] / 10;
            sum += a_number[j] % 10;
        }
        else
        {
            sum += a_number[j];
        }
        j++;
    }
    
    //+ the remainig digits
    long sum_rest = 0;
    for(int i = 0; i < digits; i +=2)
    {
        divisor = pow(10, i);
        sum_rest += (number/divisor) % 10;
    }
    
    checksum = sum + sum_rest;
    return checksum;
}