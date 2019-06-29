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
#define sz(v) ((LLI)(v).size())

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
template <typename T, typename U> istream& operator>>(istream &is, pair<T,U> &p){is >> p.first >> p.second; return is;}

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

  int n,m;
  while(cin >> n >> m){
    Graph<int> graph(n);
    REP(i,m){
      int u,v; cin >> u >> v;
      --u; --v;
      graph.add_edge(u,v,1);
    }

    int s,t; cin >> s >> t;
    --s; --t;

    Graph<int> gr2(n*3);

    REP(k,3){
      REP(i,n){
	for(auto &e : graph[i]){
	  gr2.add_edge(e.from+k*n, e.to+((k+1)%3)*n, 1);
	}
      }
    }
    
    auto dijk = dijkstra(gr2, s);

    int ans = dijk[t];

    if(ans == -1){
      cout << -1 << endl;
    }else{
      cout << ans/3 << endl;
    }
  }
  
  return 0;
}
