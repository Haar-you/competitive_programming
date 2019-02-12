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


class UnionFind{
  vector<int> _parent, _depth, _size;
public:
  UnionFind(int n): _parent(n), _depth(n,1), _size(n,1){REP(i, n) _parent[i] = i;}
  int root(int i){
    if(_parent[i] == i) return i;
    else return _parent[i] = root(_parent[i]);
  }
  bool same(int i, int j){return root(i) == root(j);}
  void merge(int i, int j){
    int ri = root(i), rj = root(j);
    if(ri != rj){
      if(_depth[ri] < _depth[rj]){
	_parent[ri] = rj; _size[rj] += _size[ri];
      }else{
	_parent[rj] = ri; _size[ri] += _size[rj];
	if(_depth[ri] == _depth[rj]) ++_depth[ri];
      }
    }
  }
  int size(int i){return _size[root(i)];}
};

template <typename T>
vector<tuple<int,int,T>> kruskal(int n, vector<tuple<int,int,T>> &graph){
  sort(graph.begin(), graph.end(), [](tuple<int,int,T> &a, tuple<int,int,T> &b){return get<2>(a) < get<2>(b);});
  UnionFind uf(n);
  vector<tuple<int,int,T>> mst;
  for(auto v : graph){
    int s,t,d;
    tie(s,t,d) = v;
    if(!uf.same(s,t)){
      uf.merge(s,t);
      mst.push_back(v);
    }
  }
  return mst;
}


template <typename T> class SegmentTree{
private:
  int size;
  vector<T> vec;
  T e;
  function<T(T,T)> f, upd;
  
  T aux(int x, int y, int i, int l, int r){
    if(r<=x || y<=l) return e;
    else if(x<=l && r<=y) return vec[i];
    else return f(aux(x,y,i*2+1,l,(l+r)/2), aux(x,y,i*2+2,(l+r)/2,r));
  };

public:
  SegmentTree(int n, T e, function<T(T,T)> f, function<T(T,T)> upd):  f(f), e(e), upd(upd){
    size = 1;
    while(size < n) size *= 2;
    size = size*2-1;
    vec = vector<T>(size, e);
  }
  void update(int i, T x){
    int j = i+(size+1)/2-1;
    vec[j] = upd(vec[j], x);
    --j;
    while(j>=0){
      vec[j/2] = f(vec[(j/2)*2+1], vec[(j/2)*2+2]);
      (j /= 2) -= 1;
    }
  }

  T find(int x, int y){return aux(x,y,0,0,(size+1)/2);}
};



const LLI inf = LONG_MAX;

using pli = pair<LLI,LLI>;

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  int N;
  LLI D;
  while(cin >> N >> D){
    vector<LLI> A(N); cin >> A;


    SegmentTree<pli> rseg(N, make_pair(inf,-1), [](pli a, pli b){return min(a,b);}, [](pli a, pli b){return b;});
    SegmentTree<pli> lseg(N, make_pair(inf,-1), [](pli a, pli b){return min(a,b);}, [](pli a, pli b){return b;});
    
    vector<pli> v;
    REP(i,N){
      v.push_back(make_pair(A[i],i));
    }
    sort(ALL(v));

    vector<tuple<int,int,LLI>> graph;

    for(auto &p : v){
      auto r = rseg.find(p.snd,N);
      if(r.snd != -1)
	graph.push_back(make_tuple(p.snd,r.snd,r.fst+p.fst-D*p.snd));
      rseg.update(p.snd,make_pair(p.fst+D*p.snd,p.snd));

      auto l = lseg.find(0,p.snd);
      if(l.snd != -1)
	graph.push_back(make_tuple(p.snd,l.snd,l.fst+p.fst+D*p.snd));
      lseg.update(p.snd,make_pair(p.fst-D*p.snd,p.snd));
    }

    auto res = kruskal(N, graph);

    LLI ans = 0;
    for(auto &t : res){
      ans += get<2>(t);
    }

    cout << ans << endl;
  }
  
  return 0;
}
