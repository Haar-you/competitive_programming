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

template <typename T> int sign(T n){return (n>0)-(n<0);}
template <typename T> T ceilGE(T a, T b){if(a % b) return a/b+1-(sign(a)*sign(b)<0?1:0); return a/b;}

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  int n,k; cin >> n >> k;

  LLI ans = ceilGE(2*n,k) + ceilGE(5*n,k) + ceilGE(8*n,k);

  cout << ans << endl;
  
  return 0;
}
