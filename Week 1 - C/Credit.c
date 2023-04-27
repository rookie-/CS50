#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
  long number = get_long("Number: ");
  long card_number = number;
  int counter = 0;
  int sum_of_digits = 0;
  int sum_of_other_digits = 0;
  int total_sum = 0;


  while (number != 0)
  {

   counter++;
   int digit = number % 10;

   if (counter % 2 == 0)
   {

    int product = digit * 2;

    sum_of_digits = sum_of_digits + product / 10 + product % 10;
   }

   else
   {
    sum_of_other_digits = sum_of_other_digits + digit;
   }

   number = number / 10;
   total_sum = sum_of_digits + sum_of_other_digits;

  }

   if (total_sum % 10 != 0)
    {
      printf ("INVALID\n");
    }


   else if (counter == 16 && (card_number >= 5100000000000000 & card_number <= 5599999999999999))
   {
    printf("MASTERCARD\n");
   }

   else if (counter == 15 && (card_number >= 340000000000000 && card_number <= 349999999999999))
   {
    printf("AMEX\n");
   }

   else if (counter == 15 && (card_number >= 370000000000000 && card_number <= 379999999999999))
   {
    printf("AMEX\n");
   }

   else if (counter == 13 && (card_number >= 4000000000000 && card_number < 5000000000000))
   {
    printf("VISA\n");
    }

   else if (counter == 16 && (card_number >= 4000000000000000 && card_number < 5000000000000000))
   {
    printf("VISA\n");
   }

   else
   {
    printf ("INVALID\n");
   }

}
