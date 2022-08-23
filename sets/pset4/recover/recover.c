#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{

    //Check for correct command line arguments
    if(argc != 2)
    {
        printf("Usage: ./recover image");
        return 1;
    }

    //check if user submitted valid file and open it
    FILE *file = fopen(argv[1],"r");
    if(file == NULL)
        return 1;



    //
    int num = 0;
    BYTE buffer[512];
    char name[sizeof("###.jpg")];


    sprintf(name, "%03i.jpg", num);
    FILE *pic = fopen(name, "w");

    while(fread(buffer, 1, 512, file))
    {
        //if start of new jpeg
        if(buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            //if first jpeg (name == 000.jpeg)
            if(num == 0)
            {
                fwrite(buffer, 1, 512, pic);
                num++;
            }else
            {
                fclose(pic);
                sprintf(name, "%03i.jpg", num);
                pic = fopen(name, "w");
                fwrite(buffer, 1, 512, pic);
                num++;

            }
        }else
        {
            if(num != 0)
            {
                fwrite(buffer, 1, 512, pic);
            }
        }
    }
    fclose(pic);
    return 0;

}