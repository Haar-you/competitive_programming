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
#define UNIQ(v) v.erase(unique(ALL(v)), v.end())
#define bit(i) (1LL<<i)
#define sz(v) ((LLI)(v).size())

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

  int N;
  while(cin >> N){
    vector<LLI> A(N); cin >> A;
    sort(ALL(A));

    vector<LLI> b(N);
    REP(i,N) b[i] = abs(A[i]);

    LLI ans = 0;
    vector<pair<int,int>> ans_op;

    if(A[0] >= 0){ // all positive
      LLI x=A.front();

      FOR(i,1,N-1){
	ans_op.push_back({x,A[i]});
	x -= A[i];
      }

      ans_op.push_back({A.back(), x});

      ans = accumulate(ALL(b), 0LL) - 2*b[0];
    }else if(A.back() < 0){ // all negative
      reverse(ALL(b));
      reverse(ALL(A));
      LLI x=A.front();

      FOR(i,1,N){
	ans_op.push_back({x,A[i]});
	x -= A[i];
      }

      ans = accumulate(ALL(b), 0LL) - 2*b[0];
    }else{
      ans = accumulate(ALL(b), 0LL);

      LLI x=A.front(),y=A.back();

      FOR(i,1,N){
	if(A[i]>=0) break;
	ans_op.push_back({y,A[i]});
	y -= A[i];
      }

      REV(i,N-2,1){
	if(A[i]<0) break;
	ans_op.push_back({x,A[i]});
	x -= A[i];
      }

      ans_op.push_back({y,x});
    }
    
    cout << ans << endl;
    for(auto &p : ans_op){
      cout << p.fst << " " << p.snd << endl;
    }
  }
  
  return 0;
}
