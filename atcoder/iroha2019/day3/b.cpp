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

pair<string, string> query(int x, int y, int z){
  cout << "? " << x << " " << y << " " << z << endl;
  string s, t; cin >> s >> t;
  return make_pair(s,t);
}

void answer(int t){
  cout << "! " << t << endl;
}

const int qs[10][3] =
  {
   {3,4,5}, {3,4,6}, {3,4,7}, {3,5,6}, {3,5,7}, {3,6,7}, {4,5,6}, {4,5,7}, {4,6,7}, {5,6,7}
  };

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);
  
  string s, t; tie(s,t) = query(0,1,2);

  if(s == "Square" or s == "Rectangle"){
    int S, T;

    for(auto &q : qs){
      string s2, t2; tie(s2, t2) = query(q[0], q[1], q[2]);
      if(s2 == s) ++S;
      if(t2 == s) ++T;
    }
    
    if(S == 6){
      answer(1);
    }else{
      answer(2);
    }
  }else{
    int S, T;
    vector<int> kS, kT;

    for(auto &q : qs){
      string s2, t2; tie(s2, t2) = query(q[0], q[1], q[2]);
      if(s2 == s){
	++S;
	for(auto x : q) kS.push_back(x);
      }	
      if(t2 == t){
	++T;
	for(auto x : q) kT.push_back(x);
      }
    }

    sort(ALL(kS));
    kS.erase(unique(ALL(kS)), kS.end());

    sort(ALL(kT));
    kT.erase(unique(ALL(kT)), kT.end());

    if(S == 4 and T == 4){
      if(kS.size() == 4) answer(1);
      else answer(2);
    }else if(S == 4){
      answer(1);
    }else{
      answer(2);
    }
  }
  
  return 0;
}
