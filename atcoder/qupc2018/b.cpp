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

  int q; cin >> q;
  
  REP(i,q){
    LLI a, b, c; cin >> a >> b >> c;
    LLI sum = a*100 + b*10 + c;

    if(sum%2 == 0){
      LLI h = sum / 2;

      h = max(h%100LL, h-a*100);
      h = max(h%10LL, h-b*10);
      h = max(0LL, h-c);

      if(h == 0)
	cout << "Yes" << endl;
      else
	cout << "No" << endl;
    }else{
      cout << "No" << endl;
    }
  }
  
  return 0;
}
