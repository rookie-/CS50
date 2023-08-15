#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "wav.h"

int check_format(WAVHEADER header);
int get_block_size(WAVHEADER header);

int main(int argc, char *argv[])
{
    // Ensure proper usage
    if (argc != 3)
    {
        printf("Program accepts two command-line arguments.");
        return 1;
    }

    // Open input file for reading
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Can't open input file.");
        return 1;
    }

    // Read header
    WAVHEADER header;
    fread(&header, sizeof(header), 1, input);

    // Use check_format to ensure WAV format
    int is_a_wav = check_format(header);
    if (is_a_wav == 0)
    {
        printf("This is a WAV file.");
    }
    else
    {
        printf("This is not a WAV file.");
        fclose(input);
        return 1;
    }


    // Open output file for writing
    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Can't open output file.");
        return 1;
    }

    // Write header to file
    fwrite(&header, sizeof(header), 1, output);

    // Use get_block_size to calculate size of block
    int block_size = get_block_size(header);

    // Write reversed audio to file

    int buffer[block_size];
    long file_size;

    //Get file size.
    fseek(input, 0, SEEK_END);
    file_size = ftell(input);

    //Reverse the file.
    int current_position = file_size;
    while(current_position > sizeof(header))
    {
      current_position -= block_size;
      fseek(input, current_position, SEEK_SET);
      fread(buffer, block_size, 1, input);
      fwrite(buffer, block_size, 1, output);
    }

    fclose(input);
    fclose(output);
    return 0;
}

int check_format(WAVHEADER header)
{
  if (header.format[0] != 'W' || header.format[1] != 'A' || header.format[2] != 'V' || header.format[3] != 'E')
  {
    return 1;
  }

   else
   {
    return 0;
   }
}

int get_block_size(WAVHEADER header)
{

int size = header.numChannels * (header.bitsPerSample / 8);

   return size;
}
