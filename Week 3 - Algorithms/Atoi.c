#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int convert(string input);

int main(void)
{
    string input = get_string("Enter a positive integer: ");

    for (int i = 0, n = strlen(input); i < n; i++)
    {
        if (!isdigit(input[i]))
        {
            printf("Invalid Input!\n");
            return 1;
        }
    }

    // Convert string to int
    printf("%i\n", convert(input));
}

int convert(string input)
{
    // TODO

    int number = 0;

    int length = strlen(input);


    if (input[0] == '\0')
    {
       return 0;
    }

   else
   {

    //Index last char
   char last_char = input[length - 1];

   //Convert last char to int
   int last_char_to_int = last_char - '0';

   //Move /0 to the left and shorten string
   input[length - 1] = '\0';

   char shorter_string[length];

   strncpy(shorter_string, input, length-1);

   int rest_of_string_to_int = convert(shorter_string);

   number = last_char_to_int + rest_of_string_to_int * 10;

    }

return number;

}
