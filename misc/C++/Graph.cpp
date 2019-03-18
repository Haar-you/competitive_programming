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
template <typename T> using Tree = vector<vector<Edge<T>>>;

//Dijkstra algorithm
template <typename T>
vector<T> dijkstra(Graph<T> &graph, int src){
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

    for(auto &e : graph[i]){
      if(cost[e.to] < 0){
	cost[e.to] = d + e.cost;
	pq.push(make_pair(cost[e.to], e.to));
      }else{
	if(cost[e.to] > d+e.cost){
	  cost[e.to] = min(cost[e.to], d + e.cost);
	  if(!check[e.to]) pq.push(make_pair(cost[e.to], e.to));
	}
      }
    }
  }
  
  return cost;
}

//Bellman-Ford algorithm
template <typename T>
vector<T> bellmanford(Graph<T> &graph, int src, bool &has_negative_cycle, T inf){
  int n = graph.size();
  vector<T> cost(n, inf);
  cost[src] = 0;

  has_negative_cycle = false;
  REP(i,n){
    REP(s,n){
      for(auto &node : graph[s]){
	int t = node.to;
	T d = node.cost;
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

  int get_depth(int a){
    return depth[a];
  }
 
  int distance(int a, int b){
    return depth[a] + depth[b] - 2 * depth[query(a,b)];
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



template <typename T> class GraphUtils{
public:
  // 間接点の列挙
  static int ap_dfs(int cur, Graph<T> &graph, vector<int> &visit, vector<int> &low, vector<int> &ret, int &v){
    if(visit[cur] != -1) return visit[cur];
    visit[cur] = v;

    int temp = v;
    vector<int> children;
    ++v;

    for(auto &next : graph[cur]){
      if(visit[next.to] == -1) children.push_back(next.to);
      int t = ap_dfs(next.to, graph, visit, low, ret, v);
      temp = min(temp, t);
    }

    low[cur] = temp;

    if((cur != 0 || children.size() >= 2) && any_of(ALL(children), [&](int x){return low[x] >= visit[cur];})) ret.push_back(cur);

    return low[cur];
  }

  static vector<int> articulation_points(Graph<T> &graph){
    int n = graph.size();
    vector<int> visit(n,-1), low(n,-1), ret;

    int v = 0;
    ap_dfs(0, graph, visit, low, ret, v);

    return ret;
  }

  // 橋の列挙
  static int br_dfs(int cur, int par, Graph<T> &graph, vector<int> &visit, vector<int> &low, vector<Edge<T>> &ret, int &v){
    if(visit[cur] != -1) return visit[cur];
    visit[cur] = v;
    int temp = v;
    ++v;
    for(auto &next : graph[cur]){
      if(next.to == par) continue;
      int t = br_dfs(next.to, cur, graph, visit, low, ret, v);
      temp = min(temp, t);
      if(low[next.to] > visit[cur]) ret.push_back(next);
    }  
    return low[cur] = temp; 
  }
  
  static vector<Edge<T>> bridges(Graph<T> &graph){
    int n = graph.size();
    vector<int> visit(n,-1), low(n,-1);
    vector<Edge<T>> ret;
    int v = 0;
    br_dfs(0,-1,graph,visit,low,ret,v);
    return ret;
  }

  // 強連結成分分解
  static void scc_dfs(int cur, Graph<T> &graph, vector<bool> &visit, vector<int> &check){
    visit[cur] = true;
    for(auto &e : graph[cur]) if(!visit[e.to]) scc_dfs(e.to,graph,visit,check);
    check.push_back(cur);
  }

  static void scc_rdfs(int cur, int i, Graph<T> &graph, vector<int> &ret){
    ret[cur] = i;
    for(auto &e : graph[cur]) if(ret[e.to] == -1) scc_rdfs(e.to,i,graph,ret);
  }

  static vector<int> strongly_connected_components(Graph<T> &graph){
    int n = graph.size();
    vector<bool> visit(n);
    vector<int> check(n);

    REP(i,n) if(!visit[i]) scc_dfs(i,graph,visit,check);

    Graph<T> rgraph(n);
    REP(i,n) for(auto &e : graph[i]) rgraph[e.to].push_back(e.rev());

    vector<int> ret(n,-1);

    reverse(ALL(check));
    int i = 0;
    for(auto c : check) if(ret[c] == -1) {scc_rdfs(c,i,rgraph,ret); ++i;}
    
    return ret;
  }

  // 二重辺連結成分分解
  static vector<vector<int>> two_edge_connected_components(const Graph<T> &graph){
    int n = graph.size();
    vector<vector<int>> ret;
    vector<int> order(n,-1);
    stack<int> S;
    vector<bool> inS(n,false);
    stack<int> roots;
    int v = 0;
    
    function<void(int,int)> dfs =
      [&](int cur, int par){
	order[cur] = v; ++v;
	S.push(cur);
	inS[cur] = true;
	roots.push(cur);
 
	for(auto &e : graph[cur]){
	  if(order[e.to] == -1){
	    dfs(e.to, cur);
	  }else if(e.to != par && inS[e.to]){
	    while(order[roots.top()] > order[e.to]) roots.pop();
	  }
	}
 
	if(cur == roots.top()){
	  vector<int> temp;
 
	  while(1){
	    auto node = S.top(); S.pop();
	    inS[node] = false;
	    temp.push_back(node);
	    if(node == cur) break;
	  }
	  
	  ret.push_back(temp);
	  roots.pop();
	}
      };
    
    REP(i,n) if(order[i] == -1) dfs(i, -1);
    return ret;
  }
};

// 最大独立集合の大きさ
// O(n*2^(n/2)) n<=40程度
// 二部グラフでは、(最大独立集合の大きさ) = (グラフの大きさ) - (最大二部マッチングの大きさ)となるので、最大二部マッチングを用いる。
int maximum_independent_set(vector<vector<int>> &graph){
  int n = graph.size();
  int h1 = n/2; //V1
  int h2 = n-h1; //V2

  vector<bool> dp1(1<<h1, true); // dp1[S] := Sが独立集合か?
  REP(i,h1) for(auto j : graph[i]) if(j<h1) dp1[(1<<i)|(1<<j)] = false;
  REP(i,1<<h1) if(!dp1[i]) REP(j,h1) dp1[i|(1<<j)] = false;

  vector<bool> dp2(1<<h2, true); // dp2[S] := Sが独立集合か?
  FOR(i,h1,n) for(auto j : graph[i]) if(j>=h1) dp2[(1<<(i-h1))|(1<<(j-h1))] = false;
  REP(i,1<<h2) if(!dp2[i]) REP(j,h2) dp2[i|(1<<j)] = false;

  vector<int> dp3(1<<h1, 0); // S1と接続しないV2の最大の部分集合
  dp3[0] = (1<<h2)-1;
  REP(i,h1){
    for(auto j : graph[i]) if(j>=h1) dp3[1<<i] |= (1<<(j-h1));
    dp3[1<<i] ^= ((1<<h2)-1);
  }
  REP(i,1<<h1) REP(j,h1) if((i&(1<<j)) == 0) dp3[i|(1<<j)] = dp3[i] & dp3[1<<j];

  vector<int> dp4(1<<h2, 0); // S2の最大独立集合の大きさ
  REP(i,1<<h2) if(dp2[i]) dp4[i] = __builtin_popcount(i);
  REP(i,1<<h2) REP(j,h2) if((i&(1<<j)) == 0) dp4[i|(1<<j)] = max(dp4[i|(1<<j)], dp4[i]);

  int ans = 0;
  REP(i,1<<h1) if(dp1[i]) chmax(ans, __builtin_popcount(i)+dp4[dp3[i]]);
  return ans;
}

// 二部グラフの判定
bool is_bipartite_graph(vector<vector<int>> &graph, LLI &a, LLI &b){
  vector<int> check(graph.size(), -1);
  vector<bool> visit(graph.size(), false);
  stack<int> st;

  st.push(0);
  check[0] = 0;

  while(!st.empty()){
    auto cur = st.top(); st.pop();
    if(visit[cur]) continue;
    visit[cur] = true;

    for(auto next : graph[cur]){
      if(check[next] == check[cur]) return false;

      if(check[next] == -1){
	check[next] = (check[cur]==0 ? 1 : 0);
      }

      st.push(next);
    }
  }

  a = b = 0;
  for(auto x : check) if(x) ++a; else ++b;
  
  return true;
}

bool is_bipartite_graph(vector<vector<int>> &graph, int root, vector<int> &check, vector<bool> &visit, int &a, int &b){
  stack<int> st;
 
  a = 1;
  b = 0;
  st.push(root);
  check[root] = 0;
 
  while(!st.empty()){
    auto cur = st.top(); st.pop();
    if(visit[cur]) continue;
    visit[cur] = true;
 
    for(auto next : graph[cur]){
      if(check[next] == check[cur]) return false;
 
      if(check[next] == -1){
	if(check[cur] == 0){
	  check[next] = 1;
	  ++b;
	}else{
	  check[next] = 0;
	  ++a;
	}
	st.push(next);
      }
    }
  }
  
  return true;
}

class BipartiteGraph{
  int n;
  UnionFind check;

public:
  BipartiteGraph(int n): n(n), check(2*n){}

  void add_diff(int i, int j){ // iとjを異なる色で塗る。
    check.merge(i,j+n);
    check.merge(i+n,j);
  }

  void add_same(int i, int j){ // iとjを同じ色で塗る。 = iとjを同じ端点と見做す。
    check.merge(i,j);
    check.merge(i+n,j+n);
  }

  bool is_bipartite_graph(int i){ // iを含む連結グラフが二部グラフかを判定する。
    return !check.same(i,i+n);
  }

  bool is_same(int i, int j){ // iとjが同じ色で塗られているか判定する。
    return check.same(i,j);
  }
};


// Euler tour
class EulerTour{
public:
  vector<int> arr;
  vector<int> begin, end;
  
  EulerTour(const vector<vector<int>> &tree){
    begin = vector<int>(tree.size());
    end = vector<int>(tree.size());
    
    function<void(int,int)> dfs =
      [&](int cur, int par){
	begin[cur] = arr.size();
	arr.push_back(cur);
	
	for(auto next : tree[cur]){
	  if(next == par) continue;
	  dfs(next, cur);
	  arr.push_back(cur);
	}
	end[cur] = arr.size();
      };

    dfs(0,-1);
  }
};


