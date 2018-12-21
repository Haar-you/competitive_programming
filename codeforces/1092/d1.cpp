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

int solve(pair<int,int> p, stack<pair<int,int>> &st1, stack<pair<int,int>> &st2){
  if(st1.empty() && st2.empty()) return 1;

  if(!st1.empty() && st2.empty()){
    if(st1.top().first == p.first){
      p.second += st1.top().second;
      st1.pop();
      return solve(p,st1,st2);
    }else{
      if(p.second % 2 == 0){
	p.first = st1.top().first;
	p.second += st1.top().second;
	st1.pop();
	return solve(p,st1,st2);
      }
      return 0;
    }
  }

  if(st1.empty() && !st2.empty()){
    if(st2.top().first == p.first){
      p.second += st2.top().second;
      st2.pop();
      return solve(p,st1,st2);
    }else{
      if(p.second % 2 == 0){
	p.first = st2.top().first;
	p.second += st2.top().second;
	st2.pop();
	return solve(p,st1,st2);
      }
      st1.push(p);
      p = st2.top(); st2.pop();
      return solve(p,st1,st2);
    }
  }

  if(st1.top().first == p.first && st2.top().first == p.first){
    p.second += st1.top().second + st2.top().second;
    st1.pop();
    st2.pop();
    return solve(p,st1,st2);
  }

  if(st1.top().first == p.first){
    p.second += st1.top().second;
    st1.pop();
    return solve(p,st1,st2);
  }

  if(st2.top().first == p.first){
    p.second += st2.top().second;
    st2.pop();
    return solve(p,st1,st2);
  }

  if(p.second % 2 == 0){
    p.first = st1.top().first;
    p.second += st1.top().second + st2.top().second;
    st1.pop();
    st2.pop();
    return solve(p,st1,st2);
  }
  
  st1.push(p);
  p = st2.top(); st2.pop();
  return solve(p,st1,st2);
}

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  int n; cin >> n;
  vector<int> a(n);
  REP(i,n) cin >> a[i];

  REP(i,n) a[i] %= 2;

  stack<pair<int,int>> st1, st2;

  REP(i,n){
    st2.push(make_pair(a[i],1));
  }
  
  if(solve(make_pair(0,0), st1, st2)){
    cout << "YES" << endl;
  }else{
    cout << "NO" << endl;
  }

  return 0;
}
