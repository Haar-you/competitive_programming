//#include<bits/stdc++.h>
using namespace std;

#include <boost/core/demangle.hpp>

#define dump(x) \
  cerr << "L" << __LINE__;						\
  cerr << ": in " << __PRETTY_FUNCTION__;				\
  cerr << " \e[32;1m" << boost::core::demangle(typeid(x).name()) << "\e[37m" << " " << (#x) << " = " << (x) << "\e[m" << endl;

template <typename Iter> ostream& out_container(ostream &os, Iter first, Iter last){
  os << "{";
  auto itr = first;
  while(itr != last){
    if(itr != first) os << ",";
    os << *itr;
    ++itr;
  }
  os << "}";
  return os;
}

// vector / array
template <typename T> ostream& operator<<(ostream &os, const vector<T> &c){return out_container(os,ALL(c));}
template <typename T, size_t N> ostream& operator<<(ostream &os, const array<T,N> &c){return out_container(os,ALL(c));}

// deque
template <typename T> ostream& operator<<(ostream &os, const deque<T> &c){return out_container(os,ALL(c));}

// stack
template <typename T>
ostream& operator<<(ostream &os, const stack<T> &s){
  if(s.empty()) os << "{}";
  else os << "{" << s.top() << ",...}";
  return os;
}

// queue
template <typename T>
ostream& operator<<(ostream &os, const queue<T> &q){
  if(q.empty()) os << "{}";
  else os << "{" << q.front() << ",...," << q.back() << "}";
  return os;
}

// priority_queue
template <typename T>
ostream& operator<<(ostream &os, const priority_queue<T> &pq){
  if(pq.empty()) os << "{}";
  else os << "{" << pq.top() << ",...}";
  return os;
}


// set
template <typename T> ostream& operator<<(ostream &os, const set<T> &c){return out_container(os,ALL(c));}
template <typename T> ostream& operator<<(ostream &os, const unordered_set<T> &c){return out_container(os,ALL(c));}

// map
template <typename T, typename U> ostream& operator<<(ostream &os, const map<T,U> &c){return out_container(os,ALL(c));}
template <typename T, typename U> ostream& operator<<(ostream &os, const unordered_map<T,U> &c){return out_container(os,ALL(c));}


// pair / tuple
template <typename T, typename U> ostream& operator<<(ostream& os, const pair<T,U> &p){os << "(" << p.first << "," << p.second << ")"; return os;}

template <typename T1, typename T2, typename T3>
ostream& operator<<(ostream &os, const tuple<T1,T2,T3> &t){
  os << "(" << get<0>(t) << "," << get<1>(t) << "," << get<2>(t) << ")";
  return os;
}

template <typename T1, typename T2, typename T3, typename T4>
ostream& operator<<(ostream &os, const tuple<T1,T2,T3,T4> &t){
  os << "(" << get<0>(t) << "," << get<1>(t) << "," << get<2>(t) << "," << get<3>(t) << ")";
  return os;
}

template <typename T1, typename T2, typename T3, typename T4, typename T5>
ostream& operator<<(ostream &os, const tuple<T1,T2,T3,T4,T5> &t){
  os << "(" << get<0>(t) << "," << get<1>(t) << "," << get<2>(t) << "," << get<3>(t) << "," << get<4>(t) << ")";
  return os;
}
