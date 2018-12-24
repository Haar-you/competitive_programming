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

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  
  return 0;
}

// グラフ用クラス
template <typename T> using Graph = vector<vector<T>>;
template <typename T> using Tree = vector<vector<T>>;

template <typename Cost = int> class WEdge{
public:
  int to;
  Cost cost;
  WEdge(int to, Cost cost): to(to), cost(cost){}

  static bool cmp_to_lt(const WEdge &e1, const WEdge &e2){return e1.to < e2.to;}
  static bool cmp_cost_lt(const WEdge &e1, const WEdge &e2){return e1.cost < e2.cost;}
  static bool cmp_to_gt(const WEdge &e1, const WEdge &e2){return e1.to > e2.to;}
  static bool cmp_cost_gt(const WEdge &e1, const WEdge &e2){return e1.cost > e2.cost;}
  void show(){
    cerr << "to: " << to << " cost: " << cost << endl;
  }
};

// 入出力ストリーム関連
template <typename T, typename U> ostream& operator<<(ostream& os, pair<T,U> &p){
  os << p.first << "," << p.second;
  return os;
}

template <typename T, typename U> istream& operator>>(istream &is, pair<T,U> &p){
  is >> p.first >> p.second;
  return is;
}

template <typename T> istream& operator>>(istream &is, vector<T> &v){
  for(auto &a : v) is >> a;
  return is;
}



template <typename T> using rev_priority_queue = priority_queue<T,vector<T>,greater<T>>;

template <typename T, typename U> P<T,U> operator+(const P<T,U> &a, const P<T,U> &b){return {a.first + b.first, a.second + b.second};}
template <typename T, typename U> P<T,U> operator-(const P<T,U> &a, const P<T,U> &b){return {a.first - b.first, a.second - b.second};}


const int dir4[4][2] = {{1,0},{-1,0},{0,1},{0,-1}};
const int dir5[5][2] = {{1,0},{-1,0},{0,1},{0,-1},{0,0}};
const int dir8[8][2] = {{1,0},{-1,0},{0,1},{0,-1},{1,1},{1,-1},{-1,1},{-1,-1}};
const int dir9[9][2] = {{1,0},{-1,0},{0,1},{0,-1},{1,1},{1,-1},{-1,1},{-1,-1},{0,0}};

const int inf = INT_MAX;

// 代わりに __gcd, __lcm を使う。
//template <typename T> T gcd(T a, T b){a = abs(a); b = abs(b); if(a<b) swap(a,b); while(b>0){a %= b; swap(a,b);} return a;}
//template <typename T> T lcm(T a, T b){return (1LL * a * b) / gcd(a,b);}

template <typename T> LLI power(T n, T p, T m){if(p==0) return 1LL; if(p==1) return n; LLI k = power(n, p/2, m); return ((k*k)%m*(p%2?n:1))%m;}

// mod逆数
template <typename T> LLI modInv(T n, T p){return power(n,p-2,p);}

template <typename T> LLI factorial(T n, T m){LLI k = 1LL; FORE(i,1,n) k = (k*i) % m; return k;}
template <typename T> LLI combination(T n, T k, T p){if(n<k||n<0||k<0) return 0; if(n==0||k==0) return 1; return (((n*modInv(k,p))%p)*combination(n-1,k-1,p))%p;}
template <typename T> LLI permutaion(T n, T k, T p){if(n<k||n<0||k<0) return 0; if(n==0||k==0) return 1; return (n * permutaion(n-1,k-1,p)) % p;}

// 組み合わせ関連の前計算用クラス
template <int mod> class MyCombination{
public:
  vector<LLI> facto = {1};
  vector<LLI> ifacto = {1};

  LLI factorial(int i){
    if(i < 0) throw exception();
    if(facto.size() <= i) facto.resize(i+1, -1);
    if(i == 0) return facto[0] = 1;
    int j = i;
    for(;j>=0;--j) if(facto[j] != -1) break;
    for(int k=j+1; k<=i; ++k) (facto[k] = facto[k-1] * k) %= mod;
    return facto[i];
  }

  LLI factorial_inverse(int i){
    if(i < 0) throw exception();
    if(ifacto.size() <= i) ifacto.resize(i+1, -1);
    if(ifacto[i] != -1) return ifacto[i];
    ifacto[i] = modInv(factorial(i), mod);
  }

  LLI P(int n, int k){
    return (factorial(n) * factorial_inverse(n-k)) % mod;
  }

  LLI C(int n, int k){
    return (P(n,k) * factorial_inverse(k)) % mod;
  }

  LLI H(int n, int k){
    return C(n+k-1, n);
  }
};


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
template <typename T> bool is_square(T n){T rt = sqrt(n); return rt*rt == n;}

// 約数個数
int count_divisor(LLI n){int count = 0; for(LLI i=1LL; i*i<=n; ++i) if(n%i == 0) ++count; count = count*2-(is_square(n)?1:0); return count;}

// 約数列挙
vector<LLI> divisor_list(LLI n){
  vector<LLI> temp, res;
  for(LLI i=1LL; i*i<n; ++i) if(n%i == 0) temp.push_back(i);
  for(auto i : temp) res.push_back(i);
  if(is_square(n)) res.push_back((LLI)sqrt(n));
  for(auto itr=temp.rbegin(); itr!=temp.rend(); ++itr) res.push_back(n/(*itr));
  return res;
}

vector<bool> prime_table(int n){
  vector<bool> res(n+1, true);
  res[0] = res[1] = false;
  FOR(i,2,n) if(res[i]) for(int j=2*i; j<=n; j+=i) res[j] = false;
  return res;
}

bool is_prime(int n){
  if(n<=1) return false;
  for(int i=2; i*i<=n; ++i){
    if(n%i==0) return false;
  }
  return true;
}

// 素因数分解
vector<int> prime_factorize(int n){
  vector<int> res;
  for(int i=2; i*i<=n; ++i){
    if(n%i == 0){
      res.push_back(i);
      n/=i;
      --i;
    }
  }
  if(n!=1) res.push_back(n);
  return res;
}

// n以上の最小の2の冪
template <typename T = int>
T minimum_power_2(T n){
  T i = 1;
  while(i<n) i = (i<<1);
  return i;
}

// 二分探索
// fが適当なxの前後でtrueからfalseに変わる場合tfはtrue, falseからtrueに変わる場合tfはfalse.
LLI my_binary_search(LLI lower, LLI upper, function<bool(LLI)> f, bool tf=true){
  LLI mid;
  while(abs(upper-lower)>1){
    mid = (lower+upper)/2;
    
    if(f(mid)^(!tf)) lower = mid;
    else upper = mid;
  }
  return upper;
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
	cost[j] = d + c;
	pq.push(make_pair(cost[j], j));
      }else{
	if(cost[j] > d+c){
	  cost[j] = min(cost[j], d + c);
	  if(!check[j]) pq.push(make_pair(cost[j], j));
	}
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
public:
  RollingHash(string _str, LLI _base, LLI _mod): str(_str), base(_base), mod(_mod), sl(str.size()), pow(sl+1), shash(sl+1){
    pow[0] = 1; shash[0] = 0;
    FORE(i,1,sl){shash[i] = (shash[i-1]*base+str[i-1]) % mod; pow[i] = pow[i-1]*base % mod;}
  }
  LLI hash(int i, int j){return (shash[j] - shash[i] * pow[j-i] + mod*mod) % mod;}
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
template <typename T> class Dinic{
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
      T f = inf;
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

  T query(int _s, int _t){
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

//Traveling Salesman Problem
//O(n^2 2^n)
int TSP(vector<vector<int>> &graph, int src){
  int v = graph.size(), n = 1 << v;
  vector<vector<int>> dp(v, vector<int>(n, inf));
  REP(i,v) dp[i][1<<i] = graph[src][i];
  FOR(s,1,n) REP(i,v) if(s & (1<<i)) REP(j,v) if(!(s & (1<<j))) dp[j][s | (1<<j)] = min(dp[j][s | (1<<j)], dp[i][s] + graph[i][j]);
  return dp[src][n-1];
}

// セグメント木
// (T, f :: T->T->T)はmonoid, eは単位元
template <typename T> class SegmentTree{
private:
  int size;
  vector<T> vec;
  T e;
  function<T(T,T)> f, upd;
  
  int aux(int x, int y, int i, int l, int r){
    if(r<=x || y<=l) return e;
    else if(x<=l && r<=y) return vec[i];
    else return f(aux(x,y,i*2+1,l,(l+r)/2), aux(x,y,i*2+2,(l+r)/2,r));
  };

public:
  SegmentTree(int n, T e, function<T(T,T)> f, function<T(T,T)> upd):
    size(minimum_power_2(n)*2-1), vec(size, e), f(f), e(e), upd(upd){}
  void update(int i, T x){
    int j = i+(size+1)/2-1;
    vec[j] = upd(vec[j], x);
    --j;
    while(j>=0){
      vec[j/2] = f(vec[(j/2)*2+1], vec[(j/2)*2+2]);
      (j /= 2) -= 1;
    }
  }

  int find(int x, int y){return aux(x,y,0,0,(size+1)/2);}
};

// 遅延セグメント木
template <typename T> class LazySegmentTree{
private:
  int size;
  vector<T> vec;
  function<T(T,T)> f, upd;
  T e;
  void propagate(int i){
    if(i<size/2){
      vec[i*2+1] = f(vec[i], vec[i*2+1]);
      vec[i*2+2] = f(vec[i], vec[i*2+2]);
      vec[i] = e;
    }
  }
  void update_aux(int s, int t, int i, int l, int r, T x){
    if(r <= s || t <= l) return;
    else if(s <= l && r <= t) vec[i] = upd(vec[i],x);
    else{
      propagate(i);
      update_aux(s,t,i*2+1,l,(l+r)/2,x);
      update_aux(s,t,i*2+2,(l+r)/2,r,x);
    }
  }
  void find_aux(int i){if(i>0) find_aux((i-1)/2); propagate(i);}
public:
  LazySegmentTree(int n, T e, function<T(T,T)> f, function<T(T,T)> upd):
    size(minimum_power_2(n)*2-1), vec(size, e), f(f), e(e), upd(upd){}
  void update(int s, int t, T x){update_aux(s,t,0,0,size/2+1,x);}
  T find(int i){
    int j=i+size/2;
    find_aux((j-1)/2);
    return vec[j];
  }
};

// KMP algorithm
class KMP{
private:
  string p;
  vector<int> table;
public:
  KMP(string p): p(p), table(p.size(), 0){
    int j=0;
    FOR(i,1,p.size()){
      if(p[i] == p[j]) table[i] = j++;
      else {table[i] = j; j = 0;}
    }
  }
  
  int search(string s, int i=0){
    int j=0;
    while(i<s.size() && j<p.size()){
      if(s[i] == p[j]){++j; ++i;}
      else if(j == 0) ++i;
      else j = table[j];
    }
    if(j==p.size()) return i-j;
    return s.size();
  }
};

// 最大二部マッチング
int bipartite_matching(vector<pair<int,int>> edges, int x, int y){
  vector<vector<pair<int,int>>> graph(x+y+2);

  int s=x+y, t=s+1;
  
  for(auto p : edges) graph[p.first].push_back(make_pair(x+p.second,1));
  REP(i,x) graph[s].push_back(make_pair(i,1));
  FOR(i,x,x+y) graph[i].push_back(make_pair(t,1));

  Dinic d(graph,s,t);
  return d.flow;
}

// 拡張ユークリッド互除法
tuple<LLI,LLI,LLI> extGCD(LLI a, LLI b){
  if(b == 0) return make_tuple(a,1,0);
  LLI d,p,q;
  tie(d,q,p) = extGCD(b,(a+b)%b);
  return make_tuple(d,p,q-a/b*p);
}

// Chinese Remainder Algorithm
bool CRA(LLI b1, LLI m1, LLI b2, LLI m2, LLI &r, LLI &m){
  LLI p,q,d; tie(d,p,q) = extGCD(m1,m2);
  if((b2-b1) % d != 0) return false;
  m = m1 * m2 / d;
  LLI t = ((b2-b1) * p / d) % (m2 / d);
  r = (b1 + m1 * t + m) % m;
  return true;
}

bool CRA(vector<LLI> &bs, vector<LLI> &ms, LLI &r, LLI &m){
  LLI R=0,M=1;
  REP(i,bs.size()){
    if(!CRA(R,M,bs[i],ms[i],r,m)) return false;
    R = r;
    M = m;
  }
  return true;
}

// 連続部分和の最大値
int max_partial_sum(vector<int> &v){
  int t = v[0], ans = t;
  FOR(i,1,v.size()) ans = max(ans, t = max(t+v[i], v[i]));
  return ans;
}

// Z-algorithm
// 最長共通接頭辞の長さ配列
template<typename T> vector<int> Z_algorithm(const T &s){
  int n = s.size();
  vector<int> v(n, 0);
  v[0] = n;
  int j = 0;
  
  FOR(i,1,n){
    while(i+j<n && s[j]==s[i+j]) ++j;
    v[i] = j;
    if(j==0) continue;
    int k = 1;
    while(i+k<n && k+v[k]<j) v[i+k] = v[k++];
    i += k-1, j -= k;
  }
  return v;
}

// Suffix Array
class SuffixArray{
public:
  vector<int> sa;
  const string str;
  
  SuffixArray(const string &s): sa(s.size()), str(s){
    int n = s.size();
    vector<int> temp(n);
    REP(i,n) temp[i] = s[i];

    for(int l=1; l<n; l*=2){
      map<pair<int,int>, int> m2;
      REP(i,n) m2[make_pair(temp[i], i+l>=n?-1:temp[i+l])] = 0;
      int i=0;
      ITR(it,m2) it->second = i++;
      REP(i,n)temp[i] = m2[make_pair(temp[i], i+l>=n?-1:temp[i+l])];
    }
    REP(i,n) sa[temp[i]] = i;
  }

  int operator[](int i){return sa[i];}

  bool starts_with(const string &s, int k){
    if(s.size() <= str.size()-k){
      REP(i,s.size()){
	if(s[i] != str[k+i]) return false;
      }
      return true;
    }
    return false;
  }
  
  int lower_bound(const string &s){
    auto f = [&](int x){
	       REP(i,s.size()){
		 if(sa[x]+i >= str.size()) return false;
		 if(s[i] < str[sa[x]+i]) return true;
		 if(s[i] > str[sa[x]+i]) return false;
	       }
	       return true;
	     };
    return my_binary_search(-1, sa.size(), f, false);
  }
};

// 二次元累積和
template <typename T> class Accum2D{
public:
  vector<vector<T>> accum;

  Accum2D(vector<vector<T>> &vv){
    int d1 = vv.size(), d2 = vv[0].size();
    accum = vector<vector<T>>(d1+1, vector<T>(d2+1));
    REP(i,d1) REP(j,d2) accum[i+1][j+1] = vv[i][j];
    FORE(i,1,d1) REPE(j,d2) accum[i][j] += accum[i-1][j];
    REPE(i,d1) FORE(j,1,d2) accum[i][j] += accum[i][j-1];
  }

  // 1-indexed
  T sum(int x1, int y1, int x2, int y2){
    return accum[x2][y2] - accum[x1-1][y2] - accum[x2][y1-1] + accum[x1-1][y1-1];
  }
};

// 一次元累積和
template <typename T> class Accum{
public:
  vector<T> accum;

  Accum(vector<T> &v){
    int n = v.size();
    accum = vector<T>(n+1);
    REP(i,n) accum[i+1] = accum[i] + v[i];
  }

  // 1-indexed
  T sum(int i, int j){
    return accum[j] - accum[i-1];
  }
};

// 動的セグメント木
template <typename M> class DynamicSegmentTree{
  using Op = function<M(M,M)>;
  class Node{
  public:
    M val;
    Node *left = nullptr, *right = nullptr;
    Node(const M &val): val(val) {}
  };
  
  Node *root = nullptr;
  LLI size;
  M zero;
  Op op;
  unordered_map<LLI, Node*> umap;

  Node* _update(Node *node, LLI l, LLI r, LLI pos, const M &val){
    LLI m = (l+r)/2;
    if(r-l == 1){
      if(node) node->val = op(node->val, val);
      else node = new Node(val);
      umap[pos] = node;
    }else{
      if(!node) node = new Node(val);
      if(pos<m) node->left = _update(node->left, l, m, pos, val);
      else node->right = _update(node->right, m, r, pos, val);
      node->val = op((node->left ? (node->left)->val : zero), (node->right ? (node->right)->val : zero));
    }
    return node;
  }

  M _query(Node* node, LLI l, LLI r, LLI x, LLI y){
    if(!node) return zero;
    LLI m = (l+r)/2;
    if(x <= l && r <= y) return node ? node->val : zero;
    if(r < x || y < l) return zero;
    return op(_query(node->left, l, m, x, y), _query(node->right, m, r, x, y));
  }

public:
  DynamicSegmentTree(LLI n, const M &zero, Op op): size(pow(2,ceil(log2(n)))), zero(zero), op(op){ // [0,2^n)
    root = new Node(zero);
  }

  void update(LLI i, M &x){
    _update(root, 0, size, i, x);
  }

  M query(LLI x, LLI y){
    return _query(root, 0, size, x, y);
  }

  M operator[](LLI i) const{
    if(umap.find(i) != umap.end()) return umap[i]->val;
    else return zero;
  }
};

// 動的遅延セグメント木
template <typename M> class DynamicLazySegmentTree{
  using Op = function<M(M,M)>;
  class Node{
  public:
    M val;
    Node *left = nullptr, *right = nullptr;
    Node(const M &val): val(val) {}
  };
  
  Node *root = nullptr;
  LLI size;
  M zero;
  Op op;
  unordered_map<LLI, Node*> umap;

  Node* propagate(Node *node, LLI l, LLI r){
    if(r-l > 1){
      int m = (l+r)/2;
      if(node->left) (node->left)->val = op(node->val, (node->left)->val);
      else node->left = new Node(node->val);

      if(node->right) (node->right)->val = op(node->val, (node->right)->val);
      else node->right = new Node(node->val);

      node->val = zero;
    }
    return node;
  }

  Node* _update(Node *node, LLI l, LLI r, LLI x, LLI y, const M &val){
    LLI m = (l+r)/2;
    if(r-l == 1){
      if(x <= l && r <= y) node->val = op(node->val, val);
      umap[l] = node;
      return node;
    }
    if(r < x || y < l) return node;
    else if(x <= l && r <= y) node->val = op(node->val, val);
    else{
      propagate(node, l, r);
      _update(node->left, l, m, x, y, val);
      _update(node->right, m, r, x, y, val);
    }
    return node;
  }

  Node* _query(Node* node, LLI l, LLI r, LLI x){
    if(r-l == 1){
      umap[l] = node;
      return node;
    }
    propagate(node, l, r);
    int m = (l+r)/2;
    if(x < m) _query(node->left, l, m, x);
    else _query(node->right, m, r, x);
    return node;
  }

public:
  DynamicLazySegmentTree(LLI n, const M &zero, Op op): size(pow(2,ceil(log2(n)))), zero(zero), op(op){ // [0,2^n)
    root = new Node(zero);
  }

  void update(LLI s, LLI t, M &x){
    _update(root, 0, size, s, t, x);
  }

  M query(LLI x){
    _query(root, 0, size, x);
    return umap[x]->val;
  }
};

// SparseTable
template <typename T> class SparseTable{
  using Op = function<T(T,T)>;
  Op f;
  vector<vector<T>> a;
  vector<int> log_table;
public:
  SparseTable(vector<T> &v, Op f): f(f){
    int n = v.size();
    int logn = 0;
    while((1<<logn) <= n) ++logn;
    
    a = vector<vector<T>>(n, vector<T>(logn));
    REP(i,n) a[i][0] = v[i];
    FOR(j,1,logn) REP(i,n) a[i][j] = f(a[i][j-1], a[min(n-1, i+(1<<(j-1)))][j-1]);

    log_table = vector<int>(n+1);
    FOR(i,2,n+1) log_table[i] = log_table[i>>1] + 1;
  }
  
  T query(int s, int t){
    int k = log_table[t-s+1];
    return f(a[s][k], a[t-(1<<k)+1][k]);
  }
};

class TreeUtils{
public:
  template <typename T> static pair<int,T> farthest(Tree<WEdge<T>> &tree, int cur, int par = -1){
    auto d = make_pair(cur, 0);
    for(auto &next : tree[cur]){
      if(next.to == par) continue;
      auto t = farthest(tree, next.to, cur);
      t.second += next.cost;
      if(t.second > d.second) d = t;
    }
    return d;
  }

  template <typename T> static void distance(Tree<WEdge<T>> &tree, int cur, int par, vector<T> &dist, T d){
    dist[cur] = d;
    for(auto &next : tree[cur]){
      if(next.to == par) continue;
      distance(tree, next.to, cur, dist, d+next.cost);
    }
  }
  
  template <typename T> static T diameter(Tree<WEdge<T>> &tree){
    auto a = farthest(tree, 0);
    auto b = farthest(tree, a.first);
    return b.second;
  }

  template <typename T> static vector<T> height(Tree<WEdge<T>> &tree){
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





