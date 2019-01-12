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

template <typename T> ostream& operator<<(ostream &os, const vector<T> &v){os << "{";ITR(i,v){if(i!=v.begin())os << ","; os << *i;}os << "}"; return os;}
template <typename T, typename U> ostream& operator<<(ostream& os, const pair<T,U> &p){os << "(" << p.first << "," << p.second << ")"; return os;}

template <typename T> T& chmin(T &a, const T &b){return a = min(a,b);}
template <typename T> T& chmax(T &a, const T &b){return a = max(a,b);}

vector<LLI> prime_factorize_unique(LLI n){
  vector<LLI> res;
  for(LLI i=2LL; i*i<=n; ++i){
    if(n%i == 0){
      res.push_back(i);

      while(n%i==0){
	n/=i;
      }
    }
  }
  if(n!=1) res.push_back(n);
  return res;
}

unordered_map<int,unordered_set<int>> visit;
vector<int> a;
vector<vector<int>> tree;

pair<int,int> farthest(int cur, int par, int prime){
  visit[prime].insert(cur);
  
  auto d = make_pair(cur, 0);
  for(auto &next : tree[cur]){
    if(a[next] % prime != 0) continue;
    if(next == par) continue;
    auto t = farthest(next, cur, prime);
    t.second += 1;
    if(t.second > d.second) d = t;
  }
  return d;
}

int diameter(int cur, int p){
  auto a = farthest(cur, -1, p);
  auto b = farthest(a.first, -1, p);
  return b.second + 1;
}

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  int n; cin >> n;
  a = vector<int>(n); cin >> a;
  tree = vector<vector<int>>(n);
  REP(i,n-1){
    int x,y; cin >> x >> y;
    --x, --y;
    tree[x].push_back(y);
    tree[y].push_back(x);
  }

  int ans = 0;

  REP(i,n){
    auto pf = prime_factorize_unique(a[i]);

    for(auto p : pf){
      if(EXIST(visit,p) && EXIST(visit[p],i)) continue;
      if(!EXIST(visit,p)) visit[p] = unordered_set<int>();
      int t = diameter(i,p);
      chmax(ans, t);
    }
  }

  cout << ans << endl;
  
  return 0;
}
