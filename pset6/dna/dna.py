import sys
import csv


def main():
    # check if the arguments are set properlu
    if len(sys.argv) < 3:
        print(f"Usage: python {sys.argv[0]} data.csv sequence.txt")
        return

    # initialize the dictionaries
    dnaDb = {}

    # initialize list for items to look for
    lookFor = []
    resultValues = []

    # initliaze the variable for the sequence
    sequence = ""

    # open the database file and load it into the dictionary
    with open(sys.argv[1], "r") as dataFile:
        dnaData = csv.DictReader(dataFile)
        dataHeaders = dnaData.fieldnames

        # iterate over each row in the csv
        for i in dnaData:
            # assign a temporary dictionary
            tmp = {}

            # iterate through the headers to get the STRs
            for j in dataHeaders:
                # ignore the header if its called "name"
                if j == "name":
                    continue

                # take each header as the key and add the value to tmp
                tmp.update({j: i[j]})

            # append the tmp dictionary to the main db dictionary
            dnaDb.update({i['name']: tmp})

        # add the header to our list to look for
        for i in dataHeaders:
            # ignore the header if its called "name"
            if i == "name":
                continue

            lookFor.append(i)

    # open the sequence file and store it to memory
    with open(sys.argv[2], "r") as sequenceFile:
        sequence = sequenceFile.read()

    for i in lookFor:
        resultValues.append(find_matches(i, sequence))

    # iterate over the items we have to look for and see how many we have in the sequence
    for i in dnaDb:
        # get the value for each key in the dictionary
        values = dnaDb.get(i)

        for j in range(len(lookFor)):
            # no match so ignore
            if int(values[lookFor[j]]) != int(resultValues[j]):
                break

            # we've found a match
            if j + 1 == len(lookFor):
                print(i)
                return

    # if we've gotten this far we haven't found a match
    print("No match")


def find_matches(dnaStr, sequence):
    # consecutive number of matches
    consecutive = 0
    inSequence = False
    maxConsecutive = 0

    # lengths of the STR and sequence
    sequenceLength = len(sequence)
    strLength = len(dnaStr)

    # the counter
    i = 0

    # loop until the sequence length is lower than the counter
    while i < sequenceLength:
        # break out if we don't have enought characters left
        if (i + strLength) > sequenceLength:
            break

        # have we found a first character match?
        if sequence[i] == dnaStr[0]:
            # by default lets assume we're in sequence
            inSequence = True

            for j in range(strLength):
                # lets make sure we're not going out of bounds
                if (i + j) > sequenceLength - 1:
                    break

                # its not a match
                if sequence[i + j] != dnaStr[j]:
                    # make sure we're not in sequence and reset consecutive
                    inSequence = False
                    consecutive = 0
                    break

            # If we're in sequence lets append the counter
            if inSequence:
                consecutive += 1

                # jump the length of the dnaStr
                i += strLength
            else:
                i += 1

            # update the maxConsecutive if we're on the longest one
            if maxConsecutive < consecutive:
                maxConsecutive = consecutive
        else:
            # if we have't, lets just jump by one character, make sure that we're not in sequence and reset the consecutive counter
            i += 1
            inSequence = False
            consecutive = 0

    # print(f"consecutive: {consecutive}, maxConsecutive: {maxConsecutive}, sequenceLength: {sequenceLength}, strLength: {strLength}, i: {i}\n{sequence}")

    # return the number on consecutive matches
    return maxConsecutive


main()