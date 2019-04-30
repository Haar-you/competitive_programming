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

template <typename T> class SparseTable{
  using Op = function<T(T,T)>;
  Op f;
  vector<vector<T>> a;
  vector<int> log_table;
public:
  SparseTable(const vector<T> &v, const Op &f): f(f){
    int n = v.size();
    int logn = 0;
    while((1<<logn) <= n) ++logn;
    
    a = vector<vector<T>>(n, vector<T>(logn));
    REP(i,n) a[i][0] = v[i];
    FOR(j,1,logn) REP(i,n) a[i][j] = f(a[i][j-1], a[min(n-1, i+(1<<(j-1)))][j-1]);

    log_table = vector<int>(n+1);
    FOR(i,2,n+1) log_table[i] = log_table[i>>1] + 1;
  }
  
  T get(int s, int t){ // [s,t)
    int k = log_table[t-s];
    return f(a[s][k], a[t-(1<<k)][k]);
  }
};

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  LLI N,K;
  while(cin >> N >> K){
    vector<LLI> A(N); cin >> A;

    SparseTable<LLI> sptable(A, [](LLI a, LLI b){return a|b;});

    auto check =
      [&](LLI x){
	LLI cnt = 0;

	int left=0, right=0;
	while(left<=right and left<N and right<N){
	  if(sptable.get(left,right+1)>=x){
	    cnt += N-right;
	    ++left;
	  }else{
	    ++right;
	  }
	  if(left>right) ++right;
	}

	return cnt >= K;
      };
    
    LLI lb = 0, ub = 1LL<<60, mid;
    while(abs(lb-ub)>1){
      mid = (lb+ub)/2;

      if(check(mid)){
	lb = mid;
      }else{
	ub = mid;
      }
    }

    LLI ans = lb;
    
    cout << ans << endl;
  }
  
  return 0;
}
