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

  int n;
  cin >> n;

  vector<int> a(200001,0);
  int Min=0;
  int Max=0;
  int len=0;
  
  char c;
  int id;
  bool first=true;
  REP(i, n){
    cin >> c >> id;  

    switch(c){
    case 'L':
      if(first){a[id]=0;first=false;}
      else{
	a[id] = Min-1;
	--Min;
      }
      ++len;
      break;
    case 'R':
      if(first){a[id]=0;first=false;}
      else{
	a[id] = Max+1;
	++Max;
      }
      ++len;
      break;
    case '?':
      cout << min(a[id]-Min, len-(a[id]-Min+1)) << endl;
      break;
    }    
  }
  
  return 0;
}
