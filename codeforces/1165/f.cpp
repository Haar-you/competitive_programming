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
    vector<int> k(n); cin >> k;

    vector<pair<int,int>> dt(m);
    REP(i,m){
      int d,t; cin >> d >> t;
      dt[i] = {d,t};
    }
    sort(RALL(dt));

    int s = accumulate(ALL(k), 0);
    
    auto check =
      [&](int x){
	if(x<s) return false;

	vector<int> k2(k);
	
	unordered_map<int,int> mp;
	RITR(it,dt){
	  if(it->fst > x) break;
	  chmax(mp[it->snd], it->fst);
	}
	
	vector<pair<int,int>> temp;
	for(auto &kv : mp){
	  temp.push_back({kv.snd, kv.fst});
	}
	sort(RALL(temp));

	int money = 0;
	FORE(i,1,x){
	  ++money;

	  while(temp.size() and temp.back().fst == i){
	    auto &p = temp.back();

	    while(money > 0 and k2[p.snd-1] > 0){
	      --k2[p.snd-1];
	      --money;
	    }
	    
	    temp.pop_back();
	  }
	}

	int s2 = accumulate(ALL(k2), 0);

	if(s2*2 <= money) return true;
	else return false;
      };

    int lb = 0, ub = s*2+1, mid;
    while(abs(lb-ub) > 1){
      mid = (lb+ub)/2;

      if(check(mid)){
	ub = mid;
      }else{
	lb = mid;
      }
    }
    
    int ans = ub;
    cout << ans << endl;
  }
 
  
  return 0;
}
