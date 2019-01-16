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
template <typename T> ostream& operator<<(ostream &os, const deque<T> &v){os << "{";ITR(i,v){if(i!=v.begin())os << ","; os << *i;}os << "}"; return os;}

template <typename T> T& chmin(T &a, const T &b){return a = min(a,b);}
template <typename T> T& chmax(T &a, const T &b){return a = max(a,b);}

// 追加直線の傾きが単調減少、クエリの値が単調増加
template <typename T> class ConvexHullTrick{
public:
  deque<pair<T,T>> lines;

  bool is_needless(pair<T,T> a, pair<T,T> b, pair<T,T> c){
    return (a.snd-b.snd)*(a.fst-c.fst) >= (a.snd-c.snd)*(a.fst-b.fst);
  }
  
  void add(T a, T b){
    if(!lines.empty()){
      auto l = lines.back();
      if(l.fst == a){
	if(l.snd < b) return;
	else lines.pop_back();
      }
    }
    while(lines.size()>=2 && is_needless(make_pair(a,b), lines.back(), *(lines.end()-2))){
      lines.pop_back();
    }
    lines.push_back(make_pair(a,b));
  }

  T apply(pair<T,T> f, T x){
    return f.fst*x + f.snd;
  }

  T query(T x){
    while(lines.size()>=2 && apply(lines[0],x)>apply(lines[1],x)){
      lines.pop_front();
    }
    return apply(lines[0],x);
  }
};

LLI dp[201000];

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);
  
  LLI N,C; cin >> N >> C;
  vector<LLI> h(N); cin >> h;

  /*
    dp[i]
    = min(dp[j] + (hi-hj)^2 + C)
    = min(dp[j] + hi^2 - 2*hi*hj + hj^2 + C)
    = min(-2*hj*hi + hj^2 + dp[j]) + hi^2 + C
  */

  ConvexHullTrick<LLI> cht;

  dp[0] = 0;
  cht.add(-2*h[0],h[0]*h[0]+dp[0]);

  FOR(i,1,N){
    dp[i] = cht.query(h[i]) + h[i]*h[i] + C;
    cht.add(-2*h[i],h[i]*h[i]+dp[i]);
  }

  cout << dp[N-1] << endl;
  
  return 0;
}
