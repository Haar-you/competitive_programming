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

class pt{
public:
  double x, y;
  pt(): x(0), y(0){}
  pt(double x, double y): x(x), y(y){}
};

pt operator+(const pt &a, const pt &b){return pt(a.x+b.x, a.y+b.y);}
pt operator-(const pt &a, const pt &b){return pt(a.x-b.x, a.y-b.y);}
pt operator-(const pt &a){return pt(-a.x, -a.y);}
bool operator==(const pt &a, const pt &b){return a.x==b.x and a.y==b.y;}
bool operator!=(const pt &a, const pt &b){return !(a==b);}

double dot(const pt &a, const pt &b){return a.x*b.x+a.y*b.y;}
double cross(const pt &a, const pt &b){return a.x*b.y-a.y*b.x;}

ostream& operator<<(ostream &os, const pt &a){os << "(" << a.x << "," << a.y << ")"; return os;}


vector<pt> upper_hull(vector<pt> pts){
  sort(ALL(pts), [](const pt &a, const pt &b){return (a.x < b.x) or (a.x == b.x and a.y < b.y);});
  reverse(ALL(pts));
  
  vector<pt> ret;

  ret.push_back(pts.back());
  pts.pop_back();
  
  while(not pts.empty()){
    auto s = pts.back();
    pts.pop_back();

    if(ret.size() == 1){
      ret.push_back(s);
    }else{
      auto p = *(ret.end()-2);
      auto q = ret.back();

      if(cross(q-p, s-p) <= 0){
	ret.push_back(s);
      }else{
	ret.pop_back();
	pts.push_back(s);
      }
    }
  }

  return ret;
}


int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  int n;
  while(cin >> n){
    vector<LLI> x(n), y(n);
    REP(i,n) cin >> x[i] >> y[i];

    vector<pt> pts(n);
    REP(i,n) pts[i] = pt(x[i], y[i]-x[i]*x[i]);

    auto uh = upper_hull(pts);

    int ans = 0;
    REP(i,(int)uh.size()-1){
      if(uh[i].x-uh[i+1].x!=0 and (i==0 or cross(uh[i]-uh[i-1],uh[i+1]-uh[i-1])!=0)){
	++ans;
      }
    }
    
    cout << ans << endl;
  }
  
  return 0;
}
