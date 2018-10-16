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

  int n;
  cin >> n;

  int l=0;
  int r=1000000000;
  int c=-1;

  cout << l << " " << 100 << endl << flush;
  string color;
  cin >> color;
  if(c==-1) c = color=="black" ? 0 : 1;
    
  REP(i,n-1){
    cout << (l+r)/2 << " " << 100 << endl << flush;

    cin >> color;

    if(c==0){
      if(color=="black")
	l=(l+r)/2;
      else
	r=(l+r)/2;
    }else{
      if(color=="white")
	l=(l+r)/2;
      else
	r=(l+r)/2;
    }
  }

  printf("%d %d %d %d\n", l, 99, r, 101);
  cout << flush;
  
  return 0;
}

