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

template <typename T> bool is_square(T n){T rt = sqrt(n); return rt*rt == n;}

vector<LLI> divisor_list(LLI n){
  vector<LLI> temp, res;
  for(LLI i=1LL; i*i<n; ++i) if(n%i == 0) temp.push_back(i);
  for(auto i : temp) res.push_back(i);
  if(is_square(n)) res.push_back((LLI)sqrt(n));
  for(auto itr=temp.rbegin(); itr!=temp.rend(); ++itr) res.push_back(n/(*itr));
  return res;
}

const LLI A_MAX = 10000000;

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  int n;
  while(cin >> n){
    vector<int> a(n); cin >> a;
    vector<int> b(a);
    sort(ALL(b));

    unordered_map<int,vector<int>> index;
    REP(i,n) index[a[i]].push_back(i);

    LLI ans = LLONG_MAX;
    pair<int,int> ans_index = {-1,-1};

    map<int,int> cnt;
    for(auto x : b){
      ++cnt[x];
      if(cnt[x] >= 2) chmin(ans, x);
    }

    if(ans != LLONG_MAX){
      ans_index = {index[ans][0]+1, index[ans][1]+1};
    }

    b.erase(unique(ALL(b)), b.end());

    vector<int> v(A_MAX+1);
    for(auto x : b) v[x] = 1;

    FORE(i,1,A_MAX){
      vector<LLI> t;
      LLI j = i;
      while(j <= A_MAX){
	if(v[j]) t.push_back(j);
	j += i;
	
	if(t.size() >= 2) break;
      }

      if(t.size() >= 2){
	if(chmin(ans, t[0]*t[1]/i)){
	  ans_index = {index[t[0]][0]+1, index[t[1]][0]+1};
	}
      }
    }


    if(ans_index.fst > ans_index.snd) swap(ans_index.fst, ans_index.snd);
    cout << ans_index.fst << " " << ans_index.snd << endl;
  }
  
  return 0;
}
