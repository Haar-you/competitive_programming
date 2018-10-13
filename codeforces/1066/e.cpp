#include <bits/stdc++.h>
#define FOR(v, a, b) for(int v = (a); v < (b); ++v)
#define FORE(v, a, b) for(int v = (a); v <= (b); ++v)
#define REP(v, n) FOR(v, 0, n)
#define REPE(v, n) FORE(v, 0, n)
#define REV(v, a, b) for(int v = (a); v >= (b); --v)
#define RS resize
#define CLR clear
#define PB push_back
#define ALL(x) (x).begin(), (x).end()
#define LLI long long int
using namespace std;

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);
  
  int n,m;
  cin >> n >> m;

  string a,b;
  cin >> a >> b;
  reverse(ALL(a));
  reverse(ALL(b));

  vector<int> v(m,0);
  int cntb = count(ALL(b),'1');
  
  REP(i,m) if(b[i]=='1') v[i]=1;
  REV(i,m-2,0) v[i] += v[i+1];

  LLI mod = 998244353;
  LLI ans = 0;
  LLI bin = 1;

  REP(i,n){
    if(a[i]=='1' && i<m){
      (ans += (bin*v[i])) %= mod;
    }
    (bin *= 2) %= mod;
  }

  cout << ans << endl;  
  
  return 0;
}
