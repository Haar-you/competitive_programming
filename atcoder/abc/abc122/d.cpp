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

const LLI mod = 1e9+7;

bool check(const string &s){
  if(s.find("AGC") != string::npos or s.find("GAC") != string::npos or s.find("ACG") != string::npos){
    return false;
  }

  if(s.size() == 4){
    if(s[0] == 'A' and s[2] == 'G' and s[3] == 'C') return false;
    if(s[0] == 'A' and s[1] == 'G' and s[3] == 'C') return false;
  }
  
  return true;
}

const string agct = "AGCT";

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  LLI N;
  while(cin >> N){

    vector<map<string,LLI>> dp(N+1);

    dp[0][""] = 1;
    REP(i,N){
      for(char c : agct){
	for(auto &kv : dp[i]){
	  string s = kv.fst;
	  string t(s);
	  t.push_back(c);
	  //dump(t);
	  if(t.size() >= 5) t.erase(t.begin());

	  if(check(t)){
	    (dp[i+1][t] += dp[i][s]) %= mod;
	  }
	}
      }
      //      dump(dp[i]);
    }

    LLI ans = 0;
    for(auto &kv : dp[N]){
      (ans += kv.snd) %= mod;
    }
    cout << ans << endl;
  }
  
  return 0;
}
