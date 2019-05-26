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
#define popcount __builtin_popcount
#define UNIQ(v) v.erase(unique(ALL(v)), v.end())

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

template <typename T> using rev_priority_queue = priority_queue<T,vector<T>,greater<T>>;

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  int Q;
  while(cin >> Q){
    LLI B = 0;

    LLI s1 = 0, s2 = 0;
    priority_queue<LLI> q1;
    rev_priority_queue<LLI> q2;

    REP(i,Q){
      int c; cin >> c;

      if(c == 1){
	LLI a,b; cin >> a >> b;

	B += b;

	if(q1.size() == q2.size()){
	  q2.push(a); s2 += a;
	  auto p = q2.top(); q2.pop(); s2 -= p;

	  q1.push(p); s1 += p;
	}else{
	  q1.push(a); s1 += a;
	  auto p = q1.top(); q1.pop(); s1 -= p;

	  q2.push(p); s2 += p;
	}

	if(not (q2.empty() or q1.top() <= q2.top())) assert(false);
	
      }else{
	if(q1.size() == q2.size()){
	  LLI x1 = q1.top();
	  LLI x2 = q2.top();

	  LLI ans1 = abs(s1-x1*(int)q1.size())+abs(s2-x1*(int)q2.size()) + B;
	  LLI ans2 = abs(s1-x2*(int)q1.size())+abs(s2-x2*(int)q2.size()) + B;
	
	  if(ans1 <= ans2)
	    cout << x1 << " " << ans1 << endl;
	  else
	    cout << x2 << " " << ans2 << endl;
	}else{
	  LLI x = q1.top();
	  LLI ans = abs(s1-x*(int)q1.size())+abs(s2-x*(int)q2.size()) + B;
	  cout << x << " " << ans << endl;
	}
      }
    }
    
  }
  
  return 0;
}
