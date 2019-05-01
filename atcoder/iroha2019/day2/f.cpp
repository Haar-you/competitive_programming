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

double dp1[11][11][11][11][11][11];
bool used1[11][11][11][11][11][11];

double dp2[11][11][11][11][11][11];
bool used2[11][11][11][11][11][11];

double rec1(int,int,int,int,int,int);
double rec2(int,int,int,int,int,int);

double rec1(int a1, int a2, int b1, int b2, int c1, int c2){
  if(a1<0 or a2<0 or b1<0 or b2<0 or c1<0 or c2<0) return 0;
  if(used1[a1][a2][b1][b2][c1][c2]) return dp1[a1][a2][b1][b2][c1][c2];
  used1[a1][a2][b1][b2][c1][c2] = true;

  double t = 0;

  if(a1 or a2) chmax(t, ((rec2(a1-1,a2,b1,b2,c1,c2)+100.0)*a1 + (rec2(a1,a2-1,b1,b2,c1,c2)+50.0)*a2)/(a1+a2));
  if(b1 or b2) chmax(t, ((rec2(a1,a2,b1-1,b2,c1,c2)+100.0)*b1 + (rec2(a1,a2,b1,b2-1,c1,c2)+50.0)*b2)/(b1+b2));
  if(c1 or c2) chmax(t, ((rec2(a1,a2,b1,b2,c1-1,c2)+100.0)*c1 + (rec2(a1,a2,b1,b2,c1,c2-1)+50.0)*c2)/(c1+c2));

  return dp1[a1][a2][b1][b2][c1][c2] = t;
}

double rec2(int a1, int a2, int b1, int b2, int c1, int c2){
  if(a1<0 or a2<0 or b1<0 or b2<0 or c1<0 or c2<0) return 0;
  if(used2[a1][a2][b1][b2][c1][c2]) return dp2[a1][a2][b1][b2][c1][c2];
  used2[a1][a2][b1][b2][c1][c2] = true;


  if(a1==0 and a2==0 and b1==0 and b2==0 and c1==0 and c2==0) return 0;

  double t = 1000000;

  if(a1 or a2) chmin(t, ((rec1(a1-1,a2,b1,b2,c1,c2))*a1 + (rec1(a1,a2-1,b1,b2,c1,c2))*a2)/(a1+a2));
  if(b1 or b2) chmin(t, ((rec1(a1,a2,b1-1,b2,c1,c2))*b1 + (rec1(a1,a2,b1,b2-1,c1,c2))*b2)/(b1+b2));
  if(c1 or c2) chmin(t, ((rec1(a1,a2,b1,b2,c1-1,c2))*c1 + (rec1(a1,a2,b1,b2,c1,c2-1))*c2)/(c1+c2));

  return dp2[a1][a2][b1][b2][c1][c2] = t;
}

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  int A1,A2,B1,B2,C1,C2;
  while(cin >> A1 >> A2 >> B1 >> B2 >> C1 >> C2){
    fill_array(dp1, 0);
    fill_array(used1, false);

    fill_array(dp2, 0);
    fill_array(used2, false);

    double ans = rec1(A1,A2,B1,B2,C1,C2);
    
    cout << setprecision(12) << ans << endl;
  }
  
  return 0;
}
