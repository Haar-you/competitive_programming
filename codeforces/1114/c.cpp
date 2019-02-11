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

using namespace std;

vector<LLI> prime_factorize(LLI n){
  vector<LLI> res;
  for(LLI i=2LL; i*i<=n; ++i){
    if(n%i == 0){
      res.push_back(i);
      n/=i;
      --i;
    }
  }
  if(n!=1) res.push_back(n);
  return res;
}

bool check_overflow_mul_ll(int64_t a, int64_t b){
  return a >= LLONG_MAX / b;
}

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);
  
  LLI n,b;
  while(cin >> n >> b){
    auto ps = prime_factorize(b);

    map<LLI, LLI> m;
    map<LLI, LLI> m2;
    for(auto p : ps){
      m[p] = 0;
      ++m2[p];
    }

    for(auto &kv : m){
      auto p = kv.fst;

      LLI q = p;
      while(q <= n && q >= 0){
	m[p] += n/q;
	if(check_overflow_mul_ll(p,q)) break;
	q *= p;
      }
    }

    for(auto &kv : m){
      kv.snd /= m2[kv.fst];
    }

    LLI ans = min_element(ALL(m), [](const pair<LLI,LLI> &a, const pair<LLI,LLI> &b){return a.snd<b.snd;})->snd;
    cout << ans << endl;
  }
  
  return 0;
}
