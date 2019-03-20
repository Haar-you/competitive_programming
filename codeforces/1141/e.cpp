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

  LLI H, n;
  while(cin >> H >> n){
    vector<LLI> d(n); cin >> d;

    vector<LLI> acc(n,d[0]);
    FOR(i,1,n) acc[i] = acc[i-1] + d[i];
    LLI min_acc = *min_element(ALL(acc));

    LLI diff_sum = accumulate(ALL(d), 0LL);

    LLI ans = 0;
    bool no_ans = false;

    REP(i,n){
      if(H+acc[i] <= 0){
	ans = i+1;
	break;
      }
    }
    
    if(ans == 0 && diff_sum >= 0){
      no_ans = true;
    }

    if(!no_ans && !ans){
      LLI lb=0, ub=H/(-diff_sum)+100, mid;

      while(abs(lb-ub)>1){
	mid = (lb+ub)/2;
	if(H-mid*(-diff_sum) <= (-min_acc)){
	  ub = mid;
	}else{
	  lb = mid;
	}
      }
      
      ans = ub*n;
      REP(i,2*n){
	if(H-ub*(-diff_sum)+acc[i%n] <= 0){
	  ans += i+1;
	  break;
	}
      }
    }

    if(no_ans){
      cout << -1 << endl;
    }else{
      cout << ans << endl;
    }
  }
  
  return 0;
}
