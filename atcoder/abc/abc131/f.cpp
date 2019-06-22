#include <bits/stdc++.h>
#define LLI long long int
#define FOR(v, a, b) for(LLI v = (a); v < (b); ++v)
#define FORE(v, a, b) for(LLI v = (a); v <= (b); ++v)
#define REP(v, n) FOR(v, 0, n)
#define REPE(v, n) FORE(v, 0, n)
#define REV(v, a, b) for(LLI v = (a); v >= (b); --v)
#define ALL(x) (x).begin(), (x).end()
#define RALL(x) (x).rbegin(), (x).rend()
#define ITR(it, c) for(auto it = (c).begin(); it != (c).end(); ++it)
#define RITR(it, c) for(auto it = (c).rbegin(); it != (c).rend(); ++it)
#define EXIST(c,x) ((c).find(x) != (c).end())
#define fst first
#define snd second
#define popcount __builtin_popcount
#define UNIQ(v) (v).erase(unique(ALL(v)), (v).end())
#define bit(i) (1LL<<(i))
#define sz(v) ((LLI)(v).size())

#ifdef DEBUG
#include <misc/C++/Debug.cpp>
#else
#define dump(...) ((void)0)
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

  int N;
  while(cin >> N){
    vector<int> xs(N), ys(N);
    REP(i,N){
      cin >> xs[i] >> ys[i];
    }

    vector<int> X(xs), Y(ys);
    sort(ALL(X)); UNIQ(X);
    sort(ALL(Y)); UNIQ(Y);

    UnionFind uf(2*N);

    vector<LLI> count_x(2*N), count_y(2*N), count_edge(2*N);
    REP(i,N){
      count_x[i] = 1;
      count_y[i+N] = 1;
    }

    REP(i,N){
      int x = lower_bound(ALL(X), xs[i]) - X.begin();
      int y = lower_bound(ALL(Y), ys[i]) - Y.begin();

      int p = uf.root(x);
      int q = uf.root(y+N);
      int k = uf.merge(x,y+N);

      if(p != q){
	count_x[k] = count_x[p] + count_x[q];
	count_y[k] = count_y[p] + count_y[q];
	count_edge[k] = count_edge[p] + count_edge[q];
      }

      count_edge[k] += 1;
    }

    map<int,LLI> m;
    REP(i,2*N){
      int k = uf.root(i);
      m[k] = count_x[k] * count_y[k] - count_edge[k];
    }

    LLI ans = 0;
    for(auto &kv : m){
      ans += kv.snd;
    }

    cout << ans << endl;
  }

  
  return 0;
}
