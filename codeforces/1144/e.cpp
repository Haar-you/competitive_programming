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

  int k;
  string s,t;
  while(cin >> k >> s >> t){

    vector<int> a(k), b(k);
    REP(i,k){
      a[i] = s[i]-'a';
      b[i] = t[i]-'a';
    }
    reverse(ALL(a));
    reverse(ALL(b));
    
    vector<int> p(k+1);
    {
      int d = 0;
      REP(i,k){
	p[i] = a[i] + b[i] + d;
	if(p[i] >= 26){
	  d = 1;
	  p[i] -= 26;
	}else{
	  d = 0;
	}
      }
      if(d==1) p[k] = d;
    }

    {
      int d = 0;
      REV(i,k,0){
	p[i] += d;
	if(p[i]%2==1){
	  p[i] /= 2;
	  d = 26;
	}else{
	  p[i] /= 2;
	  d = 0;
	}
      }
    }

    p.pop_back();
    reverse(ALL(p));

    string ans(k, ' ');
    REP(i,k) ans[i] = p[i] + 'a';

    cout << ans << endl;
  }
  
  return 0;
}
