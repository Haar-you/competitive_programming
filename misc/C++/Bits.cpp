#include<bits/stdc++.h>
using namespace std;

// ビット操作のメモ

// a ⊆ b
bool is_included_in(int a, int b){
  return (a&(~b)) == 0;
}

// for each subset b ⊆ a
void for_each_subset_desc(int a, function<void(int)> f){
  for(int t=a; ; t=(t-1)&a){
    f(t);
    if(t==0) break;
  }
}

void for_each_subset_asc(int a, function<void(int)> f){
  for(int t=0; ; t=(t-a)&a){
    f(t);
    if(t==a) break;
  }
}

// for each superset b ⊇ a
void for_each_superset_desc(int a, int n, function<void(int)> f){
  int x = (1<<n)-1, y = x^(a&x);
  for(int t=y; ; t=(t-1)&y){
    f(t|a);
    if(t==0) break;
  }
}

void for_each_superset_asc(int a, int n, function<void(int)> f){
  for(int t=a; t<(1<<n); t=(t+1)|a){
    f(t);
  }
}

// for each subset x : a ⊆ x ⊆ b
void for_each_subset_between(int a, int b, function<void(int)> f){
  int x = b^(a&b);
  for(int t=x; ; t=(t-1)&x){
    f(t|a);
    if(t==0) break;
  }
}


int main(){

  return 0;
}

