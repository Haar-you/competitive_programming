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

#define popcount __builtin_popcount

void for_each_subset_desc(int a, const function<void(int)> &f){
  for(int t=a; ; t=(t-1)&a){
    f(t);
    if(t==0) break;
  }
}

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  int N,K;
  while(cin >> N >> K){
    vector<int> A(N); cin >> A;

    vector<int> sum(1<<N);

    REP(i,1<<N){
      REP(j,N){
	if(i&(1<<j)) sum[i] += A[j];
      }
    }

    vector<LLI> dp2(1<<N), dp3(1<<N);

    dp2[0] = 1;
    dp3[0] = 1;

    FOR(i,1,1<<N){
      if(popcount(i) % 2 != 0) continue;

      REP(j,N){
	bool b = false;
	FOR(k,j+1,N){
	  if((i&(1<<j)) and (i&(1<<k)) and A[j]+A[k]<=2*K){
	    dp2[i] += dp2[i^(1<<j)^(1<<k)];
	    b = true;
	  }
	}
	if(b) break;
      }
    }

    FOR(i,1,1<<N){
      if(popcount(i) % 3 != 0) continue;

      REP(j,N){
	bool b = false;
	FOR(k,j+1,N){
	  FOR(l,k+1,N){
	    if((i&(1<<j)) and (i&(1<<k)) and (i&(1<<l)) and A[j]+A[k]+A[l]<=3*K){
	      dp3[i] += dp3[i^(1<<j)^(1<<k)^(1<<l)];
	      b = true;
	    }
	  }
	}
	if(b) break;
      }
    }
    
    LLI ans = 0;

    auto f =
      [&](int i, int j){
	if(i&j) return;
	if(popcount(j)%3) return;
	ans += dp2[i] * dp3[j];
      };
    
    REP(i,1<<N){
      if(popcount(i)%2) continue;
      for_each_subset_desc(((1<<N)-1)^i, bind(f,i,placeholders::_1));
    }

    cout << ans << endl;
  }
  
  return 0;
}
