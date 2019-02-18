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

//template <typename T, typename U> T& chmin(T &a, const U &b){return a = (a<=b?a:b);}
template <typename T, typename U> bool chmax(T &a, const U &b){if(a<=b){a=b; return true;} return false;}
template <typename T, size_t N, typename U> void fill_array(T (&a)[N], const U &v){fill((U*)a, (U*)(a+N), v);}

const int c[10] = {0,2,5,5,4,5,6,3,7,6};

LLI dp[11000][10];
int restore[11000][10];

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);
  
  int N,M;
  while(cin >> N >> M){
    vector<int> A(M); cin >> A;
    sort(ALL(A));
    
    fill_array(dp, 0);
    fill_array(restore, 0);

    REPE(i,N){
      REP(j,M){
        if(dp[i][j] == 0 && i != 0) continue;
        REP(k,M){
          if(dp[i+c[A[k]]][k] == dp[i][j]+1){
            chmax(restore[i+c[A[k]]][k], j);
          }else if(dp[i+c[A[k]]][k] < dp[i][j]+1){
            dp[i+c[A[k]]][k] = dp[i][j] + 1;
            restore[i+c[A[k]]][k] = j;
          }
        }
      }
    }
    
    string ans = "";
    
    int prev = 0;
    int mx = 0;
    REP(i,M) if(dp[N][i] >= mx){mx = dp[N][i]; prev = i;}
    
    int i = N;
    while(1){
      ans += ('0'+A[prev]);
      int t = prev;
      prev = restore[i][t];
      i -= c[A[t]];
      if(i <= 0) break;
    }
    
    cout << ans << endl;
  }
  
  return 0;
}
