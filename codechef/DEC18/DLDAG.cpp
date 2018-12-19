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
template <typename T> using rev_priority_queue = priority_queue<T,vector<T>,greater<T>>;

int bfs(vector<unordered_set<int>> &graph, vector<int> &cost, vector<bool> &visit, int cur){
  visit[cur] = true;
  
  for(auto &next : graph[cur]){
    cost[next] = max(cost[next], cost[cur]+1);
  }

  for(auto &next : graph[cur]){
    if(!visit[next])
      bfs(graph, cost, visit, next);
  }
  
  return cost[cur];
}

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  int N,M; cin >> N >> M;

  vector<unordered_set<int>> graph(N);
  vector<unordered_set<int>> rev_graph(N);
  vector<int> size(N);
  vector<int> rev_size(N);
  
  REP(i,M){
    int u,v; cin >> u >> v;
    --u; --v;
    graph[u].insert(v);
    rev_graph[v].insert(u);
    size[u]++;
    rev_size[v]++;
  }

  ///////////////////////////

  deque<int> dq;
  vector<int> cost(N);
  vector<bool> visit(N,false);

  REP(i,N){
    if(rev_size[i] == 0){
      bfs(graph, cost, visit, i);
    }
  }

  ///////////////////////////
  priority_queue<pair<int,int>> next_vertices;

  REP(i,N){
    if(size[i] == 0){
      next_vertices.push({cost[i],i});
    }
  }

  vector<vector<int>> ans;

  int count_2 = 0;

  while(!next_vertices.empty()){
    if(next_vertices.size() == 1){
      int u = next_vertices.top().second; next_vertices.pop();

      for(auto v : rev_graph[u]){
	if(graph[v].size() > 0){
	  graph[v].erase(u);
	  if(graph[v].size() == 0){
	    next_vertices.push({cost[v],v});
	  }
	}
      }

      ans.push_back({1,u+1});

    }else{
      int u = next_vertices.top().second; next_vertices.pop();
      int v = next_vertices.top().second; next_vertices.pop();

      for(auto w : rev_graph[u]){
	if(graph[w].size() > 0){
	  graph[w].erase(u);
	  if(graph[w].size() == 0){
	    next_vertices.push({cost[w],w});
	  }
	}
      }

      for(auto w : rev_graph[v]){
	if(graph[w].size() > 0){
	  graph[w].erase(v);
	  if(graph[w].size() == 0){
	    next_vertices.push({cost[w],w});
	  }
	}
      }
      ++count_2;
      ans.push_back({2,u+1,v+1});
    }
  }

  cout << ans.size() << endl;
  for(auto &v : ans) join(cout, ALL(v));
  
  return 0;
}
