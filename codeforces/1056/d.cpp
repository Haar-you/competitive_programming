#include <bits/stdc++.h>
#define FOR(v, a, b) for(int v = (a); v < (b); ++v)
#define FORE(v, a, b) for(int v = (a); v <= (b); ++v)
#define REP(v, n) FOR(v, 0, n)
#define REPE(v, n) FORE(v, 0, n)
#define REV(v, a, b) for(int v = (a); v >= (b); --v)
#define ALL(x) (x).begin(), (x).end()
#define LLI long long int
using namespace std;
template <typename T> using V = vector<T>;
template <typename T, typename U> using P = pair<T,U>;
template <typename I> void cout_join(I s, I t, string d=" "){for(auto i=s; i!=t; ++i){if(i!=s)cout<<d;cout<<*i;}cout<<endl;}

int dfs(vector<vector<int>> &tree, int cur, int par, vector<int> &count){
  if(cur != 0 && tree[cur].size() == 1) return count[cur] = 1;

  int cnt = 0;
  for(auto next : tree[cur]){
    if(next != par) cnt += dfs(tree,next,cur,count);
  }
  return count[cur] = cnt;
}

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  int n; cin >> n;
  vector<int> p(n-1);
  REP(i,n-1) cin >> p[i];

  if(n == 1){
    cout << 1 << endl;
    return 0;
  }

  vector<vector<int>> tree(n);

  REP(i,n-1){
    tree[i+1].push_back(p[i]-1);
    tree[p[i]-1].push_back(i+1);
  }
  
  vector<int> count_children(n,0);

  dfs(tree,0,-1,count_children);
  sort(ALL(count_children));
  cout_join(ALL(count_children));
  
  return 0;
}
