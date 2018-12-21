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

vector<vector<int>> tree;
vector<LLI> a;
int n;
vector<LLI> sub;
LLI sum;

LLI dfs_subtree(int cur, int par){
  sub[cur] = a[cur];
  for(auto &next : tree[cur]){
    if(next == par) continue;
    sub[cur] += dfs_subtree(next, cur);
  }
  return sub[cur];
}

LLI dfs(int cur, int par, int dist){
  LLI t = dist*a[cur];
  for(auto &next : tree[cur]){
    if(next == par) continue;
    t += dfs(next,cur,dist+1);
  }
  return t;
}

LLI solve(int cur, int par, LLI cost){
  LLI ans = cost;
  for(auto &next : tree[cur]){
    if(next == par) continue;
    ans = max(ans, solve(next, cur, cost-sub[next]+(sum-sub[next])));
  }
  return ans;
}

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  cin >> n;

  a = vector<LLI>(n);
  REP(i,n) cin >> a[i];

  tree = vector<vector<int>>(n);
  REP(i,n-1){
    int u,v; cin >> u >> v;
    --u; --v;
    tree[u].push_back(v);
    tree[v].push_back(u);
  }

  sum = accumulate(ALL(a), 0LL);

  sub = vector<LLI>(n, 0);
  dfs_subtree(0, -1);

  LLI b = dfs(0, -1, 0);

  cout << solve(0, -1, b) << endl;
  
  return 0;
}
