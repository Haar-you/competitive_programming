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

  int n,ax,ay,bx,by,cx,cy;

  cin >> n >> ax >> ay >> bx >> by >> cx >> cy;
  vector<vector<char>> chess(n,vector<char>(n,0));

  int dir[8][2] = {{1,0},{1,1},{0,1},{-1,1},{-1,0},{-1,-1},{0,-1},{1,-1}};
  
  REP(k, 8){
    int x = ax-1, y = ay-1;
    while(x>=0 && x<n && y>=0 && y<n){
      chess[x][y] = -1;

      x += dir[k][0];
      y += dir[k][1];
    }
  }

  queue<pair<int,int>> que;
  que.push(make_pair(bx-1, by-1));
  chess[bx-1][by-1] = 1;
  
  while(!que.empty()){
    pair<int,int> p = que.front();
    que.pop();
    int x = p.first, y = p.second;
    
    REP(k, 8){
      int dx=dir[k][0], dy=dir[k][1];
      if(x+dx>=0 && x+dx<n && y+dy>=0 && y+dy<n && chess[x+dx][y+dy] == 0){
	chess[x+dx][y+dy] = 1;
	que.push(make_pair(x+dx, y+dy));
      }
    }
  }
  
  cout << (chess[cx-1][cy-1] == 1 ? "YES" : "NO") << endl;
  
  return 0;
}
