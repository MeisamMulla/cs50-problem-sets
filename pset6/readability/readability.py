from cs50 import get_string
from math import floor


def main():
    # get the text from the user
    text = get_string("Text: ")

    # put the calculations in a list
    data = get_grade(text)

    # compute the index
    grade = 0.0588 * (100.0 * data["letters"] / data["words"]) - 0.296 * (100.0 * data["sentences"] / data["words"]) - 15.8

    # output the grade
    format_grade(grade)


def get_grade(text):
    letters = 0
    words = 0
    sentences = 0

    # iterate based on the number of characters inputted
    for i in range(len(text)):
        # assume that first item is the start of a word
        if i == 0:
            words += 1

        if text[i] >= "A" and text[i] <= "z":
            letters += 1

        # assume that we have a space its probably the end of one word
        if text[i] == " ":
            # if the next letter is also not a space then its probably safe to say we have another word
            if text[i + 1] != " ":
                words += 1

        # assume a sentence has finished if we have a . ! or ?
        ends = [".", "!", "?"]

        if text[i] in ends:
            sentences += 1

    return {
        'letters': letters,
        'words': words,
        'sentences': sentences
    }


def format_grade(grade):
    if grade <= 1:
        print("Before Grade 1")
    elif grade >= 16:
        print("Grade 16+")
    else:
        print(f"Grade {round(grade)}")


main()

