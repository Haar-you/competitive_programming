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

int A[15] = {0,1,2,2,2,3,3,3, 4,5,5,5,6,6,6};
int B[15] = {0,0,0,1,1,1,1,2, 2,2,3,3,3,3,4};
int C[15] = {0,0,0,0,1,1,2,2, 2,2,2,3,3,4,4};


int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  LLI a,b,c;

  while(cin >> a >> b >> c){
    LLI ans = 0;

    LLI n = min({a/3, b/2, c/2});
    ans += n * 7;

    a -= n*3;
    b -= n*2;
    c -= n*2;

    
    int t = 0;
    FORE(i,1,7){
      REP(j,7){
	if(A[i+j] - A[i-1] <= a and B[i+j] - B[i-1] <= b and C[i+j] - C[i-1] <= c){
	  chmax(t, j+1);
	}
      }
    }
    ans += t;

    cout << ans << endl;
  }
  
  return 0;
}
