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

LLI f(LLI n){
  if(n % 2 == 0){
    return n/2;
  }else{
    return n/2 - n;
  }
}

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  int q; cin >> q;

  REP(i,q){
    LLI l,r; cin >> l >> r;

    cout << f(r) - f(l-1) << endl;
  }
  
  return 0;
}
