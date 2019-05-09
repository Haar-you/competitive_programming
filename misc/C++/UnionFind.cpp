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
using namespace std;

/*
 * Unioin-Find tree
 * Weighted Union-Find tree
 * partially persistent union-find tree
 */

//unionfind木
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

//重み付きunoinfind木
class WeightedUnionFind{
  vector<int> _parent, _depth, _size, _weight;
public:
  WeightedUnionFind(int n): _parent(n), _depth(n,1), _size(n,1), _weight(n,0){REP(i, n) _parent[i] = i;}
  int root(int i){
    if(_parent[i] == i) return i;
    else {int p=root(_parent[i]); _weight[i] += _weight[_parent[i]]; return _parent[i] = p;}
  }
  int weight(int i){root(i); return _weight[i];} 
  bool same(int i, int j){return root(i) == root(j);}
  bool diff(int i, int j, int &res){res = weight(i)-weight(j); return same(i,j);}
  void merge(int i, int j, int w){
    int ri = root(i), rj = root(j);
    if(ri != rj){
      if(_depth[ri] < _depth[rj]){
	_parent[ri] = rj; _size[rj] += _size[ri]; _weight[ri] = w - _weight[i] + _weight[j];
      }else{
	_parent[rj] = ri; _size[ri] += _size[rj]; _weight[rj] = -w + _weight[i] - _weight[j];
	if(_depth[ri] == _depth[rj]) ++_depth[ri];
      }
    }
  }
  int size(int i){return _size[root(i)];}
};

// 部分永続Unionfind
class partially_persistent_unionfind{
  int N;
  vector<vector<pair<int,int>>> P;
  int T = 0;
  vector<int> rank;

public:
  partially_persistent_unionfind(int N): N(N), P(N), rank(N,1){
    REP(i,N) P[i].push_back({0,i});
  }
  
  int root(int i, int t){
    if(t >= P[i].back().fst && P[i].back().snd != i) return root(P[i].back().snd, t);
    return i;
  }

  bool same(int u, int v, int t){
    return root(u,t) == root(v,t);
  }

  void merge(int u, int v){
    u = root(u, T);
    v = root(v, T);
    ++T;

    if(u==v) return;
    if(rank[u] < rank[v]){
      P[u].push_back({T,v});
    }else{
      P[v].push_back({T,u});
      if(rank[u] == rank[v]) ++rank[u];
    }
  }
};

