```c

#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // TODO: Prompt for start size
    int startsize;

    do
    {
     startsize=get_int("Provide a start size of at least 9: ");
    }
    while (startsize < 8);

    // TODO: Prompt for end size
     int endsize;

    do
    {
     endsize=get_int("Provide an end size of at least 9: ");
    }
    while (endsize < 8);

    int n = 0;
    int oneyeargrowth = startsize / 3 - startsize / 4;
    int currentsize = startsize;

    // TODO: Calculate number of years until we reach threshold
    while (currentsize < endsize)
    {
       currentsize += oneyeargrowth;
       n++;
    }

    // TODO: Print number of years
    printf("Start size: %i\n End size: %i\n Years: %i\n.", startsize, endsize, n);
}

``` 
