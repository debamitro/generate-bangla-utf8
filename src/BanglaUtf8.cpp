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
    { BanglaLetter::m, u8"\u09AE"},
    { BanglaLetter::y, u8"\u09AF"},
    { BanglaLetter::r, u8"\u09B0"}
};

static std::unordered_map<BanglaVowel, const char *> VowelMapping = {
    { BanglaVowel::a, u8"\u0985"},
    { BanglaVowel::A, u8"\u0986"},
    { BanglaVowel::i, u8"\u0987"},
    { BanglaVowel::I, u8"\u0988"},
    { BanglaVowel::u, u8"\u0989"},
    { BanglaVowel::U, u8"\u098A"},
    { BanglaVowel::e, u8"\u098F"},
    { BanglaVowel::oi, u8"\u0990"},
    { BanglaVowel::o, u8"\u0993"},
    { BanglaVowel::ou, u8"\u0994"}
};

static std::unordered_map<BanglaVowel, const char *> VowelprefixMapping = {
    { BanglaVowel::a, ""},
    { BanglaVowel::A, u8"\u09BE"},
    { BanglaVowel::i, u8"\u09BF"},
    { BanglaVowel::I, u8"\u09C0"},
    { BanglaVowel::u, u8"\u09C1"},
    { BanglaVowel::U, u8"\u09C2"},
    { BanglaVowel::e, u8"\u09C7"},
    { BanglaVowel::oi, u8"\u09C8"},
    { BanglaVowel::o, u8"\u09CB"},
    { BanglaVowel::ou, u8"\u09CC"}
};

const char * BanglaElem::get_string (const BanglaLetter letter) const {
    auto itr = LetterMapping.find(letter);
    if (itr != LetterMapping.end()) {
        return itr->second;
    }

    return "";
}

const char * BanglaElem::get_string (const BanglaVowel vowel) const {
    auto itr = VowelprefixMapping.find(vowel);
    if (itr != VowelprefixMapping.end()) {
        return itr->second;
    }

    return "";
}

void BanglaElem::print(std::ostream & outputStream) const {
    if (letters_.size() > 1) {
        outputStream << get_string(letters_[0]);
        for (unsigned long i = 1; i < letters_.size(); ++i) {
            outputStream << u8"\u09CD"
                         << get_string(letters_[i]);
        }
    }
    else {
        outputStream << get_string(letters_[0]);
    }
    outputStream << get_string(vowelPrefix_);
}

const char * BanglaVowelElem::get_string (const BanglaVowel vowel) const {
    auto itr = VowelMapping.find(vowel);
    if (itr != VowelMapping.end()) {
        return itr->second;
    }

    return "";
}

void BanglaVowelElem::print(std::ostream & outputStream) const {
    outputStream << get_string(vowel_);
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
    {'y', BanglaLetter::y},
    {'r', BanglaLetter::r}
};

static std::unordered_map<std::string, BanglaLetter> twoLetterConversions = {
    {"kh", BanglaLetter::K},
    {"ch", BanglaLetter::ch},
    {"Ch", BanglaLetter::Ch},
    {"Th", BanglaLetter::Th},
    {"Dh", BanglaLetter::Dh},
    {"th", BanglaLetter::th},
    {"dh", BanglaLetter::dh}
};

BanglaUtf8::~BanglaUtf8 () {
    clear();
}

void BanglaUtf8::clear () {
    for (auto & elem : elems_) {
        delete elem;
    }
    elems_.clear();
}

BanglaVowel BanglaUtf8::parse_vowel(std::istream & inputChars) const {
    char c;
    inputChars.get(c);
    return vowelConversions[c];
}

std::vector<BanglaLetter> BanglaUtf8::parse_letters(std::istream & inputChars) const {
    std::vector<BanglaLetter> parsedLetters;
    std::string letters = "";
    while (inputChars) {
        char c;
        inputChars.get(c);
        if (isspace(c) || is_vowel(c)) {
            inputChars.unget();
            break;
        }

        letters += c;

        BanglaLetter parsedLetter = letterConversions[c];

        if (letters.size() > 1) {
            auto itr = twoLetterConversions.find(letters.substr(letters.size()-2,2));
            if (itr != twoLetterConversions.end()) {
                parsedLetter = itr->second;
                letters.pop_back();
                letters.pop_back();
                parsedLetters.pop_back();
            }
        }

        parsedLetters.push_back(parsedLetter);

        if (inputChars.eof()) {
            break;
        }
    }

    return parsedLetters;
}

BanglaVowel BanglaUtf8::parse_vowel_prefix(std::istream & inputChars) const {
    char c;
    inputChars.get(c);
    return vowelConversions[c];
}

bool BanglaUtf8::is_vowel (const char c) const {
    return c == 'a' || c == 'A' ||
           c == 'i' || c == 'I' ||
           c == 'u' || c == 'U' ||
           c == 'e' || c == 'o';
}

void BanglaUtf8::convert (std::istream & inputChars) {
    clear();
    while (inputChars) {
        const char c = inputChars.peek();
        if (inputChars.eof()) {
            break;
        }

        if (isspace(c)) {
            inputChars.get();

            Utf8Character * elem = new Utf8Character(c);
            elems_.push_back(elem);
            continue;
        }
        else if (is_vowel(c)) {
            BanglaVowel vowel = parse_vowel(inputChars);

            BanglaVowelElem * elem = new BanglaVowelElem(vowel);
            elems_.push_back(elem);
        }
        else {
            std::vector<BanglaLetter> letters = parse_letters(inputChars);

            const char c = inputChars.peek();
            BanglaVowel vowelPrefix = BanglaVowel::a;
            if (!inputChars.eof() && is_vowel(c)) {
                vowelPrefix = parse_vowel_prefix(inputChars);
            }

            BanglaElem * elem = new BanglaElem(letters, vowelPrefix);
            elems_.push_back(elem);
        }
    }
}

void BanglaUtf8::print (std::ostream& outputStream) const {
    for (auto & elem : elems_) {
        elem->print(outputStream);
    }
}
