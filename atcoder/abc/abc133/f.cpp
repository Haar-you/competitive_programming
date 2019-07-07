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
template <typename T, typename U> istream& operator>>(istream &is, pair<T,U> &p){is >> p.first >> p.second; return is;}

template <typename T, typename U> bool chmin(T &a, const U &b){return (a>b ? a=b, true : false);}
template <typename T, typename U> bool chmax(T &a, const U &b){return (a<b ? a=b, true : false);}
template <typename T, size_t N, typename U> void fill_array(T (&a)[N], const U &v){fill((U*)a, (U*)(a+N), v);}

template <typename Cost = int> class Edge{
public:
  int from,to;
  Cost cost;
  int color;
  Edge() {}
  Edge(int to, Cost cost): to(to), cost(cost){}
  Edge(int from, int to, Cost cost): from(from), to(to), cost(cost){}
  Edge(int from, int to, Cost cost, int color): from(from), to(to), cost(cost), color(color){}

  Edge rev() const {return Edge(to,from,cost);}
  
  friend ostream& operator<<(ostream &os, const Edge &e){
    os << "(FROM: " << e.from << "," << "TO: " << e.to << "," << "COST: " << e.cost << ")";
    return os;
  }
};

template <typename T> using Tree = vector<vector<Edge<T>>>;

template <typename T> class LCA{
private:
  vector<vector<int>> parent;
  vector<int> depth;
  int n, log2n;
  void dfs(const Tree<T> &tree, int cur, int par, int dp){
    parent[cur][0] = par;
    depth[cur] = dp;
    for(auto &e : tree[cur]) if(e.to != par) dfs(tree, e.to, cur, dp+1);
  }
public:
  LCA(const Tree<T> &tree){
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

int dist[100100];

void dfs(const Tree<int> &tree, int cur, int par){
  for(auto &e : tree[cur]){
    if(e.to == par) continue;
    dist[e.to] = dist[e.from] + e.cost;
    dfs(tree, e.to, cur);
  }
}

int num[200100];
int sum[200100];
int col[200100];
int ver[200100];

void euler_tour(const Tree<int> &tree, int cur, int par, int &k){
  for(auto &e : tree[cur]){
    if(e.to == par) continue;

    num[k] = 1;
    sum[k] = e.cost;
    col[k] = e.color;
    ver[e.to] = k;
    ++k;

    euler_tour(tree, e.to, cur, k);
    
    num[k] = -1;
    sum[k] = -e.cost;
    col[k] = e.color;
    ++k;
  }
}

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  int n,q; cin >> n >> q;
  Tree<int> tree(n);
  REP(i,n-1){
    int a,b,c,d; cin >> a >> b >> c >> d;
    --a; --b;
    --c;
    tree[a].push_back(Edge<int>(a,b,d,c));
    tree[b].push_back(Edge<int>(b,a,d,c));
  }

  LCA<int> lca(tree);

  fill_array(dist, 0);
  dfs(tree, 0, -1);

  int k = 0;
  euler_tour(tree, 0, -1, k);
  ver[0] = -1;

  vector<vector<int>> nums(n,vector<int>(1)), sums(n,vector<int>(1)), indices(n);

  REP(i,k){
    int c = col[i];
    nums[c].push_back(num[i]);
    sums[c].push_back(sum[i]);
    indices[c].push_back(i);
  }

  REP(i,n){
    int m = nums[i].size();

    REP(j,m-1){
      nums[i][j+1] += nums[i][j];
      sums[i][j+1] += sums[i][j];
    }
  }
  
  REP(i,q){
    int x,y,u,v; cin >> x >> y >> u >> v;
    --u, --v;
    --x;

    int w = lca.query(u,v);

    int ans = dist[u] + dist[v] - dist[w]*2;

    int ui = upper_bound(ALL(indices[x]),ver[u]) - indices[x].begin();
    int vi = upper_bound(ALL(indices[x]),ver[v]) - indices[x].begin();
    int wi = upper_bound(ALL(indices[x]),ver[w]) - indices[x].begin();

    ans += (nums[x][ui]+nums[x][vi]-2*nums[x][wi])*y-(sums[x][ui]+sums[x][vi]-2*sums[x][wi]);
    
    cout << ans << endl;
  }
  
  return 0;
}
