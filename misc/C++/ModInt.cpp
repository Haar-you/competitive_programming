/*

 */

// mod整数計算
template <uint32_t M> class mod_int_64{
public:
  uint64_t val;
  mod_int_64(): val(0){}
  mod_int_64(int64_t n): val(n%M){}
  mod_int_64(int32_t n): val(n%M){}
  
  const mod_int_64 operator+(const mod_int_64 &a) const {return mod_int_64((val+a.val)%M);}
  const mod_int_64 operator-(const mod_int_64 &a) const {return mod_int_64((val-a.val+M)%M);}
  const mod_int_64 operator*(const mod_int_64 &a) const {return mod_int_64((val*a.val)%M);}
  const mod_int_64 operator/(const mod_int_64 &a) const {return mod_int_64((val*a.mod_inv().val)%M);}
  
  const mod_int_64& operator=(const mod_int_64 &a){val = a.val; return *this;}
  const mod_int_64& operator+=(const mod_int_64 &a){(val += a.val) %= M; return *this;}
  const mod_int_64& operator-=(const mod_int_64 &a){((val -= a.val) += M) %= M; return *this;}
  const mod_int_64& operator*=(const mod_int_64 &a){(val *= a.val) %= M; return *this;}
  const mod_int_64& operator/=(const mod_int_64 &a){(val *= a.mod_inv().val) %= M; return *this;}

  const bool operator==(const mod_int_64 &a) const {return val==a.val;}
  const bool operator!=(const mod_int_64 &a) const {return val!=a.val;}

  const mod_int_64 power(LLI p) const{
    mod_int_64 ret = 1, e = val;
    for(; p; e *= e, p >>= 1) if(p&1) ret *= e;
    return ret;
  }
  
  const mod_int_64 mod_inv() const{
    return power(M-2);
  }
};

template <int M> istream& operator>>(istream &is, mod_int_64<M> &a){is >> a.val; return is;}
template <int M> ostream& operator<<(ostream &os, const mod_int_64<M> &a){ os << a.val; return os;}

