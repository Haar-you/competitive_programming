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

template <typename T> using V = vector<T>;
template <typename T, typename U> using P = pair<T,U>;

template <typename T> T gcd(T a, T b){a = abs(a); b = abs(b); if(a<b) swap(a,b); while(b>0){a %= b; swap(a,b);} return a;}
template <typename T> T lcm(T a, T b){return (1LL * a * b) / gcd(a,b);}

int inv(int a){return a ? 0 : 1;}

int lim[8] = {0,0,1,2,4,6,9,12};
int pt[12] =
  {
   0b00000111,

   0b00001110,

   0b00011100,
   0b00010101,
   
   0b00111000,
   0b00101010,

   0b01110000,
   0b01010100,
   0b01001001,

   0b11100000,
   0b10101000,
   0b10010010
  };

vector<int> mask(1<<12, 0);
vector<tuple<int,int,int>> ops;
map<int, vector<int>> ops2;
int n;

bool solve(vector<int> &a, int k){
  if(k <= 8){
    int t = 0;
    for(int i=0; i<k; ++i)
      if(a[i])
	t += (1<<i);

    bool ans = false;
    int res;

    REP(i,1<<lim[min(7,n-1)]){
      if((t ^ mask[i]) == 0){
	ans = true;

	for(int j=0; j<lim[min(7,n-1)]; ++j){
	  if(i & (1<<j)){
	    vector<int> temp;
	    for(int b=0; b<8; ++b)
	      if(pt[j] & (1<<b)) temp.push_back(b);

	    ops.push_back(make_tuple(temp[0], temp[1], temp[2]));
	  }
	}
	
	break;
      }
    }

    return ans;
  }else if(k <= 10){
    if(a[k-1] == 1 && a[k-2] == 0){
      a[k-1] = 0; a[k-3] = inv(a[k-3]); a[k-5] = inv(a[k-5]);
      ops.push_back(make_tuple(k-5,k-3,k-1));
    }else if(a[k-1] == 0 && a[k-2] == 1){
      a[k-2] = 0; a[k-3] = inv(a[k-3]); a[k-4] = inv(a[k-4]);
      ops.push_back(make_tuple(k-4,k-3,k-2));
    }else if(a[k-1] == 1 && a[k-2] == 1){
      a[k-1] = 0; a[k-2] = 0; a[k-3] = inv(a[k-3]);
      ops.push_back(make_tuple(k-3,k-2,k-1));
    }
    return solve(a,k-2);
  }else{
    int t = 0;
    for(int i=0; i<6; ++i) if(a[k-1-i]) t += (1<<i);
    vector<int> p = ops2[t];

    REP(i,p.size()/3){
      REP(j,3) a[k-p[i*3+j]] = inv(a[k-p[i*3+j]]);
      ops.push_back(make_tuple(k-p[i*3],k-p[i*3+1],k-p[i*3+2]));
    }

    return solve(a,k-6);
  }
}

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  cin >> n;
  vector<int> a(n);
  REP(i,n) cin >> a[i];

  for(int i=0; i<(1<<12); ++i){

    for(int j=0; j<12; ++j)
      if(i & (1<<j))
	mask[i] ^= pt[j];
  }

  ops2[0b000000] = {};
  
  ops2[0b000001] = {1,6,11,6,7,8};
  ops2[0b000010] = {2,6,10,6,7,8};
  ops2[0b000100] = {3,7,11};
  ops2[0b001000] = {4,7,10};
  ops2[0b010000] = {5,7,9};
  ops2[0b100000] = {6,7,8};
  
  ops2[0b000011] = {1,2,3,3,7,11};
  ops2[0b000101] = {1,3,5,5,7,9};
  ops2[0b001001] = {1,4,7};
  ops2[0b010001] = {1,5,9};
  ops2[0b100001] = {1,6,11};
  ops2[0b000110] = {2,3,4,4,7,10};
  ops2[0b001010] = {2,4,6,6,7,8};
  ops2[0b010010] = {2,5,8};
  ops2[0b100010] = {2,6,10};
  ops2[0b001100] = {3,4,5,5,7,9};
  ops2[0b010100] = {3,5,7};
  ops2[0b100100] = {3,6,9};
  ops2[0b011000] = {4,5,6,6,7,8};
  ops2[0b101000] = {4,6,8};
  ops2[0b110000] = {5,6,7};

  ops2[0b000111] = {1,2,3};
  ops2[0b001011] = {2,4,6,1,6,11};
  ops2[0b010011] = {1,2,3,3,5,7};
  ops2[0b100011] = {1,2,3,3,6,9};
  ops2[0b001101] = {1,4,7,3,7,11};
  ops2[0b010101] = {1,3,5};
  ops2[0b100101] = {1,3,5,5,6,7};
  ops2[0b011001] = {1,4,7,5,7,9};
  ops2[0b101001] = {1,4,7,6,7,8};
  ops2[0b110001] = {1,5,9,6,7,8};
  ops2[0b001110] = {2,3,4};
  ops2[0b010110] = {2,5,8,3,7,11};
  ops2[0b100110] = {2,6,10,3,7,11};
  ops2[0b011010] = {2,5,8,4,7,10};
  ops2[0b101010] = {2,4,6};
  ops2[0b110010] = {2,5,8,6,7,8};
  ops2[0b011100] = {3,4,5};
  ops2[0b101100] = {3,4,5,5,6,7};
  ops2[0b110100] = {3,5,7,6,7,8};
  ops2[0b111000] = {4,5,6};

  ops2[0b001111] = {1,2,3,4,7,10};
  ops2[0b010111] = {1,2,3,5,7,9};
  ops2[0b100111] = {1,2,3,6,7,8};
  ops2[0b011011] = {1,4,7,2,5,8};
  ops2[0b101011] = {1,4,7,2,6,10};
  ops2[0b110011] = {1,5,9,2,6,10};
  ops2[0b011101] = {1,3,5,4,7,10};
  ops2[0b101101] = {1,4,7,3,6,9};
  ops2[0b110101] = {1,3,5,6,7,8};
  ops2[0b111001] = {1,4,7,5,6,7};
  ops2[0b011110] = {2,3,4,5,7,9};
  ops2[0b101110] = {2,3,4,6,7,8};
  ops2[0b110110] = {2,5,8,3,6,9};
  ops2[0b111010] = {2,4,6,5,7,9};
  ops2[0b111100] = {3,4,5,6,7,8};

  ops2[0b011111] = {1,5,9,2,3,4};
  ops2[0b101111] = {1,2,3,4,6,8};
  ops2[0b110111] = {1,2,3,5,6,7};
  ops2[0b111011] = {2,4,6,1,5,9};
  ops2[0b111101] = {1,3,5,4,6,8};
  ops2[0b111110] = {2,3,4,5,6,7};

  ops2[0b111111] = {1,2,3,4,5,6};

  bool ans = solve(a,n);
  cout << (ans ? "YES" : "NO") << endl;

  if(ans){
    cout << ops.size() << endl;
    for(auto v : ops){
      cout << get<0>(v)+1 << " " << get<1>(v)+1 << " " << get<2>(v)+1 << endl;
    }
  }
  
  return 0;
}

