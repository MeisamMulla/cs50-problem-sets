#include <stdio.h>
#include <cs50.h>
#include <math.h>

int divide(int amount, int denomination);

int main(void)
{
    float amount;

    do
    {
        amount = get_float("Change owed: ");
    }
    while (amount < 0);

    int cents = round(amount * 100);
    int coins = 0;
    int result;

    // Keep running until we run out of cents
    while (cents > 0)
    {
        if (cents >= 25)
        {
            // divide the number of cents we have by the denomination
            // take the result and put that in the number of coins that
            // we have. Minus that number from the cents that we have
            // left in the "bag"
            result = divide(cents, 25);
            coins += result;
            cents -= result * 25;
        }

        if (cents >= 10)
        {
            result = divide(cents, 10);
            coins += result;
            cents -= result * 10;
        }

        if (cents >= 5)
        {
            result = divide(cents, 5);
            coins += result;
            cents -= result * 5;
        }

        if (cents >= 1)
        {
            result = divide(cents, 1);
            coins += result;
            cents -= result * 1;
        }
    }

    printf("%i\n", coins);
}

// Divide the amount by the denomination
int divide(int amount, int denomination)
{
    return amount / denomination;
}