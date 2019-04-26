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

const LLI mod = 1e9+7;

LLI dp1[2100][2100]; // not used
LLI dp2[2100][2100]; // used

bool visit1[2100][2100];
bool visit2[2100][2100];

LLI rec1(int,int);
LLI rec2(int,int);

int n;


LLI rec1(int a, int b){
  if(visit1[a][b]) return dp1[a][b];
  visit1[a][b] = true;

  if(a==2*n){
    if(b==0) return dp1[a][b] = 0;
    else return dp1[a][b] = INT_MIN;
  }

  if(b==0){
    if(rec2(a+1,b+1)>=0) dp1[a][b] = (rec2(a+1,b+1)+1) % mod;
  }else{
    chmax(dp1[a][b], rec1(a+1,b-1));
    chmax(dp1[a][b], rec2(a+1,b-1)+1);
    chmax(dp1[a][b], rec1(a+1,b+1));
    chmax(dp1[a][b], rec2(a+1,b+1)+1);

    chmax(dp1[a][b], rec2(a+1,b-1)+rec1(a+1,b+1)+1);
    chmax(dp1[a][b], rec1(a+1,b-1)+rec2(a+1,b+1)+1);
  }

  if(dp1[a][b] >= 0) dp1[a][b] %= mod;

  return dp1[a][b];
}

LLI rec2(int a, int b){
  if(visit2[a][b]) return dp2[a][b];
  visit2[a][b] = true;

  if(a==2*n){
    if(b==0) return dp2[a][b] = 0;
    else return dp2[a][b] = INT_MIN;
  }

  if(b==0){
    if(rec1(a+1,b+1)>=0) dp2[a][b] = rec1(a+1,b+1);
  }else{
    chmax(dp2[a][b], rec1(a+1,b-1));
    chmax(dp2[a][b], rec1(a+1,b+1));
    
    chmax(dp2[a][b], rec1(a+1,b-1)+rec1(a+1,b+1));
  }

  if(dp2[a][b] >= 0) dp2[a][b] %= mod;
  
  return dp2[a][b];
}


int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  while(cin >> n){

    fill_array(dp1, INT_MIN);
    fill_array(dp2, INT_MIN);
    fill_array(visit1, false);
    fill_array(visit2, false);
    
    LLI ans = rec1(0,0);
    
    cout << ans << endl;
  }
  
  return 0;
}
