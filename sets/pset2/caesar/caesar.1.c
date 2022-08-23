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

    for(int i = 0; i < length; i++)
    {
        
        if(isalpha(plaintext[i]) && !islower(plaintext[i]))
        {
            plaintext[i] = (plaintext[i] + key) % 26;
            
            if(plaintext[i] > 90)
            {
                plaintext[i] = (plaintext[i] % 65) - 25;
            }
        }else if(isalpha(plaintext[i]) && islower(plaintext[i]))
        {
            plaintext[i] = (plaintext[i] + key) % 26;
            
            if(plaintext[i] > 122)
            {
                plaintext[i] = (plaintext[i] % 97) - 25;
            }
        }
    }
    
    plaintext[length+1] = '\0';
    
    printf("ciphertext: %s\n", plaintext);
    return 0;
}


//validate funciton
int convert_string(string argv[])
{
    string s = argv[1];
    int length = strlen(s);

    //check that numbers in key are only digits 0-9
    for(int i = 0; i < length; i++)
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