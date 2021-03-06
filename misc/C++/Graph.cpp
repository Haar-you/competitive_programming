
/*

 */

template <typename Cost = int> class Edge{
public:
  int from,to;
  Cost cost;
  Edge() {}
  Edge(int to, Cost cost): to(to), cost(cost){}
  Edge(int from, int to, Cost cost): from(from), to(to), cost(cost){}

  Edge rev() const {return Edge(to,from,cost);}
  
  friend ostream& operator<<(ostream &os, const Edge &e){
    os << "(FROM: " << e.from << "," << "TO: " << e.to << "," << "COST: " << e.cost << ")";
    return os;
  }
};

template <typename T> using Graph = vector<vector<Edge<T>>>;
template <typename T> using Tree = vector<vector<Edge<T>>>;

/*
template <typename T> class Graph{
public:
  int N;
  vector<vector<Edge<T>>> g;
  Graph(int N): N(N), g(N){}

  inline void add_edge(int from, int to, T w){
    g[from].push_back(Edge<T>(from, to, w));
  }

  inline void add_undirected(int a, int b, T w){
    g[a].push_back(Edge<T>(a, b, w));
    g[b].push_back(Edge<T>(b, a, w));
  }

  inline const size_t size() const {return g.size();}
  inline vector<Edge<T>>& operator[](size_t i){return g[i];}
  inline const vector<Edge<T>>& operator[](size_t i) const {return g[i];}
  inline const bool empty() const {return g.empty();}
  inline vector<Edge<T>>& front(){return g.front();}
  inline vector<Edge<T>>& back(){return g.back();}
  inline auto begin(){return g.begin();}
  inline auto end(){return g.end();}
};
*/

//Dijkstra algorithm
template <typename T>
vector<T> dijkstra(Graph<T> &graph, int src){
  int n = graph.size();
  vector<T> cost(n, -1);
  vector<bool> check(n, false);
  priority_queue<pair<T,int>, vector<pair<T,int>>, greater<pair<T,int>>> pq;

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

// 最短経路の数え上げを行うdijkstra
/*
  [問題例]
  https://atcoder.jp/contests/arc090/tasks/arc090_c
 */
template <typename T, int MOD>
vector<T> dijkstra_with_route_counting(Graph<T> &graph, int src, vector<LLI> &route_count){
  int n = graph.size();
  vector<T> cost(n, -1);
  vector<bool> check(n, false);
  priority_queue<pair<T,int>, vector<pair<T,int>>, greater<pair<T,int>>> pq;

  route_count.assign(n,0);
  route_count[src] = 1;
  
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
	route_count[e.to] = route_count[e.from];
	pq.push(make_pair(cost[e.to], e.to));
      }else{
	if(cost[e.to] > d+e.cost){
	  cost[e.to] = min(cost[e.to], d + e.cost);
	  route_count[e.to] = route_count[e.from];
	  if(!check[e.to]) pq.push(make_pair(cost[e.to], e.to));
	}else if(cost[e.to] == d+e.cost){
	  (route_count[e.to] += route_count[e.from]) %= MOD;
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

//Prim algorithm
template <typename T> vector<tuple<int,int,T>> prim(int n, const vector<vector<pair<int,T>>> &graph){
  using tii = tuple<int,int,T>;

  vector<bool> visit(n, false);
  vector<tii> ret;

  function<bool(tii,tii)> cmp = [](const tii &a, const tii &b){return get<2>(a) > get<2>(b);};
  priority_queue<tii, vector<tii>, decltype(cmp)> pq(cmp);
  
  visit[0] = true;
  for(auto &p : graph[0]) pq.push(make_tuple(0,p.fst,p.snd));

  while(not pq.empty()){
    auto t = pq.top(); pq.pop();

    if(visit[get<0>(t)] == visit[get<1>(t)]) continue;

    int i = visit[get<0>(t)] ? get<1>(t) : get<0>(t);
    for(auto &p : graph[i]){
      pq.push(make_tuple(i,p.fst,p.snd));
    }

    visit[i] = true;
    ret.push_back(t);
  }

  return ret;
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

//Traveling Salesman Problem
//O(n^2 2^n)
int TSP(vector<vector<int>> &graph, int src){
  int v = graph.size(), n = 1 << v;
  vector<vector<int>> dp(v, vector<int>(n, inf));
  REP(i,v) dp[i][1<<i] = graph[src][i];
  FOR(s,1,n) REP(i,v) if(s & (1<<i)) REP(j,v) if(!(s & (1<<j))) dp[j][s | (1<<j)] = min(dp[j][s | (1<<j)], dp[i][s] + graph[i][j]);
  return dp[src][n-1];
}

// Topological sort
class TopologicalSort{
public:
  static bool tsort_priority_queue(const vector<vector<int>> &graph, vector<int> &ret){
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



// 間接点の列挙
template <typename T> vector<int> articulation_points(Graph<T> &graph){
  int n = graph.size();
  vector<int> visit(n, -1), low(n, -1), ret;

  int v = 0;

  function<int(int)> dfs =
    [&](int cur){
      if(visit[cur] != -1) return visit[cur];
      visit[cur] = v;

      int temp = v;
      vector<int> children;
      ++v;

      for(auto &e : graph[cur]){
	if(visit[e.to] == -1) children.push_back(e.to);
	int t = dfs(e.to);
	temp = min(temp, t);
      }

      low[cur] = temp;

      if((cur != 0 || children.size() >= 2) and any_of(ALL(children), [&](int x){return low[x] >= visit[cur];}))
	ret.push_back(cur);

      return low[cur];
    };

  dfs(0);

  return ret;
}

// 橋の列挙
template <typename T> vector<Edge<T>> bridges(Graph<T> &graph){
  int n = graph.size();
  vector<int> visit(n,-1), low(n,-1);
  vector<Edge<T>> ret;
  int v = 0;
  function<int(int,int)> dfs =
    [&](int cur, int par){
      if(visit[cur] != -1) return visit[cur];
      visit[cur] = v;
      int temp = v;
      ++v;
      for(auto &e : graph[cur]){
	if(e.to == par) continue;
	int t = dfs(e.to, cur);
	temp = min(temp, t);
	if(low[e.to] > visit[cur]) ret.push_back(e);
      }  
      return low[cur] = temp;
    };
  
  dfs(0,-1);
  return ret;
}

// 強連結成分分解
template <typename T> vector<int> strongly_connected_components(Graph<T> &graph){
  int n = graph.size();
  vector<bool> visit(n);
  vector<int> check;

  function<void(int)> dfs =
    [&](int cur){
      visit[cur] = true;
      for(auto &e : graph[cur]) if(!visit[e.to]) dfs(e.to);
      check.push_back(cur);
    };
  
  REP(i,n) if(!visit[i]) dfs(i);

  Graph<T> rgraph(n);
  REP(i,n) for(auto &e : graph[i]) rgraph[e.to].push_back(e.rev());

  vector<int> ret(n,-1);

  reverse(ALL(check));

  function<void(int,int)> rdfs =
    [&](int cur, int i){
      ret[cur] = i;
      for(auto &e : rgraph[cur]) if(ret[e.to] == -1) rdfs(e.to,i);
    };

  int i = 0;
  for(auto c : check) if(ret[c] == -1) {rdfs(c,i); ++i;}
    
  return ret;
}

// 二重辺連結成分分解
template <typename T> vector<vector<int>> two_edge_connected_components(const Graph<T> &graph){
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


class UndirectedEulerianPath{
  int n; // node count
  int edges = 0; // edge count
  vector<unordered_map<int,int>> graph;
  vector<int> degree;

  void del(int i, int j){
    if(graph[i][j] == 1) graph[i].erase(j);
    else --graph[i][j];

    if(graph[j][i] == 1) graph[j].erase(i);
    else --graph[j][i];
  }

  void dfs(int cur, deque<int> &path){
    if(not graph[cur].empty()){
      int next = graph[cur].begin()->fst;
      del(cur, next);
      dfs(next, path);
    }

    while(not graph[cur].empty()){
      int next = graph[cur].begin()->fst;
      del(cur, next);
      deque<int> temp;
      dfs(next, temp);
      for(auto x : temp) path.push_back(x);
    }

    path.push_back(cur);
  }

public:
  UndirectedEulerianPath(int n): n(n), graph(n), degree(n){}

  void add(int i, int j){
    ++graph[i][j];
    ++graph[j][i];

    ++degree[i];
    ++degree[j];

    ++edges;
  }

  bool construct(vector<int> &ret){
    int odd = 0;
    int start = 0;
    REP(i,n){
      if(degree[i]%2==1){
	++odd;
	start = i;
      }
    }

    if(odd != 0 and odd != 2) return false;

    deque<int> temp;
    dfs(start, temp);

    ret = vector<int>(temp.begin(), temp.end());

    return (int)ret.size() == edges+1;
  }
};
