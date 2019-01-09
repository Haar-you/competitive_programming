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

template <typename A, typename B, typename C>
ostream& operator<<(ostream& os, const tuple<A,B,C> &t){
  os << "(" << get<0>(t) << "," << get<1>(t) << "," << get<2>(t) << ")";
  return os;
}

LLI dp[1100][21000];

using tlll = tuple<LLI,LLI,LLI>;

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  int N; cin >> N;
  vector<tlll> a(N);
  REP(i,N) cin >> get<0>(a[i]) >> get<1>(a[i]) >> get<2>(a[i]);

  sort(ALL(a), [](tlll &a, tlll &b){return get<1>(a)+get<0>(a) < get<1>(b)+get<0>(b);});
  
  vector<LLI> w(N),s(N),v(N);
  REP(i,N){
    tie(w[i],s[i],v[i]) = a[i];
  }

  REP(i,N){
    REPE(j,20000){
      chmax(dp[i+1][j], dp[i][j]);
      if(s[i] >= j) chmax(dp[i+1][j+w[i]], dp[i][j]+v[i]);
    }
  }

  LLI ans = 0;
  REPE(i,20000) chmax(ans, dp[N][i]);
  cout << ans << endl;
  
  return 0;
}
