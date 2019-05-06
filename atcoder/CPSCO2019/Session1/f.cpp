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

using pii = pair<int,int>;

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  int N;
  while(cin >> N){
    vector<LLI> t(N), A(N), B(N);
    REP(i,N){
      cin >> t[i] >> A[i] >> B[i];
    }

    auto check =
      [&](LLI x){
        vector<pii> v;
	priority_queue<pii, vector<pii>, greater<pii>> pq;

	REP(i,N){
	  if(A[i]-x<0) return false;
	  v.push_back(make_pair(t[i]-(A[i]-x)/B[i], t[i]+(A[i]-x)/B[i]));
	}
	sort(RALL(v));

        FORE(i,1,N){
	  while(!v.empty()){
	    if(v.back().fst <= i){
	      pq.push(make_pair(v.back().snd, v.back().fst));
	      v.pop_back();
	    }
	    else break;
	  }

	  if(pq.empty()) return false;
	  
	  auto p = pq.top(); pq.pop();
	  if(i>p.fst or i<p.snd) return false;
	}

	return true;
      };

    LLI lb = INT_MIN, ub = INT_MAX, mid;
    
    while(abs(lb-ub) > 1){
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
