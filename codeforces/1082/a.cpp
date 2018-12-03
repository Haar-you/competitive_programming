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

template <typename T> int sign(T n){return (n>0)-(n<0);}
template <typename T> T ceilGE(T a, T b){if(a % b) return a/b+1-(sign(a)*sign(b)<0?1:0); return a/b;}


int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  int t; cin >> t;

  REP(_,t){
    LLI n,d,x,y; cin >> n >> x >> y >> d;
    LLI ans = 1e18;
    
    if((y-x) % d == 0){
      ans = abs((y-x)/d);
    }else{
      if(y == 1) ans = min(ans, ceilGE(x-1,d));
      if(y == n) ans = min(ans, ceilGE(n-x,d));
      
      if((y-1) % d == 0) ans = min(ans, ceilGE(x-1,d) + (y-1)/d);
      if((n-y) % d == 0) ans = min(ans, ceilGE(n-x,d) + (n-y)/d);
    }

    cout << (ans==1e18 ? -1 : ans) << endl;
  }
  
  return 0;
}
