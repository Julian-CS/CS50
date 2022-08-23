#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int convert_string(string argv[]);

int main(int argc, string argv[])
{

    //check if user submitted correct arguments
    if (argc != 2)
    {
        printf("Usage: %s key\n", argv[0]);
        return 1;
    }



    //Validate key and Convert string key to int key
    int key = convert_string(argv);


    //convert plaintext to cyphertext
    string plaintext = get_string("Plantext: ");
    int length = strlen(plaintext);


    printf("ciphertext: ");
    //print ciphertext:
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

            printf("%c", (character - m + key) % 26 + m);
        }else
        {
            printf("%c", character);
        }
    }

    printf("\n");
    return 0;
}


//validate funciton
int convert_string(string argv[])
{
    string s = argv[1];

    //check that numbers in key are only digits 0-9
    for(int i = 0, length = strlen(s); i < length; i++)
    {
        if(!isdigit(s[i]))
        {
            printf("Usage: %s key\n", argv[0]);
            exit(1);
        }
    }
    int key = atoi(s);
    return key;
    }