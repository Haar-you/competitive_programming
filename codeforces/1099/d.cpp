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

LLI a[101000];
LLI s[101000];

bool func(vector<vector<int>> &tree, int cur, int par, int h){
  if(h % 2 == 0){
    if(tree[cur].size() == 1){
      a[cur] = 0;
    }else{
      LLI m = 1e18;
      for(auto next : tree[cur]){
	if(next == par) continue;
	m = min(m, s[next]);
      }
      if(m < s[par]) return false;
      a[cur] = m - s[par];
      for(auto next : tree[cur]){
	if(next == par) continue;
	a[next] = s[next] - m; 
      }
    }
  }

  for(auto next : tree[cur]){
    if(next == par) continue;
    if(!func(tree,next,cur,h+1)) return false;
  }
  return true;
}

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  int n; cin >> n;

  vector<vector<int>> tree(n);
  REP(i,n-1){
    int p; cin >> p;
    --p;
    tree[p].push_back(i+1);
    tree[i+1].push_back(p);
  }

  REP(i,n){
    cin >> s[i];
  }

  a[0] = s[0];

  if(func(tree, 0, -1, 1)){
    LLI ans = 0;
    REP(i,n){
      ans += a[i];
    }
    cout << ans << endl;

  }else{
    cout << -1 << endl;
  }
  
  return 0;
}
