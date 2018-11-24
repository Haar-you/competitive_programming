#include <bits/stdc++.h>
#define FOR(v, a, b) for(int v = (a); v < (b); ++v)
#define FORE(v, a, b) for(int v = (a); v <= (b); ++v)
#define REP(v, n) FOR(v, 0, n)
#define REPE(v, n) FORE(v, 0, n)
#define REV(v, a, b) for(int v = (a); v >= (b); --v)
#define ALL(x) (x).begin(), (x).end()
#define LLI long long int
using namespace std;
template <typename T> using V = vector<T>;
template <typename T, typename U> using P = pair<T,U>;
template <typename I> void cout_join(I s, I t, string d=" "){for(auto i=s; i!=t; ++i){if(i!=s)cout<<d;cout<<*i;}cout<<endl;}

template <typename T> LLI power(T n, T p, T m){if(p==0) return 1LL; if(p==1) return n; LLI k = power(n, p/2, m); return ((k*k)%m*(p%2?n:1))%m;}

const LLI mod = 1e9+7;

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  LLI n; cin >> n;
  LLI count = 0;

  for(LLI i=1; i<=n; ++i){
    LLI temp = power(n/i,10LL,mod);
    LLI temp2 = (power(i,10LL,mod) - power(i-1,10LL,mod) + mod) % mod;
    (count += temp * temp2) %= mod;
  }
  
  cout << count << endl;  
  
  return 0;
}
