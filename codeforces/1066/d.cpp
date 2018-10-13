#include <bits/stdc++.h>
#define FOR(v, a, b) for(int v = (a); v < (b); ++v)
#define FORE(v, a, b) for(int v = (a); v <= (b); ++v)
#define REV(v, a, b) for(int v = (a); v >= (b); --v)
#define REP(v, n) FOR(v, 0, n)
#define REPE(v, n) FORE(v, 0, n)
#define RS resize
#define CLR clear
#define PB push_back
#define ALL(x) (x).begin(), (x).end()
using namespace std;

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);
	
  int n,m,k;
  cin >> n >> m >> k;

  vector<int> a(n);
  REP(i,n) cin >> a[i];

  int i,j=0;
  vector<int> box(m);
  for(i=n-1; i>=0; --i){
    if(box[j]+a[i]<=k){
      box[j] += a[i];
    }else if(j<m-1){
      ++j;
      ++i;
      continue;
    }else{
      break;
    }
  }

  cout << n - i - 1 << endl;
  
  return 0;
}
