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
template <typename T, typename U> P<T,U> operator+(const P<T,U> &a, const P<T,U> &b){return {a.first + b.first, a.second + b.second};}
template <typename T, typename U> P<T,U> operator-(const P<T,U> &a, const P<T,U> &b){return {a.first - b.first, a.second - b.second};}
template <typename T> void cout_join(vector<T> &v,string d=" "){REP(i,v.size()){if(i>0)cout<<d;cout<<v[i];}cout<<endl;}

double distance(double x1, double y1, double x2, double y2){
  return sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));
}

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  double a,b,c; cin >> a >> b >> c;
  double x1,y1,x2,y2; cin >> x1 >> y1 >> x2 >> y2;

  double dist = abs(x1-x2) + abs(y1-y2);

  if(a != 0 && b != 0){
    double xA,yA,xB,yB;
    yA = (-a*x1-c)/b;
    xB = (-b*y2-c)/a;
    xA = (-b*y1-c)/a;
    yB = (-a*x2-c)/b;

    dist = min(dist, fabs(yA-y1) + distance(x1,yA,xB,y2) + fabs(xB-x2));
    dist = min(dist, fabs(xA-x1) + distance(xA,y1,x2,yB) + fabs(yB-y2));
    dist = min(dist, fabs(yA-y1) + distance(x1,yA,x2,yB) + fabs(yB-y2));
    dist = min(dist, fabs(xA-x1) + distance(xA,y1,xB,y2) + fabs(xB-x2));
  }

  printf("%.012f\n", dist);
  
  return 0;
}
