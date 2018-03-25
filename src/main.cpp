#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <istream>
#include <sstream>

enum class BanglaLetter {
    a, A, i, I, u, U,
    e, oi, o, ou,
    k, K, g, G, ng,
    ch, Ch, j, J, NG,
    t, th, d, dh, n,
    T, Th, D, Dh, N
};

enum class BanglaVowelPrefix {
    A, i, I, u, U,
    e, oi, o, ou
};

enum class BanglaVowel {
    a, A, i, I, u, U,
    e, oi, o, ou
};

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

static std::unordered_map<BanglaVowelPrefix, const char *> VowelprefixMapping = {
    { BanglaVowelPrefix::A, u8"\u09BE"},
    { BanglaVowelPrefix::i, u8"\u09BF"},
    { BanglaVowelPrefix::I, u8"\u09C0"},
    { BanglaVowelPrefix::u, u8"\u09C1"},
    { BanglaVowelPrefix::U, u8"\u09C2"}
};

class BanglaElem {
public:
    BanglaElem(BanglaLetter letter, BanglaVowelPrefix vowelPrefix) :
        letter_(letter),
        vowelPrefix_(vowelPrefix) {}
    ~BanglaElem() = default;

    void print () const;
private:
    BanglaLetter letter_;
    BanglaVowelPrefix vowelPrefix_;
};

void BanglaElem::print() const {
    std::cout << LetterMapping[letter_]
              << VowelprefixMapping[vowelPrefix_];
}

class EnglishToBangla {
public:
    EnglishToBangla() : elems_() {}
    ~EnglishToBangla() = default;

    void convert (std::istream & inputChars);
    void print () const;
private:
    BanglaVowel parse_vowel(std::istream & inputChars) const;
    BanglaLetter parse_letter(std::istream & inputChars) const;
    BanglaVowelPrefix parse_vowel_prefix(std::istream & inputChars) const;
    bool is_vowel (char c) const;
    std::vector<BanglaElem> elems_;
};

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

static std::unordered_map<char, BanglaVowelPrefix> vowelPrefixConversions = {
    {'A', BanglaVowelPrefix::A},
    {'i', BanglaVowelPrefix::i},
    {'I', BanglaVowelPrefix::I},
    {'u', BanglaVowelPrefix::u},
    {'U', BanglaVowelPrefix::U}
};

BanglaVowel EnglishToBangla::parse_vowel(std::istream & inputChars) const {
    char c;
    inputChars >> c;
    return vowelConversions[c];
}

BanglaLetter EnglishToBangla::parse_letter(std::istream & inputChars) const {
    char c;
    inputChars >> c;
    return letterConversions[c];
}

BanglaVowelPrefix EnglishToBangla::parse_vowel_prefix(std::istream & inputChars) const {
    char c;
    inputChars >> c;
    return vowelPrefixConversions[c];
}

bool EnglishToBangla::is_vowel (const char c) const {
    return c == 'a' || c == 'A' ||
           c == 'i' || c == 'I' ||
           c == 'u' || c == 'U' ||
           c == 'e' || c == 'o';
}

void EnglishToBangla::convert (std::istream & inputChars) {
    while (inputChars) {
        const char c = inputChars.peek();
        if (inputChars.eof()) {
            break;
        }

        if (is_vowel(c)) {
            BanglaVowel vowel = parse_vowel(inputChars);
        }
        else {
            BanglaLetter letter = parse_letter(inputChars);
            BanglaVowelPrefix vowelPrefix = parse_vowel_prefix(inputChars);
            elems_.emplace_back(BanglaElem(letter, vowelPrefix));
        }
    }
}

void EnglishToBangla::print () const {
    for (auto & elem : elems_) {
        elem.print();
    }
}

int main () {
    EnglishToBangla converter;
    std::string input = "kAku";
    std::stringstream inputChars(input);
    converter.convert(inputChars);
    converter.print();
    std::cout << "\n";
    return 0;
}
