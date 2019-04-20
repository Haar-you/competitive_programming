#include <bits/stdc++.h>
#define FOR(v, a, b) for(int v = (a); v < (b); ++v)
#define FORE(v, a, b) for(int v = (a); v <= (b); ++v)
#define REP(v, n) FOR(v, 0, n)
#define REPE(v, n) FORE(v, 0, n)
#define REV(v, a, b) for(int v = (a); v >= (b); --v)
#define ALL(x) (x).begin(), (x).end()
#define ITR(it, c) for(auto it = (c).begin(); it != (c).end(); ++it)
#define RITR(it, c) for(auto it = (c).rbegin(); it != (c).rend(); ++it)
#define EXIST(c,x) ((c).find(x) != (c).end())
#define LLI long long int
#define fst first
#define snd second

using namespace std;

/*
  [問題例]
  https://yukicoder.me/problems/no/274
  https://yukicoder.me/problems/no/470

 */

class two_sat{
  int n;
  Graph<int> g;
  
public:
  two_sat(int n): n(n), g(2*n){}

  int inv(int i){ // not
    if(i<n) return i+n;
    else return i-n;
  }

  void add(int a, int b){
    if(a == b){ // a ∨ a <=> (!a => a)
      g[inv(a)].push_back(Edge<int>(inv(a), a, 1));
    }else{ // a ∨ b <=> (!a => b) ∧ (!b => a)
      g[inv(a)].push_back(Edge<int>(inv(a), b, 1));
      g[inv(b)].push_back(Edge<int>(inv(b), a, 1));
    }
  }
  
  void not_coexist(int a, int b){ // !(A ∧ B) <=> (!A ∨ !B)
    add(inv(a), inv(b));
  }
  
  bool solve(vector<bool> &ret){
    auto s = strongly_connected_components(g);

    REP(i,n) if(s[i] == s[i+n]) return false;

    int m = *max_element(ALL(s)) + 1;
    Graph<int> g2(m);
    vector<int> ts;

    for(auto &v : g){
      for(auto &e : v){
	if(s[e.from] != s[e.to]) g2[s[e.from]].push_back(Edge<int>(s[e.from], s[e.to], 1));
      }
    }
    
    tsort(g2, ts);

    vector<int> r(m);
    REP(i,m) r[ts[i]] = i;

    ret = vector<bool>(n);
    REP(i,n) ret[i] = r[s[i]] > r[s[i+n]];

    return true;
  }
};
