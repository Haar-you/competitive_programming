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

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  int n,k; cin >> n >> k;
  vector<int> a(n); cin >> a;

  unordered_map<int,vector<int>> m;
  REP(i,n) m[a[i]].push_back(i);

  for(auto &kv : m){
    if(kv.snd.size() > k){
      cout << "NO" << endl;
      return 0;
    }
  }

  vector<int> ans(n);
  vector<vector<bool>> memo(k, vector<bool>(5100, false));

  REP(i,k){
    FORE(j,1,5000){
      if(!m[j].empty()){
	ans[m[j].back()] = i+1;
	m[j].pop_back();
	memo[i][j] = true;
	break;
      }
    }
  }
  
  REP(i,k){
    FORE(j,1,5000){
      if(!memo[i][j] && !m[j].empty()){
	ans[m[j].back()] = i+1;
	m[j].pop_back();
	memo[i][j] = true;
      }
    }
  }
  
  cout << "YES" << endl;
  join(cout, ALL(ans));

  return 0;
}
