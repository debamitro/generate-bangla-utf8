#include "BanglaUtf8.hpp"
#include <iostream>
#include <unordered_map>
#include <vector>
#include <ctype.h>

static std::unordered_map<BanglaLetter, const char *> LetterMapping = {
    { BanglaLetter::k, u8"\u0995"},
    { BanglaLetter::K, u8"\u0996"},
    { BanglaLetter::g, u8"\u0997"},
    { BanglaLetter::G, u8"\u0998"},
    { BanglaLetter::ng, u8"\u0999"},
    { BanglaLetter::ch, u8"\u099A"},
    { BanglaLetter::Ch, u8"\u099B"},
    { BanglaLetter::j, u8"\u099C"},
    { BanglaLetter::J, u8"\u099D"},
    { BanglaLetter::NG, u8"\u099E"}
};

static std::unordered_map<BanglaVowel, const char *> VowelprefixMapping = {
    { BanglaVowel::a, ""},
    { BanglaVowel::A, u8"\u09BE"},
    { BanglaVowel::i, u8"\u09BF"},
    { BanglaVowel::I, u8"\u09C0"},
    { BanglaVowel::u, u8"\u09C1"},
    { BanglaVowel::U, u8"\u09C2"}
};

void BanglaElem::print() const {
    std::cout << LetterMapping[letter_]
              << VowelprefixMapping[vowelPrefix_];
}

static std::unordered_map<char, BanglaVowel> vowelConversions = {
    {'a', BanglaVowel::a},
    {'A', BanglaVowel::A},
    {'i', BanglaVowel::i},
    {'I', BanglaVowel::I},
    {'u', BanglaVowel::u},
    {'U', BanglaVowel::U},
    {'e', BanglaVowel::e},
    {'o', BanglaVowel::o}
};

static std::unordered_map<char, BanglaLetter> letterConversions = {
    {'k', BanglaLetter::k},
    {'K', BanglaLetter::K},
    {'g', BanglaLetter::g},
    {'G', BanglaLetter::G}
};

static std::unordered_map<char, BanglaVowel> vowelPrefixConversions = {
    {'A', BanglaVowel::A},
    {'i', BanglaVowel::i},
    {'I', BanglaVowel::I},
    {'u', BanglaVowel::u},
    {'U', BanglaVowel::U}
};

BanglaVowel BanglaUtf8::parse_vowel(std::istream & inputChars) const {
    char c;
    inputChars >> c;
    return vowelConversions[c];
}

BanglaLetter BanglaUtf8::parse_letter(std::istream & inputChars) const {
    char c;
    inputChars >> c;
    return letterConversions[c];
}

BanglaVowel BanglaUtf8::parse_vowel_prefix(std::istream & inputChars) const {
    char c;
    inputChars >> c;
    return vowelPrefixConversions[c];
}

bool BanglaUtf8::is_vowel (const char c) const {
    return c == 'a' || c == 'A' ||
           c == 'i' || c == 'I' ||
           c == 'u' || c == 'U' ||
           c == 'e' || c == 'o';
}

void BanglaUtf8::convert (std::istream & inputChars) {
    while (inputChars) {
        const char c = inputChars.peek();
        if (inputChars.eof()) {
            break;
        }

        if (isspace(c)) {
            inputChars.get();
            continue;
        }
        else if (is_vowel(c)) {
            BanglaVowel vowel = parse_vowel(inputChars);
        }
        else {
            BanglaLetter letter = parse_letter(inputChars);

            const char c = inputChars.peek();
            BanglaVowel vowelPrefix = BanglaVowel::a;
            if (!inputChars.eof() && is_vowel(c)) {
                vowelPrefix = parse_vowel_prefix(inputChars);
            }
            elems_.emplace_back(BanglaElem(letter, vowelPrefix));
        }
    }
}

void BanglaUtf8::print () const {
    for (auto & elem : elems_) {
        elem.print();
    }
}
