#include <bits/stdc++.h>
#define FOR(v, a, b) for(int v = (a); v < (b); ++v)
#define FORE(v, a, b) for(int v = (a); v <= (b); ++v)
#define REP(v, n) FOR(v, 0, n)
#define REPE(v, n) FORE(v, 0, n)
#define REV(v, a, b) for(int v = (a); v >= (b); --v)
#define ALL(x) (x).begin(), (x).end()
#define RALL(x) (x).rbegin(), (x).rend()
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

mt19937 r = mt19937(static_cast<unsigned int>(time(nullptr)));

map<pair<int,int>, char> dir;
const int dir4[4][2] = {{1,0},{-1,0},{0,1},{0,-1}};

class Iroha{
public:
  vector<string> s;
  int N;
  int ix, iy;
  int mx, my;
  int cnt;
  Iroha(const vector<string> &s, int N): s(s), N(N), ix(N-1), iy(N-1), mx(2), my(2), cnt(0){}

  pair<int,int> move(char c){
    cout << c << endl;
    cout << flush;
    
#ifdef DEBUG
    // my turn
    switch(c){
    case '.':{
      break;
    }
    case 'U':{
      mx -= 1;
      break;
    }
    case 'D':{
      mx += 1;
      break;
    }
    case 'R':{
      my += 1;
      break;
    }
    case 'L':{
      my -= 1;
      break;
    }
    }

    // iroha's turn
    while(1){
      auto p = dir4[r()%4];

      if(s[ix-1+p[0]][iy-1+p[1]] == '.'){
	ix += p[0];
	iy += p[1];
	break;
      }
    }
    
    REP(i,N){
      REP(j,N){
	if(i==ix-1 and j==iy-1) cerr << "\e[31;1mI\e[m";
	else if(i==mx-1 and j==my-1) cerr << "\e[32;1mM\e[m";
	else cerr << s[i][j];
      }
      cerr << endl;
    }
    cerr << endl;

    if(ix==mx and iy==my) return make_pair(-2,-2);
    if(cnt == 1000) return make_pair(-3,-3);
    ++cnt;
    
    if(ix==mx){
      bool b = true;
      FORE(i,min(iy,my), max(iy,my)){
	if(s[ix-1][i-1] != '.') b = false;
      }
      if(b) return make_pair(ix,iy);
    }
    if(iy==my){
      bool b = true;
      FORE(i,min(ix,mx), max(ix,mx)){
	if(s[i-1][iy-1] != '.') b = false;
      }
      if(b) return make_pair(ix,iy);
    }
    return make_pair(-1,-1);
    
#else
    int x, y;
    cin >> x >> y;
    return make_pair(x,y);
#endif
  }
};


int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);
  
  dir[{0,1}] = 'R';
  dir[{0,-1}] = 'L';
  dir[{1,0}] = 'D';
  dir[{-1,0}] = 'U';

  int N; cin >> N;
  vector<string> S(N); cin >> S;

  char next = '-';

  int mx = 2, my = 2;
  
  Iroha interactive(S, N);
  
  while(1){
    int x, y;
    tie(x,y) = interactive.move(next);

    if(x <= -2){
      break;
    }else if(x == -1){
      next = '-';
    }else{
      if(abs(x-mx) <= 1 and abs(y-my) <= 1){
	for(auto &kv : dir){
	  auto p = kv.fst;
	  if(mx+p.fst == x and my+p.snd == y) continue;
	  if(S[mx-1+p.fst][my-1+p.snd] == '.'){
	    mx += p.fst;
	    my += p.snd;
	    next = kv.snd;
	    break;
	  }
	}
      }else{
	next = '-';
      }
    }
  }
  
  return 0;
}
