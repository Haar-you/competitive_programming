#ifndef COMPILE_TEST
#define COMPILE_TEST
#include "Basic.cpp"
#endif

/*

 */

// mod整数計算
template <int M> class mod_int_64{
public:
  int64_t val;
  mod_int_64(): val(0){}
  mod_int_64(int64_t n): val(n){}
  mod_int_64(int32_t n): val(n){}
  
  const mod_int_64 operator+(const mod_int_64 &a) const {return mod_int_64((val+a.val)%M);}
  const mod_int_64 operator-(const mod_int_64 &a) const {return mod_int_64((val-a.val+M)%M);}
  const mod_int_64 operator*(const mod_int_64 &a) const {return mod_int_64((val*a.val)%M);}
  const mod_int_64 operator/(const mod_int_64 &a) const {return mod_int_64((val*mod_int_64::mod_inv(a))%M);}
  
  const mod_int_64& operator=(const mod_int_64 &a){val = a.val; return *this;}
  const mod_int_64& operator+=(const mod_int_64 &a){(val += a.val) %= M; return *this;}
  const mod_int_64& operator-=(const mod_int_64 &a){((val -= a.val) += M) %= M; return *this;}
  const mod_int_64& operator*=(const mod_int_64 &a){(val *= a.val) %= M; return *this;}
  const mod_int_64& operator/=(const mod_int_64 &a){(val *= mod_int_64::mod_inv(a)) %= M; return *this;}

  const bool operator==(const mod_int_64 &a) const {return val==a.val;}

  static mod_int_64 power(const mod_int_64 &a, const int64_t p){
    if(p == 0) return 1;
    if(p == 1) return a;
    mod_int_64 t = mod_int_64::power(a, p/2);
    return t*t*(p%2?a:1);
  }

  static mod_int_64 mod_inv(const mod_int_64 &a){
    return mod_int_64::power(a,M-2);
  }
};

template <int M> istream& operator>>(istream &is, mod_int_64<M> &a){is >> a.val; return is;}
template <int M> ostream& operator<<(ostream &os, const mod_int_64<M> &a){ os << a.val; return os;}

