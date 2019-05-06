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

vector<LLI> A;
int N,K;

int calc(LLI x){
  int ret = 0;

  while(x>0){
    if(x%10 >= 5){
      ret += x%10-4;
    }else{
      ret += x%10;
    }
    x /= 10;
  }
  return ret;
}

vector<LLI> rec(int i, int r){
  if(r==1) return {A[i]};
  
  vector<LLI> ret;

  FOR(j,i+1,N){
    auto res = rec(j,r-1);
    for(auto x : res) ret.push_back(x+A[i]);
  }

  return ret;
}

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  while(cin >> N >> K){
    A = vector<LLI>(N); cin >> A;

    int ans = INT_MAX;

    REP(i,N){
      auto res = rec(i, K);
      //      dump(res);
      for(auto x : res){
	chmin(ans, calc(x));
      }
    }

    cout << ans << endl;
  }
  return 0;
}
