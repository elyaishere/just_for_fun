/*
    Derivative of the polynomial. A polynomial can be large, but only with non-negative integer degrees and integer coefficients.
    The output must be without spaces and in descending order of degrees, although the input may not satisfy this rule.
    Also, a polynomial with untranslated terms can be entered.
*/
#include <iostream>
#include <string>
#include <map>
#include <cctype>
#include <cassert>

using namespace std;

std::string itos(unsigned int i) { // unsigned integer to string;
    std::string s;
    do {
        auto t = i % 10;
        s.push_back(t + '0');
        i /= 10;
    } while (i >0);
    return std::string(s.rbegin(), s.rend());
}

std::string derivative(std::string polynomial) {
    map<int, int> monom; // monom[degree] = coef
    std::string res;
    bool sign = false;
    bool deg = false;
    int a = 0, b = 0; // a ~ coef, b ~ degree
    for (auto i: polynomial) {
        if (isdigit(i)) {
            if (deg) { // parsing degree
                b = 10*b + (i - '0');
                continue;
            }
            else { // parsing coef
                a = 10*a + (i - '0');
                continue;
            }
        }
        if (i == 'x') {
            if (a == 0) a = 1; // for "+ x ..." or "- x..."
            b = 1; // for "...x +" or "...x -"
            deg = true;
            continue;
        }
        if (i == '^') {
            b = 0; 
            continue;
        }
        if (i == '-' || i == '+') {
            if (b > 0) { // otherwise doesn't matter
                a *= b;
                if (sign) a = -a;
                --b;
                if (monom.find(b) != monom.end()) {
                    monom[b] += a;
                } else monom[b] = a;
            }
            sign = (i == '-');
            a = 0, b = 0; // initial conditions
            deg = false;
        }
    }
    if (b > 0) { // last member
        a *= b;
        if (sign) a = -a;
        --b;
        if (monom.find(b) != monom.end()) {
            monom[b] += a;
        } else monom[b] = a;
    }

    for(auto i = monom.rbegin(); i != monom.rend(); ++i) {
        if (i->second == 0) continue; // result coef = 0 -> skip
        if (i->second < 0) res += '-', i->second = -(i->second);
        else res += '+';
        res += itos(i->second);
        if (i->first > 0) {
            res += "*x";
            if (i->first > 1) {
                res += '^';
                res += itos(i->first);
            }
        }
    }
    if (res.empty()) return "0"; // for input like "12"
    if (res[0] == '+') res.erase(res.begin()); // if "+ x ..."
    return res;  
}

int main (int argc, char** argv) { // some tests
    assert(derivative("x^2+x") == "2*x+1");
    assert(derivative("2*x^100+100*x^2") == "200*x^99+200*x");
    assert(derivative("x^10000+x+1") == "10000*x^9999+1");
    assert(derivative("-x^2-x^3") == "-3*x^2-2*x");
    assert(derivative("x+x+x+x+x+x+x+x+x+x") == "10");
    return 0;
}