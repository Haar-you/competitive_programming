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

template <typename T> ostream& operator<<(ostream &os, vector<T> &v){os << "{";ITR(i,v){if(i!=v.begin())os << ","; os << *i;}os << "}"; return os;}
template <typename T, typename U> ostream& operator<<(ostream& os, pair<T,U> &p){os << "(" << p.first << "," << p.second << ")"; return os;}

template <typename T> T& chmin(T &a, const T &b){return a = min(a,b);}
template <typename T> T& chmax(T &a, const T &b){return a = max(a,b);}

LLI dp[1<<16];
bool visit[1<<16];

LLI score[1<<16];

LLI rec(vector<vector<int>> &a, int p){
  if(visit[p]) return dp[p];
  visit[p] = true;

  for(int t=p; ; t=(t-1)&p){
    chmax(dp[p], rec(a,t)+score[p^t]);
    if(t==0) break;
  }
  
  return dp[p];
}

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  int N; cin >> N;
  vector<vector<int>> a(N, vector<int>(N)); cin >> a;

  REP(i,1<<N){
    if(__builtin_popcount(i) == 0) continue;
    
    REP(j,N){
      if((i>>j) & 1) continue;
      LLI t = score[i];
      REP(k,N) if(((i>>k) & 1) && j!=k) t += a[j][k];
      score[i | (1<<j)] = t;
    }
  }

  int p = 0;
  REP(i,N) p |= (1<<i);

  cout << rec(a, p) << endl;
  
  return 0;
}
