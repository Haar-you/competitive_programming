#include <bits/stdc++.h>
#define FOR(v, a, b) for(int v = (a); v < (b); ++v)
#define FORE(v, a, b) for(int v = (a); v <= (b); ++v)
#define REP(v, n) FOR(v, 0, n)
#define REPE(v, n) FORE(v, 0, n)
#define REV(v, a, b) for(int v = (a); v >= (b); --v)
#define ALL(x) (x).begin(), (x).end()
#define ITR(it, c) for(auto it = (c).begin(); it != (c).end(); ++it)
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

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  int n; cin >> n;
  map<int,int> p,q;
  int zero=0;

  REP(i,n){
    string s; cin >> s;
    stack<char> st;

    REP(j,s.size()){
      if(st.empty()) st.push(s[j]);
      else{
	if(st.top() == '(' && s[j] == ')') st.pop();
	else st.push(s[j]);
      }
    }
    int open=0,close=0;
    while(!st.empty()){
      if(st.top()=='(') ++open;
      else ++close;
      st.pop();
    }

    if(open > 0 && close > 0) continue;
    if(open == 0 && close == 0) ++zero;
    else if(open > 0) ++p[open];
    else ++q[close];
  }

  int ans = 0;
  for(auto &kv : p){
    ans += min(kv.snd, q[kv.fst]);
  }

  ans += zero/2;

  cout << ans << endl;
  
  return 0;
}
