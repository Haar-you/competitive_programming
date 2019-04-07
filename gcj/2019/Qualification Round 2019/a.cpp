#include<bits/stdc++.h>
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

const int f[10][2] =
  {
   {0,0}, {1,0}, {1,1}, {2,1}, {2,2},
   {2,3}, {3,3}, {2,5}, {2,6}, {2,7}
  };

int main(){
  int T; cin >> T;

  FORE(_,1,T){
    string N; cin >> N;
    int l = N.size();
    
    vector<int> a(l), b(l);

    REP(i,l){
      int x = N[i]-'0';
      a[i] = f[x][0];
      b[i] = f[x][1];
    }

    {
      reverse(ALL(a));
      while(a.back() == 0) a.pop_back();
      reverse(ALL(a));
    }
    
    {
      reverse(ALL(b));
      while(b.back() == 0) b.pop_back();
      reverse(ALL(b));
    }
    
    cout << "Case #" << _ << ": ";
    for(auto x : a) cout << x; cout << " ";
    for(auto x : b) cout << x; cout << endl;
  }
}
