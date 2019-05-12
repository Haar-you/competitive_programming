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

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  int N;
  while(cin >> N){
    vector<LLI> A(N); cin >> A;

    vector<LLI> s1(N+1);
    REP(i,N) s1[i+1] = s1[i]+ A[i];

    vector<LLI> count1(N);
    map<LLI,LLI> m1;

    REP(i,N){
      ++m1[s1[i]];
      count1[i] = m1[s1[i+1]];
    }

    FOR(i,1,N) count1[i] += count1[i-1];

    reverse(ALL(A));

    vector<LLI> s2(N+1);
    REP(i,N) s2[i+1] = s2[i] + A[i];

    vector<LLI> count2(N);
    map<LLI,LLI> m2;

    REP(i,N){
      ++m2[s2[i]];
      count2[i] = m2[s2[i+1]];
    }

    FOR(i,1,N) count2[i] += count2[i-1];

    reverse(ALL(count2));

    LLI ans = LLONG_MAX;

    chmin(ans, min(count1[N-2], count2[1]));

    FOR(i,1,N-1){
      chmin(ans, count1[i-1]+count2[i+1]);
    }

    cout << ans << endl;
  }
  
  return 0;
}
