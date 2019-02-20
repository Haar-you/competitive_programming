#include <bits/stdc++.h>
#define FOR(v, a, b) for(int v = (a); v < (b); ++v)
#define FORE(v, a, b) for(int v = (a); v <= (b); ++v)
#define REP(v, n) FOR(v, 0, n)
#define REPE(v, n) FORE(v, 0, n)
#define LLI long long int

using namespace std;

int main(){
  int q; cin >> q;
  REP(i,q){
    LLI n,a,b; cin >> n >> a >> b;
    LLI ans = min(n*a, (n/2)*b+(n%2)*a);
    
    cout << ans << endl;
  }
  
  return 0;
}
