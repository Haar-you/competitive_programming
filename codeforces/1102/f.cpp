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

int dp[1<<16][16];
int edge1[16][16];
int edge2[16][16];

int memo[16][16];
int n,m;

int func(int start){
  REP(i,1<<16) REP(j,16) dp[i][j] = 0;

  dp[1<<start][start] = 1e9;

  REP(i,1<<n){
    REP(j,n){
      if(__builtin_popcount(i) == n-1){
	int end = __builtin_ffs(~i) - 1;
	chmax(memo[start][end], min(dp[i][j],edge1[j][end]));
      }else{
	REP(k,n){
	  if(i & (1<<k)) continue;
	  chmax(dp[i|(1<<k)][k], min(dp[i][j],edge1[j][k]));
	}
      }
    }
  }
}


int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  cin >> n >> m;
  vector<vector<int>> a(n, vector<int>(m)); cin >> a;

  if(n == 1){
    int ans = 1e9;
    REP(i,m-1) chmin(ans, abs(a[0][i]-a[0][i+1]));
    cout << ans << endl;
    return 0;
  }

  REP(i,n) FOR(j,i+1,n){
    int t = 1e9;
    REP(k,m) chmin(t, abs(a[i][k]-a[j][k]));
    edge1[i][j] = edge1[j][i] = t;
  }

  // last(i) -> start(j)
  REP(i,n) REP(j,n){
    int t = 1e9;
    REP(k,m-1) chmin(t, abs(a[i][k]-a[j][k+1]));
    edge2[i][j] = t;
  }

  REP(i,n) func(i);

  int ans = 0;

  REP(i,n) REP(j,n) chmax(ans, min(memo[i][j],edge2[j][i]));
  
  
  cout << ans << endl;
  
  return 0;
}
