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

LLI f(LLI n, LLI d = -1){
  for(LLI i=2; i*i<=n; ++i){
    if(n % i == 0){
      d = i;
      break;
    }
  }

  if(d == -1) return 1;
  if(d == 2) return n / d;

  return 1 + (n-d) / 2;
}

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  LLI n; cin >> n;

  cout << f(n) << endl;
  
  return 0;
}
