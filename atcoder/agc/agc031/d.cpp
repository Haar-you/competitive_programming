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

vector<int> compose(const vector<int> &p, const vector<int> &q){
  int n = p.size();
  vector<int> ret(n);
  REP(i,n) ret[i] = p[q[i]];
  return ret;
}

vector<int> inverse(const vector<int> &p){
  int n = p.size();
  vector<int> ret(n);
  REP(i,n) ret[p[i]] = i;
  return ret;
}

template <typename T> T power(T n, LLI p, const T &e, const function<T(T,T)> &f){
  T ret = e;
  while(p>0){
    if(p&1) ret = f(ret, n);
    n = f(n, n);
    p /= 2;
  }
  return ret;
}

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  int N,K;
  while(cin >> N >> K){
    vector<int> p(N), q(N); cin >> p >> q;
    for(auto &x : p) --x;
    for(auto &x : q) --x;
    
    auto ip = inverse(p);
    auto iq = inverse(q);
    auto x = compose(q, compose(ip, compose(iq, p)));;
    auto id = vector<int>(N);
    REP(i,N) id[i] = i;
    
    vector<int> as[6] = {id, id, id, q, compose(q,ip), compose(q,ip)};
    vector<int> a = compose(power<vector<int>>(x, (K-1)/6, id, compose), as[(K+5)%6]);
    
    vector<int> bs[6] = {p,q,compose(q,ip),ip,iq,compose(iq,p)};
    auto b = bs[(K+5)%6];
    
    auto ans = compose(a, compose(b, inverse(a)));

    for(auto &x : ans) ++x;
    join(cout, ALL(ans));
  }
  
  return 0;
}
