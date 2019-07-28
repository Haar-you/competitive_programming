#include <bits/stdc++.h>
#define LLI long long int
#define FOR(v, a, b) for(LLI v = (a); v < (b); ++v)
#define FORE(v, a, b) for(LLI v = (a); v <= (b); ++v)
#define REP(v, n) FOR(v, 0, n)
#define REPE(v, n) FORE(v, 0, n)
#define REV(v, a, b) for(LLI v = (a); v >= (b); --v)
#define ALL(x) (x).begin(), (x).end()
#define RALL(x) (x).rbegin(), (x).rend()
#define ITR(it, c) for(auto it = (c).begin(); it != (c).end(); ++it)
#define RITR(it, c) for(auto it = (c).rbegin(); it != (c).rend(); ++it)
#define EXIST(c,x) ((c).find(x) != (c).end())
#define fst first
#define snd second
#define popcount __builtin_popcount
#define UNIQ(v) (v).erase(unique(ALL(v)), (v).end())
#define bit(i) (1LL<<(i))

#ifdef DEBUG
#include <misc/C++/Debug.cpp>
#else
#define dump(...) ((void)0)
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

template <typename T> int sign(T n){return (n>0)-(n<0);}

using pii = pair<int,int>;

template <typename T, typename U> pair<T,U> operator+(const pair<T,U> &a, const pair<T,U> &b){return pair<T,U>(a.fst+b.fst, a.snd+b.snd);}
template <typename T, typename U> pair<T,U>operator-(const pair<T,U> &a, const pair<T,U> &b){return pair<T,U>(a.fst-b.fst, a.snd-b.snd);}
template <typename S, typename T, typename U> pair<T,U> operator*(const S &a, const pair<T,U> &b){return pair<T,U>(a*b.fst, a*b.snd);}


template <typename T, typename U> ostream& operator<<(ostream &os, const pair<T,U> &a){os << "(" << a.fst << "," << a.snd << ")"; return os;}

void construct(vector<pair<pii,pii>> paths, int k, vector<pii> &ret){
  int d = 0;
  for(auto p : paths){
    int len = abs(p.snd.fst-p.fst.fst) + abs(p.snd.snd-p.fst.snd);
    pii dir = make_pair(sign(p.snd.fst-p.fst.fst), sign(p.snd.snd-p.fst.snd));

    if(d){
      ret.push_back(p.fst+d*dir);
    }
    
    REP(i,(len-d)/k) ret.push_back(p.fst+d*dir+((i+1)*k)*dir);

    if((len-d)%k){
      d = k - (len-d)%k;
    }else{
      d = 0;
    }
  }
}

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  LLI k,x,y;
  while(cin >> k >> x >> y){

    int sign_x = (x < 0 ? -1 : 1);
    int sign_y = (y < 0 ? -1 : 1);

    x = abs(x);
    y = abs(y);

    bool swapped = false;
    if(x < y){
      swapped = true;
      swap(x,y);
    }

    if(k%2==0 and (x+y)%2==1){
      cout << -1 << endl;
      continue;
    }

    int n = (x+y+k-1) / k;

    if(x+y > k){
      if((n*k-x-y)%2==1){
        n += 1;
      }
    }else if(x+y < k){
      if(n == 1){
        if(x+y != k) ++n;
      }
      if((n*k-x-y)%2==1){
        n += 1;
      }
    }
    
    vector<pii> ans;

    if((x+y) % k == 0){
      construct({{{0,0},{x,0}}, {{x,0},{x,y}}}, k, ans);
    }else if(x+y < k and n == 3){
      int d = (k+x-y)/2;
      construct({{{0,0},{0,-(k-x)}}, {{0,-(k-x)},{x+d,-(k-x)}}, {{x+d,-(k-x)},{x+d,y}}, {{x+d,y},{x,y}}}, k, ans);
    }else{
      int c = (n*k-x-y)/2;
      construct({{{0,0},{0,-c}}, {{0,-c},{x,-c}}, {{x,-c},{x,y}}}, k, ans);
    }
    
    cout << n << endl;
    for(auto &p : ans){
      if(swapped) swap(p.fst, p.snd);
      cout << sign_x*p.fst << " " << sign_y*p.snd << endl;
    }
  }
  
  return 0;
}
