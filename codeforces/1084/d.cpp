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

template <typename T> using Graph = vector<vector<T>>;

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

LLI dfs(Graph<WEdge<LLI>> &tree, vector<LLI> &w, int cur, int par, LLI &ans){

  vector<LLI> v = {0};

  ans = max(ans, w[cur]);
  
  for(auto &next : tree[cur]){
    if(next.to == par) continue;

    LLI t = dfs(tree, w, next.to, cur, ans);
    t += w[next.to] - next.cost;
    ans = max(ans, w[cur]+t);
    v.push_back(t);
  }

  sort(ALL(v));
  reverse(ALL(v));

  if(v.size() >= 2) ans = max(ans, w[cur]+v[0]+v[1]);

  return v[0];
}

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  int n; cin >> n;

  vector<LLI> w(n);
  REP(i,n) cin >> w[i];

  Graph<WEdge<LLI>> tree(n);
  REP(i,n-1){
    int u,v,c; cin >> u >> v >> c;
    --u; --v;
    tree[u].push_back(WEdge<LLI>(v,c));
    tree[v].push_back(WEdge<LLI>(u,c));
  }

  LLI ans = 0;
  dfs(tree, w, 0, -1, ans);
  cout << ans << endl;
  
  return 0;
}
