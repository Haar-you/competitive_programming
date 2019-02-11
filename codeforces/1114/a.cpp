#include <bits/stdc++.h>

using namespace std;

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  int x,y,z,a,b,c;
  while(cin >> x >> y >> z >> a >> b >> c){
    if(a >= x){
      a -= x;
      b += a;
      if(b >= y){
	b -= y;
	c += b;
	if(c >= z){
	  cout << "YES" << endl;
	  continue;
	}
      }
    }
    cout << "NO" << endl;
  }
  
  return 0;
}
