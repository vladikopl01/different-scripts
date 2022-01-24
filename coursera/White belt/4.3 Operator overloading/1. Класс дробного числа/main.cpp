#include <iostream>
#include <sstream>
#include <vector>
#include <set>
#include <map>
#include <numeric>

class Rational {
private:
    int numer;
    int denom;

public:
    Rational() {
        numer = 0;
        denom = 1;
    }

    Rational(int numerator, int denominator) {
        int gcd = std::gcd(numerator, denominator);
        numer = numerator / gcd;
        denom = denominator / gcd;

        if (denom < 0) {
            numer *= -1;
            denom *= -1;
        }

        if (numer == 0) {
            denom = 1;
        }
    }

    int Numerator() const {
        return numer;
    }

    int Denominator() const {
        return denom;
    }
};

bool operator==(const Rational &lhs, const Rational &rhs) {
    return lhs.Numerator() == rhs.Numerator() &&
        lhs.Denominator() == rhs.Denominator();
}

Rational operator+(const Rational &lhs, const Rational &rhs) {
    return { lhs.Numerator() * rhs.Denominator() + rhs.Numerator() * lhs.Denominator(),
    lhs.Denominator() * rhs.Denominator() };
}

Rational operator-(const Rational &lhs, const Rational &rhs) {
    return { lhs.Numerator() * rhs.Denominator() - rhs.Numerator() * lhs.Denominator(),
    lhs.Denominator() * rhs.Denominator() };
}

Rational operator*(const Rational &lhs, const Rational &rhs) {
    return Rational{
        lhs.Numerator() * rhs.Numerator(),
        lhs.Denominator() * rhs.Denominator()
    };
}

Rational operator/(const Rational &lhs, const Rational &rhs) {
    return lhs * Rational(rhs.Denominator(), rhs.Numerator());
}

std::istream &operator>>(std::istream &is, Rational &in) {
    int n, d;
    char c;
    
    if (is) {
        is >> n >> c >> d;
        if (is && c == '/') {
            in = Rational(n, d);
        }
    }

    return is;
}

std::ostream &operator<<(std::ostream &stream, const Rational &out) {
    return stream << out.Numerator() << '/' << out.Denominator();
}

bool operator<(const Rational &lhs, const Rational &rhs) {
    return (lhs - rhs).Numerator() < 0;
}

int main() {
   
    return 0;
}