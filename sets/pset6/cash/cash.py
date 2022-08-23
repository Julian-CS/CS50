from cs50 import get_float

while 1:
    change = get_float("Change: ")
    if change >= 0:
        break

cents = round(change * 100)
coin = [25, 10, 5, 1]
coins = 0

# Divide coins to get total number of whole coins.
for i in coin:
    coins += cents // i
    cents %= i
print(f"Coins used: {int(coins)}")
