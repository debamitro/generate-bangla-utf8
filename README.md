# generate-bangla-utf8

This is a translator from Bangla typed using Roman characters to utf8-encoded Unicode.

## How to build

```
make
```

There is a self-checking test which can be built and run using

```
make tests
```

## Input format

The input format is described in doc/input_format.md

## Examples

Input  : Ashbiner mAjhAmAjhi uThila bAjanA bAji

Output : আশ্বিনের মাঝামাঝি উঠিল বাজনা বাজি

Input: hu^ko mukho hyA;lA bArhi tAr bA;lA

Output: হুঁকো মুখো হ্যাংলা বাড়ি তার বাংলা
