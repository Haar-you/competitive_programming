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

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  int n;
  while(cin >> n){
    vector<int> a(n*2); cin >> a;
    for(auto &x : a) --x;

    LLI ans = 0;

    vector<vector<int>> b(n);

    REP(i,2*n){
      b[a[i]].push_back(i);
    }

    vector<bool> visit(2*n);

    LLI x = 0;
    LLI y = 0;
    REP(i,n){
      if(
	 abs(b[i][0]-x) + abs(b[i][1]-y) < abs(b[i][1]-x) + abs(b[i][0]-y)
	 ){
	ans += abs(b[i][0]-x);
	visit[b[i][0]] = true;
	x = b[i][0];
	y = b[i][1];
      }else{
	ans += abs(b[i][1]-x);
	visit[b[i][1]] = true;
	x = b[i][1];
	y = b[i][0];
      }
    }
    dump(ans);

    x = 0;
    REP(i,n){
      if(!visit[b[i][0]]){
	ans += abs(b[i][0]-x);
	visit[b[i][0]] = true;
	x = b[i][0];
      }else{
	ans += abs(b[i][1]-x);
	visit[b[i][1]] = true;
	x = b[i][1];
      }
    }
    
    cout << ans << endl;
  }
  
  return 0;
}
