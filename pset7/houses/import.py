# Import libs
import csv
import sys
from cs50 import SQL

# Checking if was passed the right number of command-line commands
if len(sys.argv) != 2:
    print("Usage: python import.py data.csv")
    exit(1)
else:
    # Connecting to DB
    db = SQL("sqlite:///students.db")
    # Openning file
    file = open(sys.argv[1], "r")
    # Converting to a reader
    reader = list(csv.reader(file))
    # Closing file
    file.close()
    for row in reader:
        name = row[0]
        # Split the names
        name = name.split()
        l = len(name)
        # If has a middle name
        # Inserting in db
        # \' == '
        if l == 2:
            db.execute(
                f'insert into students(first, middle, last, house, birth) values(\'{str(name[0])}\', NULL, \'{str(name[1])}\', \'{row[1]}\', {row[2]});')
        elif l > 2:
            db.execute(
                f'insert into students(first, middle, last, house, birth) values(\'{str(name[0])}\', \'{str(name[1])}\', \'{str(name[2])}\', \'{row[1]}\', {row[2]});')
