#include <bits/stdc++.h>
using namespace std;

#define gcd __gcd
template <class T> constexpr T lcm(T m, T n){return m*n/gcd(m,n);}

/*
 * Rational number class
 */

class Rational{
public:
  int64_t nume, deno;
  Rational(): nume(0), deno(1){}
  Rational(int64_t num): nume(num), deno(1){} 
  Rational(int64_t num, int64_t den){
    int64_t g = gcd(num,den);
    nume = num/g;
    deno = den/g;
  }
  Rational& operator+=(const Rational &a);
  Rational& operator-=(const Rational &a);
  Rational& operator*=(const Rational &a);
  Rational& operator/=(const Rational &a);
};

ostream& operator<<(ostream &os, const Rational &r){os << r.nume << "/" << r.deno; return os;}

Rational operator-(const Rational &a){return Rational(-a.nume, a.deno);}

Rational operator+(const Rational &a, const Rational &b){int64_t l = lcm(a.deno,b.deno); return Rational(a.nume*l/a.deno + b.nume*l/b.deno, l);}
Rational operator-(const Rational &a, const Rational &b){int64_t l = lcm(a.deno,b.deno); return Rational(a.nume*l/a.deno - b.nume*l/b.deno, l);}
Rational operator*(const Rational &a, const Rational &b){return Rational(a.nume*b.nume, a.deno*b.deno);}
Rational operator/(const Rational &a, const Rational &b){return Rational(a.nume*b.deno, a.deno*b.nume);}

bool operator==(const Rational &a, const Rational &b){return a.nume == b.nume && a.deno == b.deno;}
bool operator!=(const Rational &a, const Rational &b){return !(a==b);}
bool operator<(const Rational &a, const Rational &b){return a.nume*b.deno < b.nume*a.deno;}
bool operator<=(const Rational &a, const Rational &b){return a.nume*b.deno <= b.nume*a.deno;}
bool operator>(const Rational &a, const Rational &b){return !(a<=b);}
bool operator>=(const Rational &a, const Rational &b){return !(a<b);}

double to_double(const Rational &a){return (double)a.nume/a.deno;}

Rational& Rational::operator+=(const Rational &a){*this = *this+a; return *this;}
Rational& Rational::operator-=(const Rational &a){*this = *this-a; return *this;}
Rational& Rational::operator*=(const Rational &a){*this = *this*a; return *this;}
Rational& Rational::operator/=(const Rational &a){*this = *this/a; return *this;}

Rational abs(const Rational &a){return Rational(abs(a.nume), abs(a.deno));}



int main(){
  
}
