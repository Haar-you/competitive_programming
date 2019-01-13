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
#include <boost/core/demangle.hpp>
#define dump(x) cerr << "L" << __LINE__ << ": in " << __PRETTY_FUNCTION__ << " \e[32;1m" << boost::core::demangle(typeid(x).name()) << "\e[37m" << " " << (#x) << " = " << (x) << "\e[m" << endl;
#else
#define dump(x)
#endif
using namespace std;
template <typename T> using V = vector<T>;
template <typename T, typename U> using P = pair<T,U>;
template <typename I> void join(ostream &ost, I s, I t, string d=" "){for(auto i=s; i!=t; ++i){if(i!=s)ost<<d; ost<<*i;}ost<<endl;}
template <typename T> istream& operator>>(istream &is, vector<T> &v){for(auto &a : v) is >> a; return is;}
template <typename T, typename U> istream& operator>>(istream &is, pair<T,U> &p){is >> p.first >> p.second; return is;}

template <typename T> ostream& operator<<(ostream &os, const vector<T> &v){os << "{";ITR(i,v){if(i!=v.begin())os << ","; os << *i;}os << "}"; return os;}
template <typename T, typename U> ostream& operator<<(ostream& os, const pair<T,U> &p){os << "(" << p.first << "," << p.second << ")"; return os;}

template <typename T> T& chmin(T &a, const T &b){return a = min(a,b);}
template <typename T> T& chmax(T &a, const T &b){return a = max(a,b);}

const int dir4[4][2] = {{1,0},{-1,0},{0,1},{0,-1}};
int H,W;
bool visit[410][410];

void bfs(vector<string> &s, int y, int x, LLI &cnt, LLI &cnt_b){
  visit[y][x] = true;
  cnt++;
  if(s[y][x] == '#') cnt_b++;

  REP(k,4){
    int ny = y + dir4[k][0];
    int nx = x + dir4[k][1];

    if(ny>=0 && ny<H && nx>=0 && nx<W && !visit[ny][nx]){
      if(s[y][x] != s[ny][nx]){
	bfs(s,ny,nx,cnt,cnt_b);
      }
    }
  }
}

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  cin >> H >> W;
  vector<string> s(H); cin >> s;

  LLI ans = 0;
  
  REP(i,H){
    REP(j,W){
      if(!visit[i][j]){
	LLI cnt_all=0;
	LLI cnt_black=0;
	bfs(s,i,j,cnt_all,cnt_black);
	LLI cnt_white = cnt_all - cnt_black;
	LLI t = cnt_black*cnt_white;
	
	ans += t;
      }
    }
  }  
  
  cout << ans << endl;
  
  return 0;
}
