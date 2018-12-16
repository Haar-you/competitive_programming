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
	cost[j] = max(d,c);
	pq.push(make_pair(cost[j], j));
      }else{
	if(cost[j] > max(d,c)){
	  cost[j] = min(cost[j], max(d,c));
	  if(!check[j]) pq.push(make_pair(cost[j], j));
	}
      }
    }
  }
  
  return cost;
}


int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  int n,m,k; cin >> n >> m >> k;

  vector<int> x(k);
  REP(i,k){
    cin >> x[i]; --x[i];
  }

  vector<vector<pair<int,int>>> graph(n);

  REP(i,m){
    int u,v,w; cin >> u >> v >> w;
    if(u == v) continue;
    --u; --v;
    graph[u].push_back(make_pair(v, w));
    graph[v].push_back(make_pair(u, w));
  }

  auto res = dijkstra(graph, x[0]);
  
  int d = 0;

  REP(i,k){
    d = max(d, res[x[i]]);
  }

  vector<int> ans(k);
  REP(i,k) ans[i] = d;

  join(cout, ALL(ans));
  
  return 0;
}
