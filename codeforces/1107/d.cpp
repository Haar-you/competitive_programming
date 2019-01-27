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
#define gcd __gcd

using namespace std;
template <class T> constexpr T lcm(T m, T n){return m*n/gcd(m,n);}

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

int hex(char c){
  if(c >= '0' && c <= '9') return c-'0';
  else return c-'A' + 10;
}

template <typename T> bool is_square(T n){T rt = sqrt(n); return rt*rt == n;}

vector<LLI> divisor_list(LLI n){
  vector<LLI> temp, res;
  for(LLI i=1LL; i*i<n; ++i) if(n%i == 0) temp.push_back(i);
  for(auto i : temp) res.push_back(i);
  if(is_square(n)) res.push_back((LLI)sqrt(n));
  for(auto itr=temp.rbegin(); itr!=temp.rend(); ++itr) res.push_back(n/(*itr));
  return res;
}

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  int n;
  while(cin >> n){
    vector<string> s(n); cin >> s;

    vector<vector<int>> mat(n,vector<int>(n,0));
    
    REP(i,n){
      REP(j,n/4){
	int h = hex(s[i][j]);
	
	REP(k,4){
	  mat[i][j*4+k] = (h>>(3-k))&1;
	}
      }
    }

    auto divs = divisor_list(n);

    vector<vector<int>> sum(n+1, vector<int>(n+1,0));

    REP(i,n) REP(j,n) sum[i+1][j+1] = mat[i][j];

    REPE(i,n){
      FORE(j,1,n){
	sum[i][j] += sum[i][j-1];
      }
    }

    REPE(j,n){
      FORE(i,1,n){
	sum[i][j] += sum[i-1][j];
      }
    }

    LLI ans = 0;
    for(auto x : divs){
      bool f = false;
      for(int i=x; i<=n; i+=x){
        for(int j=x; j<=n; j+=x){
	  int t = sum[i][j] - sum[i-x][j] - sum[i][j-x] + sum[i-x][j-x];
	  if(t==0 || t==x*x){

	  }else{
	    f = true;
	    break;
	  }
	  if(f) break;
	}
      }
      if(!f) chmax(ans, x);
    }
    
    cout << ans << endl;
  }
  
  return 0;
}
