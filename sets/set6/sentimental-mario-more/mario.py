# TODO
from cs50 import get_int

height = get_int("Height: ")
while height < 1 or height > 8:
    height = get_int("Height: ")

space = height-1
for i in range(1, height+1):
    print(" " * space, end="")
    space -= 1
    print("#" * i, end="")
    print("  ", end="")
    print("#" * i)