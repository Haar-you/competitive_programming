#include <bits/stdc++.h>
#define FOR(v, a, b) for(int v = (a); v < (b); ++v)
#define FORE(v, a, b) for(int v = (a); v <= (b); ++v)
#define REP(v, n) FOR(v, 0, n)
#define REPE(v, n) FORE(v, 0, n)
#define REV(v, a, b) for(int v = (a); v >= (b); --v)
#define ALL(x) (x).begin(), (x).end()
#define ITR(it, c) for(auto it = (c).begin(); it != (c).end(); ++it)
#define LLI long long int
using namespace std;
template <typename T> using V = vector<T>;
template <typename T, typename U> using P = pair<T,U>;
template <typename I> void join(ostream &ost, I s, I t, string d=" "){for(auto i=s; i!=t; ++i){if(i!=s)ost<<d; ost<<*i;}ost<<endl;}

class UnionFind{
  vector<int> parent, depth, size;
public:
  UnionFind(int n): parent(n), depth(n,1), size(n,1){REP(i, n) parent[i] = i;}
  int getRoot(int i){
    if(parent[i] == i) return i;
    else return parent[i] = getRoot(parent[i]);
  }
  bool isSame(int i, int j){return getRoot(i) == getRoot(j);}
  void merge(int i, int j){
    int ri = getRoot(i), rj = getRoot(j);
    if(ri != rj){
      if(depth[ri] < depth[rj]){
	parent[ri] = rj; size[rj] += size[ri];
      }else{
	parent[rj] = ri; size[ri] += size[rj];
	if(depth[ri] == depth[rj]) ++depth[ri];
      }
    }
  }
  int getSize(int i){return size[getRoot(i)];}
};

template <typename T>
vector<tuple<int,int,T>> kruskal(int n, vector<tuple<int,int,T>> &graph){
  sort(graph.begin(), graph.end(), [](tuple<int,int,T> &a, tuple<int,int,T> &b){return get<2>(a) < get<2>(b);});
  UnionFind uf(n);
  vector<tuple<int,int,T>> mst;
  for(auto v : graph){
    int s,t,d;
    tie(s,t,d) = v;
    if(!uf.isSame(s,t)){
      uf.merge(s,t);
      mst.push_back(v);
    }
  }
  return mst;
}

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  int n,m; cin >> n >> m;
  vector<LLI> a(n);
  REP(i,n) cin >> a[i];

  vector<tuple<int,int,LLI>> graph;

  REP(i,m){
    LLI x,y,w; cin >> x >> y >> w;
    graph.push_back(make_tuple(x-1,y-1,w));
  }

  int p = min_element(ALL(a)) - a.begin();
  REP(i,n){
    if(i==p) continue;
    graph.push_back(make_tuple(i,p,a[i]+a[p]));
  }

  auto g = kruskal(n, graph);

  LLI ans = 0;
  for(auto &t : g) ans += get<2>(t);
  cout << ans << endl;
  
  return 0;
}
