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

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  int n,x;
  while(cin >> n >> x){
    vector<int> a(n); cin >> a;

    unordered_set<int> s;
    for(auto i : a) s.insert(i);
    
    auto check =
      [&](int i){
	vector<int> temp;
	for(auto k : a) if(k > i) temp.push_back(k);

	REP(i,(int)temp.size()-1){
	  if(temp[i] > temp[i+1]) return false;
	}
	  
	return true;
      };
      
    int lb = 0, ub = x, mid;
    while(abs(lb-ub) > 1){
      mid = (lb+ub)/2;

      if(check(mid)){
	ub = mid;
      }else{
	lb = mid;
      }
    }
    
    int r = ub;

    vector<int> pmin(x+1,n), pmax(x+1);
    REP(i,n){
      chmin(pmin[a[i]], i);
      chmax(pmax[a[i]], i);
    }

    vector<int> b(a);
    sort(ALL(b));
    b.erase(unique(ALL(b)), b.end());

    LLI ans = x-r+1;

    int m = 0;
    
    FORE(i,1,x){
      if(pmax[m] > pmin[i]) break;

      chmax(r, i+1);
      
      if(EXIST(s, i)) chmax(m, i);
      
      while(1){
	auto it = upper_bound(ALL(b), r);

	if(r<x and it!=b.end() and pmax[m] > pmin[*it]){
	  ++r;
	}else{
	  break;
	}
      }

      ans += x-r+1;
    }


    cout << ans << endl;
  }
  
  return 0;
}
