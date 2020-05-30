#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // to check if there is the 1 required command line argument. 
    if (argc != 2)
    {
        fprintf(stderr, "There must be 1 command line argument");
        return 1;
    }

    //Opens the memory card.
    FILE *memcard = fopen(argv[1], "r");
    if (memcard == NULL)
    {
        fprintf(stderr, "There must be 1 command line argument");
        return 1;
    }
    else
    {
        //allocate memory for the filename 
        char *filename = malloc(8 * sizeof(char));
        //allocate memory for the buffer (each = 512 bytes).
        BYTE *buffer = malloc(sizeof(BYTE) * 512);
        int fileCounter = 0;
        FILE *img = NULL;

        //This while loop iterates through the file while there are still 512 bytes chunks to read.
        while (fread(buffer, sizeof(BYTE), 512, memcard) == 512)
        {
            //When this IF is met a start of a JPEG file is found.
            if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && ((buffer[3] & 0xf0) == 0xe0))
            {
               //If a new file.
                if (fileCounter > 0)
                {
                    fclose(img);   
                }
                    //Make new JPEG file
                    sprintf(filename, "%03i.jpg", fileCounter);
                    // write the data to the new JPEG
                    img = fopen(filename, "w");
                    fwrite(buffer, sizeof(BYTE), 512, img);
                    fileCounter++;
            }
                else if (fileCounter > 0)
            {
                    fwrite(buffer, sizeof(BYTE), 512, img);
            }
            
        }
        //free the memory previously allocated. to prevent seg errors and memory leaks.
        free(filename);
        free(buffer);
        //close remaining files
        fclose(memcard);
        fclose(img);
        return 0;
    }
   
}
