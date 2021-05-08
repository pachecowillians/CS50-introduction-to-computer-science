# Import libs
import csv
import sys

# Checking if was passed the right number of command-line commands
if len(sys.argv) != 3:
    print("Usage: python dna.py data.csv sequence.txt")
else:
    # Read the csv file
    db = open(sys.argv[1], "r")
    # Need to convert to list to manipulate
    reader = list(csv.reader(db))
    db.close()

    # Read the dna file
    file = open(sys.argv[2], "r")
    dna = file.read()
    file.close()

    # Use the first line to know the words to find
    chains = reader[0][1:]
    m = []
    # Search for each chain
    for c in chains:
        found = False
        # Count from 200 to 1 to verify the max value of repetitions that is found in dna
        for x in reversed(range(200)):
            # Repeat the chain x times and verify if it is on string
            if x * c in dna:
                # Uses string to compare
                m += [str(x)]
                # If found, just stop search because is the max value
                break
    find = False
    # Search for a combination that matches
    for c in reader:
        # If matches
        if c[1:] == m:
            print(c[0])
            find = True
            # Stop searching
            break
    # If there are no matches on the for loop
    if not find:
        print("No match")
