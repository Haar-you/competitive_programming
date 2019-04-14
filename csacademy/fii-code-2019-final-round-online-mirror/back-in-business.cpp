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

const int dir4[4][2] = {{1,0},{-1,0},{0,1},{0,-1}};
const int inf = INT_MAX;
int sx, sy, fx, fy;
int N,M;

bool check(const vector<string> &field, const vector<vector<int>> &dist, int t){
  if(dist[sy][sx] < t) return false;
  
  vector<vector<bool>> visit(N, vector<bool>(M, false));
  stack<pair<int,int>> st;
  st.push({sy,sx});

  while(not st.empty()){
    auto cur = st.top(); st.pop();

    if(visit[cur.fst][cur.snd]) continue;
    visit[cur.fst][cur.snd] = true;

    for(auto d : dir4){
      int y = cur.fst + d[0], x = cur.snd + d[1];

      if(x<0 or x>=M or y<0 or y>=N or dist[y][x] < t) continue;
	
      st.push({y,x});
    }
  }
  
  return visit[fy][fx];
}


int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  while(cin >> N >> M){
    vector<string> field(N); cin >> field;

    REP(i,N){
      REP(j,M){
	if(field[i][j] == 'S'){
	  sy = i;
	  sx = j;
	}
	if(field[i][j] == 'F'){
	  fy = i;
	  fx = j;
	}
      }
    }
    
    vector<vector<int>> dist(N, vector<int>(M, inf));
    vector<vector<bool>> visit(N, vector<bool>(M));
    deque<pair<int,int>> dq;
    REP(i,N) REP(j,M) if(field[i][j] == 'P'){
      dq.push_back({i,j});
      dist[i][j] = 0;
    }
    
    while(not dq.empty()){
      auto cur = dq.front(); dq.pop_front();

      if(visit[cur.fst][cur.snd]) continue;
      visit[cur.fst][cur.snd] = true;

      for(auto d : dir4){
	int y = cur.fst + d[0], x = cur.snd + d[1];

	if(x<0 or x>=M or y<0 or y>=N) continue;
	
        chmin(dist[y][x], dist[cur.fst][cur.snd]+1);
	dq.push_back({y,x});
      }
    }
    
    int lb=-1, ub=inf/2, mid;
    while(abs(lb-ub)>1){
      mid = (lb+ub)/2;

      if(check(field, dist, mid)){
	lb = mid;
      }else{
	ub = mid;
      }
    }

    int ans = lb;

    if(ans==0){
      cout << "impossible" << endl;
    }else{
      cout << ans << endl;
    }


  }
  
  return 0;
}
