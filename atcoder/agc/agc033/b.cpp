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

string S,T;
int H,W;
int N;

bool f(const vector<int> &tak, const vector<int> &aok, int s, int mx, bool gr){
  int x = s;
  if(gr){
    REP(i,N){
      if(tak[i]){
	++x;
	if(x > mx) return true;
      }

      if(aok[i] and x > 1){
	--x;
      }
    }
  }else{
    REP(i,N){
      if(tak[i]){
	--x;
	if(x < 1) return true;
      }

      if(aok[i] and x < mx){
	++x;
      }
    }    
  }

  return false;
}


int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  while(cin >> H >> W >> N){
    int sr,sc; cin >> sr >> sc;
    cin >> S >> T;

    vector<int> vert_tak_u(N), vert_tak_d(N), vert_aok_u(N), vert_aok_d(N);
    vector<int> hor_tak_l(N), hor_tak_r(N), hor_aok_l(N), hor_aok_r(N);

    int l=0,r=0,u=0,d=0;

    REP(i,N){
      switch(S[i]){
      case 'L':{hor_tak_l[i] = 1; break;}
      case 'R':{hor_tak_r[i] = 1; break;}
      case 'U':{vert_tak_u[i] = 1; break;}
      case 'D':{vert_tak_d[i] = 1; break;}
      }
      switch(T[i]){
      case 'L':{hor_aok_l[i] = 1; chmax(l,i); break;}
      case 'R':{hor_aok_r[i] = 1; chmax(r,i); break;}
      case 'U':{vert_aok_u[i] = 1; chmax(u,i); break;}
      case 'D':{vert_aok_d[i] = 1; chmax(d,i); break;}     
      }
    }

    bool ans =
      f(hor_tak_l, hor_aok_r, sc, W, false) || f(hor_tak_r, hor_aok_l, sc, W, true) ||
      f(vert_tak_u, vert_aok_d, sr, H, false) || f(vert_tak_d, vert_aok_u, sr, H, true);
        
    
    cout << (ans ? "NO" : "YES") << endl;

  }
  
  return 0;
}
