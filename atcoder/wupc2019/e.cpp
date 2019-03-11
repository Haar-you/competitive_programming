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
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
#ifndef M_E
#define M_E 2.71828182845904523536
#endif

#ifdef DEBUG
#include <misc/C++/Debug.cpp>
#else
#define dump(x)
#endif

#define pln(x) cout << (x) << endl
#define gcd __gcd

using namespace std;
template <class T> constexpr T lcm(T m, T n){return m/gcd(m,n)*n;}

template <typename T> using V = vector<T>;
template <typename T, typename U> using P = pair<T,U>;
template <typename I> void join(ostream &ost, I s, I t, string d=" "){for(auto i=s; i!=t; ++i){if(i!=s)ost<<d; ost<<*i;}ost<<endl;}
template <typename T> istream& operator>>(istream &is, vector<T> &v){for(auto &a : v) is >> a; return is;}
template <typename T, typename U> istream& operator>>(istream &is, pair<T,U> &p){is >> p.first >> p.second; return is;}

template <typename T, typename U> T& chmin(T &a, const U &b){return a = (a<=b?a:b);}
template <typename T, typename U> T& chmax(T &a, const U &b){return a = (a>=b?a:b);}
template <typename T, size_t N, typename U> void fill_array(T (&a)[N], const U &v){fill((U*)a, (U*)(a+N), v);}

class RollingHash{
private:
  vector<int> str;
  LLI base, mod;
  int sl;
  vector<LLI> shash, pow;
public:
  RollingHash(vector<int> &_str, LLI _base, LLI _mod): str(_str), base(_base), mod(_mod), sl(str.size()), pow(sl+1), shash(sl+1){
    pow[0] = 1; shash[0] = 0;
    FORE(i,1,sl){shash[i] = (shash[i-1]*base+str[i-1]) % mod; pow[i] = pow[i-1]*base % mod;}
  }
  LLI hash(int i, int j){return (shash[j] - shash[i] * pow[j-i] + mod*mod) % mod;}
};



int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  int M,N;
  while(cin >> M >> N){
    vector<string> a(M); cin >> a;

    
    vector<int> c1(M), c2(N);
    REP(i,M){
      REP(j,N){
	if(a[i][j] == '1'){
	  ++c1[i];
	  ++c2[j];
	}
      }
    }

    const LLI base = 300000;

    dump(c1);

    RollingHash rh1(c1, base, 1e9+7);
    reverse(ALL(c1));
    RollingHash rh2(c1, base, 1e9+7);

    dump(c2);

    RollingHash rh3(c2, base, 1e9+7);
    reverse(ALL(c2));
    RollingHash rh4(c2, base, 1e9+7);

    int h = 0;
    FOR(i,1,M){
      if(rh1.hash(0,i) == rh2.hash(M-i,M) and rh1.hash(i,M) == rh2.hash(0,M-i)) ++h;
    }

    int w = 0;
    FOR(i,1,N){
      if(rh3.hash(0,i) == rh4.hash(N-i,N) and rh3.hash(i,N) == rh4.hash(0,N-i)) ++w;
    }

    cout << h*w << endl;
  }
  
  return 0;
}
