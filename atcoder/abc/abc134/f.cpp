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

const LLI mod = 1e9+7;

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

template <uint32_t M> istream& operator>>(istream &is, ModInt<M> &a){is >> a.val; return is;}
template <uint32_t M> ostream& operator<<(ostream &os, const ModInt<M> &a){ os << a.val; return os;}

template <uint32_t M> ModInt<M> operator+(int64_t a, const ModInt<M> &b){return ModInt<M>(ModInt<M>(a)+b.val);}
template <uint32_t M> ModInt<M> operator-(int64_t a, const ModInt<M> &b){return ModInt<M>(ModInt<M>(a)-b.val);}
template <uint32_t M> ModInt<M> operator*(int64_t a, const ModInt<M> &b){return ModInt<M>(ModInt<M>(a)*b.val);}
template <uint32_t M> ModInt<M> operator/(int64_t a, const ModInt<M> &b){return ModInt<M>(ModInt<M>(a)/b.val);}

using mint = ModInt<mod>;

mint dp[60][60][3000];
bool used[60][60][3000];

mint rec(int i, int j, int k){
  if(i==0 and j==0 and k==0) return dp[0][0][0] = 1;
  if(i<0 or j<0 or k<0) return 0;
  
  if(used[i][j][k]) return dp[i][j][k];
  used[i][j][k] = true;

  dp[i][j][k] = (2*j+1)*rec(i-1,j,k-2*j) + (j+1)*(j+1)*rec(i-1,j+1,k-2*j) + rec(i-1,j-1,k-2*j);
  return dp[i][j][k];
}


int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  int N,K;
  while(cin >> N >> K){

    fill_array(dp, 0);
    fill_array(used, false);

    mint ans = rec(N,0,K);
    cout << ans << endl;
  }
  
  return 0;
}
