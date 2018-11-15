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

  int t; cin >> t;

  REP(i,t){
    int d; cin >> d;

    if(d == 0){
      printf("Y %.09f %.09f\n", 0.0f, 0.0f);
    }else if(d*d - 4*d < 0){
      cout << "N" << endl;
    }else{
      double b = (1.0 * d - sqrt(d*d-4*d)) / 2;
      double a = d - b;

      printf("Y %.09f %.09f\n", a, b);
    }
  }
  
  return 0;
}
