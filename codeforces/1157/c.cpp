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

  int n;
  while(cin >> n){
    vector<int> a(n); cin >> a;

    queue<int> left, right;

    REP(i,n){
      if(i==0) left.push(a[i]);
      else if(a[i-1] < a[i]) left.push(a[i]);
      else break;
    }

    reverse(ALL(a));

    REP(i,n){
      if(i==0) right.push(a[i]);
      else if(a[i-1] < a[i]) right.push(a[i]);
      else break;
    }

    string ans;
    vector<int> temp;

    dump(left);
    dump(right);

    while(!left.empty() or !right.empty()){
      if(left.empty()){
	if(temp.empty() or temp.back()<right.front()){
	  temp.push_back(right.front());
	  right.pop();
	  ans.push_back('R');
	}else{
	  break;
	}
      }else if(right.empty()){
	if(temp.empty() or temp.back()<left.front()){
	  temp.push_back(left.front());
	  left.pop();
	  ans.push_back('L');
	}else{
	  break;
	}
      }else{
	if(temp.empty() or temp.back()<right.front() or temp.back()<left.front()){
	  if(right.front() < left.front()){
	    temp.push_back(right.front());
	    right.pop();
	    ans.push_back('R');
	  }else if(right.front() >= left.front()){
	    temp.push_back(left.front());
	    left.pop();
	    ans.push_back('L');
	  }else{
	    break;
	  }
	}else{
	  break;
	}
      }
    }

    cout << ans.size() << endl;
    cout << ans << endl;
  }
  
  return 0;
}
