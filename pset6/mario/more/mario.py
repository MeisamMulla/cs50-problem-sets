from cs50 import get_int

# our main function


def main():
    # infinite loop until we get what we want
    while True:
        # get the height from the user
        height = get_int("Height: ")

        # is it in bounds of what we want?
        if height > 0 and height < 9:
            # draw the pyramid and break out of the loop
            mario(height)
            break

# draw the pyramid


def mario(height):
    for i in range(height):
        for j in range(height):
            if i >= height - (j + 1):
                print("#", end="")
            else:
                print(" ", end="")

        print("  ", end="")

        for j in range(height):
            if i >= j:
                print("#", end="")

        print()


main()
