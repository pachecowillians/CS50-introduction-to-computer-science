# Import libs
import csv
import sys
from cs50 import SQL

# Checking if was passed the right number of command-line commands
if len(sys.argv) != 2:
    print("Usage: python roster.py [house name...]")
    exit(1)
else:
    # Connecting to db
    db = SQL("sqlite:///students.db")
    # Getting the select with order by last, then first
    result = db.execute(f'select first, middle, last, birth from students where house = \'{sys.argv[1]}\' order by last, first')
    # Print the result in screen
    for x in result:
        # If there is a middle name
        if x['middle']:
            print("{} {} {}, born {}".format(x['first'], x['middle'], x['last'], x['birth']))
        else:
            print("{} {}, born {}".format(x['first'], x['last'], x['birth']))
