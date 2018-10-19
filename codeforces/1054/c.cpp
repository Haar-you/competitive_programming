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

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  int n; cin >> n;
  vector<int> l(n), r(n);
  REP(i,n) cin >> l[i];
  REP(i,n) cin >> r[i];

  vector<int> candies(n, 0);

  REP(i,n) REP(k,n) if(l[k]+r[k] == i) candies[k] = n-i;

  REP(i,n){
    int L=0,R=0;
    FOR(j,0,i) if(candies[j] > candies[i]) ++L;
    FOR(j,i+1,n) if(candies[j] > candies[i]) ++R;

    if(l[i] != L || r[i] != R){
      cout << "NO" << endl;
      return 0;
    }
  }

  cout << "YES" << endl;
  REP(i,n){
    cout << candies[i];
    if(i < n-1) cout << " ";
  }
  cout << endl;
  
  return 0;
}
