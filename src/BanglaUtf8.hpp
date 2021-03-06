#ifndef BANGLAUTF8_HPP
#define BANGLAUTF8_HPP

#include <iostream>
#include <vector>

enum class BanglaConsonant {
    a, A, i, I, u, U,
    e, oi, o, ou,
    k, K, g, G, ng,
    ch, Ch, j, J, NG,
    T, Th, D, Dh, N,
    t, th, d, dh, n,
    p, f, b, bh, m,
    y, Y, r, l, sh, Sh, s, h,
    rh, Rh
};

enum class BanglaVowel {
    a, A, i, I, u, U,
    e, oi, o, ou
};

enum class BanglaSymbol {
    cbindu, bisarga, anuswar
};

class BanglaUtf8Elem {
public:
    BanglaUtf8Elem() = default;
    virtual ~BanglaUtf8Elem() = default;

    virtual void print (std::ostream & outputStream) const {
        outputStream << "";
    }
};

class BanglaElem : public BanglaUtf8Elem {
public:
    BanglaElem(const std::vector<BanglaConsonant>& letters, BanglaVowel vowelPrefix) :
        letters_(letters),
        vowelPrefix_(vowelPrefix) {}
    ~BanglaElem() = default;

    void print (std::ostream & outputStream) const override;
private:
    const char * get_utf8_string (BanglaConsonant letter) const;
    const char * get_utf8_string (BanglaVowel vowel) const;

    std::vector<BanglaConsonant> letters_;
    BanglaVowel vowelPrefix_;
};

class BanglaVowelElem : public BanglaUtf8Elem {
public:
    BanglaVowelElem(BanglaVowel vowel) : vowel_(vowel) {}
    ~BanglaVowelElem() = default;

    void print (std::ostream & outputStream) const override;
private:
    const char * get_utf8_string (BanglaVowel vowel) const;

    BanglaVowel vowel_;
};

class BanglaSymbolElem : public BanglaUtf8Elem {
public:
    BanglaSymbolElem(BanglaSymbol symbol) : symbol_(symbol) {}
    ~BanglaSymbolElem() = default;

    void print (std::ostream & outputStream) const override;
private:
    const char * get_utf8_string (BanglaSymbol symbol) const;

    BanglaSymbol symbol_;
};

class Utf8Character : public BanglaUtf8Elem {
public:
    Utf8Character(char c) : c_(c) {}
    ~Utf8Character() = default;

    void print (std::ostream & outputStream) const override {
        outputStream << c_;
    }

private:
    char c_;
};

class BanglaUtf8 {
public:
    BanglaUtf8() : elems_() {}
    ~BanglaUtf8();

    void convert (std::istream & inputChars);
    void print (std::ostream & outputStream) const;
    void clear ();
private:
    BanglaVowel parse_vowel(std::istream & inputChars) const;
    BanglaSymbol parse_symbol(std::istream & inputChars) const;
    bool is_symbol (char c) const;
    std::vector<BanglaUtf8Elem *> elems_;
};

#endif
