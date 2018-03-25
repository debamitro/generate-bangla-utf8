#ifndef BANGLAUTF8_HPP
#define BANGLAUTF8_HPP

#include <iostream>
#include <vector>

enum class BanglaLetter {
    a, A, i, I, u, U,
    e, oi, o, ou,
    k, K, g, G, ng,
    ch, Ch, j, J, NG,
    T, Th, D, Dh, N,
    t, th, d, dh, n,
    p, f, b, bh, m
};

enum class BanglaVowel {
    a, A, i, I, u, U,
    e, oi, o, ou
};

class BanglaElem {
public:
    BanglaElem(BanglaLetter letter, BanglaVowel vowelPrefix) :
        letter_(letter),
        vowelPrefix_(vowelPrefix) {}
    ~BanglaElem() = default;

    void print (std::ostream & outputStream) const;
private:
    BanglaLetter letter_;
    BanglaVowel vowelPrefix_;
};

class BanglaUtf8 {
public:
    BanglaUtf8() : elems_() {}
    ~BanglaUtf8() = default;

    void convert (std::istream & inputChars);
    void print (std::ostream & outputStream) const;
private:
    BanglaVowel parse_vowel(std::istream & inputChars) const;
    BanglaLetter parse_letter(std::istream & inputChars) const;
    BanglaVowel parse_vowel_prefix(std::istream & inputChars) const;
    bool is_vowel (char c) const;
    std::vector<BanglaElem> elems_;
};

#endif
