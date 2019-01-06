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

template <typename T> ostream& operator<<(ostream &os, vector<T> &v){os << "{";ITR(i,v){if(i!=v.begin())os << ","; os << *i;}os << "}"; return os;}
template <typename T, typename U> ostream& operator<<(ostream& os, pair<T,U> &p){os << "(" << p.first << "," << p.second << ")"; return os;}
int n,m;

int func1(const vector<string> &table, string pattern){
  int res = 0;
  REP(i,n){
    if(i%2==0){
      int d1 = 0;
      REP(j,m) if(table[i][j] != pattern[j%2]) ++d1;
      int d2 = 0;
      REP(j,m) if(table[i][j] != pattern[(j+1)%2]) ++d2;
      res += min(d1,d2);
    }else{
      int d1 = 0;
      REP(j,m) if(table[i][j] != pattern[2+j%2]) ++d1;
      int d2 = 0;
      REP(j,m) if(table[i][j] != pattern[2+(j+1)%2]) ++d2;
      res += min(d1,d2);
    }
  }
  return res;
}

int func2(const vector<string> &table, string pattern){
  int res = 0;
  REP(i,m){
    if(i%2==0){
      int d1 = 0;
      REP(j,n) if(table[j][i] != pattern[j%2]) ++d1;
      int d2 = 0;
      REP(j,n) if(table[j][i] != pattern[(j+1)%2]) ++d2;
      res += min(d1,d2);
    }else{
      int d1 = 0;
      REP(j,n) if(table[j][i] != pattern[2+j%2]) ++d1;
      int d2 = 0;
      REP(j,n) if(table[j][i] != pattern[2+(j+1)%2]) ++d2;
      res += min(d1,d2);
    }
  }
  return res;
}

vector<string> restore1(const vector<string> &table, string pattern){
  vector<string> res(n);
  REP(i,n){
    if(i%2==0){
      int d1 = 0;
      REP(j,m) if(table[i][j] != pattern[j%2]) ++d1;
      int d2 = 0;
      REP(j,m) if(table[i][j] != pattern[(j+1)%2]) ++d2;

      if(d1<d2){
	REP(j,m) res[i].push_back(pattern[j%2]);
      }else{
	REP(j,m) res[i].push_back(pattern[(j+1)%2]);
      }
    }else{
      int d1 = 0;
      REP(j,m) if(table[i][j] != pattern[2+j%2]) ++d1;
      int d2 = 0;
      REP(j,m) if(table[i][j] != pattern[2+(j+1)%2]) ++d2;

      if(d1<d2){
	REP(j,m) res[i].push_back(pattern[2+j%2]);
      }else{
	REP(j,m) res[i].push_back(pattern[2+(j+1)%2]);
      }
    }
  }
  return res;
}

vector<string> restore2(const vector<string> &table, string pattern){
  vector<string> res(n);
  REP(i,m){
    if(i%2==0){
      int d1 = 0;
      REP(j,n) if(table[j][i] != pattern[j%2]) ++d1;
      int d2 = 0;
      REP(j,n) if(table[j][i] != pattern[(j+1)%2]) ++d2;

      if(d1<d2){
	REP(j,n) res[j].push_back(pattern[j%2]);
      }else{
	REP(j,n) res[j].push_back(pattern[(j+1)%2]);
      }
    }else{
      int d1 = 0;
      REP(j,n) if(table[j][i] != pattern[2+j%2]) ++d1;
      int d2 = 0;
      REP(j,n) if(table[j][i] != pattern[2+(j+1)%2]) ++d2;

      if(d1<d2){
	REP(j,n) res[j].push_back(pattern[2+j%2]);
      }else{
	REP(j,n) res[j].push_back(pattern[2+(j+1)%2]);
      }
    }
  }
  return res;
}


int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  cin >> n >> m;
  vector<string> table(n);
  cin >> table;


  string p = "ACGT";

  int hor_min = 1e9;
  string hor_pat;
  do{
    int t = func1(table, p);
    if(t < hor_min){
      hor_min = t;
      hor_pat = p;
    }
  }while(next_permutation(ALL(p)));
  
  int ver_min = 1e9;
  string ver_pat;
  do{
    int t = func2(table, p);
    if(t < ver_min){
      ver_min = t;
      ver_pat = p;
    }
  }while(next_permutation(ALL(p)));


  if(hor_min <= ver_min){
    auto ans = restore1(table, hor_pat);
    for(auto &line : ans) cout << line << endl;
  }else{
    auto ans = restore2(table, ver_pat);
    for(auto &line : ans) cout << line << endl;
  }
  
  return 0;
}
