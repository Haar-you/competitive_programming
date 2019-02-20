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
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
#ifndef M_E
#define M_E 2.71828182845904523536
#endif

#ifdef DEBUG
#include <misc/C++/Debug.cpp>
#else
#define dump(x)
#endif

#define pln(x) cout << (x) << endl
#define gcd __gcd

using namespace std;
template <class T> constexpr T lcm(T m, T n){return m/gcd(m,n)*n;}

template <typename T> using V = vector<T>;
template <typename T, typename U> using P = pair<T,U>;
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
  while(cin >> n){
    vector<int> a(n*n); cin >> a;
    sort(ALL(a));

    vector<int> count(1100);
    for(auto x : a) ++count[x];
    
    vector<vector<int>> mat(n, vector<int>(n));
    bool no_ans = false;

    if(n%2==0){
      vector<int> t;
      FORE(i,1,1000){
	if(count[i] == 0) continue;
	if(count[i] % 4 != 0){
	  no_ans = true;
	}
	int c = count[i]/4;
	REP(j,c) t.push_back(i);
      }

      if(no_ans){
	cout << "NO" << endl;
        continue;
      }
      
      cout << "YES" << endl;

      REP(i,n/2) REP(j,n/2){
	mat[i][j] = t[i+j*n/2];
	mat[n-1-i][j] = t[i+j*n/2];
	mat[i][n-1-j] = t[i+j*n/2];
	mat[n-1-i][n-1-j] = t[i+j*n/2];
      }

      REP(i,n) join(cout, ALL(mat[i]));
    }else{
      vector<int> t;
      FORE(i,1,1000){
	if(count[i] == 0) continue;
	if(count[i] >= 4){
	  int k = count[i]/4;
	  REP(j,k){
	    t.push_back(i);
	    count[i] -= 4;
	    if(t.size() >= (n/2)*(n/2)) break;
	  }
	}
	if(t.size() >= (n/2)*(n/2)) break;
      }

      if(t.size() < (n/2)*(n/2)){
	cout << "NO" << endl;
	continue;
      }

      vector<int> t2;
      FORE(i,1,1000){
	if(count[i] == 0) continue;
	if(count[i] >= 2){
	  int k = count[i]/2;
	  REP(j,k){
	    t2.push_back(i);
	    count[i] -= 2;
	    if(t2.size() >= (n-1)) break;
	  }
	}
	if(t2.size() >= (n-1)) break;
      }

      if(t2.size() < (n-1)){
	cout << "NO" << endl;
	continue;
      }

      vector<int> center;
      FORE(i,1,1000){
	if(count[i] == 1) center.push_back(i);
      }

      if(center.size() != 1){
	cout << "NO" << endl;
	continue;
      }

      cout << "YES" << endl;

      mat[n/2][n/2] = center[0];

      REP(i,(n-1)/2){
	mat[n/2][i] = t2[i];
	mat[n/2][n-1-i] = t2[i];
      }

      REP(i,(n-1)/2){
	mat[i][n/2] = t2[i+(n-1)/2];
	mat[n-1-i][n/2] = t2[i+(n-1)/2];
      }

      REP(i,n/2) REP(j,n/2){
	mat[i][j] = t[i+j*(n/2)];
	mat[n-1-i][j] = t[i+j*(n/2)];
	mat[i][n-1-j] = t[i+j*(n/2)];
	mat[n-1-i][n-1-j] = t[i+j*(n/2)];
      }
      
      REP(i,n) join(cout, ALL(mat[i]));

    }
  }
  
  return 0;
}
