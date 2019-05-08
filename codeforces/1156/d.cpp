#include <bits/stdc++.h>
#define FOR(v, a, b) for(int v = (a); v < (b); ++v)
#define FORE(v, a, b) for(int v = (a); v <= (b); ++v)
#define REP(v, n) FOR(v, 0, n)
#define REPE(v, n) FORE(v, 0, n)
#define REV(v, a, b) for(int v = (a); v >= (b); --v)
#define ALL(x) (x).begin(), (x).end()
#define RALL(x) (x).rbegin(), (x).rend()
#define ITR(it, c) for(auto it = (c).begin(); it != (c).end(); ++it)
#define RITR(it, c) for(auto it = (c).rbegin(); it != (c).rend(); ++it)
#define EXIST(c,x) ((c).find(x) != (c).end())
#define LLI long long int
#define fst first
#define snd second

#ifdef DEBUG
#include <misc/C++/Debug.cpp>
#else
#define dump(x) ((void)0)
#endif

#define gcd __gcd

using namespace std;
template <class T> constexpr T lcm(T m, T n){return m/gcd(m,n)*n;}

template <typename I> void join(ostream &ost, I s, I t, string d=" "){for(auto i=s; i!=t; ++i){if(i!=s)ost<<d; ost<<*i;}ost<<endl;}
template <typename T> istream& operator>>(istream &is, vector<T> &v){for(auto &a : v) is >> a; return is;}
template <typename T, typename U> istream& operator>>(istream &is, pair<T,U> &p){is >> p.first >> p.second; return is;}

template <typename T, typename U> bool chmin(T &a, const U &b){return (a>b ? a=b, true : false);}
template <typename T, typename U> bool chmax(T &a, const U &b){return (a<b ? a=b, true : false);}
template <typename T, size_t N, typename U> void fill_array(T (&a)[N], const U &v){fill((U*)a, (U*)(a+N), v);}


class UnionFind{
  vector<int> _parent, _depth, _size;
  int _count;
public:
  UnionFind(int n): _parent(n), _depth(n,1), _size(n,1), _count(n){REP(i, n) _parent[i] = i;}
  int root(int i){
    if(_parent[i] == i) return i;
    else return _parent[i] = root(_parent[i]);
  }
  bool same(int i, int j){return root(i) == root(j);}
  int merge(int i, int j){
    int ri = root(i), rj = root(j);
    if(ri == rj) return ri;
    else{
      --_count;
      if(_depth[ri] < _depth[rj]){
	_parent[ri] = rj; _size[rj] += _size[ri];
	return rj;
      }else{
	_parent[rj] = ri; _size[ri] += _size[rj];
	if(_depth[ri] == _depth[rj]) ++_depth[ri];
	return ri;
      }
    }
  }
  int size(int i){return _size[root(i)];}
  int count(){return _count;}
};


int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  int n;
  while(cin >> n){
    vector<int> x(n-1), y(n-1), c(n-1);

    UnionFind uf0(n), uf1(n);

    REP(i,n-1){
      cin >> x[i] >> y[i] >> c[i];
      --x[i];
      --y[i];

      if(c[i] == 0){
	uf0.merge(x[i],y[i]);
      }else{
	uf1.merge(x[i],y[i]);
      }
    }

    LLI ans = 0;
    
    set<int> r0;
    REP(i,n) r0.insert(uf0.root(i));
    for(auto x : r0) ans += (LLI)uf0.size(x) * (uf0.size(x)-1);

    set<int> r1;
    REP(i,n) r1.insert(uf1.root(i));
    for(auto x : r1) ans += (LLI)uf1.size(x) * (uf1.size(x)-1);
    
    REP(i,n){
      ans += (LLI)(uf0.size(i)-1) * (uf1.size(i)-1);
    }
    
    cout << ans << endl;
  }
  
  return 0;
}
