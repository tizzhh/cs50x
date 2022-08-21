# TODO
from cs50 import get_string


def main():
    print("Text: ", end="")
    text = get_string("")
    letters = count_letters(text)
    words = count_words(text)
    sent = count_sent(text)
    L = letters / words * 100.0
    S = sent / words * 100.0
    index = 0.0588 * L - 0.296 * S - 15.8
    index = round(index)
    if index < 1:
        print("Before Grade 1")
    elif index > 16:
        print("Grade 16+")
    else:
        print(f"Grade {index}")


def count_letters(text):
    letters = 0
    for ch in text:
        if ch.isalpha():
            letters += 1
    return letters


def count_words(text):
    words = 0
    for i in text:
        if i == " ":
            words += 1
    return words + 1


def count_sent(text):
    sent = 0
    for i in text:
        if i == "." or i == "?" or i == "!":
            sent += 1
    return sent


if __name__ == "__main__":
    main()
