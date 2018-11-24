#include <bits/stdc++.h>
#define FOR(v, a, b) for(int v = (a); v < (b); ++v)
#define FORE(v, a, b) for(int v = (a); v <= (b); ++v)
#define REP(v, n) FOR(v, 0, n)
#define REPE(v, n) FORE(v, 0, n)
#define REV(v, a, b) for(int v = (a); v >= (b); --v)
#define ALL(x) (x).begin(), (x).end()
#define LLI long long int
using namespace std;
template <typename T> using V = vector<T>;
template <typename T, typename U> using P = pair<T,U>;
template <typename I> void cout_join(I s, I t, string d=" "){for(auto i=s; i!=t; ++i){if(i!=s)cout<<d;cout<<*i;}cout<<endl;}

tuple<LLI,LLI,LLI> extGCD(LLI a, LLI b){
  if(b == 0) return make_tuple(a,1,0);
  LLI d,p,q;
  tie(d,q,p) = extGCD(b,(a+b)%b);
  return make_tuple(d,p,q-a/b*p);
}

bool CRT(LLI b1, LLI m1, LLI b2, LLI m2, LLI &r, LLI &m){
  LLI p,q,d; tie(d,p,q) = extGCD(m1,m2);
  if((b2-b1) % d != 0) return false;
  m = m1 * m2 / d;
  LLI t = ((b2-b1) * p / d) % (m2 / d);
  r = (b1 + m1 * t + m) % m;
  return true;
}

bool CRT(vector<LLI> &bs, vector<LLI> &ms, LLI &r, LLI &m){
  LLI R=0,M=1;
  REP(i,bs.size()){
    if(!CRT(R,M,bs[i],ms[i],r,m)) return false;
    R = r;
    M = m;
  }
  return true;
}

int digit_sum(LLI a, int n){
  int r = 0;
  while(a != 0){
    r += a % n;
    a /= n;
  }
  return r;
}

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  vector<LLI> a(29);
  REP(i,29) cin >> a[i];

  vector<LLI> b(29);
  REP(i,29) b[i] = i+1;

  LLI r, m;
  if(!CRT(a,b,r,m)){
    cout << "invalid" << endl;
  }else{
    bool f = true;
    REP(i,29) if(a[i] != digit_sum(r,i+2)) f = false;
    if(r <= 1e12 && f) cout << r << endl;
    else cout << "invalid" << endl;
  }

  return 0;
}
