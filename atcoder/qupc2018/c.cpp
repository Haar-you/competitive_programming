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
const int inf = INT_MAX / 2;

int h,w,X;
vector<string> field;
int dist[1100][1100];
int dist2[1100][1100];

int dir4[4][2] = {{1,0},{-1,0},{0,1},{0,-1}};

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  cin >> h >> w >> X;
  field.resize(h);
  REP(i,h) cin >> field[i];

  int sy,sx,gx,gy;
  REP(i,h) REP(j,w) if(field[i][j] == 'S') {sy=i;sx=j;break;}
  REP(i,h) REP(j,w) if(field[i][j] == 'G') {gy=i;gx=j;break;}

  deque<pair<int,int>> q;
  REP(i,h) REP(j,w) dist[i][j] = inf;

  REP(i,h) REP(j,w) if(field[i][j] == '@'){
    dist[i][j] = 0;
    q.push_back(make_pair(i,j));
  }

  while(!q.empty()){
    auto p = q.front(); q.pop_front();

    REP(k,4){
      int y = p.first + dir4[k][1], x = p.second + dir4[k][0];
      if(y>=0 && y<h && x>=0 && x<w && field[y][x] != '#'){
	if(dist[y][x] > dist[p.first][p.second] + 1){
	  dist[y][x] = dist[p.first][p.second] + 1;
	  q.push_back(make_pair(y,x));
	}
      }
    }
  }  

  if(dist[sy][sx] <= X){
    cout << -1 << endl;
    return 0;
  }

  REP(i,h) REP(j,w) if(dist[i][j] <= X) field[i][j] = '#';

  REP(i,h) REP(j,w) dist2[i][j] = inf;

  q.push_back(make_pair(sy,sx));
  dist2[sy][sx] = 0;

  while(!q.empty()){
    auto p = q.front(); q.pop_front();

    REP(k,4){
      int y = p.first + dir4[k][1], x = p.second + dir4[k][0];
      if(y>=0 && y<h && x>=0 && x<w && field[y][x] != '#'){
	if(dist2[y][x] > dist2[p.first][p.second] + 1){
	  dist2[y][x] = dist2[p.first][p.second] + 1;
	  q.push_back(make_pair(y,x));
	}
      }
    }
  }  

  if(dist2[gy][gx] >= inf)
    cout << -1 << endl;
  else
    cout << dist2[gy][gx] << endl;

  return 0;
}
