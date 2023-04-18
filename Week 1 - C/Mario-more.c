#include <cs50.h>
#include <stdio.h>

int main(void)
{

  int n;

    do
    {

      n = get_int("Height: ");
    }
    while (n < 1 || n > 8);


for (int i = 0; i < n; i++)

{

 for (int left = 0; left < n; left++)
 {
  if (i + left < n-1)

  printf(" ");

  else

  printf("#");
 }

 for (int space = 0; space < 2; space++)
 {
  printf("  ");
 }

 for (int right = 0; right <= i; right++)
 {
  printf("#");
 }

   printf("\n");

}

return 0;

}
