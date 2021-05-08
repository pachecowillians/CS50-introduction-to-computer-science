# The lib for get_int
from cs50 import get_int
# Define the height before the while to it can be recongized
height = -1
# Force the user to type an number in range [1,8]
while(height <= 0 or height > 8):
    height = int(get_int("Height: "))
# Loop for print the hashtags
for i in range(0, height):
    # Print the spaces
    print((height - i - 1) * " ", end="")
    # Print the hashtags using the * operator in strings
    print((i + 1) * "#", "", (i + 1) * "#")