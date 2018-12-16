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

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  int n; cin >> n;
  vector<int> a(n);
  REP(i,n) cin >> a[i];

  int ans = 1e7;

  FORE(x,0,100){
    int t = 0;
    REP(i,n){
      t += 2*a[i]*(abs(x-0)+abs(0-i)+abs(i-x));
    }
    ans = min(ans,t);
  }
  cout << ans << endl;
  
  return 0;
}
