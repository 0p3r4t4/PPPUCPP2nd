// 10.exercise.06.roman.cpp

#include "std_lib_facilities.h"
#include "10.exercise.06.roman.h"

namespace Roman {

vector<lut_row> lut = {     // Look up table to process Roman int in and out
    {"M",   1000,   1},
    {"M",   1000,   2},
    {"M",   1000,   3},
    {"M",   1000,   4},
    {"CM",  900,    11},
    {"D",   500,    7},
    {"CD",  400,    11},
    {"C",   100,    8},
    {"C",   100,    9},
    {"C",   100,    10},
    {"C",   100,    11},
    {"XC",  90,     18},
    {"L",   50,     14},
    {"XL",  40,     18},
    {"X",   10,     15},
    {"X",   10,     16},
    {"X",   10,     17},
    {"X",   10,     18},
    {"IX",  9,      25},
    {"V",   5,      21},
    {"IV",  4,      25},
    {"I",   1,      22},
    {"I",   1,      23},
    {"I",   1,      24},
    {"I",   1,      25},
    {"E",   0,      lut_end}
};

const size_t lut_size{lut.size()};

Roman_int::Roman_int(string s) : m_value{0}
{
    stringstream ss{s};
    // try-catch??
    m_value = parse_roman(ss);
}

Roman_int::Roman_int(int a) : m_value{a} { };

string Roman_int::value() const
{
    string s{compose_roman(m_value)};
    return s;
}

size_t lut_idx(string& particle, size_t start)
{
    for (size_t i = start; i < lut_size; ++i)
        if (lut[i].particle == particle) return i;
    throw Not_a_particle{};
}

string get_particle(istream& is, size_t start)
{
    char first, second;
    string particle;

    // Read two chars and compose a particle, taking account of EOF
    is >> first;
    if (is.eof()) return "E";       // no more to read, use "E" as fake end
    is >> second;
    if (is.eof()){
        is.clear();                 // backtrack the out of bounds read
        particle = first;           // only one symbol remaining
        try {
            lut_idx(particle, start);   // throws Not_a_particle  
        }
        catch (Not_a_particle& e) {
            is.putback(first);      // rollback read char from is
            throw;                  // rethrow to caller
        }
    }
    else {
        particle = first + second;
        try {
            lut_idx(particle, start);
        }
        catch (Not_a_particle& e) {
            is.putback(second);     // rollback second read char from is
            particle = first;
            try {
                lut_idx(particle, start);
            }
            catch (Not_a_particle& e) {
                is.putback(first);  // rollback first read char from is
                throw;              // rethrow to caller
            }
        }
    }

    return particle;
}

int parse_roman(istream& is)
{
    int r{0};
    size_t idx{0};

    while (idx != lut_end) {
        string particle = get_particle(is, idx);
        idx = lut_idx(particle, idx);
        r += lut[idx].value;
        idx = lut[idx].next;
    }

    return r;
}

string compose_roman(int a)
{
    string s{""};
    return s;
}

ostream& operator<<(ostream& os, const Roman_int& rhs)
{
    os << rhs.value();
    return os;
}

istream& operator>>(istream& is, Roman_int& rhs)
{
    // try-catch??
    rhs = Roman_int{parse_roman(is)};
    return is;
}

} // namespace Roman
