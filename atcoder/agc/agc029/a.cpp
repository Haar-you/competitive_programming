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

  string s; cin >> s;
  int n = s.size();

  vector<int> cnt(n+1);
  REP(i,n) cnt[i+1] = cnt[i] + (s[i] == 'W' ? 1 : 0);

  int white = count(ALL(s), 'W');

  LLI ans = 0;

  REP(i,n){
    if(s[i] == 'B')
      ans += white - cnt[i];
  }

  cout << ans << endl;
  
  return 0;
}
