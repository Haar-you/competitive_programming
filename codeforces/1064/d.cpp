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

  vector<string> labyrinth;
  
  const int inf = INT_MAX - 5000000;
  int dir[4][2] = {{1,0},{0,1},{-1,0},{0,-1}};
  int n,m,r,c,x,y;
  
  cin >> n >> m >> r >> c >> x >> y;

  labyrinth = vector<string>(n);
  REP(i,n) cin >> labyrinth[i];

  vector<vector<int>> left(n, vector<int>(m, inf));
  vector<vector<bool>> visit(n, vector<bool>(m,false));

  left[r-1][c-1] = 0;

  deque<pair<int,int>> dq;
  dq.push_front(make_pair(r-1,c-1));

  while(!dq.empty()){
    pair<int,int> f = dq.front(); dq.pop_front();
    if(visit[f.first][f.second])continue;

    visit[f.first][f.second] = true;
    REP(k,4){
      int nx = f.second + dir[k][0], ny = f.first + dir[k][1];
      if(ny>=0 && ny<n && nx>=0 && nx<m && !visit[ny][nx] && labyrinth[ny][nx] == '.'){
	
	if(dir[k][0]==-1){
	  left[ny][nx] = min(left[ny][nx], left[f.first][f.second]+1);
	  dq.push_back(make_pair(ny,nx));
	}
	else{
	  left[ny][nx] = min(left[ny][nx], left[f.first][f.second]);
	  dq.push_front(make_pair(ny,nx));
	}
      }
    }
  }
    
  int count=0;
  REP(i,n){
    REP(j,m){
      if(labyrinth[i][j]=='.'){
	if((left[i][j]<=x && left[i][j]-(c-1-j)<=y)) ++count;
      }
    }
  }

  cout << count << endl;

  return 0;
}
