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

template <typename T> bool is_square(T n){T rt = sqrt(n); return rt*rt == n;}

bool test(vector<LLI> &v){
  LLI sum = 0;

  REP(i,v.size()){
    sum += v[i];
    if(!is_square(sum) || v[i] < 1 || v[i] > 1e13){
      return false;
    }
  }
  return true;
}

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  int n; cin >> n;

  vector<LLI> x(n/2);
  REP(i,n/2) cin >> x[i];


  vector<LLI> ans(n);
  LLI sum = 0;

  REP(i,n/2){
    ans[i*2+1] = x[i];

    LLI a = max(1LL, (LLI)sqrt(sum));
    while((a+1)*(a+1) <= a*a + x[i]){
      if(is_square(a*a+x[i])){
	ans[i*2] = a*a-sum;
	break;
      }
      ++a;
    }
    sum += ans[i*2] + ans[i*2+1];
  }

  if(!test(ans)){
    cout << "No" << endl;
  }else{
    cout << "Yes" << endl;
    join(cout, ALL(ans));
  }
  
  return 0;
}
