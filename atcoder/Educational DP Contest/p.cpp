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

const LLI mod = 1e9+7;

LLI dp[101000][2];
bool visit[101000][2];

LLI rec(vector<vector<int>> &tree, int col, int cur, int par){
  if(visit[cur][col]) return dp[cur][col];
  visit[cur][col] = true;

  dp[cur][col] = 1;
  if(col){ //black
    for(auto next : tree[cur]){
      if(next == par) continue;
      (dp[cur][1] *= rec(tree, 0, next, cur)) %= mod;
    }
  }else{ //white
    for(auto next : tree[cur]){
      if(next == par) continue;
      (dp[cur][0] *= (rec(tree, 0, next, cur) + rec(tree, 1, next, cur)) % mod) %= mod;
    }
  }
  
  return dp[cur][col];
}

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  int N; cin >> N;
  vector<vector<int>> tree(N);
  REP(i,N-1){
    int x,y; cin >> x >> y;
    --x, --y;
    tree[x].push_back(y);
    tree[y].push_back(x);
  }

  LLI ans = (rec(tree, 0, 0, -1) + rec(tree, 1, 0, -1)) % mod;

  cout << ans << endl;

  return 0;
}
