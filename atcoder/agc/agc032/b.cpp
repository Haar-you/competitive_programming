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

  int N;
  while(cin >> N){
    vector<vector<int>> cograph(N);
    if(N%2==0){
      REP(i,N/2){
	cograph[i].push_back(N-1-i);
	cograph[N-1-i].push_back(i);
      }
    }else{
      REP(i,N/2){
	cograph[i].push_back(N-2-i);
	cograph[N-2-i].push_back(i);
      }
    }

    vector<vector<int>> graph(N);
    REP(i,N){
      sort(ALL(cograph[i]));
      vector<bool> use(N, true);
      for(auto x : cograph[i]) use[x] = false;
      REP(j,N) if(use[j]) graph[i].push_back(j);
    }

    vector<pair<int,int>> ans;
    REP(i,N){
      for(auto j : graph[i]){
	if(i<j) ans.push_back({i+1,j+1});
      }
    }

    cout << ans.size() << endl;
    for(auto &p : ans){
      cout << p.fst << " " << p.snd << endl;
    }
  }
  
  return 0;
}
