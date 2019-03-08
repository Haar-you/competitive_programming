#include <bits/stdc++.h>
using namespace std;

template <typename T> class HLDecomposition{
  Tree<T> tree;
  int n;

  vector<int> sub, par, head, id, rid, next, end;

  int dfs_sub(int cur, int p){
    par[cur] = p;
    int t = 0;
    for(auto &e : tree[cur]){
      if(e.to == p) continue;
      sub[cur] += dfs_sub(e.to, cur);
      if(sub[e.to] > t){
	t = sub[e.to];
	next[cur] = e.to;
	swap(e, tree[cur][0]);
      }
    }
    return sub[cur];
  }

  void dfs_build(int cur, int &i){
    id[cur] = i;
    rid[i] = cur;
    ++i;

    for(auto &e : tree[cur]){
      if(e.to == par[cur]) continue;
      head[e.to] = (e.to == tree[cur][0].to ? head[cur] : e.to);
      dfs_build(e.to, i);
    }

    end[cur] = i;
  }
  

public:
  HLDecomposition(const Tree<T> &tree):
    tree(tree), n(tree.size()), sub(n,1), par(n,-1), head(n), id(n), rid(n), next(n,-1), end(n, -1){
    dfs_sub(0, -1);
    int i=0;
    dfs_build(0, i);
  }

  void path_query_vertex(int x, int y, const function<void(int,int)> &f){
    while(1){
      if(id[x] > id[y]) swap(x, y);
      f(max(id[head[y]], id[x]), id[y]+1);
      if(head[x] == head[y]) return;
      y = par[head[y]];
    }
  }

  void path_query_edge(int x, int y, const function<void(int,int)> &f){
    while(1){
      if(id[x] > id[y]) swap(x, y);
      if(head[x] == head[y]){
	if(x != y) f(id[x]+1, id[y]+1);
	return;
      }
      f(id[head[y]], id[y]+1);
      y = par[head[y]];
    }
  }

  int parent(int x){return par[x];};

  void subtree_query_edge(int x, const function<void(int,int)> &f){
    f(id[x]+1, end[x]);
  }
};
