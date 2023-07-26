#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char *argv[])
{
//Check for command line args
if (argc != 2)
 {
    printf("Program accepts one command-line argument.");
    return 1;
 }

//Open file
  FILE *card = fopen(argv[1], "r");
  if (card == NULL)
  {
    printf("Can't open file.");
    return 1;
  }

   typedef uint8_t BYTE;
   BYTE *buffer = malloc(512 * sizeof(BYTE));

   int counter = 0;
   FILE *img = NULL;


//Read from raw file in 512-byte chunks.
while (fread(buffer, 512, 1, card) == 1)
{

//If start of a new JPEG.
    if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
    {

      if (img != NULL)
      {
        fclose(img);
      }

      char filename[8];
      sprintf(filename, "%03i.jpg", counter);
      img = fopen(filename, "w");
      fwrite(buffer, 512, 1, img);
      counter++;
    }

//If not the start of a new JPEG.
    else if (img != NULL)
    {
     fwrite(buffer, 512, 1, img);
    }
}

//Close last img file.
if (img != NULL)
{
  fclose(img);
}

  fclose(card);
  free(buffer);
  return 0;
}
