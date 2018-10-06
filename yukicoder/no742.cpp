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
  int n;
  cin >> n;
  vector<int> ms(n);
  for(int i=0; i<n; ++i) cin >> ms[i];

  BIT bit(30000);
  int count = 0;
  for(int i=n-1; i>=0; --i){
    count += bit.get(ms[i]);
    bit.update(ms[i],1);
  }

  cout << count << endl;
  
  return 0;
}
