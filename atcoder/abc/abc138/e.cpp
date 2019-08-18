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

template <typename T, typename U> bool chmin(T &a, const U &b){return (a>b ? a=b, true : false);}
template <typename T, typename U> bool chmax(T &a, const U &b){return (a<b ? a=b, true : false);}
template <typename T, size_t N, typename U> void fill_array(T (&a)[N], const U &v){fill((U*)a, (U*)(a+N), v);}

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  string s,t;
  while(cin >> s >> t){
    set<char> s_char;
    for(auto c : s){
      s_char.insert(c);
    }

    bool no = false;
    for(auto c : t){
      if(not EXIST(s_char,c)){
        no = true;
      }
    }

    int n = s.size();
    int m = t.size();

    s += s;
    
    vector<vector<int>> next(2*n+1, vector<int>(26, 2*n));
    REV(i,2*n-1,0){
      REP(j,26){
        next[i][j] = next[i+1][j];
      }
      next[i][s[i]-'a'] = i;
    }
    
    LLI ans = 0;
    int cur = 0;
    for(auto c : t){
      int nc = next[cur][c-'a'];
      ans += (LLI)(nc-cur+1);
      cur = (nc+1)%n;
    }

    if(no){
      cout << -1 << endl;
    }else{
      cout << ans << endl;  
    }
  }
  
  return 0;
}
