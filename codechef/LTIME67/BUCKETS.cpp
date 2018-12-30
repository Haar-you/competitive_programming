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

  int n,k; cin >> n >> k;
  vector<vector<int>> a(n,vector<int>(k));
  REP(i,n) REP(j,k) cin >> a[i][j];
  vector<int> s(n);
  REP(i,n) s[i] = accumulate(ALL(a[i]),0);

  vector<double> ans(k);

  REP(i,k){
    vector<double> v(n);
    v[0] = 1.0 * a[0][i] / s[0];
    FOR(j,1,n){
      v[j] = v[j-1]*(a[j][i]+1)/(s[j]+1) + (1-v[j-1])*a[j][i]/(s[j]+1);
    }
    ans[i] = v[n-1];
  }
  
  join(cout,ALL(ans));
  
  return 0;
}
