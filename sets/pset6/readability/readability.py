from cs50 import get_string


def main():

    text = get_string("Text: ")

    letters = count_letters(text)
    words = count_words(text)
    sentences = count_sentences(text)

    # Using Coleman-Liau index to calculate reading level
    L = (float(letters) / words) * 100.0
    S = (float(sentences) / words) * 100.0
    index = 0.0588 * L - 0.296 * S - 15.8

    if index > 16:
        print("Grade 16+")
    elif index < 1:
        print("Before Grade 1")
    else:
        print(f"Grade {round(index)}")


# function to count sentences
def count_sentences(text):
    periods = 0
    for i in text:
        if i == "." or i == "?" or i == "!":
            periods += 1
    return periods


# function to count words
def count_words(text):
    spaces = 0
    for i in text:
        if i == " ":
            spaces += 1
    words = spaces + 1
    return words


# function to count letters
def count_letters(text):
    special = 0
    for i in text:
        if not i.isalpha():
            special += 1
    letters = len(text) - special
    return letters


if __name__ == "__main__":
    main()
