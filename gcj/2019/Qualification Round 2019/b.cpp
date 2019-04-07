#include <bits/stdc++.h>
#define FOR(v, a, b) for(int v = (a); v < (b); ++v)
#define FORE(v, a, b) for(int v = (a); v <= (b); ++v)
#define REP(v, n) FOR(v, 0, n)
#define REPE(v, n) FORE(v, 0, n)
#define REV(v, a, b) for(int v = (a); v >= (b); --v)
#define ALL(x) (x).begin(), (x).end()
#define ITR(it, c) for(auto it = (c).begin(); it != (c).end(); ++it)
#define RITR(it, c) for(auto it = (c).rbegin(); it != (c).rend(); ++it)
#define EXIST(c,x) ((c).find(x) != (c).end())
#define LLI long long int
#define fst first
#define snd second
using namespace std;

int main(){
  int T; cin >> T;

  FORE(_,1,T){
    int N; cin >> N;
    string P; cin >> P;

    string ans(P);
    
    for(auto &c : ans){
      if(c == 'S') c = 'E';
      else c = 'S';
    }

    cout << "Case #" << _ << ": " << ans << endl;
  }
  
  return 0;
}
