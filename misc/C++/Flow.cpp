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
  問題例

  [最小カット問題]
  https://atcoder.jp/contests/abc010/tasks/abc010_4
  https://kupc2016.contest.atcoder.jp/tasks/kupc2016_e
  https://arc074.contest.atcoder.jp/tasks/arc074_d
  https://atcoder.jp/contests/wupc2019/tasks/wupc2019_f

  [重み付き最大二部マッチング]
  http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2429 


 */

// Dinic algorithm
template <typename T, T INF> class Dinic{
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
      T f = INF;
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
  Dinic(int size): graph(size), size(size){}
 
  void add_edge(int from, int to, const T &cap){
    graph[from].push_back({to, cap});
  }
  
  T max_flow(int _s, int _t){
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


// Ford-Fulkerson algorithm
template <typename T, T INF> class FordFulkerson{
public:
  struct edge{
    int to, rev;
    T cap;
    bool is_rev;
  };
  
private:
  int size;

  vector<vector<edge>> graph;
  vector<bool> visit;
  
  T dfs(int from, int to, T flow){
    if(from == to) return flow;
    visit[from] = true;

    for(auto &e : graph[from]){
      if(!visit[e.to] and e.cap > 0){
        T d = dfs(e.to, to, min(flow, e.cap));
	if(d > 0){
	  e.cap -= d;
	  graph[e.to][e.rev].cap += d;
	  return d;
	}
      }
    }
    return 0;
  }
  
public:  
  FordFulkerson(int size): size(size), graph(size), visit(size){}

  void add_edge(int from, int to, const T &cap){
    graph[from].push_back((edge){to, (int)graph[to].size(), cap, false});
    graph[to].push_back((edge){from, (int)graph[from].size()-1, 0, true});
  }

  T max_flow(int s, int t){
    T ret = 0;

    while(1){
      visit.assign(size,false);
      T flow = dfs(s,t,INF);
      if(flow == 0) return ret;
      ret += flow;
    }
  }

  const vector<vector<edge>>& get_graph(){
    return graph;
  }
};

// 最大二部マッチング
class BipartiteMatching{
public:
  int x, y;
  FordFulkerson<int,INT_MAX> mflow;
  int s, t;
  BipartiteMatching(int x, int y): x(x), y(y), mflow(x+y+2), s(x+y), t(s+1){
    REP(i,x) mflow.add_edge(s,i,1);
    REP(i,y) mflow.add_edge(x+i,t,1);
  }

  void add_edge(int i, int j){
    mflow.add_edge(i,x+j,1);
  }

  int matching(){
    return mflow.max_flow(s,t);
  }

  vector<pair<int,int>> get_matching_edges(){
    auto g = mflow.get_graph();
    vector<pair<int,int>> ret;

    REP(i,(int)g.size()-2){
      for(const auto &e : g[i]){
	if((not e.is_rev) and e.cap==0 and e.to!=t) ret.push_back({i, e.to-x});
      }
    }

    return ret;
  }
};


// 最小費用流
template <typename T, T INF> class MinimumCostFlow{
public:
  struct edge{
    int from, to;
    T cap, cost;
    int rev;
    bool is_rev;
    edge(int from, int to, T cap, T cost, int rev, bool is_rev):
      from(from), to(to), cap(cap), cost(cost), rev(rev), is_rev(is_rev){}
  };

private:
  int size;
  vector<vector<edge>> g;

public:
  MinimumCostFlow(int size): size(size), g(size){}

  void add_edge(int from, int to, T cap, T cost){
    g[from].emplace_back(from, to, cap, cost, g[to].size(), false);
    g[to].emplace_back(to, from, 0, -cost, g[from].size()-1, true);
  }

  int min_cost_flow(int src, int dst, T f){
    T ret = 0, flow = f;
    vector<T> h(size,0), cost(size,INF);
    vector<int> prev_node(size), prev_edge(size);
    priority_queue<pair<T,int>, vector<pair<T,int>>, greater<pair<T,int>>> pq;
      
    while(flow>0){
      fill(ALL(cost), INF);

      // src -> dst の最小コスト経路を探索する。 (dijkstra algorithm)
      cost[src] = 0;
      pq.emplace(0,src);

      while(!pq.empty()){
	T c;
	int v;
	tie(c,v) = pq.top(); pq.pop();

	if(cost[v] < c) continue;
	
        REP(i,(int)g[v].size()){
	  edge &e = g[v][i];
	  int w = e.to;
	  T cap = e.cap, cst = e.cost;
	  if(cap > 0 && cost[w] + h[w] > cost[v] + h[v] + cst){
	    cost[w] = cost[v] + cst + h[v] - h[w];
	    prev_node[w] = v;
	    prev_edge[w] = i;
	    pq.emplace(cost[w],w);
	  }
	}
      }
      
      if(cost[dst] == INF) return -1; // dstへ到達不可能

      REP(i,size) h[i] += cost[i];


      // src -> dst の最小コスト経路へ流せる量(df)を決定する。
      T df = flow;
      for(int cur = dst; cur != src; cur = prev_node[cur]){
	df = min(df, g[prev_node[cur]][prev_edge[cur]].cap);
      }

      flow -= df;
      ret += df * h[dst];

      // capの更新
      for(int cur = dst; cur != src; cur = prev_node[cur]){
	edge &e = g[prev_node[cur]][prev_edge[cur]];
	e.cap -= df;
	g[cur][e.rev].cap += df;	
      }
    }
    
    return ret;
  }

  const vector<vector<edge>>& get_graph(){
    return g;
  }
};

// 重み付き最大二部マッチング
class WeightedBipartiteMatching{
public:
  int left, right;
  MinimumCostFlow<int,INT_MAX/2> mcflow;
  int s, t;

  WeightedBipartiteMatching(int left, int right): left(left), right(right), mcflow(left+right+2), s(left+right), t(s+1){
    REP(i,left) mcflow.add_edge(s, i, 1, 0);
    REP(i,right) mcflow.add_edge(left+i, t, 1, 0);
  }

  void add_edge(int from, int to, int cost){
    mcflow.add_edge(from, left+to, 1, cost);
  }

  int matching(const int flow){
    return mcflow.min_cost_flow(s, t, flow);
  }

  vector<tuple<int,int,int>> get_matching_edges(){
    auto g = mcflow.get_graph();
    vector<tuple<int,int,int>> ret;

    REP(i,left){
      for(auto &e : g[i]){
	if((not e.is_rev) and e.to != t and e.cap == 0) ret.emplace_back(i, e.to-left, e.cost);
      }
    }

    return ret;
  }
};
