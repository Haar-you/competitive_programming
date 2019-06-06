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
#define UNIQ(v) v.erase(unique(ALL(v)), v.end())
#define bit(i) (1LL<<i)
#define sz(v) ((LLI)(v).size())

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

const LLI MAX = (1LL<<32)-1;

LLI solve(int l){
  LLI ret = 0;

  stack<LLI> loop;
  stack<LLI> res;
  res.push(0);

  REP(i,l){
    string c; cin >> c;
    if(c == "add"){
      res.top() += 1;
      if(res.top()>MAX) return -1;
    }else if(c == "end"){
      res.top() *= loop.top();
      if(res.top()>MAX) return -1;
      
      loop.pop();
      LLI t = res.top(); res.pop();
      res.top() += t;
      if(res.top()>MAX) return -1;
    }else{
      LLI t; cin >> t;
      res.push(0);
      loop.push(t);
    }
  }
  
  ret = res.top();
  return ret;
}

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  int l;
  while(cin >> l){
    LLI ans = solve(l);
    
    if(ans==-1){
      cout << "OVERFLOW!!!" << endl;
    }else{
      cout << ans << endl;
    }
  }
  
  return 0;
}
