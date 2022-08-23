from cs50 import get_int
import re


def count_digits
def calc_checksum

while 1:
    number = get_int("Number: ")
    if number >= 0:
        break

digits = count_digits

checksum = calc_checksum

if (checksum % 10) != 0:
        print('INVALID')

starting_number = number/pow((10,digits-2));

m = re.match('')



def count_digits:
    digits = number
    count = 0
    while digits > 0:
        digits = digits / 10
        count += 1
    return count

def calc_checksum:
    checksum = 0
    a_number = []

    for i in range(1, digits, 2):
        divisor = pow(10, i)
        j = (number/divisor) % 10) * 2.0
        a_number.append(j)
        if a_number[-1] > 9:
            checksum += a_number[-1] / 10
            checksum += a_number[-1] % 10
        else:
            checksum += a_number[-1]
    for i in range(0, digits, 2):
        divisor = pow(10, i)
        sum_rest += (number/divisor) % 10

    var = checksum + sum_rest
    return var