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

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  string s; cin >> s;
  int k; cin >> k;


  int count_snow = 0;
  int count_candy = 0;
  int len = 0;
  int count_other = 0;

  REP(i,s.size()){
    if(s[i] == '*') ++count_snow;
    else if(s[i] == '?') ++count_candy;
  }

  count_other = s.size() - 2*(count_snow + count_candy);

  if(count_snow == 0){
    if(count_other <= k && count_other+count_candy >= k){
      string ans;

      int t = k-count_other;

      REP(i,s.size()){
	if(i<s.size()-1 && s[i+1] == '?'){
	  if(t>0){
	    ans += s[i];
	    --t;
	  }
	  ++i;
	}else{
	  ans += s[i];
	}
      }

      cout << ans << endl;
    }else{
      cout << "Impossible" << endl;
    }
  }else{
    if(count_other <= k){
      int t = k-count_other;

      string ans;

      REP(i,s.size()){
	if(i<s.size()-1 && s[i+1] == '*'){
	  REP(j,t)
	    ans += s[i];
	  
	  t = 0;
	  ++i;
	}else if(i<s.size()-1 && s[i+1] == '?'){
	  ++i;
	}else{
	  ans += s[i];
	}
      }

      cout << ans << endl;
    }else{
      cout << "Impossible" << endl;
    }
  }
    
  return 0;
}
