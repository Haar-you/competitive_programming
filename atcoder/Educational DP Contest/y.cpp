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
#ifdef DEBUG
#include <boost/core/demangle.hpp>
#define dump(x) cerr << "L" << __LINE__ << ": in " << __PRETTY_FUNCTION__ << " \e[32;1m" << boost::core::demangle(typeid(x).name()) << "\e[37m" << " " << (#x) << " = " << (x) << "\e[m" << endl;
#else
#define dump(x)
#endif
using namespace std;
template <typename T> using V = vector<T>;
template <typename T, typename U> using P = pair<T,U>;
template <typename I> void join(ostream &ost, I s, I t, string d=" "){for(auto i=s; i!=t; ++i){if(i!=s)ost<<d; ost<<*i;}ost<<endl;}
template <typename T> istream& operator>>(istream &is, vector<T> &v){for(auto &a : v) is >> a; return is;}
template <typename T, typename U> istream& operator>>(istream &is, pair<T,U> &p){is >> p.first >> p.second; return is;}

template <typename T> ostream& operator<<(ostream &os, const vector<T> &v){os << "{";ITR(i,v){if(i!=v.begin())os << ","; os << *i;}os << "}"; return os;}
template <typename T, typename U> ostream& operator<<(ostream& os, const pair<T,U> &p){os << "(" << p.first << "," << p.second << ")"; return os;}

template <typename T> T& chmin(T &a, const T &b){return a = min(a,b);}
template <typename T> T& chmax(T &a, const T &b){return a = max(a,b);}

template <typename T> LLI power(T n, T p, T m){if(p==0) return 1LL; if(p==1) return n; LLI k = power(n, p/2, m); return ((k*k)%m*(p%2?n:1))%m;}
template <typename T> LLI mod_inv(T n, T p){return power(n,p-2,p);}

template <LLI mod> class MyCombination{
public:
  vector<LLI> facto = {1};
  vector<LLI> ifacto = {1};

  LLI factorial(int i){
    if(i < 0) throw exception();
    if(facto.size() <= i) facto.resize(i+1, -1);
    if(i == 0) return facto[0] = 1;
    int j = i;
    for(;j>=0;--j) if(facto[j] != -1) break;
    for(int k=j+1; k<=i; ++k) (facto[k] = facto[k-1] * k) %= mod;
    return facto[i];
  }

  LLI factorial_inverse(int i){
    if(i < 0) throw exception();
    if(ifacto.size() <= i) ifacto.resize(i+1, -1);
    if(ifacto[i] != -1) return ifacto[i];
    return ifacto[i] = mod_inv(factorial(i), mod);
  }

  LLI P(int n, int k){
    if(n < 0 || k < 0 || n < k) return 0;
    return (factorial(n) * factorial_inverse(n-k)) % mod;
  }

  LLI C(int n, int k){
    if(n < 0 || k < 0 || n < k) return 0;
    return (P(n,k) * factorial_inverse(k)) % mod;
  }

  LLI H(int n, int k){
    return C(n+k-1, n);
  }
};

const LLI mod = 1e9+7;
LLI dp[3100];

MyCombination<mod> com;

LLI f(LLI x, LLI y){
  return com.C(x+y,x);
}


int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  int H,W,N; cin >> H >> W >> N;
  vector<pair<int,int>> walls(N); cin >> walls;
  sort(ALL(walls));

  REP(i,N){
    dp[i] = f(walls[i].fst-1,walls[i].snd-1);

    REP(j,i) ((dp[i] -= (dp[j]*f(walls[i].fst-walls[j].fst, walls[i].snd-walls[j].snd))%mod) += mod) %= mod;
  }

  LLI ans = f(H-1,W-1);
  REP(i,N) ((ans -= (dp[i]*f(H-walls[i].fst, W-walls[i].snd))%mod) += mod) %= mod;

  cout << ans << endl;
  
  return 0;
}
