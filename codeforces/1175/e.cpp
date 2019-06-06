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
#define UNIQ(v) v.erase(unique(ALL(v)), v.end())
#define bit(i) (1LL<<i)
#define sz(v) ((LLI)(v).size())

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

const int MAX = 500000;
int par[21][MAX+1];

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  int n,m;
  while(cin >> n >> m){
    vector<int> l(n), r(n);
    REP(i,n){
      cin >> l[i] >> r[i];
    }

    vector<int> x(m), y(m);
    REP(i,m){
      cin >> x[i] >> y[i];
    }

    fill_array(par, -1);

    vector<int> ord(n); iota(ALL(ord), 0);
    sort(ALL(ord), [&](int i, int j){return l[i] < l[j];});

    priority_queue<int> pq; 

    {
      int j = 0;
      REPE(i,MAX){
	while(j<n and l[ord[j]]<=i){
	  pq.push(r[ord[j]]);
	  ++j;
	}

	if(not pq.empty()){
	  int next = pq.top();
	  if(next >= i){
	    par[0][i] = next;
	  }
	}
      }
    }

    FORE(i,1,20){
      REPE(j,MAX){
	int k = par[i-1][j];
	if(k!=-1){
	  par[i][j] = par[i-1][k];
	}
      }
    }
    
    auto check =
      [&](int t, int a, int b){
	int x = a;
	REPE(i,20){
	  if((t>>i)&1){
	    if(par[i][x] == -1) return false;
	    x = par[i][x];
	  }
	}
	
        return x>=b;
      };

    
    REP(i,m){
      int a = x[i], b = y[i];

      int ans = 0;
      bool no = false;

      if(not check(MAX+10,a,b)) no = true;
      else{
	int lb = -1, ub = MAX+1, mid;
	while(abs(lb-ub) > 1){
	  mid = (lb+ub)/2;

	  if(check(mid,a,b)){
	    ub = mid;
	  }else{
	    lb = mid;
	  }
	}
	
	ans = ub;
      }

      if(no) cout << -1 << "\n";
      else cout << ans << "\n";
    }
    cerr << endl;
  }
  
  return 0;
}
