#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>


int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)
{

string text = get_string("Text: ");

int number_of_letters = count_letters(text);
int number_of_words = count_words(text);
int number_of_sentences = count_sentences(text);

//index = 0.0588 * L - 0.296 * S - 15.8

float L = (float) number_of_letters / number_of_words * 100;
float S = (float) number_of_sentences / number_of_words * 100;

float index = 0.0588 * L - 0.296 * S - 15.8;


if (index > 16)
{
 printf("Grade 16+\n");
}

else if (index < 1)
{
printf("Before Grade 1\n");
}

else
{
  printf("Grade %i\n", (int) round(index));
}

}


intu text)
{
int charcount = 0;

  for (int i = 0; i < strlen(text); i++)
  {
   if (isalpha(text[i]))
    {
        charcount++;
    }

  }
   return charcount++;

}

int count_words(string text)
{
  int spaces = 1;

  for (int i = 0; i < strlen(text); i++)
  {
   if (isspace(text[i]))
   {
    spaces++;
   }
  }

   return spaces;
}

int count_sentences(string text)
{

int sentences = 0;

  for (int i = 0; i < strlen(text); i++)
  {

   if (text[i] == '.' || text[i] == '!' || text[i] == '?')

   {
    sentences++;
   }

  }
  return sentences;

}
