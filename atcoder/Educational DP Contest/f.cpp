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

int dp[3100][3100];


void restore_lcs(const string &a, const string &b, int i, int j, string &r){
  if(i==0 || j==0) return;
  if(a[i-1] == b[j-1]){
    restore_lcs(a,b,i-1,j-1,r);
    r.push_back(a[i-1]);
  }else{
    if(dp[i-1][j] >= dp[i][j-1]) restore_lcs(a,b,i-1,j,r);
    else restore_lcs(a,b,i,j-1,r);
  }
}

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  string s,t; cin >> s >> t;

  REP(i,s.size()){
    REP(j,t.size()){
      if(s[i] == t[j]){
	dp[i+1][j+1] = dp[i][j] + 1;
      }else{
	dp[i+1][j+1] = max(dp[i][j+1], dp[i+1][j]);
      }
    }
  }

  string ans;
  restore_lcs(s,t,s.size(),t.size(),ans);
  cout << ans << endl;
  
  return 0;
}