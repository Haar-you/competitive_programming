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

  int Q;
  while(cin >> Q){
    REP(_,Q){
      char C; cin >> C;
      LLI E; cin >> E;

      string ans;
      bool no = false;

      if(E==0){
	if(C=='a') ans = "a";
	else ans = "aa";
      }else{
	int N = 0;

        vector<string> s;

	do{
	  if(E <= 25){
	    string t;
	    REP(i,N) t.push_back(C);
	    for(char i='a'; i<='z' and t.size()<E+N; ++i){
	      if(i!=C){
		t.push_back(i);
	      }
	    }
	    sort(ALL(t));
	    if(t != ""){ 
	      s.push_back(t);
	    }
	  }

	  if(E%2!=0) break;

	  E /= 2;
	  ++N;
	}while(1);

	if(s.empty()){
	  no = true;
	}else{
	  sort(ALL(s));
	  dump(s);
	  ans = s[0];
	}
      }
      
      if(no){
	cout << -1 << endl;
      }else{
	cout << ans << endl;
      }
    }
  }
  
  return 0;
}
