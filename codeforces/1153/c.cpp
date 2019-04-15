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

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  int n;
  string s;
  while(cin >> n >> s){

    bool no = false;
    
    if(s.size()%2==1 or s.front() == ')' or s.back() == '(') no = true;

    s.front() = '(';
    s.back() = ')';

    {
      string t(s);

      FORE(i,1,n-2){
	if(s[i] == '?') s[i] = '(';
      }

      stack<char> st;
      FORE(i,1,n-2){
	if(st.empty()){
	  st.push(s[i]);
	}else{
	  if(st.top() == '(' and s[i] == ')') st.pop();
	  else st.push(s[i]);
	}
      }

      int k = st.size() / 2;

      REV(i,n-2,1){
	if(t[i] == '?' and k){
	  s[i] = ')';
	  --k;
	}
      }
    }

    {
      stack<char> st;
      FORE(i,1,n-2){
	if(st.empty()){
	  st.push(s[i]);
	}else{
	  if(st.top() == '(' and s[i] == ')') st.pop();
	  else st.push(s[i]);
	}
      }
      if(not st.empty()) no = true;
    }

    if(no){
      cout << ":(" << endl;
    }else{
      cout << s << endl;
    }
  }
  
  return 0;
}
