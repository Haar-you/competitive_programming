#ifndef COMPILE_TEST
#define COMPILE_TEST
#include "Basic.cpp"
#include "Misc.cpp"
#include "DataStructure.cpp"
#endif

/*

 */

template <typename Cost = int> class Edge{
public:
  int from,to;
  Cost cost;
  Edge() {}
  Edge(int to, Cost cost): to(to), cost(cost){}
  Edge(int from, int to, Cost cost): from(from), to(to), cost(cost){}

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
template <typename T> using Tree = vector<vector<Edge<T>>>;

//Dijkstra algorithm
template <typename T>
vector<T> dijkstra(vector<vector<pair<int,T>>> &graph, int src){
  int n = graph.size();
  vector<T> cost(n, -1);
  vector<bool> check(n, false);
  rev_priority_queue<pair<T,int>> pq;

  cost[src] = 0;
  pq.push(make_pair(0,src));

  while(!pq.empty()){
    int i; T d;
    tie(d,i) = pq.top(); pq.pop();

    if(check[i]) continue;
    check[i] = true;

    for(auto &next : graph[i]){
      int j; T c;
      tie(j,c) = next;

      if(cost[j] < 0){
	cost[j] = d + c;
	pq.push(make_pair(cost[j], j));
      }else{
	if(cost[j] > d+c){
	  cost[j] = min(cost[j], d + c);
	  if(!check[j]) pq.push(make_pair(cost[j], j));
	}
      }
    }
  }
  
  return cost;
}


//Bellman-Ford algorithm
template <typename T>
vector<T> bellmanford(vector<vector<pair<int,T>>> &graph, int src, bool &has_negative_cycle){
  int n = graph.size();
  vector<T> cost(n, inf);
  cost[src] = 0;

  has_negative_cycle = false;
  REP(i,n){
    REP(s,n){
      for(auto node : graph[s]){
	int t = node.first;
	T d = node.second;
	if(cost[s] < inf && cost[t] < inf && cost[s]+d < cost[t] && i == n-1){
	  has_negative_cycle = true;
	  return cost;
	}
	if(cost[s] >= inf && cost[t] >= inf) cost[t] = inf;
	else cost[t] = min(cost[t], cost[s]+d);
      }
    }
  }
  
  return cost;
}

//Warshall-Floyd algorithm
template <typename T>
vector<vector<T>> warshallfloyd(vector<vector<pair<int,T>>> &graph, bool &has_negative_cycle){
  int n = graph.size();
  vector<vector<T>> cost(n, vector<T>(n,inf));
  has_negative_cycle = false;
  REP(i,n) cost[i][i] = 0;
  REP(i,n) for(auto v : graph[i]) cost[i][v.first] = v.second;
  REP(k,n) REP(i,n) REP(j,n) if(cost[i][k] < inf && cost[k][j] < inf) cost[i][j] = min(cost[i][j], cost[i][k]+cost[k][j]);
  REP(i,n) if(cost[i][i] < 0) has_negative_cycle = true;
  return cost;
}

template <typename T>
vector<vector<T>> warshallfloyd(vector<vector<pair<int,T>>> &graph){
  int n = graph.size();
  vector<vector<T>> cost(n, vector<T>(n,inf));
  REP(i,n) cost[i][i] = 0;
  REP(i,n) for(auto v : graph[i]) cost[i][v.first] = v.second;
  REP(k,n) REP(i,n) REP(j,n) if(cost[i][k] < inf && cost[k][j] < inf) cost[i][j] = min(cost[i][j], cost[i][k]+cost[k][j]);
  return cost;
}

//Kruskal algorithm
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

//Lowest Common Ancestor
class LCA{
private:
  vector<vector<int>> parent;
  vector<int> depth;
  int n, log2n;
  void dfs(vector<vector<int>> &tree, int cur, int par, int dp){parent[cur][0] = par; depth[cur] = dp; for(auto next : tree[cur]) if(next != par) dfs(tree, next, cur, dp+1);}
public:
  LCA(vector<vector<int>> &tree){
    n = tree.size();
    log2n = (int)ceil(log(n) / log(2)) + 1;
    parent = vector<vector<int>>(n, vector<int>(log2n, 0));
    depth = vector<int>(n, 0);

    dfs(tree, 0, -1, 0);
    REP(k,log2n-1) REP(v,n) parent[v][k+1] = (parent[v][k] < 0) ? -1 : parent[parent[v][k]][k];
  }

  int query(int a, int b){
    if(depth[a] >= depth[b]) swap(a,b);
    REP(k,log2n) if((depth[b] - depth[a]) >> k & 1) b = parent[b][k];
    if(a == b) return a;
    REV(k, log2n-1, 0) if(parent[a][k] != parent[b][k]){a = parent[a][k]; b = parent[b][k];}
    return parent[a][0];
  }
};


//Dinic algorithm (maximum flow algrithm)
template <typename T> class Dinic{
private:
  vector<vector<pair<int,T>>> graph;
  int size, s, t;
  vector<vector<T>> cap;
  vector<int> level;
  
  bool buildLevel(){
    fill(ALL(level), 0);
    level[s] = 1;
    deque<int> deq = {s};
    while(!deq.empty()){
      int cur = deq.front(); deq.pop_front();
      REP(i,size)
	if(level[i]==0 && cap[cur][i]>0){
	  level[i] = level[cur] + 1;
	  deq.push_back(i);
	}
    }
    return level[t] != 0;
  }
  void dfs(vector<int> &path, T &flow){
    if(path.empty()) return;
    int cur = path.back();
    if(cur == t){
      T f = inf;
      FOR(i,1,path.size()) f = min(f, cap[path[i-1]][path[i]]);
      FOR(i,1,path.size()){
	cap[path[i-1]][path[i]] -= f;
	cap[path[i]][path[i-1]] += f;
      }
      flow += f;
    }else{
      REP(i,size){
	if(cap[cur][i]>0 && level[i]>level[cur]){
	  path.push_back(i);
	  dfs(path, flow);
	  path.pop_back();
	}
      }
    }
  }
  T augment(){
    T f = 0;
    vector<int> path = {s};
    dfs(path, f);
    return f;
  }
  T loop(){
    T f = 0;
    while(buildLevel()) f += augment();
    return f;
  }

public:
  Dinic(vector<vector<pair<int,T>>> &_graph): graph(_graph), size(graph.size()) {}

  T query(int _s, int _t){
    cap = vector<vector<T>>(size, vector<T>(size, 0));
    level = vector<int>(size, 0);

    REP(i,size)
      for(auto &p : graph[i]){
	int j = p.first;
	T d = p.second;
	cap[i][j] += d;
      }

    s = _s;
    t = _t;

    return loop();
  }
};

//Traveling Salesman Problem
//O(n^2 2^n)
int TSP(vector<vector<int>> &graph, int src){
  int v = graph.size(), n = 1 << v;
  vector<vector<int>> dp(v, vector<int>(n, inf));
  REP(i,v) dp[i][1<<i] = graph[src][i];
  FOR(s,1,n) REP(i,v) if(s & (1<<i)) REP(j,v) if(!(s & (1<<j))) dp[j][s | (1<<j)] = min(dp[j][s | (1<<j)], dp[i][s] + graph[i][j]);
  return dp[src][n-1];
}

// 最大二部マッチング
int bipartite_matching(vector<pair<int,int>> edges, int x, int y){
  vector<vector<pair<int,int>>> graph(x+y+2);

  int s=x+y, t=s+1;
  
  for(auto p : edges) graph[p.first].push_back(make_pair(x+p.second,1));
  REP(i,x) graph[s].push_back(make_pair(i,1));
  FOR(i,x,x+y) graph[i].push_back(make_pair(t,1));

  Dinic<int> d(graph);
  return d.query(s,t);
}


// Topological sort
class TopologicalSort{
public:
  static bool tsort_priority_queue(vector<vector<int>> graph, vector<int> &ret){
    int n = graph.size();
    vector<int> indeg(n);
    REP(i,n){
      for(auto j : graph[i]){
	++indeg[j];
      }
    }
    priority_queue<int,vector<int>,greater<int>> q;
    REV(i,n-1,0){
      if(indeg[i]==0) q.push(i);
    }

    while(!q.empty()){
      int cur = q.top(); q.pop();
      ret.push_back(cur);
      for(auto next : graph[cur]){
	--indeg[next];
	if(indeg[next]==0){
	  q.push(next);
	}
      }
    }
    
    return ret.size()==n;
  }
};

class TreeUtils{
public:
  template <typename T> static pair<int,T> farthest(Tree<T> &tree, int cur, int par = -1){
    auto d = make_pair(cur, 0);
    for(auto &next : tree[cur]){
      if(next.to == par) continue;
      auto t = farthest(tree, next.to, cur);
      t.second += next.cost;
      if(t.second > d.second) d = t;
    }
    return d;
  }

  template <typename T> static void distance(Tree<T> &tree, int cur, int par, vector<T> &dist, T d){
    dist[cur] = d;
    for(auto &next : tree[cur]){
      if(next.to == par) continue;
      distance(tree, next.to, cur, dist, d+next.cost);
    }
  }
  
  template <typename T> static T diameter(Tree<T> &tree){
    auto a = farthest(tree, 0);
    auto b = farthest(tree, a.first);
    return b.second;
  }

  template <typename T> static vector<T> height(Tree<T> &tree){
    auto a = farthest(tree, 0);
    auto b = farthest(tree, a.first);

    int n = tree.size();
    vector<T> d1(n), d2(n), h(n);

    distance(tree, a.first, -1, d1, 0);
    distance(tree, b.first, -1, d2, 0);

    REP(i,n) h[i] = max(d1[i], d2[i]);
    
    return h;
  }
};
