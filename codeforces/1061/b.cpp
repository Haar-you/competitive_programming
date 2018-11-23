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
template <typename I> void cout_join(I s, I t, string d=" "){for(auto i=s; i!=t; ++i){if(i!=s)cout<<d;cout<<*i;}cout<<endl;}

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  int n, m; cin >> n >> m;
  vector<int> a(n);

  REP(i,n) cin >> a[i];
  sort(ALL(a));

  LLI sum = accumulate(ALL(a), 0LL);
  LLI mx = *max_element(ALL(a));

  LLI ch = 0;
  REP(i,n) if(a[i] > ch) ++ch;

  LLI rest = n+(mx-ch);
		 
  cout << sum - rest << endl;
  
  return 0;
}
