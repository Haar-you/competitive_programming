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

int alice(const int i, const LLI X, vector<int> &dp_a, vector<int> &dp_b, vector<bool> &used_a, vector<bool> &used_b, const vector<LLI> &a);
int bob(const int i, const LLI X, vector<int> &dp_a, vector<int> &dp_b, vector<bool> &used_a, vector<bool> &used_b, const vector<LLI> &a);

int N;

int alice(const int i, const LLI X, vector<int> &dp_a, vector<int> &dp_b, vector<bool> &used_a, vector<bool> &used_b, const vector<LLI> &a){
  if(i==N) return dp_a[i] = 0;
  if(used_a[i]) return dp_a[i];
  used_a[i] = true;
  
  int ret = -10000;
  LLI sum = a[i];
  FORE(j,i+1,N){
    chmax(ret, -bob(j,X,dp_a,dp_b,used_a,used_b,a) + (sum>=X?1:-1));
    if(j==N) break;
    sum += a[j];
  }
  
  return dp_a[i] = ret;
}

int bob(const int i, const LLI X, vector<int> &dp_a, vector<int> &dp_b, vector<bool> &used_a, vector<bool> &used_b, const vector<LLI> &a){
  if(i==N) return dp_b[i] = 0;
  if(used_b[i]) return dp_b[i];
  used_b[i] = true;

  int ret = -10000;
  LLI sum = a[i];
  FORE(j,i+1,N){
    chmax(ret, -alice(j,X,dp_a,dp_b,used_a,used_b,a) + (sum<X?1:-1));
    if(j==N) break;
    sum += a[j];
  }

  return dp_b[i] = ret;
}


int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  while(cin >> N){
    vector<LLI> a(N); cin >> a;

    auto check = [&](LLI X){
		   vector<int> dp_a(N+1), dp_b(N+1);
		   vector<bool> used_a(N+1), used_b(N+1);
		   int m = alice(0,X,dp_a,dp_b,used_a,used_b,a);
		   return m >= 0;
		 };

    LLI lb=-1e14, ub=1e14, mid;
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
