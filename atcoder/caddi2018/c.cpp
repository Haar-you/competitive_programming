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

// 素因数分解
vector<LLI> prime_factorize(LLI n){
  vector<LLI> res;
  for(LLI i=2; i*i<=n; ++i){
    if(n%i == 0){
      res.push_back(i);
      n/=i;
      --i;
    }
  }
  if(n!=1) res.push_back(n);
  return res;
}

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  LLI n,p; cin >> n >> p;

  vector<LLI> primes = prime_factorize(p);

  map<LLI,LLI> m;
  
  for(auto a : primes){
    m[a]++;
  }

  LLI ans = 1;

  for(auto &kv : m){
    if(kv.second >= n){
      ans *= powl(kv.first, kv.second/n);
    }
  }
  
  cout << ans << endl;
  
  return 0;
}
