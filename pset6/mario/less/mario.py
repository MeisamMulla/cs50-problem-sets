from cs50 import get_int

# Our main funcion


def main():
    # continue forever
    while True:
        height = get_int("Height: ")

        # does the input match our range
        if height <= 8 and height > 0:
            # draw it if it does
            mario(height)
            # end the loop
            break


def mario(height):
    for i in range(height):
        for j in range(height):
            if i >= height - (j + 1):
                print("#", end="")
            else:
                print(" ", end="")
        print()


main()