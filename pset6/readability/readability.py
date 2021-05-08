# Import the lib for get_string
from cs50 import get_string


# Function to calc the index
def CalcIndex(l, s):
    return 0.0588 * l - 0.296 * s - 15.8


# Read the text
text = get_string("Text: ")

# Split by words and count the words
w = len(text.split())

# Split by .? and ! and takes -1 from each
s = len(text.split(".")) + len(text.split("?")) + len(text.split("!")) - 3

l = 0

# Sum the letters of sentence
for x in text:
    if x.isalpha():
        l += 1

# Calc the index
i = round(CalcIndex(100 * l / w, 100 * s / w))

# Validate each grade
if (i < 1):
    print("Before Grade 1")
elif (i >= 16):
    print("Grade 16+")
else:
    print(f'Grade {i}')
