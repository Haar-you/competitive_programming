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


// 拡張ユークリッド互除法
tuple<LLI,LLI,LLI> extGCD(LLI a, LLI b){
  if(b == 0) return make_tuple(a,1,0);
  LLI d,p,q;
  tie(d,q,p) = extGCD(b,(a+b)%b);
  return make_tuple(d,p,q-a/b*p);
}

// Chinese Remainder Algorithm
bool CRA(LLI b1, LLI m1, LLI b2, LLI m2, LLI &r, LLI &m){
  LLI p,q,d; tie(d,p,q) = extGCD(m1,m2);
  if((b2-b1) % d != 0) return false;
  m = m1 * m2 / d;
  LLI t = ((b2-b1) * p / d) % (m2 / d);
  r = (b1 + m1 * t + m) % m;
  return true;
}


int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  vector<LLI> n(200);
  for(char i='a'; i<='z'; ++i) cin >> n[i];

  cout << n['a']-n['b'] << endl;
  cout << n['c']+n['d'] << endl;
  cout << max(0LL, n['f']-n['e']+1) << endl;
  cout << (n['g']+n['h']+n['i'])/3+1 << endl;

  string s = "dagabaji";
  vector<string> ss;
  REP(i,1<<8){
    if(__builtin_popcount(i) == n['j']){
      string t;
      REP(j,8) if(i&(1<<j)) t.push_back(s[j]);
      ss.push_back(t);
    }
  }
  sort(ALL(ss));
  cout << ss[0] << endl;

  LLI r, m;
  CRA(n['k'],59,n['l'],61,r,m);

  LLI f1 = r + m*(n['m']-1);

  vector<LLI> perfect = {6, 28, 496, 8128, 33550336, 8589869056};

  LLI f2 = LLONG_MAX;
  for(auto p : perfect) if(abs(f1-p)>=n['n']) chmin(f2, p);

  cout << min(f1,f2) << endl;
  cout << max(f1,f2) << endl;

  cout << (n['o']+n['p']+n['q'])*(n['r']+n['s']+n['t'])*(n['u']+n['v']+n['w'])*(n['x']+n['y']+n['z'])%9973 << endl;
  
  return 0;
}
