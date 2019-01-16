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
#ifdef DEBUG
#include <boost/core/demangle.hpp>
#define dump(x) cerr << "L" << __LINE__ << ": in " << __PRETTY_FUNCTION__ << " \e[32;1m" << boost::core::demangle(typeid(x).name()) << "\e[37m" << " " << (#x) << " = " << (x) << "\e[m" << endl;
#else
#define dump(x)
#endif
using namespace std;
template <typename T> using V = vector<T>;
template <typename T, typename U> using P = pair<T,U>;
template <typename I> void join(ostream &ost, I s, I t, string d=" "){for(auto i=s; i!=t; ++i){if(i!=s)ost<<d; ost<<*i;}ost<<endl;}
template <typename T> istream& operator>>(istream &is, vector<T> &v){for(auto &a : v) is >> a; return is;}
template <typename T, typename U> istream& operator>>(istream &is, pair<T,U> &p){is >> p.first >> p.second; return is;}

template <typename T> ostream& operator<<(ostream &os, vector<T> &v){os << "{";ITR(i,v){if(i!=v.begin())os << ","; os << *i;}os << "}"; return os;}
template <typename T, typename U> ostream& operator<<(ostream& os, pair<T,U> &p){os << "(" << p.first << "," << p.second << ")"; return os;}

template <typename T> T& chmin(T &a, const T &b){return a = min(a,b);}
template <typename T> T& chmax(T &a, const T &b){return a = max(a,b);}

LLI N,M;

LLI dp[101000];
LLI dp2[101000];

LLI rec(vector<vector<int>> &tree, int cur){
  dp[cur] = 1;

  for(auto next : tree[cur]){
    (dp[cur] *= (rec(tree,next)+1)%M) %= M;
  }

  return dp[cur];
}

LLI rec2(vector<vector<int>> &tree, int cur, LLI val){
  int c = tree[cur].size();
  
  vector<LLI> left(c+1,1);
  REP(i,c) (left[i+1] = left[i] * (dp[tree[cur][i]]+1)%M) %= M;
  
  LLI right = 1;

  REV(i,tree[cur].size()-1,0){
    int next = tree[cur][i];
    dp2[next] = (val*left[i]%M*right%M+1)%M;

    (right *= (dp[tree[cur][i]]+1)%M) %= M;
    rec2(tree, next, dp2[next]);
  }
  
  return dp2[cur];
}

void remove_parent_edge(vector<vector<int>> &tree, int cur, int par){
  auto it = find(ALL(tree[cur]),par);
  if(it != tree[cur].end()) tree[cur].erase(it);
  for(auto next : tree[cur]){
    remove_parent_edge(tree,next,cur);
  }
}

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  cin >> N >> M;
  vector<vector<int>> tree(N);
  REP(i,N-1){
    int x,y; cin >> x >> y;
    --x, --y;
    tree[x].push_back(y);
    tree[y].push_back(x);
  }

  remove_parent_edge(tree,0,-1);

  rec(tree, 0);
  rec2(tree, 0, dp2[0]=1);

  REP(i,N){
    LLI ans = (dp2[i]*dp[i])%M;
    cout << ans << endl;
  }
  
  return 0;
}
