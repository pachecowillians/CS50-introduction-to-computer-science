# Import get_string
from cs50 import get_string
# Reading the card name
card = get_string("Number: ")
# Definning the variables
i = 0
soma1 = 0
# Soma2 is the var of first sum
soma2 = 0
# Reverse the card's order and go through it
for x in reversed(card):
    # Once it goes to normal sum, and then to other
    if i % 2 == 0:
        soma1 += int(x)
    else:
        # String containning the number times 2 in string
        v = str(2 * int(x))
        # Go through the previous string and sum each digit
        for y in v:
            soma2 += int(y)
    i += 1

c = soma1 + soma2
# Initial contition to be a valid credit card
if(c % 10 != 0):
    print("INVALID")
# Conditions to be AMEX
elif ((card[0:2] in ["34", "37"]) and len(card) == 15):
    print("AMEX")
# Conditions to be MASTERCARD
elif ((card[0:2] in ["51", "52", "53", "54", "55"]) and len(card) == 16):
    print("MASTERCARD")
# Conditions to be visa
elif ((card[0] == "4") and (len(card) == 16 or len(card) == 13)):
    print("VISA")
# If does not fill any of the previous conditions, it is invalid too
else:
    print("INVALID")