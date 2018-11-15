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

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  int n; cin >> n;
  vector<int> a(n);
  REP(i,n) cin >> a[i];
  vector<int> b(a);

  int ans = 0;
  
  int i = 0;
  for(;i<n;++i){
    if(a[i] != i+1) break;
  }
  ans = max(ans,i-1);

  reverse(ALL(b));
  for(i=0;i<n;++i){
    if(b[i] != 1000-i) break;
  }
  ans = max(ans,i-1);

  for(i=0;i<n;++i){
    int j=i;
    for(;j<n;++j){
      if(a[j] != a[i]+j-i) break;
    }
    ans = max(ans,j-i-2);
  }

  cout << ans << endl;
  
  return 0;
}
