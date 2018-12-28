#include <bits/stdc++.h>
#define FOR(v, a, b) for(int v = (a); v < (b); ++v)
#define FORE(v, a, b) for(int v = (a); v <= (b); ++v)
#define REP(v, n) FOR(v, 0, n)
#define REPE(v, n) FORE(v, 0, n)
#define REV(v, a, b) for(int v = (a); v >= (b); --v)
#define ALL(x) (x).begin(), (x).end()
#define ITR(it, c) for(auto it = (c).begin(); it != (c).end(); ++it)
#define LLI long long int
using namespace std;
template <typename T> using V = vector<T>;
template <typename T, typename U> using P = pair<T,U>;
template <typename I> void join(ostream &ost, I s, I t, string d=" "){for(auto i=s; i!=t; ++i){if(i!=s)ost<<d; ost<<*i;}ost<<endl;}

vector<int> aux(string &s, int n){
  vector<int> a(n);
  stack<char> st;
  int cl=0,op=0;
  REP(i,n){
    a[i] = cl!=0 ? -1 : op;
    if(st.empty()){
      st.push(s[i]);
      if(s[i] == '(') ++op;
      else ++cl;
    }else{
      if(st.top() == '(' && s[i] == ')'){
	st.pop();
	--op;
      }else{
	st.push(s[i]);
	if(s[i] == '(') ++op;
	else ++cl;
      }
    }
  }
  return a;
}

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  int n; cin >> n;
  string s; cin >> s;

  auto a = aux(s,n);
  reverse(ALL(s));
  for_each(ALL(s), [](char &c){c=(c=='('?')':'(');});
  auto b = aux(s,n);
  reverse(ALL(s));
  for_each(ALL(s), [](char &c){c=(c=='('?')':'(');});

  int ans = 0;
  REP(i,n){
    if(a[i]==-1 || b[n-1-i]==-1) continue;
    if((s[i]=='(' && a[i]==b[n-i-1]+1) || (s[i]==')' && b[n-i-1]==a[i]+1)) ++ans;
  }
  cout << ans << endl;
  
  return 0;
}
