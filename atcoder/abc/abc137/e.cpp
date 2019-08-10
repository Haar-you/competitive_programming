#include <bits/stdc++.h>
#define LLI long long int
#define FOR(v, a, b) for(LLI v = (a); v < (b); ++v)
#define FORE(v, a, b) for(LLI v = (a); v <= (b); ++v)
#define REP(v, n) FOR(v, 0, n)
#define REPE(v, n) FORE(v, 0, n)
#define REV(v, a, b) for(LLI v = (a); v >= (b); --v)
#define ALL(x) (x).begin(), (x).end()
#define RALL(x) (x).rbegin(), (x).rend()
#define ITR(it, c) for(auto it = (c).begin(); it != (c).end(); ++it)
#define RITR(it, c) for(auto it = (c).rbegin(); it != (c).rend(); ++it)
#define EXIST(c,x) ((c).find(x) != (c).end())
#define fst first
#define snd second
#define popcount __builtin_popcount
#define UNIQ(v) (v).erase(unique(ALL(v)), (v).end())
#define bit(i) (1LL<<(i))

#ifdef DEBUG
#include <misc/C++/Debug.cpp>
#else
#define dump(...) ((void)0)
#endif

#define gcd __gcd

using namespace std;
template <class T> constexpr T lcm(T m, T n){return m/gcd(m,n)*n;}

template <typename I> void join(ostream &ost, I s, I t, string d=" "){for(auto i=s; i!=t; ++i){if(i!=s)ost<<d; ost<<*i;}ost<<endl;}
template <typename T> istream& operator>>(istream &is, vector<T> &v){for(auto &a : v) is >> a; return is;}

template <typename T, typename U> bool chmin(T &a, const U &b){return (a>b ? a=b, true : false);}
template <typename T, typename U> bool chmax(T &a, const U &b){return (a<b ? a=b, true : false);}
template <typename T, size_t N, typename U> void fill_array(T (&a)[N], const U &v){fill((U*)a, (U*)(a+N), v);}

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

template <typename C, typename T> void add_edge(C &g, int from, int to, T w){
  g[from].push_back(Edge<T>(from, to, w));
}

template <typename C, typename T> void add_undirected(C &g, int a, int b, T w){
  g[a].push_back(Edge<T>(a, b, w));
  g[b].push_back(Edge<T>(b, a, w));
}

bool visited[5000];
bool visited2[5000];

template <typename T>
vector<T> bellman_ford(const Graph<T> &graph, int src, bool &has_negative_cycle, T inf){
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

void dfs(int cur, const Graph<LLI> &g){
  if(visited[cur]) return;
  visited[cur] = true;

  for(auto &e : g[cur]){
    dfs(e.to, g);
  }
}

void dfs2(int cur, const Graph<LLI> &g){
  if(visited2[cur]) return;
  visited2[cur] = true;

  for(auto &e : g[cur]){
    dfs2(e.to, g);
  }
}

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  int N,M,P;
  while(cin >> N >> M >> P){
    Graph<LLI> g(N);
    REP(i,M){
      int a,b;
      LLI c;
      cin >> a >> b >> c;
      --a, --b;
      add_edge(g,a,b,P-c);
    }

    fill_array(visited, false);
    dfs(0,g);

    Graph<LLI> g2(N);
    for(auto &v : g){
      for(auto &e : v){
        add_edge(g2,e.to,e.from,e.cost);
      }
    }
    
    fill_array(visited2, false);
    dfs2(N-1,g2);

    REP(i,N){
      if(not visited[i] or not visited2[i]) g[i].clear();
    }

    bool neg;
    auto dist = bellman_ford(g,0,neg,1LL<<40);

    if(neg){
      cout << -1 << endl;
    }else{
      cout << max(0LL, -dist[N-1]) << endl;
    }
  }
  
  return 0;
}
