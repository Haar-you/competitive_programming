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

vector<int> solve(int a, int b, int n, int mask){
  if(__builtin_popcount(mask) == 1) return {a,b};

  int x,y,z;

  REP(i,n){
    if((mask&(1<<i)) and (a&(1<<i)) != (b&(1<<i))){
      x = a^(a&(1<<i));
      y = b^(b&(1<<i));

      int new_mask = mask^(1<<i);
      REP(j,n){
	if(new_mask&(1<<j)) z = x^(1<<j);
      }

      auto ret1 = solve(x,z,n,new_mask);
      auto ret2 = solve(z,y,n,new_mask);

      for(auto &p : ret1) p |= (a&(1<<i));
      for(auto &p : ret2) p |= (b&(1<<i));

      for(auto p : ret2) ret1.push_back(p);
      
      return ret1;
    }
  }
}

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  int N,A,B;
  while(cin >> N >> A >> B){
    if(__builtin_parity(A) == __builtin_parity(B)){
      cout << "NO" << endl;
    }else{
      cout << "YES" << endl;
      auto ans = solve(A,B,N,(1<<N)-1);
      join(cout, ALL(ans));
    }
  }
  
  return 0;
}
