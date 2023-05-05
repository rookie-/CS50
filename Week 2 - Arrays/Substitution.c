#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>


int main(int argc, string argv[])
{

//Checking if key is valid.

   if (argc != 2)
  {
  printf("Provide one command-line argument!\n");
  return 1;
  }

 string key = argv[1];

 int length_of_key = strlen(key);

 if (length_of_key != 26)
    {
    printf("Key should have 26 characters!\n");
    return 1;
    }


  bool contains_non_alpha = false;
  bool letters_repeat = false;

  for (int i = 0; i < length_of_key; i++)
  {
    char letter = key[i];
    for (int j = i + 1; j < length_of_key; j++)
    {
      char check_for_repeat_letters = key[j];
      if (letter == check_for_repeat_letters)
      {
        letters_repeat = true;
        printf("Letters in key should not repeat!\n");
        return 1;
      }
    }


    if (!isalpha(key[i]))
    {
    contains_non_alpha = true;
    printf("Key should contain only alphabetical characters!\n");
    return 1;
    }

  }

  string plain_text = get_string("plaintext: ");

  int key_position = 0;

  int string_length = strlen(plain_text);

  printf("ciphertext: ");

  //Converting plaintext to ciphertext.

  for (int i = 0; i < string_length; i++)

 {
    if (isupper(plain_text[i]))

    {
    key_position = (plain_text[i] - 'A');
    }

    else if (islower(plain_text[i]))

    {
    key_position = (plain_text[i] - 'a');
    }



    if (isalpha(plain_text[i]) && islower(plain_text[i]))
    {

    char cipher_text = key[key_position];

    printf("%c", tolower(cipher_text));

   }

   else if (isalpha(plain_text[i]) && isupper(plain_text[i]))
   {

    char cipher_text = key[key_position];

    printf("%c", toupper(cipher_text));
   }

   else
   {
    printf("%c", plain_text[i]);
   }

  }

  printf("\n");

  return 0;

}
