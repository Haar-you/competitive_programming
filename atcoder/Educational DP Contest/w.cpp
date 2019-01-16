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


template <typename T, typename U> class RangeRangeSegmentTree{
  int size;
  T e1;
  vector<T> vec1;
  function<T(T,T)> f1;
  U e2;
  vector<U> vec2;
  function<U(U,U)> f2;
  function<T(U,T,int)> g;

  void propagate(int i, int l){
    if(i < size/2){
      vec2[i*2+1] = f2(vec2[i], vec2[i*2+1]);
      vec2[i*2+2] = f2(vec2[i], vec2[i*2+2]);
    }
    vec1[i] = g(vec1[i], vec2[i], l);
    vec2[i] = e2;
  }

  T update_aux(int i, int l, int r, int s, int t, U x){
    propagate(i,r-l);
    if(r <= s || t <= l) return vec1[i];
    else if(s <= l && r <= t){
      vec2[i] = f2(vec2[i],x);
      propagate(i,r-l);
      return vec1[i];
    }else return vec1[i] = f1(update_aux(i*2+1,l,(l+r)/2,s,t,x), update_aux(i*2+2,(l+r)/2,r,s,t,x));
  }
  
  T query_aux(int i, int l, int r, int x, int y){
    propagate(i,r-l);
    if(r <= x || y <= l) return e1;
    else if(x <= l && r <= y) return vec1[i];
    else return f1(query_aux(i*2+1,l,(l+r)/2,x,y), query_aux(i*2+2,(l+r)/2,r,x,y));
  }
  
public:
  RangeRangeSegmentTree(){}
  RangeRangeSegmentTree(int n, T e1, function<T(T,T)> f1, U e2, function<U(U,U)> f2, function<T(T,U,int)> g):
    e1(e1), f1(f1), e2(e2), f2(f2), g(g){
    size = 1;
    while(size<n) size*=2;
    size *= 2;
    size -= 1;

    vec1 = vector<T>(size,e1);
    vec2 = vector<U>(size,e2);
  }

  void update(int s, int t, U x){
    update_aux(0,0,size/2+1,s,t,x);
  }
  
  T query(int x, int y){
    return query_aux(0,0,size/2+1,x,y);
  }
};

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  int N, M;
  while(cin >> N >> M){
    RangeRangeSegmentTree<LLI,LLI>
      seg(
	  N+1,
	  0, [](LLI a, LLI b){return max(a,b);},
	  0, [](LLI a, LLI b){return a+b;},
	  [](LLI a, LLI b, int l){return a+b;}
	  );
	  
    vector<vector<pair<LLI,LLI>>> v(N+1);

    REP(i,M){
      LLI l,r,a; cin >> l >> r >> a;
      --l, --r;
      v[r].push_back(make_pair(l,a));
    }

    REP(i,N){
      LLI t = seg.query(0,i);

      seg.update(i,i+1,t);
      for(auto &p : v[i]){
	seg.update(p.fst,i+1,p.snd);
      }
    }

    LLI ans = seg.query(0,N+1);
    cout << ans << endl;
  }
  
  return 0;
}
