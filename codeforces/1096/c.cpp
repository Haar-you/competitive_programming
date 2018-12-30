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


int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  int T; cin >> T;

  vector<int> angle(180,-1);

  FORE(n,3,360){
    FORE(i,1,n-2){
      if((180*i)%n==0){
	int ang = 180*i/n;
	if(angle[ang] == -1) angle[ang] = n;
      }
    }
  }

  REP(i,T){
    int ang; cin >> ang;
    cout << angle[ang] << endl;
  }
  
  return 0;
}
