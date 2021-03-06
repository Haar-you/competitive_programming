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

  int N,K;
  string S;
  while(cin >> N >> K >> S){
    vector<int> a;

    if(S[0] == '0') a.push_back(0);

    REP(i,N){
      if(S[i] == '0'){
	if(a.size() % 2 == 1) a.push_back(0);
	++a.back();
      }else{
	if(a.size() % 2 == 0) a.push_back(0);
	++a.back();
      }
    }

    if(S.back() == '0') a.push_back(0);

    vector<int> sum(a.size()+1);
    REP(i,(int)a.size()) sum[i+1] = sum[i] + a[i];

    int ans = 0;

    REP(i,(int)a.size()){
      if(i%2==1) continue;
      int j = min((int)a.size(),i+2*K+1);
      chmax(ans, sum[j] - sum[i]);
    }

    cout << ans << endl;
  }
  
  return 0;
}
