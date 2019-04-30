#include <bits/stdc++.h>
#define FOR(v, a, b) for(int v = (a); v < (b); ++v)
#define FORE(v, a, b) for(int v = (a); v <= (b); ++v)
#define REP(v, n) FOR(v, 0, n)
#define REPE(v, n) FORE(v, 0, n)
#define REV(v, a, b) for(int v = (a); v >= (b); --v)
#define ALL(x) (x).begin(), (x).end()
#define RALL(x) (x).rbegin(), (x).rend()
#define ITR(it, c) for(auto it = (c).begin(); it != (c).end(); ++it)
#define RITR(it, c) for(auto it = (c).rbegin(); it != (c).rend(); ++it)
#define EXIST(c,x) ((c).find(x) != (c).end())
#define LLI long long int
#define fst first
#define snd second

#ifdef DEBUG
#include <misc/C++/Debug.cpp>
#else
#define dump(x) ((void)0)
#endif

using namespace std;

 
template <typename Cost = int> class Edge{
public:
  int from,to;
  Cost cost;
  Edge() {}
  Edge(int to, Cost cost): to(to), cost(cost){}
  Edge(int from, int to, Cost cost): from(from), to(to), cost(cost){}
 
  Edge rev() const {return Edge(to,from,cost);}
  
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

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  int N,M,K; cin >> N >> M >> K;

  vector<int> A(M), B(M), C(M);
  vector<vector<int>> v(N);
    
  REP(i,M){
    int a,b,c; cin >> a >> b >> c;
    --a;
    --b;

    if(a > b) swap(a, b);

    A[i] = a;
    B[i] = b;
    C[i] = c;
      
    v[a].push_back(c);
    v[b].push_back(c);
  }
  dump(v);

  for(auto &x : v){
    sort(ALL(x));
    x.erase(unique(ALL(x)), x.end());
  }
    
  int s = 0, t = N-1;
 
  vector<vector<int>> p(N);
  int cnt = N;
  {
    FOR(i,1,N-1){
      p[i] = vector<int>(v[i].size());
      REP(j,(int)v[i].size()){
	p[i][j] = cnt;
	++cnt;
      }
    }
  }
    
  Graph<int> graph(cnt);
    
  REP(i,M){
    if(A[i] == 0 and B[i] == N-1){
      graph[s].push_back(Edge<int>(s, t, 0));
      graph[t].push_back(Edge<int>(t, s, 0));
    }else if(A[i] == 0){
      int x = p[B[i]][lower_bound(ALL(v[B[i]]),C[i])-v[B[i]].begin()];
      graph[s].push_back(Edge<int>(s, x, 0));
      graph[x].push_back(Edge<int>(x, s, 0));
    }else if(B[i] == N-1){
      int x = p[A[i]][lower_bound(ALL(v[A[i]]),C[i])-v[A[i]].begin()];
      graph[x].push_back(Edge<int>(x, t, 0));
      graph[t].push_back(Edge<int>(t, x, 0));
    }else{
      int x = p[A[i]][lower_bound(ALL(v[A[i]]),C[i])-v[A[i]].begin()];
      int y = p[B[i]][lower_bound(ALL(v[B[i]]),C[i])-v[B[i]].begin()];
      graph[x].push_back(Edge<int>(x, y, 0));
      graph[y].push_back(Edge<int>(y, x, 0));
    }
  }
 
  FOR(i,1,N-1){
    for(auto j : p[i]){
      graph[i].push_back(Edge<int>(i, j, 1));
      graph[j].push_back(Edge<int>(j, i, 0));
    }
  }
 
  auto res = dijkstra(graph, s)[t];
 
  if(res < 0){
    cout << -1 << endl;
  }else{
    LLI ans = (res+1) * K;
    cout << ans << endl;
  }
  
  return 0;
}
