#include <bits/stdc++.h>
#define LLI long long int
#define FOR(v, a, b) for(LLI v = (a); v < (b); ++v)
#define FORE(v, a, b) for(LLI v = (a); v <= (b); ++v)
#define REP(v, n) FOR(v, 0, n)
#define REPE(v, n) FORE(v, 0, n)
#define REV(v, a, b) for(LLI v = (a); v >= (b); --v)
#define ALL(x) (x).begin(), (x).end()
#define RALL(x) (x).rbegin(), (x).rend()
#define ITR(it, c) for(auto it = (c).begin(); it != (c).end(); ++it)
#define RITR(it, c) for(auto it = (c).rbegin(); it != (c).rend(); ++it)
#define EXIST(c,x) ((c).find(x) != (c).end())
#define fst first
#define snd second
#define popcount __builtin_popcount
#define UNIQ(v) (v).erase(unique(ALL(v)), (v).end())
#define bit(i) (1LL<<(i))

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

  LLI n,k;
  while(cin >> n >> k){
    vector<LLI> a(n); cin >> a;

    vector<LLI> b;
    REP(i,n) b.push_back(a[i]);
    REP(i,n) b.push_back(a[i]);

    vector<vector<LLI>> poss(400000);
    REP(i,2*n){
      poss[b[i]].push_back(i);
    }
    
    vector<LLI> next(n);
    REP(i,n){
      next[i] = *upper_bound(ALL(poss[a[i]]), i);
      if(next[i] >= n) next[i] -= n;
    }

    LLI cycle = 1;

    LLI j = 0;
    vector<LLI> last;
    
    REP(i,n){
      if(next[j] <= j){
        ++cycle;
        last.push_back(j);
      }

      (j = next[j]+1) %= n;

      if(j==0) break;
    }

    k %= cycle;

    vector<LLI> ans;

    if(k!=0){
      FOR(i,last[k-1],n){
        if(next[i] > i and next[i] < n){
          i = next[i];
        }else{
          ans.push_back(a[i]);
        }
      }
    }
    
    join(cout, ALL(ans));
  }
  
  return 0;
}
