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

bool is_palindrome(const string &s){
  int n = s.size();
  REP(i,n/2) if(s[i] != s[n-1-i]) return false;
  return true;
}

int rec(string &s, int d=0){
  if(s.size() == 1 || s.size() == 2) return -1;
  int ans;
  string sub = s.substr(0,s.size()/2);
  if(s.size() % 2 == 1){
    if(d!=0) return 2;
    if(count(ALL(s),s[0]) >= s.size()-1) return -1;
    else if(is_palindrome(sub)) ans = rec(sub,d+1)>0 ? 2 : -1;
    else ans = 2;
  }else{
    if(count(ALL(s),s[0]) == s.size()) return -1;
    else if(is_palindrome(sub)) ans = rec(sub,d+1);
    else ans = 1;
  }

  return ans;
}

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  string s;
  while(cin >> s){
    int ans = rec(s);
    if(ans == -1) cout << "Impossible" << endl;
    else cout << ans << endl;
  }
  
  return 0;
}

