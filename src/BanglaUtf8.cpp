#include "BanglaUtf8.hpp"
#include <iostream>
#include <unordered_map>
#include <vector>
#include <ctype.h>

static const std::unordered_map<BanglaConsonant, const char *> LetterMapping = {
    { BanglaConsonant::k, u8"\u0995"},
    { BanglaConsonant::K, u8"\u0996"},
    { BanglaConsonant::g, u8"\u0997"},
    { BanglaConsonant::G, u8"\u0998"},
    { BanglaConsonant::ng, u8"\u0999"},
    { BanglaConsonant::ch, u8"\u099A"},
    { BanglaConsonant::Ch, u8"\u099B"},
    { BanglaConsonant::j, u8"\u099C"},
    { BanglaConsonant::J, u8"\u099D"},
    { BanglaConsonant::NG, u8"\u099E"},
    { BanglaConsonant::T, u8"\u099F"},
    { BanglaConsonant::Th, u8"\u09A0"},
    { BanglaConsonant::D, u8"\u09A1"},
    { BanglaConsonant::Dh, u8"\u09A2"},
    { BanglaConsonant::N, u8"\u09A3"},
    { BanglaConsonant::t, u8"\u09A4"},
    { BanglaConsonant::th, u8"\u09A5"},
    { BanglaConsonant::d, u8"\u09A6"},
    { BanglaConsonant::dh, u8"\u09A7"},
    { BanglaConsonant::n, u8"\u09A8"},
    { BanglaConsonant::p, u8"\u09AA"},
    { BanglaConsonant::f, u8"\u09AB"},
    { BanglaConsonant::b, u8"\u09AC"},
    { BanglaConsonant::bh, u8"\u09AD"},
    { BanglaConsonant::m, u8"\u09AE"},
    { BanglaConsonant::y, u8"\u09AF"},
    { BanglaConsonant::r, u8"\u09B0"},
    { BanglaConsonant::l, u8"\u09B2"},
    { BanglaConsonant::sh, u8"\u09B6"},
    { BanglaConsonant::Sh, u8"\u09B7"},
    { BanglaConsonant::s, u8"\u09B8"},
    { BanglaConsonant::h, u8"\u09B9"},
    { BanglaConsonant::rh, u8"\u09DC"},
    { BanglaConsonant::Rh, u8"\u09DD"}
};

static const std::unordered_map<BanglaVowel, const char *> VowelMapping = {
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

static const std::unordered_map<BanglaVowel, const char *> VowelprefixMapping = {
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

const char * BanglaElem::get_string (const BanglaConsonant letter) const {
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

static const std::unordered_map<char, BanglaVowel> vowelConversions = {
    {'a', BanglaVowel::a},
    {'A', BanglaVowel::A},
    {'i', BanglaVowel::i},
    {'I', BanglaVowel::I},
    {'u', BanglaVowel::u},
    {'U', BanglaVowel::U},
    {'e', BanglaVowel::e},
    {'o', BanglaVowel::o}
};

static const std::unordered_map<char, BanglaConsonant> letterConversions = {
    {'k', BanglaConsonant::k},
    {'K', BanglaConsonant::K},
    {'g', BanglaConsonant::g},
    {'G', BanglaConsonant::G},
    {'c', BanglaConsonant::ch},
    {'C', BanglaConsonant::Ch},
    {'j', BanglaConsonant::j},
    {'J', BanglaConsonant::J},
    {'T', BanglaConsonant::T},
    {'D', BanglaConsonant::D},
    {'N', BanglaConsonant::N},
    {'t', BanglaConsonant::t},
    {'d', BanglaConsonant::d},
    {'n', BanglaConsonant::n},
    {'p', BanglaConsonant::p},
    {'f', BanglaConsonant::f},
    {'b', BanglaConsonant::b},
    {'m', BanglaConsonant::m},
    {'y', BanglaConsonant::y},
    {'r', BanglaConsonant::r},
    {'l', BanglaConsonant::l},
    {'s', BanglaConsonant::s},
    {'h', BanglaConsonant::h}
};

static const std::unordered_map<std::string, BanglaConsonant> twoLetterConversions = {
    {"kh", BanglaConsonant::K},
    {"gh", BanglaConsonant::G},
    {"ch", BanglaConsonant::ch},
    {"Ch", BanglaConsonant::Ch},
    {"Th", BanglaConsonant::Th},
    {"Dh", BanglaConsonant::Dh},
    {"th", BanglaConsonant::th},
    {"dh", BanglaConsonant::dh},
    {"bh", BanglaConsonant::bh},
    {"sh", BanglaConsonant::sh},
    {"Sh", BanglaConsonant::Sh},
    {"rh", BanglaConsonant::rh},
    {"Rh", BanglaConsonant::Rh},
    {"ng", BanglaConsonant::ng},
    {"NG", BanglaConsonant::NG}
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

    auto itr = vowelConversions.find(c);
    if (itr != vowelConversions.end()) {
        return itr->second;
    }
    else {
        std::cout << "Couldn't parse vowel " << c << "\n";
        std::exit(1);
    }
}

std::vector<BanglaConsonant> BanglaUtf8::parse_consonants(std::istream & inputChars) const {
    std::vector<BanglaConsonant> parsedLetters;
    std::string letters = "";
    while (inputChars) {
        char c;
        inputChars.get(c);
        if (isspace(c) || is_vowel(c)) {
            inputChars.unget();
            break;
        }

        letters += c;

        BanglaConsonant parsedLetter;
        auto itr = letterConversions.find(c);
        if (itr != letterConversions.end()) {
            parsedLetter = itr->second;
        }
        else {
            std::cout << "Couldn't parse consonant " << c << "\n";
            std::exit(1);
        }

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
            std::vector<BanglaConsonant> letters = parse_consonants(inputChars);

            const char c = inputChars.peek();
            BanglaVowel vowelPrefix = BanglaVowel::a;
            if (!inputChars.eof() && is_vowel(c)) {
                vowelPrefix = parse_vowel(inputChars);
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
