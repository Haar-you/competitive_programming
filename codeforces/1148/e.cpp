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

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  int n;
  while(cin >> n){
    vector<LLI> s(n), t(n); cin >> s >> t;

    vector<int> ord(n); iota(ALL(ord), 0);

    sort(ALL(ord), [&](int i, int j){return s[i] < s[j];});
    sort(ALL(t));

    bool no = false;
    vector<tuple<int,int,int>> ans;

    if(t.front() < s[ord.front()] or t.back() > s[ord.back()]) no = true;

    if(not no){
      vector<LLI> ds(n);
      REP(i,n) ds[i] = t[i]-s[ord[i]];
      vector<int> negp;
      REP(i,n) if(ds[i] < 0) negp.push_back(i);
      reverse(ALL(negp));

      if(accumulate(ALL(ds),0LL) != 0) no = true;

      if(not no){
	REP(i,n){
	  if(ds[i] < 0){
	    no = true;
	    break;
	  }

	  while(negp.size()){
	    int j = negp.back();
	    LLI x = abs(ds[j]);
	    if(x >= ds[i]){
	      ans.push_back(make_tuple(ord[i],ord[j],ds[i]));
	      if(x == ds[i]) negp.pop_back();
	      ds[j] += ds[i];
	      ds[i] = 0;
	      break;
	    }else{
	      ans.push_back(make_tuple(ord[i],ord[j],x));
	      negp.pop_back();
	      ds[j] = 0;
	      ds[i] -= x;
	    }
	  }
	}
      }
    }

    if(no){
      cout << "NO" << endl;
    }else{
      cout << "YES" << endl;
      cout << ans.size() << endl;
      for(auto &t : ans){
	if(s[get<0>(t)] > s[get<1>(t)]) swap(get<0>(t), get<1>(t));
	else cout << get<0>(t)+1 << " " << get<1>(t)+1 << " " << get<2>(t) << endl;
      }
    }
  }
  
  return 0;
}
