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
  int n,s; cin >> n >> s;

  vector<vector<int>> tree(n);
  REP(i,n-1){
    int a,b; cin >> a >> b;
    --a; --b;
    tree[a].push_back(b);
    tree[b].push_back(a);
  }

  int k = 0;
  REP(i,n) if(tree[i].size() == 1) ++k;

  printf("%.09f\n", 2.0f*s/k);
  
  return 0;
}
