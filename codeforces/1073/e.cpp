#include <bits/stdc++.h>
#define FOR(v, a, b) for(int v = (a); v < (b); ++v)
#define FORE(v, a, b) for(int v = (a); v <= (b); ++v)
#define REP(v, n) FOR(v, 0, n)
#define REPE(v, n) FORE(v, 0, n)
#define REV(v, a, b) for(int v = (a); v >= (b); --v)
#define RS resize
#define CLR clear
#define PB push_back
#define ALL(x) (x).begin(), (x).end()
#define LLI long long int
using namespace std;

template <typename T> using V = vector<T>;
template <typename T, typename U> using P = pair<T,U>;

template <typename T> T gcd(T a, T b){a = abs(a); b = abs(b); if(a<b) swap(a,b); while(b>0){a %= b; swap(a,b);} return a;}
template <typename T> T lcm(T a, T b){return (1LL * a * b) / gcd(a,b);}

const LLI mod = 998244353;

LLI dp[20][1<<10][2];
LLI dpc[20][1<<10][2];

int popCount(int n){
  int count = 0;
  for(int i=0; i<32; ++i) if(n & (1<<i)) ++count;
  return count;
}

LLI solve(string s, int k){
  REP(i,20) REP(a,1<<10) REP(p,2){
    dp[i][a][p] = 0; dpc[i][a][p] = 0;
  }
  LLI r=0;

  for(int i=1; i<s.size(); ++i){
    if(i == 1){
      for(int j=1; j<=9; ++j){
	dp[i][1<<j][1] = j;
	dpc[i][1<<j][1] = 1;
      }
    }else{
      for(int j=0; j<(1<<10); ++j){
	if(dp[i-1][j][1] == 0) continue;
	for(int a=0; a<=9; ++a){
	  dp[i][j|(1<<a)][1] += (dp[i-1][j][1]*10%mod + a*dpc[i-1][j][1]%mod)%mod;
	  (dpc[i][j|(1<<a)][1] += dpc[i-1][j][1]) %= mod;
	}
      }
    }
  }
  
  FOR(i,1,s.size()){
    for(int j=0; j<(1<<10); ++j){
      if(popCount(j) <= k) (r += dp[i][j][1]) %= mod;
    }
  }

  REP(i,20) REP(a,1<<10) REP(p,2){
    dp[i][a][p] = 0; dpc[i][a][p] = 0;
  }
  
  for(int i=1; i<=s.size(); ++i){
    if(i == 1){
      for(int j=1; j<=s[0]-'0'; ++j){
	if(j < s[0]-'0'){
	  dp[i][1<<j][1] = j;
	  dpc[i][1<<j][1] = 1;
	}else{
	  dp[i][1<<j][0] = j;
	  dpc[i][1<<j][0] = 1;
	}
      }
    }else{
      REP(b,2){
	for(int j=0; j<(1<<10); ++j){
	  if(dp[i-1][j][b] == 0) continue;
	  int lim = b ? 9 : s[i-1]-'0';
	  for(int a=0; a<=lim; ++a){
	    dp[i][j|(1<<a)][b||a<lim] += (dp[i-1][j][b]*10%mod + a*dpc[i-1][j][b]%mod)%mod;
	    (dpc[i][j|(1<<a)][b||a<lim] += dpc[i-1][j][b]) %= mod;
	  }
	}
      }
    }
  }

  REP(b,2){
    for(int j=0; j<(1<<10); ++j){
      if(popCount(j) <= k) (r += dp[s.size()][j][b]) %= mod;
    }
  }
  
  return r;
}

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  LLI l,r;
  int k;
  cin >> l >> r >> k;

  LLI L = solve(to_string(l-1),k) , R = solve(to_string(r),k);
  cout << (R-L+mod)%mod << endl; 
  return 0;
}
