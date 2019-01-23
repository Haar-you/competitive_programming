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
#include <boost/core/demangle.hpp>
#define dump(x) cerr << "L" << __LINE__ << ": in " << __PRETTY_FUNCTION__ << " \e[32;1m" << boost::core::demangle(typeid(x).name()) << "\e[37m" << " " << (#x) << " = " << (x) << "\e[m" << endl;
#else
#define dump(x)
#endif
#define pln(x) cout << (x) << endl
using namespace std;
template <typename T> using V = vector<T>;
template <typename T, typename U> using P = pair<T,U>;
template <typename I> void join(ostream &ost, I s, I t, string d=" "){for(auto i=s; i!=t; ++i){if(i!=s)ost<<d; ost<<*i;}ost<<endl;}
template <typename T> istream& operator>>(istream &is, vector<T> &v){for(auto &a : v) is >> a; return is;}
template <typename T, typename U> istream& operator>>(istream &is, pair<T,U> &p){is >> p.first >> p.second; return is;}

template <typename Iter> ostream& out_container(ostream &os, Iter first, Iter last){
  os << "{"; auto itr = first; while(itr != last){if(itr != first) os << ","; os << *itr; ++itr;} os << "}"; return os;
}

template <typename T> ostream& operator<<(ostream &os, const vector<T> &c){return out_container(os,ALL(c));}
template <typename T> ostream& operator<<(ostream &os, const deque<T> &c){return out_container(os,ALL(c));}
template <typename T> ostream& operator<<(ostream &os, const set<T> &c){return out_container(os,ALL(c));}
template <typename T> ostream& operator<<(ostream &os, const unordered_set<T> &c){return out_container(os,ALL(c));}
template <typename T, typename U> ostream& operator<<(ostream &os, const map<T,U> &c){return out_container(os,ALL(c));}
template <typename T, typename U> ostream& operator<<(ostream &os, const unordered_map<T,U> &c){return out_container(os,ALL(c));}
template <typename T, typename U> ostream& operator<<(ostream& os, const pair<T,U> &p){os << "(" << p.first << "," << p.second << ")"; return os;}

template <typename T> T& chmin(T &a, const T &b){return a = min(a,b);}
template <typename T> T& chmax(T &a, const T &b){return a = max(a,b);}

const int dir4[4][2] = {{1,0},{-1,0},{0,1},{0,-1}};

vector<int> solve(int n, int m, int p, vector<int> &s, vector<string> &field){
  vector<vector<int>> occupied(n, vector<int>(m,-1));
  vector<set<pair<int,int>>> sets(p);
  vector<int> ans(p);

  REP(i,n){
    REP(j,m){
      if(field[i][j]>='1' && field[i][j]<='9'){
	sets[field[i][j]-'1'].insert(make_pair(i,j));
	occupied[i][j] = field[i][j]-'1';
      }
    }
  }
  
  REP(i,n*m*p){
    int turn = i%p;
    set<pair<int,int>> nset;
    
    deque<pair<int,int>> dq;
    map<pair<int,int>,int> dist;
    for(auto &cell : sets[turn]){
      int x = cell.snd, y = cell.fst;

      dq.push_back({y,x});
      dist[{y,x}] = 0;
    }

    while(!dq.empty()){
      auto &cur = dq.front(); dq.pop_front();

      int d = dist[cur];
      
      if(d == s[turn]){
	nset.insert(cur);
	continue;
      }

      REP(j,4){
	int nx = cur.snd+dir4[j][0];
	int ny = cur.fst+dir4[j][1];

	if(nx<0 || nx>=m || ny<0 || ny>=n || field[ny][nx]=='#' || occupied[ny][nx]!=-1) continue;

	occupied[ny][nx] = turn;
	dist[{ny,nx}] = d+1;
	dq.push_back({ny,nx});
      }
    }
    
    sets[turn].swap(nset);
  }

  REP(i,n){
    REP(j,m){
      if(occupied[i][j] != -1)
      	ans[occupied[i][j]]++;
    }
  }
  
  return ans;
}

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  int n,m,p;
  while(cin >> n >> m >> p){
    vector<int> s(p); cin >> s;
    vector<string> field(n); cin >> field;
    auto ans = solve(n,m,p,s,field);
    join(cout,ALL(ans));
  }
  
  return 0;
}
