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

template <typename T> int sign(T n){return (n>0)-(n<0);}
template <typename T> T ceilGE(T a, T b){if(a % b) return a/b+1-(sign(a)*sign(b)<0?1:0); return a/b;}

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  int n;
  LLI s;
  cin >> n >> s;
  vector<LLI> v(n);
  REP(i,n) cin >> v[i];

  LLI sum = accumulate(ALL(v),0LL);

  if(s>sum){
    cout << -1 << endl;
  }else{
    sort(ALL(v));

    LLI a = 0;
    REP(i,n) a += (v[i]-v[0]);

    LLI ans;
    
    if(s<=a){
      ans = v[0];
    }else{
      s -= a;
      LLI k = ceilGE(s,(LLI)n);
      ans = v[0]-k;
    }

    cout << ans << endl;
  }
  
  return 0;
}
