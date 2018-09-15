#include "BanglaUtf8.hpp"
#include <iostream>
#include <unordered_map>
#include <vector>
#include <ctype.h>

template <class T>
struct int_hash {
    std::size_t operator() (const T& key) const {
        std::hash<int> func;
        return func(static_cast<int>(key));
    }
};

static const std::unordered_map<BanglaConsonant, const char *, int_hash<BanglaConsonant> > consonantToUtf8 = {
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

const char * BanglaElem::get_utf8_string (const BanglaConsonant letter) const {
    auto itr = consonantToUtf8.find(letter);
    if (itr != consonantToUtf8.end()) {
        return itr->second;
    }

    return "";
}

static const std::unordered_map<BanglaVowel, const char *, int_hash<BanglaVowel> > vowelToUtf8 = {
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

const char * BanglaVowelElem::get_utf8_string (const BanglaVowel vowel) const {
    auto itr = vowelToUtf8.find(vowel);
    if (itr != vowelToUtf8.end()) {
        return itr->second;
    }

    return "";
}

static const std::unordered_map<BanglaVowel, const char *, int_hash<BanglaVowel> > vowelprefixToUtf8 = {
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

const char * BanglaElem::get_utf8_string (const BanglaVowel vowel) const {
    auto itr = vowelprefixToUtf8.find(vowel);
    if (itr != vowelprefixToUtf8.end()) {
        return itr->second;
    }

    return "";
}

static const std::unordered_map<BanglaSymbol, const char *, int_hash<BanglaSymbol> > symbolToUtf8 = {
    { BanglaSymbol::cbindu, u8"\u0981"},
    { BanglaSymbol::bisarga, u8"\u0983"},
    { BanglaSymbol::anuswar, u8"\u0982"}
};

const char * BanglaSymbolElem::get_utf8_string (const BanglaSymbol symbol) const {
    auto itr = symbolToUtf8.find(symbol);
    if (itr != symbolToUtf8.end()) {
        return itr->second;
    }

    return "";
}

void BanglaElem::print(std::ostream & outputStream) const {
    outputStream << get_utf8_string(letters_[0]);
    if (letters_.size() > 1) {
        for (unsigned long i = 1; i < letters_.size(); ++i) {
            outputStream << u8"\u09CD"
                         << get_utf8_string(letters_[i]);
        }
    }
    outputStream << get_utf8_string(vowelPrefix_);
}

void BanglaVowelElem::print(std::ostream & outputStream) const {
    outputStream << get_utf8_string(vowel_);
}

void BanglaSymbolElem::print (std::ostream & outputStream) const {
    outputStream << get_utf8_string(symbol_);
}

static const std::unordered_map<char, BanglaVowel> oneLetterToVowel = {
    {'a', BanglaVowel::a},
    {'A', BanglaVowel::A},
    {'i', BanglaVowel::i},
    {'I', BanglaVowel::I},
    {'u', BanglaVowel::u},
    {'U', BanglaVowel::U},
    {'e', BanglaVowel::e},
    {'o', BanglaVowel::o}
};

static const std::unordered_map<char, BanglaConsonant> oneLetterToConsonant = {
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

static const std::unordered_map<std::string, BanglaConsonant> twoLettersToConsonant = {
    {"kh", BanglaConsonant::K},
    {"gh", BanglaConsonant::G},
    {"ch", BanglaConsonant::ch},
    {"Ch", BanglaConsonant::Ch},
    {"jh", BanglaConsonant::J},
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

static const std::unordered_map<std::string, BanglaVowel> twoLettersToVowel = {
    {"aa", BanglaVowel::A},
    {"ee", BanglaVowel::I},
    {"oo", BanglaVowel::U},
    {"oi", BanglaVowel::oi},
    {"ou", BanglaVowel::ou}
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


// TODO - this routine needs to recgnize two-letter vowels (oi and ou)
BanglaVowel BanglaUtf8::parse_vowel(std::istream & inputChars) const {
    char c;
    inputChars.get(c);

    auto itr = oneLetterToVowel.find(c);
    if (itr != oneLetterToVowel.end()) {
        return itr->second;
    }
    else {
        std::cout << "Couldn't parse vowel " << c << "\n";
        std::exit(1);
    }
}

template<typename T>
bool match_one_letter (char c, T& match);
template<typename T>
bool match_two_letters (const std::string & s, T& match);

template <>
bool match_one_letter<> (char c, BanglaConsonant& match) {
    auto itr = oneLetterToConsonant.find(c);
    if (itr != oneLetterToConsonant.end()) {
        match = itr->second;
        return true;
    }

    return false;
}

template <>
bool match_one_letter<> (char c, BanglaVowel& match) {
    auto itr = oneLetterToVowel.find(c);
    if (itr != oneLetterToVowel.end()) {
        match = itr->second;
        return true;
    }

    return false;
}

template <>
bool match_two_letters<> (const std::string & s, BanglaVowel& match) {
    auto itr = twoLettersToVowel.find(s);
    if (itr != twoLettersToVowel.end()) {
        match = itr->second;
        return true;
    }

    return false;
}

template <>
bool match_two_letters<> (const std::string & s, BanglaConsonant& match) {
    auto itr = twoLettersToConsonant.find(s);
    if (itr != twoLettersToConsonant.end()) {
        match = itr->second;
        return true;
    }

    return false;
}

static bool is_vowel (const char c) {
    return c == 'a' || c == 'A' ||
           c == 'i' || c == 'I' ||
           c == 'u' || c == 'U' ||
           c == 'e' || c == 'o';
}

template<typename T>
bool is_valid_character (char c);

template <>
bool is_valid_character<BanglaVowel> (char c) {
    return !isspace(c) && is_vowel(c);
}

template <>
bool is_valid_character<BanglaConsonant> (char c) {
    return !isspace(c) && !is_vowel(c);
}

template<typename T>
std::vector<T> parse_consonant_or_vowel (std::istream& inputChars) {
    std::vector<T> parsedLetters;
    std::string letters = "";
    char c;
    while (inputChars.get(c)) {
        if (!is_valid_character<T>(c)) {
            inputChars.unget();
            break;
        }

        letters += c;

        T parsedLetter;
        if (!match_one_letter(c, parsedLetter)) {
            continue;
        }

        if (letters.size() > 1) {
            if (match_two_letters(letters.substr(letters.size()-2,2), parsedLetter)) {
                letters.pop_back();
                letters.pop_back();
                if (parsedLetters.size() > 0) {
                    parsedLetters.pop_back();
                }
            }
        }

        parsedLetters.push_back(parsedLetter);
    }

    if (parsedLetters.empty()) {
        std::cout << "Couldn't parse consonants/vowels from " << letters << "\n";
        std::exit(1);
    }

    return parsedLetters;
}

BanglaSymbol BanglaUtf8::parse_symbol (std::istream & inputChars) const {
    char c;
    inputChars.get(c);

    if (c == '^') {
        return BanglaSymbol::cbindu;
    }
    else if (c == ':') {
        return BanglaSymbol::bisarga;
    }
    else if (c == ';') {
        return BanglaSymbol::anuswar;
    }
    else {
        std::cout << "Couldn't parse symbol " << c << "\n";
        std::exit(1);
    }
}

bool BanglaUtf8::is_symbol (const char c) const {
    return c == '^' || c == ':' || c == ';';
}

void BanglaUtf8::convert (std::istream & inputChars) {
    clear();
    while (inputChars) {
        const char c = inputChars.peek();
        if (inputChars.eof()) {
            break;
        }

        if (isspace(c)) {
            // Recognize a space character

            inputChars.get();

            Utf8Character * elem = new Utf8Character(c);
            elems_.push_back(elem);
        }
        else if (is_vowel(c)) {
            // Recognize a one-letter or two-letter vowel

            std::vector<BanglaVowel> letters = parse_consonant_or_vowel<BanglaVowel>(inputChars);

            BanglaVowelElem * elem = new BanglaVowelElem(letters[0]);
            elems_.push_back(elem);
        }
        else if (is_symbol(c)) {
            // Recognize a symbol - these are all one-letter

            BanglaSymbol symbol = parse_symbol(inputChars);

            BanglaSymbolElem * elem = new BanglaSymbolElem(symbol);
            elems_.push_back(elem);
        }
        else {
            // Recognize a consonant optionally followed by a vowel
            std::vector<BanglaConsonant> letters = parse_consonant_or_vowel<BanglaConsonant>(inputChars);

            const char c = inputChars.peek();
            BanglaVowel vowelPrefix = BanglaVowel::a;
            if (!inputChars.eof() && is_vowel(c)) {
                std::vector<BanglaVowel> letters = parse_consonant_or_vowel<BanglaVowel>(inputChars);
                vowelPrefix = letters[0];
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
