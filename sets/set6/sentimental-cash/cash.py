# TODO
from cs50 import get_float

cents = get_float("Change owed: ")
while cents < 0:
    cents = get_float("Change owed: ")

cents *= 100
cents = int(cents)

quarters = cents // 25
cents -= quarters * 25

dimes = cents // 10
cents -= dimes * 10

nickels = cents // 5
cents -= nickels * 5

pennies = cents

coins = quarters + dimes + nickels + pennies
print(coins)