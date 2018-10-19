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
  
  int x,y,z,t1,t2,t3;
  cin >> x >> y >> z >> t1 >> t2 >> t3;
  
  if(t1*abs(y-x) < t2*(abs(z-x)+abs(y-x))+3*t3)
    cout << "NO" << endl;
  else
    cout << "YES" << endl;
  
  return 0;
}
