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
#define sz(v) ((LLI)(v).size())

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

LLI power(LLI n, LLI p, LLI m){
  LLI ret = 1;
  while(p>0){
    if(p&1) (ret *= n) %= m;
    (n *= n) %= m;
    p /= 2;
  }
  return ret;
}

LLI mod_inv(LLI n, LLI p){return power(n,p-2,p);}

// 組み合わせ関連の前計算用クラス
template <LLI MOD> class Combination{
public:
  static vector<LLI> facto;
  static vector<LLI> ifacto;

  static void init(int N){
    facto.assign(N+1, 1);
    ifacto.assign(N+1, 1);

    FORE(i,1,N){
      (facto[i] = facto[i-1] * i) %= MOD;
    }

    ifacto[N] = mod_inv(facto[N],MOD);

    REV(i,N-1,0){
      ifacto[i] = ifacto[i+1] * (i+1) % MOD;
    }
  }

  static LLI factorial(LLI i){
    assert(i < facto.size());
    return facto[i];
  }
  
  static LLI factorial_inverse(LLI i){
    assert(i < ifacto.size());
    return ifacto[i];
  }

  static LLI P(LLI n, LLI k);
  static LLI C(LLI n, LLI k);
  static LLI H(LLI n, LLI k);
  static LLI stirling_number(LLI n, LLI k);
  static LLI bell_number(LLI n, LLI k);
  static vector<LLI> montmort_number(int n);
};

template <LLI MOD> vector<LLI> Combination<MOD>::facto = vector<LLI>();
template <LLI MOD> vector<LLI> Combination<MOD>::ifacto = vector<LLI>();

template <LLI MOD> LLI Combination<MOD>::H(LLI n, LLI k){
  if(n == 0 and k == 0) return 1;
  return C(n+k-1, k);
}

template <LLI MOD> LLI Combination<MOD>::C(LLI n, LLI k){
  if(n < k or n < 0 or k < 0) return 0;
  return P(n,k) * factorial_inverse(k) % MOD;
}

template <LLI MOD> LLI Combination<MOD>::P(LLI n, LLI k){
  if(n < k or n < 0 or k < 0) return 0;
  return factorial(n) * factorial_inverse(n-k) % MOD;
}


int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  Combination<mod>::init(1000000);

  int N,K;
  while(cin >> N >> K){
    FORE(i,1,K){
      LLI x = Combination<mod>::C(K-1,i-1);      
      LLI y = Combination<mod>::H(i+1,N-K-(i-1));

      LLI ans = x*y%mod;
      cout << ans << endl;
    }
  }
  
  return 0;
}
