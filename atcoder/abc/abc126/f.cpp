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

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);
  
  int M,K;
  while(cin >> M >> K){
    vector<int> ans;
    bool no = false;


    if(K >= (1<<M)){
      no = true;
    }else{
      if(M == 0){
	ans.push_back(0);
	ans.push_back(0);
      }else if(M == 1){
	if(K == 0){
	  ans.push_back(0);
	  ans.push_back(0);
	  ans.push_back(1);
	  ans.push_back(1);
	}else{
	  no = true;
	}
      }else{
	FOR(i,0,1<<M){
	  if(i == K) continue;
	  ans.push_back(i);
	}
	ans.push_back(K);
	REV(i,(1<<M)-1,0){
	  if(i == K) continue;
	  ans.push_back(i);
	}
	ans.push_back(K);
      }
    }

    if(no){
      cout << -1 << endl;
    }else{
      join(cout, ALL(ans));
    }
  }
  
  return 0;
}
