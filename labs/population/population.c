#include <cs50.h>
#include <stdio.h>

int main(void)
{
   int population, years, end_size;
    // TODO: Prompt for start size
    do
    {
        population = get_int("Population start size: ");
    } while(population <= 9);
    
    int start = population; 
    
    // TODO: Prompt for end size
    do
    {
        end_size = get_int("Population end size: ");
    } while(end_size <= population);
    
    // TODO: Calculate number of years until we reach threshold
    
    for (years = 0; population < end_size; population = population + (population / 3) - (population /4)){
        years++;
    }

    // TODO: Print number of years
    printf("It takes %i years for the %i lamas to reach %i size\n", years, start, end_size);
    
    return 0;
}