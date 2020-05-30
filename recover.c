#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // THERE MUST BE 1 COMMAND LINE ARG
    if (argc != 2)
    {
        fprintf(stderr, "There must be 1 command line argument");
        return 1;
    }

    //OPEN THE MEMORY CARD
    FILE *memcard = fopen(argv[1], "r");
    if (memcard == NULL)
    {
        fprintf(stderr, "There must be 1 command line argument");
        return 1;
    }
    else
    {
        //ESTABLISH FILENAME 
        char *filename = malloc(8 * sizeof(char));
             //ESTABLISH THE BUFFER
        BYTE *buffer = malloc(sizeof(BYTE) * 512);
        int fileCounter = 0;
        FILE *img = NULL;

        //WHILE LOOP TO CAPTURE FREAD
        while (fread(buffer, sizeof(BYTE), 512, memcard) == 512)
        {
            //IF JPEG WRITE TO NEW JPG FILE
            if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && ((buffer[3] & 0xf0) == 0xe0))
            {
               //THIS IS A NEW FILE
                if (fileCounter > 0)
                {
                    fclose(img);   
                }
                    //Make new JPEG file
                    sprintf(filename, "%03i.jpg", fileCounter);
                    // write to the new JPEG
                    img = fopen(filename, "w");
                    fwrite(buffer, sizeof(BYTE), 512, img);
                    fileCounter++;
            }
                else if (fileCounter > 0)
            {
                    fwrite(buffer, sizeof(BYTE), 512, img);
            }
            
        }
        free(filename);
        free(buffer);
        //close remaining files
        fclose(memcard);
        fclose(img);
        return 0;
    }
   
}