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


template <typename Cost = int> class Edge{
public:
  int from,to;
  Cost cost;
  Edge() {}
  Edge(int to, Cost cost): to(to), cost(cost){}
  Edge(int from, int to, Cost cost): from(from), to(to), cost(cost){}

  Edge rev(){return Edge(to,from,cost);}
  
  static bool cmp_to_lt(const Edge &e1, const Edge &e2){return e1.to < e2.to;}
  static bool cmp_cost_lt(const Edge &e1, const Edge &e2){return e1.cost < e2.cost;}
  static bool cmp_to_gt(const Edge &e1, const Edge &e2){return e1.to > e2.to;}
  static bool cmp_cost_gt(const Edge &e1, const Edge &e2){return e1.cost > e2.cost;}
  friend ostream& operator<<(ostream &os, const Edge &e){
    os << "(FROM: " << e.from << "," << "TO: " << e.to << "," << "COST: " << e.cost << ")";
    return os;
  }
};

template <typename T> using Graph = vector<vector<Edge<T>>>;

int size[200100];
int size_dfs(Graph<int> &g, int cur, int par){
  size[cur] = 1;
  int j = -1;
  REP(i,g[cur].size()){
    auto &e = g[cur][i];
    if(e.to == par){
      j = i;
      continue;
    }
    size[cur] += size_dfs(g, e.to, cur);
  }
  if(j != -1) g[cur].erase(g[cur].begin()+j);
  return size[cur];
}

int rec(Graph<int> &g, int cur, int par, int m, vector<int> &ans){
  int c = 0;
  for(auto &e : g[cur]) if(size[e.to] == 1) ++c;

  if(c > 1 && c == g[cur].size()){
    vector<int> temp;
    for(auto &e : g[cur]) temp.push_back(e.to);
    if(ans[cur] == -1) temp.push_back(cur);

    REP(i,temp.size()){
      ans[temp[i]] = temp[(i+1)%temp.size()];
    }

    return 0;
  }
  
  if(c == 1){
    sort(ALL(g[cur]), [&](Edge<int> &a, Edge<int> &b){return size[a.to] < size[b.to];});
  }else{
    sort(ALL(g[cur]), [&](Edge<int> &a, Edge<int> &b){return size[a.to] > size[b.to];});
  }
  
  vector<int> temp;
  FOR(i,1,g[cur].size()){
    auto &e = g[cur][i];
    if(size[e.to] == 1) temp.push_back(e.to);
    else rec(g, e.to, cur, 0, ans);
  }

  REP(i,temp.size()){
    ans[temp[i]] = temp[(i+1)%temp.size()];
  }

  if(g[cur].size() > 0){
    if(m % 2 == 0){
      ans[g[cur][0].to] = cur;
      ans[cur] = g[cur][0].to;
    }else if(size[g[cur][0].to] == 1){
      ans[g[cur][0].to] = ans[cur];
      ans[cur] = g[cur][0].to;
    }
    rec(g, g[cur][0].to, cur, m+1, ans);
  }
}

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  int N,M;
  while(cin >> N >> M){
    vector<pair<int,int>> edges(M);
    REP(i,M){
      int u,v; cin >> u >> v; --u, --v;
      edges.push_back(make_pair(u,v));
    }

    Graph<int> tree(N);
    UnionFind uf(N);
    for(auto &e : edges){
      if(!uf.same(e.fst, e.snd)){
	int u = e.fst, v = e.snd;
        tree[u].push_back(Edge<int>(u,v,1));
	tree[v].push_back(Edge<int>(v,u,1));
	uf.merge(e.fst, e.snd);
      }
    }

    fill_array(size, 0);
    size_dfs(tree, 0, -1);
    

    vector<int> ans(N,-1);
    rec(tree, 0, -1, 0, ans);
    for(auto &x : ans) ++x;
    join(cout, ALL(ans));
  }
  
  return 0;
}
