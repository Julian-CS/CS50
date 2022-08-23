from cs50 import get_int

# get user input
x = 0
while x < 1 or x > 8:
    x = get_int("Height: ")

# counter variable i for hashtags, loop and j for spaces
i = 1
for j in range(x - 1, -1, -1):
    print(" " * j, end="")
    print("#" * i)
    i += 1
