#include <bits/stdc++.h>
#define FOR(v, a, b) for(int v = (a); v < (b); ++v)
#define FORE(v, a, b) for(int v = (a); v <= (b); ++v)
#define REP(v, n) FOR(v, 0, n)
#define REPE(v, n) FORE(v, 0, n)
#define REV(v, a, b) for(int v = (a); v >= (b); --v)
#define ALL(x) (x).begin(), (x).end()
#define RALL(x) (x).rbegin(), (x).rend()
#define ITR(it, c) for(auto it = (c).begin(); it != (c).end(); ++it)
#define RITR(it, c) for(auto it = (c).rbegin(); it != (c).rend(); ++it)
#define EXIST(c,x) ((c).find(x) != (c).end())
#define LLI long long int
#define fst first
#define snd second

#ifdef DEBUG
#include <misc/C++/Debug.cpp>
#else
#define dump(x) ((void)0)
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

const LLI mod = 1000000007;

LLI f(LLI x){
  if(x==0) return 0;

  LLI ret = 0;

  {
    LLI t = 1;
    int b = 0;

    while(t <= x){
      t *= 2;
      ++b;
    }
    --b;
    t/=2;
    
    LLI odd = 0;
    REP(i,b){
      if(i%2==0){
	odd += (1LL<<i);
      }
    }
      
    LLI even = 0;
    REP(i,b){
      if(i%2==1){
	even += (1LL<<i);
      }
    }
    
    if(b%2==0){
      odd += x-t+1;
    }else{
      even += x-t+1;
    }

    odd %= mod;
    even %= mod;

    ret += (odd*odd%mod + even*(even+1)%mod)%mod;
  }
  
  return ret;
}

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  LLI l, r;
  while(cin >> l >> r){
    LLI ans = (f(r) - f(l-1) + mod) % mod;
    
    cout << ans << endl;
  }
  
  return 0;
}
