#include <stdio.h>

void print_r(int size, int array[]);

int main(void)
{
    int array[6] = {5, 2, 1, 3, 6, 4};

    int swap = -1;

    while (swap != 0)
    {
        swap = 0;

        for (int i = 0; i < 6 - 1; i++)
        {

            if (array[i] > array[i + 1])
            {
                int tmp = array[i];
                array[i] = array[i + 1];
                array[i + 1] = tmp;
                swap++;
            }

        }

        print_r(6, array);
    }



}

void print_r(int size, int array[])
{
    for(int i = 0; i < size; i++)
    {
        printf("%i, ", array[i]);
    }

    printf("\n");
}