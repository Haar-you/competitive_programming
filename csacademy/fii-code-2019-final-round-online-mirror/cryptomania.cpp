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

LLI power(LLI n, LLI p, LLI m){
  LLI ret = 1;
  while(p>0){
    if(p&1) (ret *= n) %= m;
    (n *= n) %= m;
    p /= 2;
  }
  return ret;
}

LLI mod_inv(LLI n, LLI p){return power(n,p-2,p);}

LLI N, P;

bool check(LLI A, LLI B, LLI a, LLI b, LLI c){
  return B == ((a*A%P*A%P + b*A%P)%P + c)%P;
}

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  while(cin >> N >> P){
    vector<int> A(N), B(N); cin >> A >> B;

    LLI a=0,b=0,c=0;
    bool no = false;

    if(N==1){
      a = b = 0;
      c = B[0];
    }else if(N==2){
      FOR(i,0,P){
	LLI j = ((B[0]-B[1]+P)%P - i*(A[0]*A[0]%P-A[1]*A[1]%P+P)%P)%P * mod_inv(A[0]-A[1]+P,P)%P;
	LLI k = ((B[0] - i*A[0]%P*A[0]%P + P)%P - j*A[0]%P + P) % P;
	
	if(check(A[0],B[0],i,j,k) and check(A[1],B[1],i,j,k)){
	  a = i; b = j; c = k;
	  break;
	}
	if(i==P-1) no = true;
      }
    }else{
      LLI x = ((B[0]-B[1]+P)*mod_inv(A[0]-A[1]+P,P)%P - (B[1]-B[2]+P)*mod_inv(A[1]-A[2]+P,P)%P + P)%P;
      a = x * mod_inv(A[0]-A[2]+P,P) % P;
      b = ((B[0]-B[1]+P)%P - a*(A[0]*A[0]%P-A[1]*A[1]%P+P)%P + P)%P * mod_inv(A[0]-A[1]+P,P) % P;
      c = ((B[0] - a*A[0]%P*A[0]%P + P) % P - b*A[0]%P + P) % P;

      REP(i,N){
	if(not check(A[i],B[i],a,b,c)) no = true;
      }
    }

    if(no){
      cout << "impossible" << endl;
    }else{
      cout << a << " " << b << " " << c << endl;
    }
  }
  
  return 0;
}
