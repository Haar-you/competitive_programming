/*

 */

// mod整数計算
template <uint32_t M> class mod_int_64{
public:
  uint64_t val;
  mod_int_64(): val(0){}
  mod_int_64(int64_t n): val(n%M){}
  
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

template <uint32_t M> istream& operator>>(istream &is, mod_int_64<M> &a){is >> a.val; return is;}
template <uint32_t M> ostream& operator<<(ostream &os, const mod_int_64<M> &a){ os << a.val; return os;}

// 実行時mod整数

class runtime_mod_int{
public:
  static uint64_t M;
  
  uint64_t val;
  runtime_mod_int(): val(0){}
  runtime_mod_int(int64_t n): val(n%M){}
  
  const runtime_mod_int operator+(const runtime_mod_int &a) const {return runtime_mod_int((val+a.val)%M);}
  const runtime_mod_int operator-(const runtime_mod_int &a) const {return runtime_mod_int((val-a.val+M)%M);}
  const runtime_mod_int operator*(const runtime_mod_int &a) const {return runtime_mod_int((val*a.val)%M);}
  const runtime_mod_int operator/(const runtime_mod_int &a) const {return runtime_mod_int((val*a.mod_inv().val)%M);}
  
  const runtime_mod_int& operator=(const runtime_mod_int &a){val = a.val; return *this;}
  const runtime_mod_int& operator+=(const runtime_mod_int &a){(val += a.val) %= M; return *this;}
  const runtime_mod_int& operator-=(const runtime_mod_int &a){((val -= a.val) += M) %= M; return *this;}
  const runtime_mod_int& operator*=(const runtime_mod_int &a){(val *= a.val) %= M; return *this;}
  const runtime_mod_int& operator/=(const runtime_mod_int &a){(val *= a.mod_inv().val) %= M; return *this;}

  const bool operator==(const runtime_mod_int &a) const {return val==a.val;}
  const bool operator!=(const runtime_mod_int &a) const {return val!=a.val;}

  const runtime_mod_int power(LLI p) const{
    runtime_mod_int ret = 1, e = val;
    for(; p; e *= e, p >>= 1) if(p&1) ret *= e;
    return ret;
  }
  
  const runtime_mod_int mod_inv() const{
    return power(M-2);
  }
};

uint64_t runtime_mod_int::M;

istream& operator>>(istream &is, runtime_mod_int &a){is >> a.val; return is;}
ostream& operator<<(ostream &os, const runtime_mod_int &a){ os << a.val; return os;}
