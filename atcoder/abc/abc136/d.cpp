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

  string s;
  while(cin >> s){
    int n = s.size();

    vector<int> ans(n);

    vector<int> nextL(n), nextR(n);

    REV(i,n-1,0){
      if(s[i] == 'L'){
        nextL[i] = i;
      }else{
        nextL[i] = nextL[i+1];
      }
    }

    REP(i,n){
      if(s[i] == 'R'){
        nextR[i] = i;
      }else{
        nextR[i] = nextR[i-1];
      }
    }

    REP(i,n){
      if(s[i] == 'R'){
        ans[nextL[i] - (nextL[i]-i)%2] ++;
      }else{
        ans[nextR[i] + (i-nextR[i])%2] ++;
      }
    }

    join(cout, ALL(ans));
  }
  
  return 0;
}
