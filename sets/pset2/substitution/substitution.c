#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

string convert_string(string argv[]);

int main(int argc, string argv[])
{

    //check if user submitted correct arguments
    if (argc != 2)
    {
        printf("Usage: %s key\n", argv[0]);
        return 1;
    }



    //Validate key and Convert string key
    string key = convert_string(argv);


    //convert plaintext to cyphertext
    string plaintext = get_string("plaintext: ");
    int length = strlen(plaintext);

    //print ciphertext:
    printf("ciphertext: ");
    for(int i = 0; i < length; i++)
    {
        char character = plaintext[i];

        if(isalpha(character))
        {
            char m = 'A';
            if(islower(character))
            {
                m = 'a';
            }


            character -= m;
            if(islower(character+m))
            {
                printf("%c", (tolower(key[(int)character])));
            }else
            {
                printf("%c", (key[(int)character]));
            }

        }else
        {
            printf("%c", character);
        }
    }

    printf("\n");
    return 0;
}


//validate funciton
string convert_string(string argv[])
{
    string s = argv[1];
    long sum = 0;
    int count = 0;

    if(strlen(s) != 26)
    {
        printf("Usage: %s key\n", argv[0]);
        exit(1);
    }
    //check that numbers in key are only characters (how to check for repeat chracters???)
    for(int i = 0, length = strlen(s); i < length; i++)
    {
        if(!isalpha(s[i]))
        {
            printf("Usage: %s key\n", argv[0]);
            exit(1);
        }
        s[i] = toupper(s[i]);
        sum += s[i];
    }

    //check for single duplicate characters
    if(sum != 2015)
    {
        printf("Usage: %s key\n", argv[0]);
        exit(1);
    }

    //check for multiple duplicate characters
    for(int i = 0, length = strlen(s); i < length; i++)
     {
         for(int j = 0; i < length; i++)
         {
             if(s[i] == s[j])
             {
                count++;
             }
         }
         if(count != 1)
         {
            printf("Usage: %s key\n", argv[0]);
            exit(1);
         }else
         {
             count = 0;
         }
     }

    return s;
    }