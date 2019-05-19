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
#define popcount __builtin_popcount

#ifdef DEBUG
#include <misc/C++/Debug.cpp>
#else
#define dump(x) ((void)0)
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
  
  static bool cmp_to_lt(const Edge &e1, const Edge &e2){return e1.to < e2.to;}
  static bool cmp_cost_lt(const Edge &e1, const Edge &e2){return e1.cost < e2.cost;}
  static bool cmp_to_gt(const Edge &e1, const Edge &e2){return e1.to > e2.to;}
  static bool cmp_cost_gt(const Edge &e1, const Edge &e2){return e1.cost > e2.cost;}
  friend ostream& operator<<(ostream &os, const Edge &e){
    os << "(FROM: " << e.from << "," << "TO: " << e.to << "," << "COST: " << e.cost << ")";
    return os;
  }
};

template <typename T> using Tree = vector<vector<Edge<T>>>;

class TreeUtils{
public:
  template <typename T> static void distance(Tree<T> &tree, int cur, int par, vector<T> &dist, T d){
    dist[cur] = d;
    for(auto &next : tree[cur]){
      if(next.to == par) continue;
      distance(tree, next.to, cur, dist, d+next.cost);
    }
  }
};

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  int N;
  while(cin >> N){

    Tree<LLI> tree(N);
    REP(i,N-1){
      int u,v,w; cin >> u >> v >> w;
      --u, --v;
      tree[u].push_back(Edge<LLI>(u,v,w));
      tree[v].push_back(Edge<LLI>(v,u,w));
    }

    vector<LLI> d(N);
    TreeUtils::distance<LLI>(tree,0,-1,d,0);

    REP(i,N) d[i] %= 2;

    join(cout, ALL(d), "\n");
  }
  
  return 0;
}
