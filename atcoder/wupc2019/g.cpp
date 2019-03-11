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

const LLI inf = 1e18;
LLI dp[1<<15];
LLI used[1<<15];
LLI dis[15][15];
int N,M;

LLI rec(int s){
  if(used[s]) return dp[s];
  used[s] = true;

  REP(i,N){
    if(s & (1<<i)){
      LLI t = rec(s^(1<<i));
      REP(j,N){
	if(!(s & (1<<j))) t += dis[j][i];
      }
      chmin(dp[s], t);
    }
  }

  return dp[s];
}

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  while(cin >> N >> M){
    vector<int> A(M); cin >> A;

    fill_array(dp, inf);
    fill_array(used, false);
    fill_array(dis, 0);

    dp[0] = 0;

    // iを待っているときにjが来たときの不満度の総和
    REP(i,N){
      REP(j,N){
        LLI d = 0;
	LLI s = 0;
        REV(k,M-1,0){
	  if(A[k] == j) ++d;
	  if(A[k] == i) s += d;
	}
	dis[i][j] = s;
      }
    }
    LLI ans = rec((1<<N)-1);
    cout << ans << endl;
  }
  
  return 0;
}
