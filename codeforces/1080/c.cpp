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

LLI black(LLI x1, LLI y1, LLI x2, LLI y2){
  if((x1+y1)%2==0){
    return (x2-x1+1)*(y2-y1+1)/2;
  }else{
    return (x2-x1+1)*(y2-y1+1)/2 + (x2-x1+1)*(y2-y1+1)%2;
  }
}

LLI white(LLI x1, LLI y1, LLI x2, LLI y2){
  if((x1+y1)%2==0){
    return (x2-x1+1)*(y2-y1+1)/2 + (x2-x1+1)*(y2-y1+1)%2;
  }else{
    return (x2-x1+1)*(y2-y1+1)/2;
  }
}

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  int t; cin >> t;

  REP(_,t){
    LLI n,m; cin >> n >> m;
    LLI x1,y1,x2,y2; cin >> x1 >> y1 >> x2 >> y2;
    LLI x3,y3,x4,y4; cin >> x3 >> y3 >> x4 >> y4;

    LLI w,b;

    w = white(1,1,n,m);
    b = black(1,1,n,m);
    
    w += black(x1,y1,x2,y2);
    b -= black(x1,y1,x2,y2);

    w -= white(x3,y3,x4,y4);
    b += white(x3,y3,x4,y4);
    
    if(max(x1,x3) <= min(x2,x4) && max(y1,y3) <= min(y2,y4)){
      w -= black(max(x1,x3),max(y1,y3),min(x2,x4),min(y2,y4));
      b += black(max(x1,x3),max(y1,y3),min(x2,x4),min(y2,y4));
    }
    
    cout << w << " " << b << endl;
  }
  
  return 0;
}
