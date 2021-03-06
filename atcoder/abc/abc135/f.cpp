#include <bits/stdc++.h>
#define LLI long long int
#define FOR(v, a, b) for(LLI v = (a); v < (b); ++v)
#define FORE(v, a, b) for(LLI v = (a); v <= (b); ++v)
#define REP(v, n) FOR(v, 0, n)
#define REPE(v, n) FORE(v, 0, n)
#define REV(v, a, b) for(LLI v = (a); v >= (b); --v)
#define ALL(x) (x).begin(), (x).end()
#define RALL(x) (x).rbegin(), (x).rend()
#define ITR(it, c) for(auto it = (c).begin(); it != (c).end(); ++it)
#define RITR(it, c) for(auto it = (c).rbegin(); it != (c).rend(); ++it)
#define EXIST(c,x) ((c).find(x) != (c).end())
#define fst first
#define snd second
#define popcount __builtin_popcount
#define UNIQ(v) (v).erase(unique(ALL(v)), (v).end())
#define bit(i) (1LL<<(i))

#ifdef DEBUG
#include <misc/C++/Debug.cpp>
#else
#define dump(...) ((void)0)
#endif

#define gcd __gcd

using namespace std;
template <class T> constexpr T lcm(T m, T n){return m/gcd(m,n)*n;}

template <typename I> void join(ostream &ost, I s, I t, string d=" "){for(auto i=s; i!=t; ++i){if(i!=s)ost<<d; ost<<*i;}ost<<endl;}
template <typename T> istream& operator>>(istream &is, vector<T> &v){for(auto &a : v) is >> a; return is;}
template <typename T, typename U> istream& operator>>(istream &is, pair<T,U> &p){is >> p.first >> p.second; return is;}

template <typename T, typename U> bool chmin(T &a, const U &b){return (a>b ? a=b, true : false);}
template <typename T, typename U> bool chmax(T &a, const U &b){return (a<b ? a=b, true : false);}
template <typename T, size_t N, typename U> void fill_array(T (&a)[N], const U &v){fill((U*)a, (U*)(a+N), v);}

template <typename T> class RollingHash{
private:
  T str;
  LLI base, mod;
  int sl;
  vector<LLI> shash, pow;
public:
  RollingHash(const T &str, LLI base, LLI mod): str(str), base(base), mod(mod), sl(str.size()), shash(sl+1), pow(sl+1){
    pow[0] = 1;
    shash[0] = 0;
    FORE(i,1,sl){
      shash[i] = (shash[i-1]*base+str[i-1]) % mod;
      pow[i] = pow[i-1]*base % mod;
    }
  }

  LLI hash(int i, int j){ // [i, j)
    return (shash[j] - shash[i] * pow[j-i] + mod*mod) % mod;
  }

  LLI hash(const T &p){
    LLI phash = 0;
    REP(i,(int)p.size()) phash = (phash*base+p[i]) % mod;
    return phash;
  }
  
  vector<int> find(const T &p){
    vector<int> ret;
    int pl = p.size();
    LLI phash = hash(p);
    REPE(i,sl-pl) if(hash(i,i+pl) == phash) ret.push_back(i);
    return ret;
  }
};


template <typename T> struct MultiRollingHash{
  RollingHash<T> a, b, c;
  int sl;
  
  MultiRollingHash(const T &s): a(s,31,1000000007), b(s,33,998244353), c(s,41,1000000009), sl(s.size()){
  }

  tuple<LLI,LLI,LLI> hash(int i, int j){
    return make_tuple(a.hash(i,j), b.hash(i,j), c.hash(i,j));
  }

  vector<int> find(const T &p){
    vector<int> ret;

    int pl = p.size();
    LLI pahash = a.hash(p);
    LLI pbhash = b.hash(p);
    LLI pchash = c.hash(p);
    
    REPE(i,sl-pl){
      if(a.hash(i,i+pl) == pahash and
         b.hash(i,i+pl) == pbhash and
         c.hash(i,i+pl) == pchash)
        ret.push_back(i);
    }

    return ret;
  }
};


bool tsort_priority_queue(const vector<vector<int>> &graph, vector<int> &&ret = {}){
  int n = graph.size();
  vector<int> indeg(n);
  REP(i,n){
    for(auto j : graph[i]){
      ++indeg[j];
    }
  }
  priority_queue<int,vector<int>,greater<int>> q;
  REV(i,n-1,0){
    if(indeg[i] == 0) q.push(i);
  }

  while(!q.empty()){
    int cur = q.top(); q.pop();
    ret.push_back(cur);
    for(auto next : graph[cur]){
      --indeg[next];
      if(indeg[next]==0){
        q.push(next);
      }
    }
  }
    
  return (int)ret.size() == n;
}

int dp[1001000];
bool used[1001000];

int dfs(vector<vector<int>> &graph, int cur){
  if(used[cur]) return dp[cur];
  used[cur] = true;
 
  for(auto next : graph[cur]){
    chmax(dp[cur], dfs(graph, next)+1);
  }
  return dp[cur];
}

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  string s,t;
  while(cin >> s >> t){
    int ans = 0;
    
    string ss(s);
    while(s.size() < t.size()){
      s += ss;
    }

    int m = s.size();
    s += s;

    MultiRollingHash<string> rh(s);
    auto res = rh.find(t);

    int n = t.size();
    vector<vector<int>> g(m);

    for(auto x : res){
      if(x >= m) break;
      g[x].push_back((x+n)%m);
    }

    fill_array(dp, 0);
    fill_array(used, false);
    
    bool has_cycle = !tsort_priority_queue(g);

    if(has_cycle){
      ans = -1;
    }else{
      REP(i,m){
        chmax(ans, dfs(g,i));
      }
    }

    cout << ans << endl;
  }
  
  return 0;
}
