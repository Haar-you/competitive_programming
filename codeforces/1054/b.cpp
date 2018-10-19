#include <bits/stdc++.h>
#define FOR(v, a, b) for(int v = (a); v < (b); ++v)
#define FORE(v, a, b) for(int v = (a); v <= (b); ++v)
#define REP(v, n) FOR(v, 0, n)
#define REPE(v, n) FORE(v, 0, n)
#define REV(v, a, b) for(int v = (a); v >= (b); --v)
#define RS resize
#define CLR clear
#define PB push_back
#define ALL(x) (x).begin(), (x).end()
#define LLI long long int
using namespace std;

//Binary Indexed Tree (0-indexed)
class BIT{
private:
  vector<int> tree;
  int n;
public:
  BIT(int size): tree(size, 0), n(size){}
  void update(int x, int a){while(x < n){tree[x] += a; x |= (x + 1);}}
  int sum(int x){int a = 0; while(x >= 0){a += tree[x]; x = (x & (x+1)) - 1;} return a;}
  int get(int x){return sum(x) - (x==0 ? 0 : sum(x-1));}
};

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);
  
  int n; cin >> n;
  vector<int> a(n); REP(i,n) cin >> a[i];
  BIT bit(n+1000);

  int t=-1;
  REP(i,n){
    if(a[i] >= n || (i==0 && a[i] != 0) || (a[i] > 0 && bit.sum(a[i]-1) != a[i])){
      t = i+1;
      break;
    }

    if(bit.get(a[i]) == 0) bit.update(a[i], 1);
  }

  cout << t << endl;
  
  return 0;
}
