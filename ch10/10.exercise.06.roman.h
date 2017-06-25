// 10.exercise.06.roman.h
//
// COMMENTS 
//  See details on 10.exercise.06.md

#include "std_lib_facilities.h"

#ifndef ROMAN_H
#define ROMAN_H

namespace Roman {

constexpr size_t lut_end{100};
constexpr int max{4999};    // max int representable with implemented notation
constexpr int min{1};       // min int

class Not_a_particle { };   // Exception when get_particle or lut_idx doesn't
                            // found a particle
class Not_roman { };        // Exception when Roman_int initialized with
                            // value out of [min, max]

struct lut_row {
    string particle;    // particle of Roman number, p.e. M, XL, V or I
    int value;          // associated decimal value
    size_t next;        // next particle to look ahead after this particle
};

class Roman_int {
public:
    Roman_int(string s);    // Initialize with a Roman numeral
    Roman_int(int a);       // Initialize with an int

    string value() const;   // return a string with the Roman numeral
    int as_int() const { return m_value; }  // return the int value
private:
    int m_value;
};

size_t lut_idx(string& particle, size_t start);

string get_particle(istream& is, size_t start);
int parse_roman(istream& is);
string compose_roman(int a);

ostream& operator<<(ostream& os, const Roman_int& rhs);
istream& operator>>(istream& is, Roman_int& rhs);

int parse_roman(istream& is);
} // namespace Roman

#endif
