// 10.exercise.06.roman.cpp
//
// COMMENTS 
//  See details on 10.exercise.06.md

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
    stringstream ss{s};         // to be able to reuse parse_roman()
    m_value = parse_roman(ss);  // could throw Not_roman

    string dummy;
    ss >> dummy;
    if (dummy.size() != 0)      // s is not totally consumed, so error
        throw Not_roman{};
}

Roman_int::Roman_int(int a) : m_value{a}
{
    if (m_value < min || m_value > max) throw Not_roman{};
};

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
    first = is.get();
    if (is.eof() || isspace(first)) return "E";  // no more to read,
                                                 // use "E" as fake end
    particle = first;       // examine at least the first character
    second = is.get();

    if (is.eof()){
        is.clear();                 // backtrack the out of bounds read
        try {
            lut_idx(particle, start);   // throws Not_a_particle  
        }
        catch (Not_a_particle& e) {
            is.putback(first);      // rollback read char from is
            throw;                  // rethrow to caller
        }
    }
    else {
        particle += second;
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
    int r{0};       // accumulator
    size_t idx{0};  // index to begin the search of a particle in the LUT

    while (idx != lut_end) {
        try {
            string particle = get_particle(is, idx);
            idx = lut_idx(particle, idx);
            r += lut[idx].value;
            idx = lut[idx].next;
        }
        catch (Not_a_particle& e) {
            // No particle has been parsed.
            if (r == 0) throw Not_roman{};
            break;  // return the roman parsed so far
        }
    }

    return r;
}

string compose_roman(int a)
// Returns a string with the Roman numeral for a
// Precondition: a msut be representable with a Roman numeral
{
    if (a < min || a > max) throw Not_roman{};

    string s{""};
    size_t idx{0};

    while (a != 0) {
        if (a >= lut[idx].value) {    // Test if m_value can hold it
            s += lut[idx].particle;
            a -= lut[idx].value;
        }
        ++idx;   // next particle
    }

    return s;
}

ostream& operator<<(ostream& os, const Roman_int& rhs)
{
    os << rhs.value();
    return os;
}

istream& operator>>(istream& is, Roman_int& rhs)
{
    try {
        rhs = Roman_int{parse_roman(is)};
    }
    catch (Not_roman& e) {   // on error, just set failbit on istream
        is.clear(ios_base::failbit);
    }
    return is;
}

} // namespace Roman
