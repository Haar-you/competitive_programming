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

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  int n;
  string l,r;
  while(cin >> n >> l >> r){
    vector<deque<int>> left(26), right(26);
    deque<int> lindef, rindef;

    REP(i,n){
      if(l[i] == '?') lindef.push_back(i);
      else left[l[i]-'a'].push_back(i);

      if(r[i] == '?') rindef.push_back(i);
      else right[r[i]-'a'].push_back(i);
    }

    vector<pair<int,int>> ans;

    REP(i,26){
      int t = min(left[i].size(), right[i].size());

      REP(j,t){
	ans.push_back({left[i].front()+1, right[i].front()+1});
	left[i].pop_front();
	right[i].pop_front();
      }
    }
    
    REP(i,26){
      int t = min(left[i].size(), rindef.size());

      REP(j,t){
	ans.push_back({left[i].front()+1, rindef.front()+1});
	left[i].pop_front();
	rindef.pop_front();
      }
    }

    REP(i,26){
      int t = min(lindef.size(), right[i].size());

      REP(j,t){
	ans.push_back({lindef.front()+1, right[i].front()+1});
	lindef.pop_front();
        right[i].pop_front();
      }
    }

    {
      int t = min(lindef.size(), rindef.size());

      REP(i,t){
	ans.push_back({lindef.front()+1, rindef.front()+1});
	lindef.pop_front();
	rindef.pop_front();
      }
    }


    cout << ans.size() << endl;
    for(auto &p : ans){
      cout << p.fst << " " << p.snd << endl;
    }
  }
  
  return 0;
}
