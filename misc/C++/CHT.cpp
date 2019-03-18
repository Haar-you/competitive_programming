#include <bits/stdc++.h>
#define fst first
#define snd second
using namespace std;

// ConvexHullTrick
// 追加直線の傾き、クエリの値がともに単調性をもつバージョン
// MIN: true -> minクエリ, false -> maxクエリ
// クエリが単調減少のバージョンは未検証。

// verified at https://atcoder.jp/contests/dp/tasks/dp_z (Minクエリ)
// verified at https://codeforces.com/contest/939/problem/E (Maxクエリ)

template <typename T, bool MIN = true> class ConvexHullTrick{
  deque<pair<T,T>> lines;
  bool is_needless(const pair<T,T> &a, const pair<T,T> &b, const pair<T,T> &c){
    return (a.snd-b.snd)*(a.fst-c.fst) >= (a.snd-c.snd)*(a.fst-b.fst);
  }
  
  T apply(const pair<T,T> &f, const T &x){
    return f.fst*x + f.snd;
  }

  function<bool(T,T)> comp;

public:
  ConvexHullTrick(){
    if(MIN) comp = [](const T &a, const T &b){return a > b;};
    else comp = [](const T &a, const T &b){return a < b;};
  }
  
  void add(const T &a, const T &b){
    if(!lines.empty()){
      pair<T,T> l = lines.back();
      
      if(l.fst == a){
	if(!comp(l.snd,b)) return;
	lines.pop_back();
      }
    }
    while(lines.size()>=2 && is_needless(make_pair(a,b), lines.back(), *(lines.end()-2))){
      lines.pop_back();
    }
    lines.push_back(make_pair(a,b));
  }

  T query(const T &x){
    while(lines.size()>=2 && comp(apply(lines[0],x), apply(lines[1],x))){
      lines.pop_front();
    }
    return apply(lines[0],x);
  }
};


int main(){
  
  return 0;
}

