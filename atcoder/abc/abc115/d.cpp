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

LLI h[51];

LLI solve(LLI L, LLI x){
  if(x==0) return 0;
  if(L==0) return 1;
  if(x == h[L]){
    return 1LL + 2*solve(L-1,(h[L]-3)/2);
  }
  if(x > h[L]/2){
    return 1LL + solve(L-1,(h[L]-3)/2) + solve(L-1,x-h[L]/2-1);
  }
  return solve(L-1,x-1);
}

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  h[0] = 1;
  FORE(i,1,50){
    h[i] = 3+2*h[i-1];
  }

  LLI n,x; cin >> n >> x;

  cout << solve(n,x) << endl;
  
  return 0;
}
