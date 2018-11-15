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
template <typename T> void cout_join(vector<T> &v,string d=" "){REP(i,v.size()){if(i>0)cout<<d;cout<<v[i];}cout<<endl;}

template <typename T> LLI power(T n, T p, T m){if(p==0) return 1LL; if(p==1) return n; LLI k = power(n, p/2, m); return ((k*k)%m*(p%2?n:1))%m;}

const LLI mod = 1e9+7;

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  LLI n,q; cin >> n >> q;
  string s; cin >> s;
  vector<LLI> sum(n+1,0);

  FORE(i,1,n){
    sum[i] = sum[i-1] + (s[i-1]-'0');
  }

  REP(i,q){
    LLI l,r; cin >> l >> r;
    LLI cnt1 = sum[r] - sum[l-1], cnt0 = r-(l-1)-cnt1;
    
    LLI enj = (power(2LL,cnt1,mod)-1+mod) % mod;
    enj += (enj * ((power(2LL,cnt0,mod)-1+mod)%mod)) % mod;
    enj %= mod;

    cout << enj << endl;
  }
  
  return 0;
}
