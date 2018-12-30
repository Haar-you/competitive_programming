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

LLI calc(int N, vector<LLI> &a, LLI y, LLI m, LLI d){
  LLI days = accumulate(ALL(a),0);

  LLI res = y*days+(y+3)/4;
  
  REP(i,m-1) res += a[i];
  res += d;
  return res;
}


int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  int T; cin >> T;

  REP(_,T){
    int N; cin >> N;
    vector<LLI> a(N);
    REP(i,N) cin >> a[i];

    LLI yb,mb,db; cin >> yb >> mb >> db;
    LLI yc,mc,dc; cin >> yc >> mc >> dc;

    LLI ans = calc(N,a,yc,mc,dc) - calc(N,a,yb,mb,db) + 1;
    cout << ans << endl;
  }
  
  return 0;
}
