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

  int m = n/2;
  vector<LLI> b(m);
  REP(i,m) cin >> b[i];


  vector<LLI> a(n);

  a[0] = 0;
  a[n-1] = b[0];
  
  FOR(i,1,m){
    if(b[i] - a[i-1] <= a[n-i]){
      a[i] = a[i-1];
      a[n-1-i] = b[i] - a[i-1];
    }else{
      a[n-1-i] = a[n-i];
      a[i] = b[i] - a[n-1-i];
    }
  }

  join(cout, ALL(a));
  
  return 0;
}
