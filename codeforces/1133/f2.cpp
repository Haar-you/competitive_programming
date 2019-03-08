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
#include <misc/C++/Debug.cpp>
#else
#define dump(x)
#endif

#define pln(x) cout << (x) << endl
#define gcd __gcd

using namespace std;
template <class T> constexpr T lcm(T m, T n){return m/gcd(m,n)*n;}

template <typename T> using V = vector<T>;
template <typename T, typename U> using P = pair<T,U>;
template <typename I> void join(ostream &ost, I s, I t, string d=" "){for(auto i=s; i!=t; ++i){if(i!=s)ost<<d; ost<<*i;}ost<<endl;}
template <typename T> istream& operator>>(istream &is, vector<T> &v){for(auto &a : v) is >> a; return is;}
template <typename T, typename U> istream& operator>>(istream &is, pair<T,U> &p){is >> p.first >> p.second; return is;}

template <typename T, typename U> T& chmin(T &a, const U &b){return a = (a<=b?a:b);}
template <typename T, typename U> T& chmax(T &a, const U &b){return a = (a>=b?a:b);}
template <typename T, size_t N, typename U> void fill_array(T (&a)[N], const U &v){fill((U*)a, (U*)(a+N), v);}


class UnionFind{
  vector<int> _parent, _depth, _size;
public:
  UnionFind(int n): _parent(n), _depth(n,1), _size(n,1){REP(i, n) _parent[i] = i;}
  int root(int i){
    if(_parent[i] == i) return i;
    else return _parent[i] = root(_parent[i]);
  }
  bool same(int i, int j){return root(i) == root(j);}
  int merge(int i, int j){
    int ri = root(i), rj = root(j);
    if(ri == rj) return ri;
    if(ri != rj){
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
};

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  int n,m,D;
  while(cin >> n >> m >> D){
    vector<pair<int,int>> edges;
    vector<vector<int>> graph(n);
    vector<int> deg(n);
    REP(i,m){
      int u,v; cin >> u >> v; --u, --v;
      edges.push_back(make_pair(u,v));
      graph[u].push_back(v);
      graph[v].push_back(u);
      ++deg[u];
      ++deg[v];
    }

    if(deg[0] < D){
      cout << "NO" << endl;
      continue;
    }

    UnionFind uf1(n);

    for(auto &e : edges){
      if(e.fst != 0 && e.snd != 0){
	uf1.merge(e.fst, e.snd);
      }
    }

    set<int> st;
    for(auto x : graph[0]){
      st.insert(uf1.root(x));
    }

    if(st.size() > D){
      cout << "NO" << endl;
      continue;
    }

    cout << "YES" << endl;

    vector<pair<int,int>> ans;
    UnionFind uf(n);

    int c = 0;
    for(auto x : graph[0]){
      if(EXIST(st,uf1.root(x))){
	ans.push_back(make_pair(0,x));
	uf.merge(0,x);
	++c;
	st.erase(uf1.root(x));
      }
    }

    for(auto x : graph[0]){
      if(!uf.same(0,x) && c<D){
	ans.push_back(make_pair(0,x));
	uf.merge(0,x);
	++c;
      }
    }

    for(auto &e : edges){
      if(!uf.same(e.fst,e.snd) && e.fst != 0 && e.snd != 0){
	ans.push_back(make_pair(e.fst, e.snd));
	uf.merge(e.fst, e.snd);
      }
    }

    for(auto &e : ans){
      cout << e.fst+1 << " " << e.snd+1 << endl;
    }
  }
  
  return 0;
}
