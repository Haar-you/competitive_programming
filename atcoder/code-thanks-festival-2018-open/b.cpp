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

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  LLI x,y; cin >> x >> y;

  if(3*x-y>=0 && (3*x-y)%8==0 && 3*y-x>=0 && (3*y-x)%8==0)
    cout << "Yes" << endl;
  else
    cout << "No" << endl;
  
  return 0;
}
