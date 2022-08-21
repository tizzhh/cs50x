# TODO
from cs50 import get_string

print("Number: ", end="")
number = get_string("")
length = len(number)
number = int(number)
summ1 = 0
summ2 = 0
i = 0
x = 0
num1 = number
num2 = number

while num1 > 0:
    if i % 2 == 0:
        x = num1 // 10 % 10 * 2
        if x > 9:
            summ1 += x // 10 + x % 10
        else:
            summ1 += x
    num1 //= 10
    i += 1
j = 1
while num2 > 0:
    if j % 2 != 0:
        summ2 += num2 % 10
    num2 //= 10
    j += 1
ftd = number // 100000000000000
ftd1 = number // 10000000000000

if (summ1 + summ2) % 10 == 0:
    if (length == 16) and (ftd == 51 or ftd == 52 or ftd == 53 or ftd == 54 or ftd == 55):
        print("MASTERCARD")
    elif (length == 15) and (ftd1 == 34 or ftd1 == 37):
        print("AMEX")
    elif (length == 13 or length == 16) and (number // 1000000000000000 == 4 or number // 1000000000000 == 4):
        print("VISA")
    else:
        print("INVALID")
else:
    print("INVALID")