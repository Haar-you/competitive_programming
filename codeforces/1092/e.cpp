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

template <typename T> using Tree = vector<vector<T>>;
template <typename Cost = int> class WEdge{
public:
  int to;
  Cost cost;
  WEdge(int to, Cost cost): to(to), cost(cost){}
};

class TreeUtils{
public:
  template <typename T> static pair<int,T> farthest(Tree<WEdge<T>> &tree, int cur, int par = -1){
    auto d = make_pair(cur, 0);
    for(auto &next : tree[cur]){
      if(next.to == par) continue;
      auto t = farthest(tree, next.to, cur);
      t.second += next.cost;
      if(t.second > d.second) d = t;
    }
    return d;
  }

  template <typename T> static void distance(Tree<WEdge<T>> &tree, int cur, int par, vector<T> &dist, T d){
    dist[cur] = d;
    for(auto &next : tree[cur]){
      if(next.to == par) continue;
      distance(tree, next.to, cur, dist, d+next.cost);
    }
  }
  
  template <typename T> static T diameter(Tree<WEdge<T>> &tree){
    auto a = farthest(tree, 0);
    auto b = farthest(tree, a.first);
    return b.second;
  }

  template <typename T> static vector<T> height(Tree<WEdge<T>> &tree, int cur=0){
    auto a = farthest(tree, cur);
    auto b = farthest(tree, a.first);

    int n = tree.size();
    vector<T> d1(n,-1), d2(n,-1), h(n);

    distance(tree, a.first, -1, d1, 0);
    distance(tree, b.first, -1, d2, 0);

    REP(i,n) h[i] = max(d1[i], d2[i]);
    
    return h;
  }
};



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


int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  int n,m; cin >> n >> m;

  Tree<WEdge<int>> tree(n);
  UnionFind uf(n);
  
  REP(i,m){
    int u,v; cin >> u >> v;
    --u; --v;
    tree[u].push_back(WEdge<int>(v,1));
    tree[v].push_back(WEdge<int>(u,1));
    uf.merge(u,v);
  }

  vector<pair<int,int>> v;
  unordered_map<int,int> visit;

  REP(i,n){
    if(!visit[uf.getRoot(i)]){

      auto h = TreeUtils::height(tree, i);

      REP(i,n) if(h[i] == -1) h[i] = 100000;
      auto itr = min_element(ALL(h));

      v.push_back(make_pair(*itr, itr-h.begin()));

      visit[uf.getRoot(i)] = true;
    }
  }

  sort(ALL(v));
  reverse(ALL(v));

  FOR(i,1,v.size()){
    int a = v[0].second;
    int b = v[i].second;

    tree[a].push_back(WEdge<int>(b,1));
    tree[b].push_back(WEdge<int>(a,1));
  }

  cout << TreeUtils::diameter(tree) << endl;

  FOR(i,1,v.size()){
    cout << v[0].second+1 << " " << v[i].second+1 << endl;
  }
  
  return 0;
}
