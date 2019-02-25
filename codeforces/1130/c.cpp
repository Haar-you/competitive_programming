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
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
#ifndef M_E
#define M_E 2.71828182845904523536
#endif

#ifdef DEBUG
#include <misc/C++/Debug.cpp>
#else
#define dump(x)
#endif

#define pln(x) cout << (x) << endl
#define gcd __gcd

using namespace std;
template <class T> constexpr T lcm(T m, T n){return m/gcd(m,n)*n;}

template <typename T> using V = vector<T>;
template <typename T, typename U> using P = pair<T,U>;
template <typename I> void join(ostream &ost, I s, I t, string d=" "){for(auto i=s; i!=t; ++i){if(i!=s)ost<<d; ost<<*i;}ost<<endl;}
template <typename T> istream& operator>>(istream &is, vector<T> &v){for(auto &a : v) is >> a; return is;}
template <typename T, typename U> istream& operator>>(istream &is, pair<T,U> &p){is >> p.first >> p.second; return is;}

template <typename T, typename U> T& chmin(T &a, const U &b){return a = (a<=b?a:b);}
template <typename T, typename U> T& chmax(T &a, const U &b){return a = (a>=b?a:b);}
template <typename T, size_t N, typename U> void fill_array(T (&a)[N], const U &v){fill((U*)a, (U*)(a+N), v);}

const int dir4[4][2] = {{1,0},{-1,0},{0,1},{0,-1}};

const int inf = 1e9;

int dist1[50][50];
int dist2[50][50];

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  int n,r1,c1,r2,c2;
  while(cin >> n >> r1 >> c1 >> r2 >> c2){
    vector<string> f(n); cin >> f;
    --r1, --c1, --r2, --c2;

    fill_array(dist1, inf);
    fill_array(dist2, inf);

    deque<pair<int,int>> dq;
    dq.push_back({r1,c1});
    dist1[r1][c1] = 0;

    while(!dq.empty()){
      int y,x; tie(y,x) = dq.front(); dq.pop_front();

      REP(i,4){
	int ny = y + dir4[i][0], nx = x + dir4[i][1];

	if(ny < 0 || ny >= n || nx < 0 || nx >= n || f[ny][nx] == '1') continue;

        if(dist1[ny][nx] > dist1[y][x]+1){
	  dist1[ny][nx] = dist1[y][x]+1;
	  dq.push_back({ny,nx});
	}
      }
    }

    dq.push_back({r2,c2});
    dist2[r2][c2] = 0;
    
    while(!dq.empty()){
      int y,x; tie(y,x) = dq.front(); dq.pop_front();

      REP(i,4){
	int ny = y + dir4[i][0], nx = x + dir4[i][1];

	if(ny < 0 || ny >= n || nx < 0 || nx >= n || f[ny][nx] == '1') continue;

        if(dist2[ny][nx] > dist2[y][x]+1){
	  dist2[ny][nx] = dist2[y][x]+1;
	  dq.push_back({ny,nx});
	}
      }
    }    

    int ans = inf;

    REP(i,n){
      REP(j,n){
	REP(k,n){
	  REP(l,n){
	    if(dist1[i][j] < inf && dist2[k][l] < inf){
	      chmin(ans, (i-k)*(i-k) + (j-l)*(j-l));
	    }
	  }
	}
      }
    }
    
    cout << ans << endl;
  }
  
  return 0;
}
