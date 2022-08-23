"""
counts = []
for STR in STRS:
    counts.append(max_repeat_STR(STR, dna))

alternative method:
counts = [max_repeat_STR(STR,dna) for STR in STRS] 
"""

import sys
import csv


def main():
    # check if user submitted correct number of arguments
    if len(sys.argv) != 3:
        sys.exit("Usage: python dna.py file.csv f.txt")

    # Open file, Create reader object,skip first line and store the STRS in STRS var
    with open(sys.argv[1]) as csv_file:
        reader = csv.reader(csv_file)
        STRS = next(reader)[1:]

        # Open TXT_file and store it in dna variable
        with open(sys.argv[2]) as txt_file:
            dna = txt_file.read()
            counts = [max_repeat_STR(STR, dna) for STR in STRS]
            print_match(reader, counts)


# Calculate how many times each STR repeats in DNA file
def max_repeat_STR(STR, dna):
    answer = [0] * len(dna)
    for i in range(len(dna) - len(STR), -1, -1):
        if STR == dna[i : i + len(STR)]:
            if i + len(STR) > len(dna) - 1:
                answer[i] = 1
            else:
                answer[i] = 1 + answer[i + len(STR)]
    return max(answer)


# Print match of dna
def print_match(reader, counts):
    for row in reader:
        person = row[0]
        values = [int(val) for val in row[1:]]
        if values == counts:
            print(person)
            return
    print("No match")
    return


if __name__ == "__main__":
    main()
