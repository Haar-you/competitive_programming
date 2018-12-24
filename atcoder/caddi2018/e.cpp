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

LLI dp[200100][16];
LLI dp2[200100][16];

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  LLI n; cin >> n;
  vector<LLI> a(n);
  REP(i,n) cin >> a[i];

  REPE(x,15) dp[n-1][x] = x;
  REV(i,n-2,0){
    LLI t = a[i];
    REPE(x,15){
      LLI y = 0;
      LLI t2 = a[i+1];
      while(t > t2){
	++y;
	t2 *= 4;
      }
      
      if(t <= a[i+1]) dp[i][x] = dp[i+1][0] + x;
      else{
	if(y > 15)
	  dp[i][x] = (dp[i+1][15] + (y-15)*(n-i-1)) + x;
	else
	  dp[i][x] = dp[i+1][y] + x;
      }
      t *= 4;
    }
  }
  
  REPE(x,15) dp2[0][x] = x;
  FOR(i,1,n){
    LLI t = a[i];
    REPE(x,15){
      LLI y = 0;
      LLI t2 = a[i-1];
      while(t > t2){
	++y;
	t2 *= 4;
      }
      
      if(t <= a[i-1]) dp2[i][x] = dp2[i-1][0] + x;
      else{
	if(y > 15)
	  dp2[i][x] = (dp2[i-1][15] + (y-15)*i) + x;
	else
	  dp2[i][x] = dp2[i-1][y] + x;
      }
      t *= 4;
    }
  }

  LLI ans = dp[0][0]*2;
  
  FORE(i,1,n){
    LLI t = dp[i][0]*2 + dp2[i-1][0]*2 + i;
    ans = min(ans, t);
  }

  cout << ans << endl;
  
  return 0;
}
