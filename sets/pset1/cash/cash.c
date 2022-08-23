#include <stdio.h>
#include <math.h>
#include <cs50.h>

int main(){
    float change;
    int cents;
    int coins = 0;
    int type[] = {25, 10, 5, 1};
    int size = sizeof(type) / sizeof(int);

    //get positive change and convert it to whole numbers
    do{
        change = get_float("change: ");
        cents = round(change * 100);
    } while (change < 0);

   
   for (int i = 0; i < size; i++)
   {
       coins += cents / type[i];
       cents %= type[i];
   }
   
    printf ("Coins used: %i\n", coins);
}