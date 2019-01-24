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
#define gcd __gcd

using namespace std;
template <class T> constexpr T lcm(T m, T n){return m*n/gcd(m,n);}

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

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  int n;
  while(cin >> n){
    string s; cin >> s;
    vector<vector<int>> dp(n+1, vector<int>(3));
    vector<vector<int>> re(n+1, vector<int>(3));

    dp[0][0] = s[0]=='R'?0:1;
    dp[0][1] = s[0]=='G'?0:1;
    dp[0][2] = s[0]=='B'?0:1;

    FOR(i,1,n){
      if(dp[i-1][1] < dp[i-1][2]){
	dp[i][0] = dp[i-1][1] + (s[i]=='R'?0:1);
	re[i][0] = 1;
      }else{
	dp[i][0] = dp[i-1][2] + (s[i]=='R'?0:1);
	re[i][0] = 2;
      }

      if(dp[i-1][0] < dp[i-1][2]){
	dp[i][1] = dp[i-1][0] + (s[i]=='G'?0:1);
	re[i][1] = 0;
      }else{
	dp[i][1] = dp[i-1][2] + (s[i]=='G'?0:1);
	re[i][1] = 2;
      }

      if(dp[i-1][0] < dp[i-1][1]){
	dp[i][2] = dp[i-1][0] + (s[i]=='B'?0:1);
	re[i][2] = 0;
      }else{
	dp[i][2] = dp[i-1][1] + (s[i]=='B'?0:1);
	re[i][2] = 1;
      }
    }

    re[n][0] = re[n][1] = re[n][2] = (min_element(ALL(dp[n-1])) - dp[n-1].begin());

    string p = "RGB";
    string ans;
    int t = 0;
    REV(i,n,1){
      ans.push_back(p[re[i][t]]);
      t = re[i][t];
    }
    
    reverse(ALL(ans));
    int d = 0;
    REP(i,n) if(s[i] != ans[i]) ++d;

    cout << d << endl << ans << endl;
  }
  
  return 0;
}
