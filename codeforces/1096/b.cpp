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

const LLI mod = 998244353; 

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  int n; cin >> n;
  string s; cin >> s;

  LLI a=0;
  REP(i,n){
    if(s[i]!=s[0]) break;
    ++a;
  }
  LLI b=0;
  REP(i,n){
    if(s[n-1-i]!=s[n-1]) break;
    ++b;
  }

  LLI ans=0;
  if(s[0]==s[n-1]){
    ans = (a+1)*(b+1);
  }else{
    ans = a+b+1;
  }

  ans %= mod;
  cout << ans << endl;
  
  return 0;
}
