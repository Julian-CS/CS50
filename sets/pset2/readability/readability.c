#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <math.h>


int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main()
{
    double index, L, S;

    //Getting user input
    string text = get_string("Text: ");

    //counting letters, words and sentences
    int letters = count_letters(text);
    int words = count_words(text);
    int sentences = count_sentences(text);

    //Calculating index
    L = ((double) letters / words) * 100.0;
    S = ((double) sentences / words) * 100.0;
    index = 0.0588 * L - 0.296 * S - 15.8;



    if (index > 16)
    {
        printf("Grade 16+\n");
    }
    else if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", (int) round(index));
    }

    return 0;

}

int count_sentences(string text)
{
    int length = strlen(text);
    int periods = 0;

    for (int i = 0; i < length; i++)
    {
        if(text[i] =='.' || text[i] == '!' || text[i] == '?')
        {
            periods++;
        }
    }
    //periods are the same as sentences
    return periods;
}


int count_words(string text)
{
    int length = strlen(text);
    int spaces = 0;
    int words;

   for (int i = 0; i < length; i++)
    {
        if(isspace(text[i]))
        {
                spaces++;
        }
    }
    words = spaces + 1;
    return words;
}



//Function to count letters
int count_letters(string text)
{
    int length = strlen(text);
    int special = 0;
    int letters;

   for (int i = 0; i < length; i++)
    {
            if(!isalpha(text[i]))
            {
                special++;
            }
    }
    letters = length - special;
    return letters;
}