#include <stdio.h>
#include <cs50.h>
#include <math.h>


int main(void)
{
    long card = get_long("Number: ");

    // make temporary card number to work on
    long tmp_card = card;

    // get the number of characters in tmp_card
    int count = 0;
    while (tmp_card > 0)
    {
        tmp_card /= 10;
        count++;
    }

    // if we dont have enough characters in the number then exit
    if (count != 13 && count != 16 && count != 15)
    {
        printf("INVALID\n");
        return 0;
    }

    // reset the tmp_card and rerun loop but this time keep first 2 numbers
    tmp_card = card;

    while (tmp_card / 100)
    {
        tmp_card /= 10;
    }

    int first_two_numbers = tmp_card;

    // save first two for later to return company name, reset tmp_card again
    int multiply_two = 0;
    int not_multiply_two = 0;

    tmp_card = card;

    // do a luhn check
    for (int i = 0; i < count; i++)
    {
        // get the last number
        int le_number = tmp_card % 10;

        //printf("\n%d", le_number);

        // if this number is even we're going to
        if (i % 2 == 0)
        {
            // add it to not_multiply_to
            not_multiply_two += le_number;
        }
        else
        {
            // otherwise multiply the number by 2 and then add it to our multiply_to sum
            int le_number_b = le_number * 2;

            // if the number is larger than 10 we have to split it up and add the individual numbers to the sum
            if (le_number_b >= 10)
            {
                multiply_two += le_number_b % 10;
                multiply_two += round(le_number_b / 10);

                //printf(" [1: %i, 2: %i] ", le_number_b % 10, le_number_b / 10);
            }
            else
            {
                // otherwise just add it as is
                multiply_two += le_number_b;
            }

            //printf(" i: %i, le_number(%i) * 2 = %i, lnb: %i", i, le_number, le_number * 2, le_number_b);
        }


        // divide by 10 so tmp has one less number at the end
        tmp_card /= 10;
    }

    int sum = multiply_two + not_multiply_two;

    if (sum % 10 != 0)
    {
        printf("INVALID\n");
        return 0;
    }

    if (first_two_numbers / 10 == 4)
    {
        printf("VISA\n");
        return 0;
    }

    switch (first_two_numbers)
    {
        case 34:
        case 37:
            printf("AMEX\n");
            break;

        case 51:
        case 52:
        case 53:
        case 54:
        case 55:
            printf("MASTERCARD\n");
            break;

        default:
            printf("INVALID\n");
    }

}
