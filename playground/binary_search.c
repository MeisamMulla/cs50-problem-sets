#include <stdio.h>
#include <cs50.h>
#include <math.h>

#define SIZE 16

int array[SIZE];
int target, start, end, element, middle;

bool search();

int main(void)
{
    int items[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 12, 15, 16, 20, 22, 26};

    for (int i = 0; i < 16; i++)
    {
        array[i] = items[i];
    }

    start = 0;
    end = SIZE - 1;

    target = get_int("What's the target? ");

    search();
}

/**
 * How binary search works
 *
 * - we take a sorted array and split it in half
 * - check if the middle value matches what we're looking for, if it does we end
 * - otherwise if the target value is greater than the middle amount we change the start value to middle+1 and repeat the search
 * - otherwise if the target vakue is lower than the middle amount we change the end value to middle-1 and repeat the search
 * - if we find the value of end to be greater than the start we abort because the target value doesnt exist.
 **/
bool search()
{
    middle = (end + start) / 2;

    if (array[middle] == target)
    {
        printf("Target found at position %i\n", middle);
        return true;
    }

    if (start > end)
    {
        printf("Target not found\n");
        return false;
    }

    if (target > array[middle])
    {
        start = middle + 1;
    }
    else
    {
        end = middle - 1;
    }

    search();

    return false;
}