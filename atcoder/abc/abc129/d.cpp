#include <bits/stdc++.h>
#define LLI long long int
#define FOR(v, a, b) for(LLI v = (a); v < (b); ++v)
#define FORE(v, a, b) for(LLI v = (a); v <= (b); ++v)
#define REP(v, n) FOR(v, 0, n)
#define REPE(v, n) FORE(v, 0, n)
#define REV(v, a, b) for(LLI v = (a); v >= (b); --v)
#define ALL(x) (x).begin(), (x).end()
#define RALL(x) (x).rbegin(), (x).rend()
#define ITR(it, c) for(auto it = (c).begin(); it != (c).end(); ++it)
#define RITR(it, c) for(auto it = (c).rbegin(); it != (c).rend(); ++it)
#define EXIST(c,x) ((c).find(x) != (c).end())
#define fst first
#define snd second
#define popcount __builtin_popcount
#define UNIQ(v) v.erase(unique(ALL(v)), v.end())
#define bit(i) (1LL<<i)
#define sz(v) ((LLI)(v).size())

#ifdef DEBUG
#include <misc/C++/Debug.cpp>
#else
#define dump(...) ((void)0)
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

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  int H, W;
  while(cin >> H >> W){
    vector<string> S(H); cin >> S;

    int ans = 0;

    vector<vector<int>> up(H, vector<int>(W));
    REP(i,H){
      REP(j,W){
	if(i+1<H){
	  up[i+1][j] += up[i][j];
	  if(S[i][j] == '.') up[i+1][j] += 1;
	  else up[i+1][j] = 0;
	}
      }
    }

    
    vector<vector<int>> down(H, vector<int>(W));
    REV(i,H-1,0){
      REP(j,W){
	if(i-1>=0){
	  down[i-1][j] += down[i][j];
	  if(S[i][j] == '.') down[i-1][j] += 1;
	  else down[i-1][j] = 0;
	}
      }
    }

    
    vector<vector<int>> left(H, vector<int>(W));
    REP(j,W){
      REP(i,H){
	if(j+1<W){
	  left[i][j+1] += left[i][j];
	  if(S[i][j] == '.') left[i][j+1] += 1;
	  else left[i][j+1] = 0;
	}
      }
    }

    
    vector<vector<int>> right(H, vector<int>(W));
    REV(j,W-1,0){ 
      REP(i,H){
	if(j-1>=0){
	  right[i][j-1] += right[i][j];
	  if(S[i][j] == '.') right[i][j-1] += 1;
	  else right[i][j-1] = 0;
	}
      }
    }
    dump(up);
    dump(down);
    dump(left);
    dump(right);
    

    REP(i,H){
      REP(j,W){
	if(S[i][j] == '.'){
	  chmax(ans, up[i][j] + down[i][j] + right[i][j] + left[i][j] + 1);
	}
      }
    }

    cout << ans << endl;
  }
  
  return 0;
}
