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

  vector<vector<bool>> cake(n, vector<bool>(n));
  vector<vector<bool>> cake2(n, vector<bool>(n));

  REP(i,n) REP(j,n) if((i+2*j)%5==0) cake[i][j] = true;
    
  int dir[5][2] = {{0,0},{1,0},{0,1},{-1,0},{0,-1}};
  REP(i,n) REP(j,n) REP(k,5)
    if(cake[i][j])
      if(i+dir[k][0]>=0 && i+dir[k][0]<n && j+dir[k][1]>=0 && j+dir[k][1]<n)
	cake2[i+dir[k][0]][j+dir[k][1]] = true;

  REP(i,n) REP(j,n) if(!cake2[i][j]) cake[i][j]=true;
  
  REP(i,n){
    REP(j,n) cout << (cake[i][j] ? "X" : ".");
    cout << endl;
  }
  
  return 0;
}

