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
#define dump(x)
#endif

#define gcd __gcd

using namespace std;
template <class T> constexpr T lcm(T m, T n){return m/gcd(m,n)*n;}

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
    vector<LLI> a(n); cin >> a;

    vector<LLI> acc(n+1);
    REP(i,n) acc[i+1] = acc[i] + a[i];

    map<LLI, vector<pair<int,int>>> m;
    REP(i,n) FOR(j,i,n) m[acc[j+1]-acc[i]].push_back({i,j});
    
    vector<pair<int,int>> ans;

    for(auto &kv : m){
      auto &vec = kv.snd;

      sort(ALL(vec), [](const pair<int,int> &a, const pair<int,int> &b){return a.snd < b.snd;});

      vector<pair<int,int>> temp;

      int last = -1;

      for(auto &p : vec){
	if(p.fst > last){
	  last = p.snd;
	  temp.push_back(p);
	}
      }
      if(temp.size() > ans.size()) ans = temp;
    }

    cout << ans.size() << endl;
    for(auto &p : ans){
      cout << p.fst+1 << " " << p.snd+1 << endl;
    }
  }
  
  return 0;
}
