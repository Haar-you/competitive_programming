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

template <typename T> using V = vector<T>;
template <typename T, typename U> using P = pair<T,U>;

template <typename T> T gcd(T a, T b){a = abs(a); b = abs(b); if(a<b) swap(a,b); while(b>0){a %= b; swap(a,b);} return a;}
template <typename T> T lcm(T a, T b){return (1LL * a * b) / gcd(a,b);}

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  int n,k; cin >> n >> k;
  vector<string> mat(n);
  REP(i,n) cin >> mat[i];

  int inf = 1e9;
  deque<pair<int,int>> dq = {make_pair(0,0)};
  vector<vector<int>> dist(n, vector<int>(n, inf));
  dist[0][0] = 0;
  while(!dq.empty()){
    pair<int,int> p = dq.front(); dq.pop_front();

    int x = p.first, y = p.second;

    if(x+1<n){
      if(mat[y][x] != 'a'){
	if(dist[y][x+1] >= inf)
	  dq.push_back(make_pair(x+1,y));
	dist[y][x+1] = min(dist[y][x+1], dist[y][x] + 1);
      }
      else if(mat[y][x] == 'a'){
	if(dist[y][x+1] >= inf)
	  dq.push_back(make_pair(x+1,y));
	dist[y][x+1] = min(dist[y][x+1], dist[y][x]);
      }
    }
    if(y+1<n){
      if(mat[y][x] != 'a'){
	if(dist[y+1][x] >= inf)
	  dq.push_back(make_pair(x,y+1));
	dist[y+1][x] = min(dist[y+1][x], dist[y][x] + 1);
      }
      else if(mat[y][x] == 'a'){
	if(dist[y+1][x] >= inf)
	  dq.push_back(make_pair(x,y+1));
	dist[y+1][x] = min(dist[y+1][x], dist[y][x]);
      }
    }
  }

  REP(i,n) REP(j,n) if(dist[i][j]<k) mat[i][j] = 'a';

  vector<vector<int>>().swap(dist);

  string ans = {mat[0][0]};
  set<pair<int,int>> next = {make_pair(0,0)};
  REP(i,2*n-2){
    set<pair<int,int>> pos;
    
    char m='z';
    for(auto v : next){
      int x = v.first, y = v.second;
      if(x+1 < n) m = min(m, mat[y][x+1]);
      if(y+1 < n) m = min(m, mat[y+1][x]);
    }

    for(auto v : next){
      int x = v.first, y = v.second;
      if(x+1<n){
	if(mat[y][x+1] == m){
	  pos.insert(make_pair(x+1,y));
	}
      }
      if(y+1<n){
	if(mat[y+1][x] == m){
	  pos.insert(make_pair(x,y+1));
	}
      }
    }
    next.swap(pos);
    
    ans.push_back(m);
  }

  cout << ans << endl;
  
  return 0;
}
