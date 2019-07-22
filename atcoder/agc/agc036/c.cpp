#include <bits/stdc++.h>
#define LLI long long int
#define FOR(v, a, b) for(LLI v = (a); v < (b); ++v)
#define FORE(v, a, b) for(LLI v = (a); v <= (b); ++v)
#define REP(v, n) FOR(v, 0, n)
#define REPE(v, n) FORE(v, 0, n)
#define REV(v, a, b) for(LLI v = (a); v >= (b); --v)
#define ALL(x) (x).begin(), (x).end()
#define RALL(x) (x).rbegin(), (x).rend()
#define ITR(it, c) for(auto it = (c).begin(); it != (c).end(); ++it)
#define RITR(it, c) for(auto it = (c).rbegin(); it != (c).rend(); ++it)
#define EXIST(c,x) ((c).find(x) != (c).end())
#define fst first
#define snd second
#define popcount __builtin_popcount
#define UNIQ(v) (v).erase(unique(ALL(v)), (v).end())
#define bit(i) (1LL<<(i))

#ifdef DEBUG
#include <misc/C++/Debug.cpp>
#else
#define dump(...) ((void)0)
#endif

#define gcd __gcd

using namespace std;
template <class T> constexpr T lcm(T m, T n){return m/gcd(m,n)*n;}

template <typename I> void join(ostream &ost, I s, I t, string d=" "){for(auto i=s; i!=t; ++i){if(i!=s)ost<<d; ost<<*i;}ost<<endl;}
template <typename T> istream& operator>>(istream &is, vector<T> &v){for(auto &a : v) is >> a; return is;}
template <typename T, typename U> istream& operator>>(istream &is, pair<T,U> &p){is >> p.first >> p.second; return is;}

template <typename T, typename U> bool chmin(T &a, const U &b){return (a>b ? a=b, true : false);}
template <typename T, typename U> bool chmax(T &a, const U &b){return (a<b ? a=b, true : false);}
template <typename T, size_t N, typename U> void fill_array(T (&a)[N], const U &v){fill((U*)a, (U*)(a+N), v);}

const LLI mod = 998244353;

template <uint32_t M> class ModInt{
public:
  uint64_t val;
  ModInt(): val(0){}
  ModInt(int64_t n): val(n>=M ? n%M : n){}
  
  constexpr ModInt operator+(const ModInt &a) const {return ModInt((val+a.val)%M);}
  constexpr ModInt operator-(const ModInt &a) const {return ModInt((val-a.val+M)%M);}
  constexpr ModInt operator*(const ModInt &a) const {return ModInt((val*a.val)%M);}
  constexpr ModInt operator/(const ModInt &a) const {return ModInt((val*a.mod_inv().val)%M);}
  
  constexpr ModInt& operator=(const ModInt &a){val = a.val; return *this;}
  constexpr ModInt& operator+=(const ModInt &a){if((val += a.val) >= M) val -= M; return *this;}
  constexpr ModInt& operator-=(const ModInt &a){if(val < a.val) val += M; val -= a.val; return *this;}
  constexpr ModInt& operator*=(const ModInt &a){(val *= a.val) %= M; return *this;}
  constexpr ModInt& operator/=(const ModInt &a){(val *= a.mod_inv().val) %= M; return *this;}

  constexpr bool operator==(const ModInt &a) const {return val==a.val;}
  constexpr bool operator!=(const ModInt &a) const {return val!=a.val;}

  constexpr ModInt power(LLI p) const{
    ModInt ret = 1, e = val;
    for(; p; e *= e, p >>= 1) if(p&1) ret *= e;

    return ret;
  }
  
  constexpr ModInt mod_inv() const{
    int64_t a = val, b = M, u = 1, v = 0;

    while(b){
      int64_t t = a/b;
      a -= t*b; swap(a,b);
      u -= t*v; swap(u,v);
    }
    u %= M;
    if(u < 0) u += M;
    
    return u;
  }
};

template <uint32_t M> ModInt<M> operator+(int64_t a, const ModInt<M> &b){return ModInt<M>(ModInt<M>(a)+b.val);}
template <uint32_t M> ModInt<M> operator-(int64_t a, const ModInt<M> &b){return ModInt<M>(ModInt<M>(a)-b.val);}
template <uint32_t M> ModInt<M> operator*(int64_t a, const ModInt<M> &b){return ModInt<M>(ModInt<M>(a)*b.val);}
template <uint32_t M> ModInt<M> operator/(int64_t a, const ModInt<M> &b){return ModInt<M>(ModInt<M>(a)/b.val);}

template <uint32_t M> istream& operator>>(istream &is, ModInt<M> &a){is >> a.val; return is;}
template <uint32_t M> ostream& operator<<(ostream &os, const ModInt<M> &a){ os << a.val; return os;}

using mint = ModInt<mod>;

/**
 * @attention 使用前にinit関数を呼び出す
 */
template <LLI M> class Combination{
public:  
  static vector<mint> facto;
  static vector<mint> ifacto;

  static void init(int N){
    facto.assign(N+1, 1);
    ifacto.assign(N+1, 1);

    FORE(i,1,N){
      facto[i] = facto[i-1] * i;
    }

    ifacto[N] = 1 / facto[N];

    REV(i,N-1,0){
      ifacto[i] = ifacto[i+1] * (i+1);
    }
  }

  static mint factorial(int i){
    assert(i < (int)facto.size());
    return facto[i];
  }
  
  static mint factorial_inverse(int i){
    assert(i < (int)ifacto.size());
    return ifacto[i];
  }

  static mint P(int n, int k);
  static mint C(int n, int k);
  static mint H(int n, int k);
  static mint stirling_number(LLI n, LLI k);
  static mint bell_number(LLI n, LLI k);
};

template <LLI M> vector<mint> Combination<M>::facto = vector<mint>();
template <LLI M> vector<mint> Combination<M>::ifacto = vector<mint>();

template <LLI M> mint Combination<M>::P(int n, int k){
  if(n < k or n < 0 or k < 0) return 0;
  return factorial(n) * factorial_inverse(n-k);
}

template <LLI M> mint Combination<M>::C(int n, int k){
  if(n < k or n < 0 or k < 0) return 0;
  return P(n,k) * factorial_inverse(k);
}

template <LLI M> mint Combination<M>::H(int n, int k){
  if(n == 0 and k == 0) return 1;
  return C(n+k-1, k);
}

using Com = Combination<mod>;

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  Com::init(2000000);

  int n,m;
  while(cin >> n >> m){
    mint ans = 0;

    REPE(i,m){
      if((3*m-i)%2==0){
        ans += Com::C(n,i) * Com::C((3*m-i)/2+n-1,n-1);
      }
    }

    mint t = 0;

    REPE(i,m){
      if((m-i)%2==0){
        t += Com::C(n,i) * Com::C((m-i)/2+n-1,n-1);
        t -= Com::C(n-1,i) * Com::C((m-i)/2+n-2,n-2);
      }
    }

    t *= n;
    
    ans -= t;

    cout << ans << endl;
  }
  
  return 0;
}
