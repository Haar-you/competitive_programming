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

int query(int i, int j){
  cout << "? " << i << " " << j << endl;
  int ret; cin >> ret;
  return ret;
}

void answer(vector<int> &ans){
  cout << "! ";
  join(cout, ALL(ans));
}

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  vector<int> a = {4, 8, 15, 16, 23, 42};

  vector<int> ans(6);

  int w = query(1,2);
  int x = query(2,3);
  int y = query(3,4);
  int z = query(4,5);

  do{
    if(a[0]*a[1] == w and
       a[1]*a[2] == x and
       a[2]*a[3] == y and
       a[3]*a[4] == z){
      ans = a;
      break;
    }
  }while(next_permutation(ALL(a)));
  
  
  answer(ans);
  
  return 0;
}
