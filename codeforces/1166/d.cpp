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

bool check_overflow_mul_ll(int64_t a, int64_t b){
  return a >= LLONG_MAX / b;
}

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  int q; cin >> q;
  while(q--){
    LLI a,b,m; cin >> a >> b >> m;

    if(a==b){
      cout << 1 << " " << a << endl;
      continue;
    }

    bool no = true;

    vector<LLI> ans;

    FORE(k,2,50){
      if(check_overflow_mul_ll(a, 1LL<<(k-2))) continue;
      LLI d = b-a*(1LL<<(k-2));
      if(d<=0) continue;

      vector<LLI> temp;
      LLI MAX = LLONG_MAX;
      if(not check_overflow_mul_ll(1LL<<(k-2), m)) MAX = (1LL<<(k-2))*m;

      LLI MIN = 1LL<<(k-2);

      dump(d);

      bool fail = false;
      
      FORE(i,2,k-1){
	MIN = 1LL<<(k-i-1);
	if(not check_overflow_mul_ll(1LL<<(k-i-1), m)) MAX = 1LL<<(k-i-1) * m;
	
	LLI r = min(m, (d-MIN)/(1LL<<(k-i-1)));
	if(r <= 0) fail = true;

	dump(r);

	if(fail)break;

	temp.push_back(r);

	d -= r * (1LL<<(k-i-1));
      }
      if(fail) continue;

      dump(d);

      if(1 <= d and d <= m){
	temp.push_back(d);
      }else{
	fail = true;
      }

      if(fail) continue;

      dump(temp);

      ans = vector<LLI>(k);
      ans[0] = a;

      FOR(i,1,k){
	REP(j,i){
	  ans[i] += ans[j];
	}
	ans[i] += temp[i-1];
      }
      
      no = false;
      break;
    }

    if(no){
      cout << -1 << endl;
    }else{
      cout << ans.size() << " ";
      join(cout, ALL(ans));
    }
  }
  
  return 0;
}
