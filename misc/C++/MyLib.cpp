#include <bits/stdc++.h>
#define FOR(v, a, b) for(int v = (a); v < (b); ++v)
#define FORE(v, a, b) for(int v = (a); v <= (b); ++v)
#define REP(v, n) FOR(v, 0, n)
#define REPE(v, n) FORE(v, 0, n)
#define REV(v, a, b) for(int v = (a); v >= (b); --v)
#define RS resize
#define CLR clear
#define PB push_back
#define ALL(x) (x).begin(), (x).end()
#define LLI long long int
using namespace std;

template <typename T> using V = vector<T>;
template <typename T, typename U> using P = pair<T,U>;

template <typename T> T gcd(T a, T b){a = abs(a); b = abs(b); if(a<b) swap(a,b); while(b>0){a %= b; swap(a,b);} return a;}
template <typename T> T lcm(T a, T b){return (1LL * a * b) / gcd(a,b);}

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  
  return 0;
}

int dir4[4][2] = {{1,0},{-1,0},{0,1},{0,-1}};
int dir5[5][2] = {{1,0},{-1,0},{0,1},{0,-1},{0,0}};
int dir8[8][2] = {{1,0},{-1,0},{0,1},{0,-1},{1,1},{1,-1},{-1,1},{-1,-1}};
int dir9[9][2] = {{1,0},{-1,0},{0,1},{0,-1},{1,1},{1,-1},{-1,1},{-1,-1},{0,0}};

const int inf = INT_MAX;

template <typename T>
LLI power(T n, T p, T m){
  if(p==0) return 1LL;
  if(p==1) return n;
  LLI k = power(n, p/2, m);
  return (k*k*(p%2?n:1))%m;
}

// mod逆数
template <typename T> LLI modInv(T n, T p){return power(n,p-2,p);}

template <typename T> LLI factorial(T n, T m){LLI k = 1LL; FORE(i,1,n) k = (k*i) % m; return k;}

template <typename T> LLI combination(T n, T k, T p){if(n<k||n<0||k<0) return 0; if(n==0||k==0) return 1; return (((n*modInv(k,p))%p)*combination(n-1,k-1,p))%p;}

template <typename T> LLI permutaion(T n, T k, T p){if(n<k||n<0||k<0) return 0; if(n==0||k==0) return 1; return (n * permutaion(n-1,k-1,p)) % p;}
// 符号関数
template <typename T> int sign(T n){return (n>0)-(n<0);}

// a/b以上の最小の整数
template <typename T> T ceilGE(T a, T b){if(a % b) return a/b+1-(sign(a)*sign(b)<0?1:0); return a/b;}
// a/bを超える最小の整数
template <typename T> T ceilGT(T a, T b){return a/b+1-(sign(a)*sign(b)<0?1:0);}

// a/b以下の最大の整数
template <typename T> T floorLE(T a, T b){return a/b-(sign(a)*sign(b)<0?1:0);}
// a/b未満の最大の整数
template <typename T> T floorLT(T a, T b){if(a % b) return a/b-(sign(a)*sign(b)<0?1:0); return a/b-1;}

// 二乗判定
template <typename T> bool isSquare(T n){T rt = sqrt(n); return rt*rt == n;}

int countDivisor(LLI n){int count = 0; for(LLI i=1LL; i*i<=n; ++i) if(n%i == 0) ++count; count = count*2-(isSquare(n)?1:0); return count;}

vector<LLI> listDivisors(LLI n){
  vector<LLI> temp, res;
  for(LLI i=1LL; i*i<n; ++i) if(n%i == 0) temp.push_back(i);
  for(auto i : temp) res.push_back(i);
  if(isSquare(n)) res.push_back((LLI)sqrt(n));
  for(auto itr=temp.rbegin(); itr!=temp.rend(); ++itr) res.push_back(n/(*itr));
  return res;
}














//unionfind木
class UnionFind{
  vector<int> parent, depth, size;
public:
  UnionFind(int n): parent(n), depth(n,1), size(n,1){REP(i, n) parent[i] = i;}
  int getRoot(int i){
    if(parent[i] == i) return i;
    else return parent[i] = getRoot(parent[i]);
  }
  bool isSame(int i, int j){return getRoot(i) == getRoot(j);}
  void merge(int i, int j){
    int ri = getRoot(i), rj = getRoot(j);
    if(ri != rj){
      if(depth[ri] < depth[rj]){
	parent[ri] = rj; size[rj] += size[ri];
      }else{
	parent[rj] = ri; size[ri] += size[rj];
	if(depth[ri] == depth[rj]) ++depth[ri];
      }
    }
  }
  int getSize(int i){return size[getRoot(i)];}
};

//重み付きunoinfind木
class WeightedUnionFind{
  vector<int> parent, depth, size, weight;
public:
  WeightedUnionFind(int n): parent(n), depth(n,1), size(n,1), weight(n,0){REP(i, n) parent[i] = i;}
  int getRoot(int i){
    if(parent[i] == i) return i;
    else {int p=getRoot(parent[i]); weight[i] += weight[parent[i]]; return parent[i] = p;}
  }
  int getWeight(int i){getRoot(i); return weight[i];} 
  bool isSame(int i, int j){return getRoot(i) == getRoot(j);}
  bool diff(int i, int j, int &res){res = getWeight(i)-getWeight(j); return isSame(i,j);}
  void merge(int i, int j, int w){
    int ri = getRoot(i), rj = getRoot(j);
    if(ri != rj){
      if(depth[ri] < depth[rj]){
	parent[ri] = rj; size[rj] += size[ri]; weight[ri] = w - weight[i] + weight[j];
      }else{
	parent[rj] = ri; size[ri] += size[rj]; weight[rj] = -w + weight[i] - weight[j];
	if(depth[ri] == depth[rj]) ++depth[ri];
      }
    }
  }
  int getSize(int i){return size[getRoot(i)];}
};

//Dijkstra algorithm
template <typename T>
vector<T> dijkstra(vector<vector<pair<int,T>>> &graph, int src){
  int n = graph.size();
  vector<T> cost(n, -1);
  vector<bool> check(n, false);
  priority_queue<pair<T,int>, vector<pair<T,int>>, greater<pair<T,int>>> pq;

  cost[src] = 0;
  pq.push(make_pair(0,src));

  while(!pq.empty()){
    pair<T,int> temp = pq.top(); pq.pop();
    int v = temp.second;
    T d = temp.first;
    check[v] = true;

    for(auto next : graph[v]){
      int u = next.first;
      T c = next.second;

      if(cost[u] < 0){
	cost[u] = d + c;
	pq.push(make_pair(cost[u], u));
      }else{
	cost[u] = min(cost[u], d + c);
	if(!check[u]) pq.push(make_pair(cost[u], u));
      }
    }
  }
  
  return cost;
}

//Bellman-Ford algorithm
template <typename T>
vector<T> bellmanford(vector<vector<pair<int,T>>> &graph, int src, bool &has_negative_cycle){
  int n = graph.size();
  vector<T> cost(n, inf);
  cost[src] = 0;

  has_negative_cycle = false;
  REP(i,n){
    REP(s,n){
      for(auto node : graph[s]){
	int t = node.first;
	T d = node.second;
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

//Kruskal algorithm
template <typename T>
vector<tuple<int,int,T>> kruskal(int n, vector<tuple<int,int,T>> &graph){
  sort(graph.begin(), graph.end(), [](tuple<int,int,T> &a, tuple<int,int,T> &b){return get<2>(a) < get<2>(b);});
  UnionFind uf(n);
  vector<tuple<int,int,T>> mst;
  for(auto v : graph){
    int s,t,d;
    tie(s,t,d) = v;
    if(!uf.isSame(s,t)){
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
};

//Longest Common Subsequence
template <typename T>
int LCS(T a, T b){
  vector<vector<int>> dp(a.size()+1, vector<int>(b.size()+1, 0));
  FORE(i,1,a.size()) FORE(j,1,b.size()) dp[i][j] = a[i-1] == b[j-1] ? dp[i-1][j-1]+1 : max(dp[i-1][j], dp[i][j-1]);
  return dp[a.size()][b.size()];
}

//Longest Increasing Subsequence
template <typename T>
int LIS(T xs){
  vector<int> dp(xs.size(), inf);
  for(auto x : xs) dp[lower_bound(ALL(dp),x)-dp.begin()] = x;
  int i; for(i=0;i<xs.size() && dp[i]<inf;++i); return i;
}

//Levenshtein distance
int levenshtein(string a, string b){
  vector<vector<int>> dp(a.size()+1, vector<int>(b.size()+1, 0));
  REPE(i,a.size()) dp[i][0] = i;
  REPE(i,b.size()) dp[0][i] = i;
  FORE(i,1,a.size()) FORE(j,1,b.size())
    dp[i][j] = min(min(dp[i-1][j]+1, dp[i][j-1]+1), dp[i-1][j-1]+(a[i-1] == b[j-1] ? 0 : 1));
  return dp[a.size()][b.size()];
}

//Rolling Hash
class RollingHash{
private:
  string str;
  LLI base, mod;
  int sl;
  vector<LLI> shash, pow;
  LLI hash(int i, int j){return (shash[j] - shash[i] * pow[j-i] + mod*mod) % mod;}
public:
  RollingHash(string _str, LLI _base, LLI _mod): str(_str), base(_base), mod(_mod), sl(str.size()), pow(sl+1), shash(sl+1){
    pow[0] = 1; shash[0] = 0;
    FORE(i,1,sl){shash[i] = (shash[i-1]*base+str[i-1]) % mod; pow[i] = pow[i-1]*base % mod;}
  }
  vector<int> find(string p){
    vector<int> r;
    int pl = p.size();
    LLI phash = 0; FOR(i,0,pl) phash = (phash*base+p[i]) % mod;
    REPE(i,sl-pl) if(hash(i,i+pl) == phash) r.push_back(i);
    return r;
  }
};


//Rolling Hash (2D version)
class RollingHash2D{
private:
  vector<string> strs;
  LLI baseh, basew, mod;
  int slh, slw;
  vector<vector<LLI>> shash;
  vector<LLI> powh, poww;
  LLI hash(int i1, int j1, int i2, int j2){
    return (((shash[i2][j2]-(shash[i1][j2]*powh[i2-i1])%mod+mod*mod)%mod - (shash[i2][j1]*poww[j2-j1])%mod + mod*mod)%mod + ((shash[i1][j1]*powh[i2-i1])%mod*poww[j2-j1])%mod)%mod;
  }
public:
  RollingHash2D(vector<string> _strs, LLI _baseh, LLI _basew, LLI _mod):
    strs(_strs), baseh(_baseh), basew(_basew), mod(_mod), slh(strs.size()), slw(strs[0].size()),
    powh(slh+1), poww(slw+1), shash(slh+1, vector<LLI>(slw+1, 0)){
    powh[0] = 1; FORE(i,1,slh) powh[i] = (powh[i-1]*baseh) % mod;
    poww[0] = 1; FORE(i,1,slw) poww[i] = (poww[i-1]*basew) % mod;
    FORE(i,1,slh) FORE(j,1,slw) shash[i][j] = (shash[i][j-1] * basew + strs[i-1][j-1]) % mod;
    FORE(i,1,slh) FORE(j,1,slw) shash[i][j] = (shash[i-1][j] * baseh + shash[i][j]) % mod;
  }
  
  vector<pair<int,int>> find(vector<string> p){
    vector<pair<int,int>> r;
    int plh = p.size(), plw = p[0].size();
    LLI phash = 0;
    FOR(i,0,plh){
      LLI temp = 0; FOR(j,0,plw) temp = (temp*basew+p[i][j]) % mod;
      phash = (phash*baseh+temp) % mod;
    }
    
    REPE(i,slh-plh) REPE(j,slw-plw) if(hash(i,j,i+plh,j+plw) == phash) r.push_back(make_pair(i,j));
    return r;
  }
};

//Binary Indexed Tree (1-indexed)
class BIT_1{
private:
  vector<int> tree;
  int n;
public:
  BIT_1(int size): tree(size+1, 0), n(size){}
  void update(int x, int a){while(x <= n){tree[x] += a; x += (x & (-x));}}
  int sum(int x){int a = 0; while(x > 0){a += tree[x]; x -= (x & (-x));} return a;}
  int get(int x){return sum(x) - (x==1 ? 0 : sum(x-1));}
};

//Binary Indexed Tree (0-indexed)
class BIT_0{
private:
  vector<int> tree;
  int n;
public:
  BIT_0(int size): tree(size, 0), n(size){}
  void update(int x, int a){while(x < n){tree[x] += a; x |= (x + 1);}}
  int sum(int x){int a = 0; while(x >= 0){a += tree[x]; x = (x & (x+1)) - 1;} return a;}
  int get(int x){return sum(x) - (x==0 ? 0 : sum(x-1));}
};


//Dinic algorithm (maximum flow algrithm)
class Dinic{
private:
  vector<vector<pair<int,int>>> graph;
  int size, s, t;
  vector<vector<int>> cap;
  vector<int> level;
  bool buildLevel(){
    fill(ALL(level), 0);
    level[s] = 1;
    deque<int> deq = {s};
    while(!deq.empty()){
      int cur = deq.front(); deq.pop_front();
      REP(i,size) if(level[i]==0 && cap[cur][i]>0){level[i] = level[cur] + 1; deq.push_back(i);}
    }
    return level[t] != 0;
  }
  void dfs(vector<int> &path, int &flow){
    if(path.empty()) return;
    int cur = path.back();
    if(cur == t){
      int f = inf;
      FOR(i,1,path.size()) f = min(f, cap[path[i-1]][path[i]]);
      FOR(i,1,path.size()){cap[path[i-1]][path[i]] -= f; cap[path[i]][path[i-1]] += f;}
      flow += f;
    }else{
      REP(i,size){if(cap[cur][i]>0 && level[i]>level[cur]){path.push_back(i); dfs(path, flow); path.pop_back();}}
    }
  }
  int augment(){int f = 0; vector<int> path = {s}; dfs(path, f); return f;}
  int loop(){int f = 0; while(buildLevel()) f += augment(); return f;}
public:
  int flow;
  Dinic(vector<vector<pair<int,int>>> &_graph, int _s, int _t):
    graph(_graph), size(graph.size()), s(_s), t(_t), cap(size, vector<int>(size, 0)), level(size, 0){
    REP(i,size) for(auto p : graph[i]){int j = p.first, d = p.second; cap[i][j] += d;}
    flow = loop();
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
