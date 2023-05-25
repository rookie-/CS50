#include <cs50.h>
#include <stdio.h>

int max(int array[], int n);

int main(void)
{
    int n;
    do
    {
        n = get_int("Number of elements: ");
    }
    while (n < 1);

    int arr[n];

    for (int i = 0; i < n; i++)
    {
        arr[i] = get_int("Element %i: ", i);
    }

    printf("The max value is %i.\n", max(arr, n));
}

// TODO: return the max value
int max(int array[], int n)
{
  int max_index;

  //Using selection sort to find the max value

  for (int i = 0; i < n; i++)
  {
    max_index = i;

    for (int j = i + 1; j < n; j++)
    {
      if (array[max_index] < array[j])

     max_index = j;

    }
  //Swap bigger numbers for smaller
     if (max_index != i)
     {
     int temp = array[i];
     array[i] = array[max_index];
     array[max_index] = temp;
     }

  }

int max_value = array[0];
    return max_value;
}
