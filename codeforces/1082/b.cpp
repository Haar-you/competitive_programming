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
template <typename I> void join(ostream &ost, I s, I t, string d=" "){for(auto i=s; i!=t; ++i){if(i!=s)ost<<d; ost<<*i;}ost<<endl;}

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  int n; cin >> n;
  string s; cin >> s;
  s = "." + s + ".";

  vector<int> a(n+2), b(n+2);

  FORE(i,1,n) if(s[i] == 'G') a[i] = a[i-1]+1;
  REV(i,n,1) if(s[i] == 'G') b[i] = b[i+1]+1;

  int cnt = count(ALL(s),'G');
  int ans = *max_element(ALL(a));
  
  FORE(i,1,n){
    if(s[i] == 'S'){
      if(a[i-1]+b[i+1] == cnt) ans = cnt;
      else ans = max(ans, a[i-1]+b[i+1]+1);
    }
  }

  cout << ans << endl;

  return 0;
}
