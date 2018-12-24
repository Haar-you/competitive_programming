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

vector<int> aux(vector<vector<int>> &graph, string &s, char c ){
  int n = graph.size();
  vector<int> res(n);

  REP(i,n){
    bool sec = true;
    for(auto &next : graph[i]) if(s[next] == c) sec = false;

    if(sec) res[i] = 1;
    else res[i] = 0;
  }

  return res;
}

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  int n,m;
  LLI k;
  cin >> n >> m >> k;
  string s; cin >> s;

  vector<vector<int>> graph(n);
  REP(i,m){
    int a,b; cin >> a >> b;
    --a; --b;
    graph[a].push_back(b);
    graph[b].push_back(a);
  }

  auto v = aux(graph, s, 'B');
  auto v2 = aux(graph, s, 'R');
  
  if(k % 2 == 1){
    REP(i,n) cout << (v[i] ? "Second" : "First") << endl;
  }else{
    vector<int> ans(n);
    
    REP(i,n){
      bool sec = true;
      for(auto &next : graph[i]){
	if(v2[next] == 1) sec = false;
      }
      if(sec) ans[i] = 1;
      else ans[i] = 0;
    }
    
    REP(i,n) cout << (ans[i] ? "Second" : "First") << endl;
  }
  
  return 0;
}
