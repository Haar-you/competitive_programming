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

template <typename T, typename U> bool chmin(T &a, const U &b){return (a>b ? a=b, true : false);}
template <typename T, typename U> bool chmax(T &a, const U &b){return (a<b ? a=b, true : false);}

struct point{
  int x, y;
  point(): x(0), y(0){}
  point(int x, int y): x(x), y(y){}
  point& operator+=(const point &a){this->x+=a.x; this->y+=a.y; return *this;}
  point& operator-=(const point &a){this->x-=a.x; this->y-=a.y; return *this;}
};

point operator+(const point &a, const point &b){return point(a.x+b.x, a.y+b.y);}
point operator-(const point &a, const point &b){return point(a.x-b.x, a.y-b.y);}
bool operator==(const point &a, const point &b){return a.x==b.x and a.y==b.y;}
bool operator!=(const point &a, const point &b){return !(a==b);}

ostream& operator<<(ostream &os, const point &a){
  os << "(" << a.x << "," << a.y << ")";
  return os;
}

template <typename T>
void bfs_grid(const vector<T> &field, int W, int H,
	      const vector<point> &start_points, const vector<point> &dir,
	      const function<bool(point)> &check_passable,
	      vector<vector<int>> &dist
	      ){
  dist = vector<vector<int>>(H, vector<int>(W, -1));

  vector<vector<bool>> visit(H, vector<bool>(W));

  queue<point> q;
  for(auto &p : start_points){
    dist[p.y][p.x] = 0;
    q.push(p);
  }
  
  while(not q.empty()){
    auto cur = q.front(); q.pop();

    if(visit[cur.y][cur.x]) continue;
    visit[cur.y][cur.x] = true;

    for(auto &d : dir){
      auto next = cur + d;

      if(next.x < 0 or next.x >= W or next.y < 0 or next.y >= H or (not check_passable(next))) continue;

      if(dist[next.y][next.x] == -1){
	dist[next.y][next.x] = dist[cur.y][cur.x] + 1;
      }else{
	chmin(dist[next.y][next.x], dist[cur.y][cur.x] + 1);
      }
      q.push(next);
    }
  }
}

template <typename T>
void dfs_grid(const vector<T> &field, int W, int H,
	      const vector<point> &start_points, const vector<point> &dir,
	      const function<bool(point)> &check_passable,
	      vector<vector<bool>> &visit
	      ){
  stack<point> st;
  for(auto &p : start_points) st.push(p);

  while(not st.empty()){
    auto cur = st.top(); st.pop();

    if(visit[cur.y][cur.x]) continue;
    visit[cur.y][cur.x] = true;

    for(auto &d : dir){
      auto next = cur + d;

      if(next.x < 0 or next.x >= W or next.y < 0 or next.y >= H or (not check_passable(next))) continue;

      st.push(next);
    }
  }
}


const vector<point> dir4 = {point(0,1), point(0,-1), point(1,0), point(-1,0)};
const vector<point> dir8 = {point(-1,-1), point(-1,0), point(-1,1), point(1,-1), point(1,0), point(1,1), point(0,-1), point(0,1)};

int main(){
  

  

  return 0;
}
