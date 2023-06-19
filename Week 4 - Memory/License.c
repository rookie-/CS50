#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    // Check for command line args
    if (argc != 2)
    {
        printf("Usage: ./read infile\n");
        return 1;
    }

    // Create buffer to read into
    char original_buffer[7];

    // Create array to store plate numbers
    char *plates[8];

    FILE *infile = fopen(argv[1], "r");

    int idx = 0;

    while (fread(original_buffer, 1, 7, infile) == 7)
    {

        // Allocate memory for each buffer.

       char *buffer = malloc(strlen(original_buffer) + 1);

       if (buffer == NULL)
       {
        free(buffer);
        return 1;
       }

        strcpy(buffer, original_buffer);
        // Replace '\n' with '\0'
        buffer[6] = '\0';


       //Allocate memory for each plate.
       plates[idx] = malloc(strlen(buffer) + 1);

       if (plates[idx] == NULL)
       {
        free(plates[idx]);
        return 1;
       }

        // Save plate number in array
        strcpy(plates[idx], buffer);
        idx++;

        free(buffer);
    }


    for (int i = 0; i < 8; i++)
    {
        printf("%s\n", plates[i]);
        free(plates[i]);
    }
}
