from cs50 import get_float
from math import floor

# our main function


def main():
    while True:
        cash = get_float("Change owed: ")

        # make sure its more than 0
        if cash >= 0:
            # get the change we have to give back
            change = get_change(cash)

            # display it on the screen
            print(f"{change}")

            # break out of the loop
            break


# return the number of coins needed


def get_change(cash):
    # initial number of coins
    coins = 0

    # convert cash into cents
    cents = cash * 100

    # keep running until cents becomes 0
    while cents > 0:
        # reduce if available
        if cents >= 25:
            # get the number of coins we can split the amount by and floor that number
            number = floor(cents / 25)

            # remove the said number multiplied by the multiplier from the cents we have left
            cents -= number * 25

            # add that number of coins to our coin bag
            coins += number

        if cents >= 10:
            number = floor(cents / 10)
            cents -= number * 10
            coins += number

        if cents >= 5:
            number = floor(cents / 5)
            cents -= number * 5
            coins += number

        if cents >= 1:
            number = cents
            cents -= number
            coins += number

    return round(coins)


main()
