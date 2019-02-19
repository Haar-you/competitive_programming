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

  int H,W,K;

  while(cin >> H >> W >> K){
    vector<LLI> count_col(W,H), count_row(H,W);

    REP(i,K){
      int r,c; cin >> r >> c;
      --count_col[c-1];
      --count_row[r-1];
    }


    vector<LLI> sum_col(W+1);
    REP(i,W) sum_col[i+1] = sum_col[i] + count_col[i];

    vector<LLI> sum_row(H+1);
    REP(i,H) sum_row[i+1] = sum_row[i] + count_row[i];

    LLI ans = 0;

    {
      LLI temp = 0;
      REP(i,W) temp += count_col[i] * i;
      LLI m = temp;

      FOR(i,1,W){
	temp += sum_col[i];
	temp -= sum_col[W] - sum_col[i];
	chmin(m, temp);
      }
      
      ans += m;
    }

    {
      LLI temp = 0;
      REP(i,H) temp += count_row[i] * i;
      LLI m = temp;

      FOR(i,1,H){
	temp += sum_row[i];
	temp -= sum_row[H] - sum_row[i];
	chmin(m, temp);
      }
      
      ans += m;
    }

    cout << ans << endl;
  }
  
  return 0;
}
