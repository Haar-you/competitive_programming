#include <bits/stdc++.h>
#define FOR(v, a, b) for(int v = (a); v < (b); ++v)
#define FORE(v, a, b) for(int v = (a); v <= (b); ++v)
#define REP(v, n) FOR(v, 0, n)
#define REPE(v, n) FORE(v, 0, n)
#define REV(v, a, b) for(int v = (a); v >= (b); --v)
#define ALL(x) (x).begin(), (x).end()
#define ITR(it, c) for(auto it = (c).begin(); it != (c).end(); ++it)
#define LLI long long int
using namespace std;
template <typename T> using V = vector<T>;
template <typename T, typename U> using P = pair<T,U>;
template <typename I> void join(ostream &ost, I s, I t, string d=" "){for(auto i=s; i!=t; ++i){if(i!=s)ost<<d; ost<<*i;}ost<<endl;}

template <typename T> LLI power(T n, T p, T m){if(p==0) return 1LL; if(p==1) return n; LLI k = power(n, p/2, m); return ((k*k)%m*(p%2?n:1))%m;}
template <typename T> LLI modInv(T n, T p){return power(n,p-2,p);}
template <typename T> LLI factorial(T n, T m){LLI k = 1LL; FORE(i,1,n) k = (k*i) % m; return k;}
template <typename T> LLI combination(T n, T k, T p){if(n<k||n<0||k<0) return 0; if(n==0||k==0) return 1; return (((n*modInv(k,p))%p)*combination(n-1,k-1,p))%p;}


const LLI mod = 998244353;

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  LLI n,m,k; cin >> n >> m >> k;

  LLI ans = combination(n-1,k,mod);

  (ans *= (m * power(m-1,k,mod)) % mod) %= mod;

  cout << ans << endl;
  
  return 0;
}
