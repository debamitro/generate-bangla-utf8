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
    { BanglaLetter::NG, u8"\u099E"},
    { BanglaLetter::T, u8"\u099F"},
    { BanglaLetter::Th, u8"\u09A0"},
    { BanglaLetter::D, u8"\u09A1"},
    { BanglaLetter::Dh, u8"\u09A2"},
    { BanglaLetter::N, u8"\u09A3"},
    { BanglaLetter::t, u8"\u09A4"},
    { BanglaLetter::th, u8"\u09A5"},
    { BanglaLetter::d, u8"\u09A6"},
    { BanglaLetter::dh, u8"\u09A7"},
    { BanglaLetter::n, u8"\u09A8"},
    { BanglaLetter::p, u8"\u09AA"},
    { BanglaLetter::f, u8"\u09AB"},
    { BanglaLetter::b, u8"\u09AC"},
    { BanglaLetter::bh, u8"\u09AD"},
    { BanglaLetter::m, u8"\u09AE"}
};

static std::unordered_map<BanglaVowel, const char *> VowelprefixMapping = {
    { BanglaVowel::a, ""},
    { BanglaVowel::A, u8"\u09BE"},
    { BanglaVowel::i, u8"\u09BF"},
    { BanglaVowel::I, u8"\u09C0"},
    { BanglaVowel::u, u8"\u09C1"},
    { BanglaVowel::U, u8"\u09C2"}
};

void BanglaElem::print(std::ostream & outputStream) const {
    outputStream << LetterMapping[letter_]
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
    {'G', BanglaLetter::G},
    {'c', BanglaLetter::ch},
    {'C', BanglaLetter::Ch},
    {'j', BanglaLetter::j},
    {'J', BanglaLetter::J},
    {'T', BanglaLetter::T},
    {'D', BanglaLetter::D},
    {'t', BanglaLetter::t},
    {'d', BanglaLetter::d},
    {'p', BanglaLetter::p},
    {'f', BanglaLetter::f},
    {'b', BanglaLetter::b},
    {'m', BanglaLetter::m},
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
    return vowelConversions[c];
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

void BanglaUtf8::print (std::ostream& outputStream) const {
    for (auto & elem : elems_) {
        elem.print(outputStream);
    }
}
