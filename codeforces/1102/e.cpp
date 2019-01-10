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

template <typename T> LLI power(T n, T p, T m){if(p==0) return 1LL; if(p==1) return n; LLI k = power(n, p/2, m); return ((k*k)%m*(p%2?n:1))%m;}

class UnionFind{
  vector<int> _parent, _depth, _size;
  int _group;
public:
  UnionFind(int n): _parent(n), _depth(n,1), _size(n,1), _group(n){REP(i, n) _parent[i] = i;}
  int root(int i){
    if(_parent[i] == i) return i;
    else return _parent[i] = root(_parent[i]);
  }
  bool same(int i, int j){return root(i) == root(j);}
  int merge(int i, int j){
    int ri = root(i), rj = root(j);
    if(ri != rj){
      --_group;
      if(_depth[ri] < _depth[rj]){
	_parent[ri] = rj; _size[rj] += _size[ri];
      }else{
	_parent[rj] = ri; _size[ri] += _size[rj];
	if(_depth[ri] == _depth[rj]) ++_depth[ri];
      }
    }
    return root(i);
  }
  int size(int i){return _size[root(i)];}
  int count_group(){return _group;}
};

const LLI mod = 998244353;

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  int n; cin >> n;
  vector<LLI> a(n); cin >> a;

  UnionFind uf(n);
  map<int,vector<int>> m;
  REP(i,n) m[a[i]].push_back(i);

  vector<int> l(n),r(n);
  REP(i,n) l[i] = r[i] = i;


  for(auto &kv : m){
    auto &v = kv.snd;

    REP(i,v.size()-1){
      int x = uf.root(v[i]);
      int y = uf.root(v[i+1]);
      int z = uf.merge(v[i],v[i+1]);

      FOR(j,r[x]+1,l[y]){
	uf.merge(v[i],j);
      }

      l[z] = l[x];
      r[z] = r[y];
    }
  }

  cout << power(2LL,(LLI)uf.count_group()-1,mod) << endl;
  
  return 0;
}
