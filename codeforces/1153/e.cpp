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

#ifdef DEBUG
#include <misc/C++/Debug.cpp>
#else
#define dump(x) ((void)0)
#endif

#define gcd __gcd

using namespace std;
template <class T> constexpr T lcm(T m, T n){return m/gcd(m,n)*n;}

template <typename I> void join(ostream &ost, I s, I t, string d=" "){for(auto i=s; i!=t; ++i){if(i!=s)ost<<d; ost<<*i;}ost<<endl;}
template <typename T> istream& operator>>(istream &is, vector<T> &v){for(auto &a : v) is >> a; return is;}
template <typename T, typename U> istream& operator>>(istream &is, pair<T,U> &p){is >> p.first >> p.second; return is;}

template <typename T, typename U> bool chmin(T &a, const U &b){return (a>b ? a=b, true : false);}
template <typename T, typename U> bool chmax(T &a, const U &b){return (a<b ? a=b, true : false);}
template <typename T, size_t N, typename U> void fill_array(T (&a)[N], const U &v){fill((U*)a, (U*)(a+N), v);}

mt19937 r(static_cast<unsigned int>(time(nullptr)));
const int dir4[4][2] = {{1,0},{-1,0},{0,1},{0,-1}};

class Test{
public:
  int n;

  vector<vector<vector<pair<int,int>>>> g;
  int sx, sy, tx, ty;
  
  Test(int n): n(n){
#ifdef DEBUG

    vector<vector<bool>> visit(n, vector<bool>(n));
    sx = r() % n;
    sy = r() % n;

    g = vector<vector<vector<pair<int,int>>>>(n, vector<vector<pair<int,int>>>(n));
    

    while(1){
      int a = r() % 4;

      int nx = sx + dir4[a][0];
      int ny = sy + dir4[a][1];

      if(nx < 0 or nx >= n or ny < 0 or ny >= n) continue;
      tx = nx;
      ty = ny;
      break;
    }

    visit[sx][sy] = true;
    visit[tx][ty] = true;

    g[sx][sy].push_back({tx,ty});
    g[tx][ty].push_back({sx,sy});
    
    while(1){
      int a = r() % 100;

      if(a == 100-1){
	break;
      }else{
	a %= 4;
	int nx = tx + dir4[a][0];
	int ny = ty + dir4[a][1];

	if(nx < 0 or nx >= n or ny < 0 or ny >= n or visit[nx][ny]) continue;

	g[tx][ty].push_back({nx,ny});
	g[nx][ny].push_back({tx,ty});
	
	tx = nx;
	ty = ny;
	visit[tx][ty] = true;
      }
    }
    
#endif
  }
  
  int query(int x1, int y1, int x2, int y2){
    printf("? %d %d %d %d\n", x1, y1, x2, y2);
    fflush(stdout);

#ifdef DEBUG
    int ret = 0;

    --x1, --y1, --x2, --y2;

    FORE(x,x1,x2){
      FORE(y,y1,y2){
	for(auto &p : g[x][y]){
	  if(p.fst < x1 or p.fst > x2 or p.snd < y1 or p.snd > y2){
	    ++ret;
	  }
	}
      }
    }

    return ret;
#else
    int ret; cin >> ret;
    return ret;
#endif    
  }

  void answer(int x1, int y1, int x2, int y2){
    printf("! %d %d %d %d\n", x1, y1, x2, y2);
    fflush(stdout);

#ifdef DEBUG
    printf("answer: %d %d %d %d\n", sx+1, sy+1, tx+1, ty+1);
#endif
  }
};


int main(){
  int n; cin >> n;

  vector<int> xs;
  vector<int> ys;

  Test test(n);

  FORE(x,1,n){
    int ret = test.query(x,1,x,n);
    if(ret % 2 == 1) xs.push_back(x);
  }

  FORE(y,1,n){
    int ret = test.query(1,y,n,y);
    if(ret % 2 == 1) ys.push_back(y);
  }

  if(xs.empty()){
    int lb = 0, ub = n+1, mid;
    while(abs(lb-ub)>1){
      mid = (lb+ub)/2;

      if(test.query(1,ys[0],mid,ys[0]) % 2 == 1){
	ub = mid;
      }else{
	lb = mid;
      }
    }
    
    int x = ub;

    test.answer(x,ys[0],x,ys[1]);
  }else if(ys.empty()){
    int lb = 0, ub = n+1, mid;
    while(abs(lb-ub)>1){
      mid = (lb+ub)/2;

      if(test.query(xs[0],1,xs[0],mid) % 2 == 1){
	ub = mid;
      }else{
	lb = mid;
      }
    }
    
    int y = ub;

    test.answer(xs[0],y,xs[1],y);
  }else{
    vector<int> ans_x, ans_y;

    for(auto x : xs){
      for(auto y : ys){
	int ret = test.query(x,y,x,y);
	if(ret == 1){
	  ans_x.push_back(x);
	  ans_y.push_back(y);
	}
      }
    }
    test.answer(ans_x[0],ans_y[0],ans_x[1],ans_y[1]);
  }
  
  
  return 0;
}
