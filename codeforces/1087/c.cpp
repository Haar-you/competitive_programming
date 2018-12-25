#include <bits/stdc++.h>
#define FOR(v, a, b) for(int v = (a); v < (b); ++v)
#define FORE(v, a, b) for(int v = (a); v <= (b); ++v)
#define REP(v, n) FOR(v, 0, n)
#define REPE(v, n) FORE(v, 0, n)
#define REV(v, a, b) for(int v = (a); v >= (b); --v)
#define ALL(x) (x).begin(), (x).end()
#define ITR(it, c) for(auto it = (c).begin(); it != (c).end(); ++it)
#define LLI long long int
using namespace std;
template <typename T> using V = vector<T>;
template <typename T, typename U> using P = pair<T,U>;
template <typename I> void join(ostream &ost, I s, I t, string d=" "){for(auto i=s; i!=t; ++i){if(i!=s)ost<<d; ost<<*i;}ost<<endl;}
template <typename T, typename U> ostream& operator<<(ostream& os, pair<T,U> &p){
  os << p.first << "," << p.second;
  return os;
}
template <typename T, typename U> istream& operator>>(istream &is, pair<T,U> &p){
  is >> p.first >> p.second;
  return is;
}

int manhattan(pair<int,int> &a, pair<int,int> &b){
  return abs(a.first-b.first) + abs(a.second-b.second);
}

int dist(pair<int,int> &a, pair<int,int> &b, pair<int,int> &c, pair<int,int> &p){
  return manhattan(a,p) + manhattan(b,p) + manhattan(c,p);
}

vector<vector<int>> field(1001, vector<int>(1001));

int clean(pair<int,int> x, pair<int,int> y){
  if(x.first > y.first) swap(x,y);

  FORE(i,x.first,y.first) field[i][x.second] = 1;
  if(x.second < y.second){
    FORE(i,x.second,y.second) field[y.first][i] = 1;
  }else{
    FORE(i,y.second,x.second) field[y.first][i] = 1;
  }
}

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  pair<int,int> a,b,c;
  cin >> a >> b >> c;

  vector<pair<int,int>> p;
  REPE(x,1000) REPE(y,1000) p.push_back({x,y});

  auto q = *min_element(ALL(p), [&](pair<int,int> &x, pair<int,int> &y){return dist(a,b,c,x) < dist(a,b,c,y);});

  clean(a,q);
  clean(b,q);
  clean(c,q);

  int n = 0;
  REPE(i,1000) n += accumulate(ALL(field[i]), 0);
  cout << n << endl;

  REPE(x,1000) REPE(y,1000) if(field[x][y]) cout << x << " " << y << endl;
  
  return 0;
}
