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
#include <boost/core/demangle.hpp>
#define dump(x) cerr << "L" << __LINE__ << ": in " << __PRETTY_FUNCTION__ << " \e[32;1m" << boost::core::demangle(typeid(x).name()) << "\e[37m" << " " << (#x) << " = " << (x) << "\e[m" << endl;
#else
#define dump(x)
#endif
#define pln(x) cout << (x) << endl
using namespace std;
template <typename T> using V = vector<T>;
template <typename T, typename U> using P = pair<T,U>;
template <typename I> void join(ostream &ost, I s, I t, string d=" "){for(auto i=s; i!=t; ++i){if(i!=s)ost<<d; ost<<*i;}ost<<endl;}
template <typename T> istream& operator>>(istream &is, vector<T> &v){for(auto &a : v) is >> a; return is;}
template <typename T, typename U> istream& operator>>(istream &is, pair<T,U> &p){is >> p.first >> p.second; return is;}

template <typename Iter> ostream& out_container(ostream &os, Iter first, Iter last){
  os << "{"; auto itr = first; while(itr != last){if(itr != first) os << ","; os << *itr; ++itr;} os << "}"; return os;
}

template <typename T> ostream& operator<<(ostream &os, const vector<T> &c){return out_container(os,ALL(c));}
template <typename T> ostream& operator<<(ostream &os, const deque<T> &c){return out_container(os,ALL(c));}
template <typename T> ostream& operator<<(ostream &os, const set<T> &c){return out_container(os,ALL(c));}
template <typename T> ostream& operator<<(ostream &os, const unordered_set<T> &c){return out_container(os,ALL(c));}
template <typename T, typename U> ostream& operator<<(ostream &os, const map<T,U> &c){return out_container(os,ALL(c));}
template <typename T, typename U> ostream& operator<<(ostream &os, const unordered_map<T,U> &c){return out_container(os,ALL(c));}
template <typename T, typename U> ostream& operator<<(ostream& os, const pair<T,U> &p){os << "(" << p.first << "," << p.second << ")"; return os;}

template <typename T> T& chmin(T &a, const T &b){return a = min(a,b);}
template <typename T> T& chmax(T &a, const T &b){return a = max(a,b);}

const LLI mod = 1e9+7;

LLI rec(int i, int j, int T, vector<vector<LLI>> &dp, vector<vector<bool>> &visit, vector<int> &a){
  if(j >= 600 || i >= T+50) return 0;
  if(visit[i][j]) return dp[i][j];
  visit[i][j] = true;
  
  if(j == 0) return dp[i][j] = 0;
  if(j == 1) return dp[i][j] = 1;
  if(j % 2 == 1) return dp[i][j] = 0;

  if(i < T-1){
    REPE(k,a[i+1]){
      (dp[i][j] += rec(i+1,k+j/2,T,dp,visit,a)) %= mod;
    }
  }else{
    (dp[i][j] += rec(i+1,j/2,T,dp,visit,a)) %= mod;
  }

  return dp[i][j];
}

LLI solve(int T, vector<int> &a){
  vector<vector<LLI>> dp(T+50, vector<LLI>(600));
  vector<vector<bool>> visit(T+50, vector<bool>(600));

  LLI ans = 0;

  REP(i,T){
    REPE(j,a[i]){
      (ans += rec(i,j,T,dp,visit,a)) %= mod;
    }
  }

  return ans;
}

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);


  int T;
  while(cin >> T){
    vector<int> a(T); cin >> a;

    LLI ans = solve(T,a);
    pln(ans);
  }
  
  return 0;
}
