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

  int n,m;
  while(cin >> n >> m){
    vector<bitset<200>> a(n);
    REP(i,n){
      REP(j,m){
	int x; cin >> x;
	if(x) a[i].set(j);
      }
    }

    bitset<200> c;
    REP(i,m) c.set(i);

    vector<bitset<200>> bs(m);
    REP(i,m) REP(j,i) bs[i].set(j);
	

    if(all_of(ALL(a), [&](const bitset<200> &x){return x==a[0] or x==(c^a[0]);})){
      cout << "YES" << endl;

      vector<int> row(n), col(m);
      
      REP(i,n) row[i] = a[0]==a[i];
      REP(i,m) col[i] = a[0][i];

      join(cout, ALL(row), "");
      join(cout, ALL(col), "");
    }else{
      bool no = true;

      REP(i,n){
	REP(j,m){
	  bitset<200> t = i?a[0]:a[1];

	  bool fail = false;
	  REP(k,n){
	    if(i==k) continue;
	    if(a[k] != t and a[k] != (c^t)){
	      fail = true;
	      break;
	    }
	  }

	  if(fail) continue;

	  if((a[i]^bs[j]) == t or (a[i]^bs[j]) == (c^t)){
	    cout << "YES" << endl;

	    vector<int> row(n), col(m);

	    REP(k,j) col[k] = a[i][k];
	    FOR(k,j,m) col[k] = !a[i][k];

	    REP(k,i) row[k] = (a[i]^bs[j])==a[k];
	    FOR(k,i+1,n) row[k] = (a[i]^bs[j])!=a[k];

	    
	    join(cout, ALL(row), "");
	    join(cout, ALL(col), "");
	    
	    no = false;
	    break;
	  }
	}
	if(!no) break;
      }
	 
      if(no){
	cout << "NO" << endl;
      }
    }
  }
  
  return 0;
}
