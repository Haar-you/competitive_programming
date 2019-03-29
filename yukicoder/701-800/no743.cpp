#include<bits/stdc++.h>
using namespace std;

class BIT{
private:
  vector<int> tree;
  int n;
public:
  BIT(int size){tree.resize(size+1); for(auto v : tree){v = 0;}; n = size;}
  void update(int x, int a){while(x <= n){tree[x] += a; x += (x & (-x));}}
  int get(int x){int a = 0; while(x > 0){a += tree[x]; x -= (x & (-x));} return a;}
};

int main(){
  int n, m;
  cin >> n >> m;
  vector<pair<int,int>> v(n);
  for(int i=0; i<n; ++i){
    int a,b;
    cin >> a >> b;
    v[i] = (a<b) ? make_pair(a,b) : make_pair(b,a);
  }

  sort(v.begin(), v.end(), [](const pair<int, int> &a, const pair<int, int> &b){return a.first < b.first;});
  
  BIT bit(m);
  int count = 0;

  for(int i=0; i<n; ++i){
    count += bit.get(v[i].second) - bit.get(v[i].first);
    bit.update(v[i].second,1);
  }

  cout << count << endl;
  
  return 0;
}
