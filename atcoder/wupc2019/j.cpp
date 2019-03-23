#include <bits/stdc++.h>
#define FOR(v, a, b) for(int v = (a); v < (b); ++v)
#define FORE(v, a, b) for(int v = (a); v <= (b); ++v)
#define REP(v, n) FOR(v, 0, n)
#define REPE(v, n) FORE(v, 0, n)
#define REV(v, a, b) for(int v = (a); v >= (b); --v)
#define ALL(x) (x).begin(), (x).end()
#define ITR(it, c) for(auto it = (c).begin(); it != (c).end(); ++it)
#define RITR(it, c) for(auto it = (c).rbegin(); it != (c).rend(); ++it)
#define EXIST(c,x) ((c).find(x) != (c).end())
#define LLI long long int
#define fst first
#define snd second
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
#ifndef M_E
#define M_E 2.71828182845904523536
#endif

#ifdef DEBUG
#include <misc/C++/Debug.cpp>
#else
#define dump(x)
#endif

#define pln(x) cout << (x) << endl
#define gcd __gcd

using namespace std;
template <class T> constexpr T lcm(T m, T n){return m/gcd(m,n)*n;}

template <typename T> using V = vector<T>;
template <typename T, typename U> using P = pair<T,U>;
template <typename I> void join(ostream &ost, I s, I t, string d=" "){for(auto i=s; i!=t; ++i){if(i!=s)ost<<d; ost<<*i;}ost<<endl;}
template <typename T> istream& operator>>(istream &is, vector<T> &v){for(auto &a : v) is >> a; return is;}
template <typename T, typename U> istream& operator>>(istream &is, pair<T,U> &p){is >> p.first >> p.second; return is;}

template <typename T, typename U> T& chmin(T &a, const U &b){return a = (a<=b?a:b);}
template <typename T, typename U> T& chmax(T &a, const U &b){return a = (a>=b?a:b);}
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

template <LLI mod> class Combination{
public:
  vector<LLI> facto = {1};
  vector<LLI> ifacto = {1};

  LLI factorial(LLI i){
    if(i < 0) throw exception();
    if(facto.size() <= i) facto.resize(i+1, -1);
    if(i == 0) return facto[0] = 1;
    LLI j = i;
    for(;j>=0;--j) if(facto[j] != -1) break;
    for(LLI k=j+1; k<=i; ++k) (facto[k] = facto[k-1] * k) %= mod;
    return facto[i];
  }

  LLI factorial_inverse(LLI i){
    if(i < 0) throw exception();
    if(ifacto.size() <= i) ifacto.resize(i+1, -1);
    if(ifacto[i] != -1) return ifacto[i];
    return ifacto[i] = mod_inv(factorial(i), mod);
  }

  LLI P(LLI n, LLI k){
    return (factorial(n) * factorial_inverse(n-k)) % mod;
  }

  LLI C(LLI n, LLI k){
    return (P(n,k) * factorial_inverse(k)) % mod;
  }

  LLI H(LLI n, LLI k){
    return C(n+k-1, n);
  }
};

LLI dp[2100][2100];

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  Combination<mod> com;

  int N,M;
  while(cin >> N >> M){
    vector<int> a(N); cin >> a;

    fill_array(dp, 0);

    dp[0][0] = 1;
    
    REP(i,N){
      REP(j,M){
	REPE(k,a[i]){
	  // ai個の場所からk個を選んで、ai個のボールからk個を選んで配置する順列。
	  LLI t = com.C(a[i],k) * com.P(a[i],k) % mod;
	  (dp[i+1][j+k] += dp[i][j] * t % mod) %= mod;
	}
      }
    }

    // 包除原理により、少なくとも一つのボールと筒の色が一致するような全組み合わせを計算する。
    LLI t = 0;
    FORE(i,1,M){
      LLI s = dp[N][i] * com.factorial(M-i) % mod;
      (t += (s * (i%2 ? 1 : -1) + mod) % mod) %= mod;
    }
    
    LLI ans = 1;

    // 条件を考慮せずにボールを配置する全組み合わせを計算する。
    int k = M;
    REP(i,N){
      (ans *= com.P(k,a[i])) %= mod;
      k -= a[i];
    }

    ((ans -= t) += mod) %= mod;

    // 同色のボールは互いに区別しないのでΠ(ai!)で割る。
    for(auto x : a) (ans *= mod_inv(com.factorial(x),mod)) %= mod;
    
    cout << ans << endl;
  }
  
  return 0;
}
