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
#define dump(x)
#endif

#define gcd __gcd

using namespace std;
template <class T> constexpr T lcm(T m, T n){return m/gcd(m,n)*n;}

template <typename I> void join(ostream &ost, I s, I t, string d=" "){for(auto i=s; i!=t; ++i){if(i!=s)ost<<d; ost<<*i;}ost<<endl;}
template <typename T> istream& operator>>(istream &is, vector<T> &v){for(auto &a : v) is >> a; return is;}
template <typename T, typename U> istream& operator>>(istream &is, pair<T,U> &p){is >> p.first >> p.second; return is;}

template <typename T, typename U> T& chmin(T &a, const U &b){return a = (a<=b?a:b);}
template <typename T, typename U> T& chmax(T &a, const U &b){return a = (a>=b?a:b);}
template <typename T, size_t N, typename U> void fill_array(T (&a)[N], const U &v){fill((U*)a, (U*)(a+N), v);}

void rec(int cur, const vector<vector<int>> &graph, vector<bool> &visit, vector<int> &ret){
  if(visit[cur]) return;
  visit[cur] = true;
  if(ret.empty() or ret[0] != cur) ret.push_back(cur);

  for(auto next : graph[cur]){
    if(next == cur) continue;
    rec(next, graph, visit, ret);
  }
}


int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  int N,K;
  while(cin >> N >> K){
    vector<int> a(N), b(N); cin >> a >> b;

    vector<vector<int>> g(N);
    REP(i,N){
      g[a[i]-1].push_back(b[i]-1);
      g[b[i]-1].push_back(a[i]-1);
    }

    vector<int> dp(N+1, -1e9);
    dp[0] = 0;

    vector<bool> visit(N);
    REP(i,N){
      if(not visit[i]){
	vector<int> cycle;
	rec(i, g, visit, cycle);
	for(auto &x : cycle) ++x;

	int m = cycle.size();
	
	vector<vector<int>> dp1(m+1, vector<int>(m+1, -1e9));
	vector<vector<int>> dp2(m+1, vector<int>(m+1, -1e9));
	dp1[0][0] = 0;
	dp2[0][0] = 0;
	
	REP(j,m){
	  REP(k,m){
	    if(j<k) continue;
	    if((k+1)%2==0){
	      chmax(dp1[j+1][k+1], dp1[j][k]+cycle[j]);
	      chmax(dp1[j+1][k], dp1[j][k]);
	      
	      chmax(dp2[j+1][k+1], dp2[j][k]-cycle[j]);
	      chmax(dp2[j+1][k], dp2[j][k]);
	    }else{
	      chmax(dp1[j+1][k+1], dp1[j][k]-cycle[j]);
	      chmax(dp1[j+1][k], dp1[j][k]);

	      chmax(dp2[j+1][k+1], dp2[j][k]+cycle[j]);
	      chmax(dp2[j+1][k], dp2[j][k]);
	    }
	  }
	}

	int s = accumulate(ALL(cycle), 0);

	vector<int> res(m+1,-1e9);

	REPE(j,m/2){
	  res[m-j] = s + max(dp1[m][j*2], dp2[m][j*2]);
	}

	vector<int> temp(N+1, -1e9);
        REV(j,N,0){
	  REV(k,m,0){
	    if(j+k<=N){
	      chmax(temp[j+k], dp[j]+res[k]);
	    }
	  }
	}
	dp.swap(temp);
      }
    }

    int ans = 0;
    FORE(i,K,N) chmax(ans, dp[i]);

    cout << ans << endl;
  }
  
  return 0;
}
