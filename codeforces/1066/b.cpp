#include <bits/stdc++.h>
#define FOR(v, a, b) for(int v = (a); v < (b); ++v)
#define FORE(v, a, b) for(int v = (a); v <= (b); ++v)
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

  int n,r;
  cin >> n >> r;
  vector<int> a(n), c(n+1,0);
  int h=0;
  REP(i,n){
    cin >> a[i];
    if(a[i]) ++h;
  }

  int count = 0;

  REP(i,n){
    if(a[i]){
      ++c[max(0,i-r+1)];
      --c[min(n,i+r)];
    }
  }
  FOR(i,1,n) c[i] += c[i-1];

  bool fail = false;
  REP(i,n) if(c[i]==0) {fail = true; break;}
  
  FOR(i,0,n){
    if(a[i]){
      bool b = true;
      FOR(j, max(0,i-r+1), min(n,i+r)){
	if(c[j]==1){b = false; break;} 
      }
      if(b){
	FOR(j, max(0,i-r+1), min(n,i+r)){
	  --c[j];
	}
	++count;
      }
    }
  }

  cout << (fail ? -1 : h - count) << endl;
  
  return 0;
}
