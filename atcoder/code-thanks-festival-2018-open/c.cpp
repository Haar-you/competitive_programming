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

LLI solve(int N, vector<LLI> &x){
  vector<LLI> dp(N+1);
  dp[0] = 0;
  FOR(i,1,N) dp[i] = dp[i-1] + (x[i]-x[i-1])*i;
  return accumulate(ALL(dp),0LL);
}

LLI test(int N, vector<LLI> &x){
  LLI ans = 0;
  REP(i,N){
    FOR(j,i+1,N){
      ans += abs(x[i] - x[j]);
    }
  }
  return ans;
}

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  LLI N; cin >> N;
  vector<LLI> x(N);
  REP(i,N) cin >> x[i];
  sort(ALL(x));
  
  cout << solve(N,x) << endl;
  
  return 0;
}
