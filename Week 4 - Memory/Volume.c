// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);

    // TODO: Copy header from input file to output file

    uint8_t header[44];

    // Read infile's header.
    fread(header, 44, 1, input);

    // Write header into outfile.
    fwrite(header, 44, 1, output);

    // TODO: Read samples from input file and write updated data to output file

    int16_t original_buffer;

    while (fread(&original_buffer, sizeof(int16_t), 1, input) == 1)
    {
     int16_t *buffer = malloc(sizeof(int16_t));

      if (buffer == NULL)
      {
        free (buffer);
        return 1;
      }

      memcpy(buffer, &original_buffer, sizeof(int16_t));

      *buffer = *buffer * factor;

      fwrite(buffer, 2, 1, output);

      free(buffer);
    }


    // Close files
    fclose(input);
    fclose(output);
}
