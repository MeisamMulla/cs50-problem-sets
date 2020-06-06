from cs50 import get_string
from math import floor


def main():
    # get the number
    number = get_string("Number: ")

    # store the numbers length
    length = len(str(number))

    # check if card is valid length
    if length not in [13, 15, 16]:
        print("INVALID")
        return

    # do a lunh check
    if not luhn(number):
        print("INVALID")
        return

    # print out the issuer of the card
    print(issuer(number))


def luhn(number):
    number = number[::-1]

    # the numbers that don't have to be multiplied by 2
    nmt = 0

    # the numbers that have to be multipled by 2
    mt = 0

    for i in range(len(number)):
        # if i is even then we're just adding the number to nmt
        if i % 2 == 0:
            nmt += int(number[i])
        else:
            result = int(number[i]) * 2

            if result >= 10:
                # take the second number and add it to mt
                mt += floor(result / 10)
                # take the first number and add it to mt
                mt += result % 10
            else:
                # otherwise just add the result
                mt += result

    # if the sum of mt and nmt ends with 0 its a valid numner
    if (mt + nmt) % 10 == 0:
        return True

    return False


def issuer(number):
    amex = [34, 37]
    mastercard = [51, 52, 53, 54, 55]
    visa = []

    first_two = int(number[0] + number[1])

    if number[0] == "4":
        return "VISA"

    if first_two in mastercard:
        return "MASTERCARD"

    if first_two in amex:
        return "AMEX"

    return "INVALID"


main()

