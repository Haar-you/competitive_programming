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
  string S;
  int A,B,C,D;
  while(cin >> N >> S >> A >> B >> C >> D){
    vector<bool> used(N);

    bool ans = true;

    int o = count(ALL(S), 'o');
    int x = count(ALL(S), 'x');

    if(o != A+B+C or x != A+B+D) ans = false;

    vector<int> oxox_str;
    vector<int> xoxo_str;
    vector<int> oxo_str;
    vector<int> xox_str;
    
    int k = 0;
    REP(i,N){
      if(i == 0 or S[i-1] == S[i]){
	k = i;
      }

      if(i != k and (i == N-1 or S[i] == S[i+1])){
	if(S[k] == 'o' and S[i] == 'o') oxo_str.push_back(i-k+1);
	if(S[k] == 'o' and S[i] == 'x') oxox_str.push_back(i-k+1);
	if(S[k] == 'x' and S[i] == 'x') xox_str.push_back(i-k+1);
	if(S[k] == 'x' and S[i] == 'o') xoxo_str.push_back(i-k+1);
      }
    }
    
    dump(oxo_str);
    dump(oxox_str);
    dump(xox_str);
    dump(xoxo_str);
    
    sort(RALL(oxox_str));
    sort(RALL(xoxo_str));

    int ox = 0;
    int xo = 0;

    while(oxox_str.size()){
      if(ox + oxox_str.back() <= 2*A){
	ox += oxox_str.back();
	oxox_str.pop_back();
      }else{
	break;
      }
    }

    while(xoxo_str.size()){
      if(xo + xoxo_str.back() <= 2*B){
	xo += xoxo_str.back();
	xoxo_str.pop_back();
      }else{
	break;
      }
    }
    
    dump(oxox_str);
    dump(xoxo_str);
    
    
    int c = 0;

    for(auto i : oxo_str) c += i-1;
    for(auto i : xox_str) c += i-1;
    for(auto i : oxox_str) c += i-2;
    for(auto i : xoxo_str) c += i-2;

    if(2*A-ox + 2*B-xo > c) ans = false; 
    

    
    cout << (ans ? "Yes" : "No") << endl;
  }
  
  return 0;
}
