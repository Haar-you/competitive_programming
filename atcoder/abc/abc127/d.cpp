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
#define popcount __builtin_popcount
#define UNIQ(v) v.erase(unique(ALL(v)), v.end())

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
  
  int N,M;
  while(cin >> N >> M){
    vector<LLI> A(N); cin >> A;
    sort(RALL(A));

    vector<pair<int,LLI>> BC(M);

    REP(i,M){
      LLI b,c; cin >> b >> c;
      BC[i] = {b,c};
    }

    sort(ALL(BC), [](const pair<int,LLI> &a, const pair<int,LLI> &b){return a.snd > b.snd;});

    LLI ans = 0;

    for(auto &p : BC){
      int b = p.fst;
      LLI c = p.snd;

      REP(i,b){
	if(A.empty() or A.back()>=c) break;
	A.pop_back();
	ans += c;
      }
    }

    ans += accumulate(ALL(A), 0LL);
    

    cout << ans << endl;
  }
  
  return 0;
}
