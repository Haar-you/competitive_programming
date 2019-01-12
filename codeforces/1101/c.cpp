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

  int T; cin >> T;

  REP(_,T){
    int n; cin >> n;
    vector<pair<pair<int,int>,int>> t(n);
    map<int,int> start_points;
    REP(i,n){
      int l,r; cin >> l >> r;
      t[i] = {{r,l},i};
      ++start_points[l];
    }
    sort(ALL(t));
    vector<pair<pair<int,int>,int>> g1,g2;

    vector<int> ans(n,2);
    bool no_ans = false;
    
    REP(i,n){
      int r = t[i].fst.fst;
      int l = t[i].fst.snd;
      if(start_points[l] == 1) start_points.erase(l);
      else start_points[l]--;

      if(start_points.empty()){
	no_ans = true;
	break;
      }
      
      if(start_points.upper_bound(r) == start_points.begin()){
	REPE(j,i) ans[t[j].snd] = 1;
	break;
      }
    }

    if(no_ans){
      cout << -1 << endl;
      continue;
    }
    join(cout, ALL(ans));
  }
  
  return 0;
}
