//#include<bits/stdc++.h>

#include <sys/types.h>
#include <unistd.h>
#include <boost/format.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>

#include <boost/core/demangle.hpp>

using namespace std;


template <typename T> void dump_out(const T &val);


#define dump(...) dump_aux(__LINE__, __PRETTY_FUNCTION__, (#__VA_ARGS__), __VA_ARGS__)

template <class T> void dump_show_name_val(const string &name, const T val){
  cerr << "    \e[32;1m" << boost::core::demangle(typeid(val).name()) << "\e[37m" << " " << name << " = ";
  dump_out(val);
  cerr << "\e[m" << endl;
}

template <class T> void dump_aux_aux(vector<string> &names, const T &val){
  dump_show_name_val(names.back(), val);
}

template <class T, class... U> void dump_aux_aux(vector<string> &names, const T &val, U const &... vals){
  dump_show_name_val(names.back(), val);
  names.pop_back();

  dump_aux_aux(names, vals...);
}

template <class... T> void dump_aux(const int line, const char *func, const char *name, T const &... vals){
  cerr << "\e[47;30m" << "L" << line <<  ": in " << func << "\e[m" << endl;

  vector<string> valnames;
  boost::algorithm::split(valnames, name, boost::is_any_of(","));
  reverse(ALL(valnames));

  dump_aux_aux(valnames, vals...);
}

template <typename T> void dump_out_aux(const vector<T> &val);
template <typename T, size_t N> void dump_out_aux(const array<T,N> &val);
template <typename T> void dump_out_aux(const deque<T> &val);
template <typename T> void dump_out_aux(const stack<T> &val);
template <typename T> void dump_out_aux(const queue<T> &val);
template <typename T> void dump_out_aux(const priority_queue<T> &val);
template <typename T, typename Container, typename Compare> void dump_out_aux(const priority_queue<T,Container,Compare> &val);
template <typename t> void dump_out_aux(const set<t> &val);
template <typename T> void dump_out_aux(const unordered_set<T> &val);
template <typename T, typename U> void dump_out_aux(const map<T,U> &val);
template <typename T, typename U> void dump_out_aux(const unordered_map<T,U> &val);

template <typename T, typename U> void dump_out_aux(const pair<T,U> &val);
template <typename T1, typename T2, typename T3> void dump_out_aux(const tuple<T1,T2,T3> &val);
template <typename T1, typename T2, typename T3, typename T4> void dump_out_aux(const tuple<T1,T2,T3,T3> &val);
template <typename T1, typename T2, typename T3, typename T4, typename T5> void dump_out_aux(const tuple<T1,T2,T3,T4,T5> &val);

void dump_out_aux(int val);
void dump_out_aux(double val);
void dump_out_aux(const string &val);




template <typename Iter> void out_container(Iter first, Iter last){
  cerr << "{";
  auto itr = first;
  while(itr != last){
    if(itr != first) cerr << ",";
    dump_out_aux(*itr);
    ++itr;
  }
  cerr << "}";
}

template <typename T> void show_size(const T &val){
  cerr << ": " << "size=" << val.size();
}

// vector
template <typename T> void dump_out_aux(const vector<T> &val){
  out_container(ALL(val));
  show_size(val);
}

// array
template <typename T, size_t N> void dump_out_aux(const array<T,N> &val){
  out_container(ALL(val));
  show_size(val);
}

// deque
template <typename T> void dump_out_aux(const deque<T> &val){
  out_container(ALL(val));
  show_size(val);
}

// stack
template <typename T> void dump_out_aux(const stack<T> &val){
  if(val.empty()) cerr << "{}";
  else if(val.size() == 1) cerr << "{" << val.top() << "}";
  else cerr << "{" << val.top() << ", ...}";
  show_size(val);
}

// queue
template <typename T> void dump_out_aux(const queue<T> &val){
  if(val.empty()) cerr << "{}";
  else if(val.size() == 1) cerr << "{" << val.front() << "}";
  else if(val.size() == 2) cerr << "{" << val.front() << "," << val.back() << "}"; 
  else cerr << "{" << val.front() << ", ..., " << val.back() << "}";
  show_size(val);
}

// priority_queue
template <typename T> void dump_out_aux(const priority_queue<T> &val){
  if(val.empty()) cerr << "{}";
  else if(val.size() == 1) cerr << "{" << val.top() << "}";
  else cerr << "{" << val.top() << ", ..." << "}";
  show_size(val);
}

template <typename T, typename Container, typename Compare> void dump_out_aux(const priority_queue<T,Container,Compare> &val){
  if(val.empty()) cerr << "{}";
  else if(val.size() == 1) cerr << "{" << val.top() << "}";
  else cerr << "{" << val.top() << ", ..." << "}";
  show_size(val);
}




// set
template <typename T> void dump_out_aux(const set<T> &val){
  out_container(ALL(val));
  show_size(val);
}

// unrodered_set
template <typename T> void dump_out_aux(const unordered_set<T> &val){
  out_container(ALL(val));
  show_size(val);
}

// map
template <typename T, typename U> void dump_out_aux(const map<T,U> &val){
  out_container(ALL(val));
  show_size(val); 
}

// unordered_map
template <typename T, typename U> void dump_out_aux(const unordered_map<T,U> &val){
  out_container(ALL(val));
  show_size(val);
}


// pair
template <typename T, typename U> void dump_out_aux(const pair<T,U> &val){
  cerr << "(" << val.fst << "," << val.snd << ")";
}

// tuple (3~5)
template <typename T1, typename T2, typename T3> void dump_out_aux(const tuple<T1,T2,T3> &val){
  cerr << "(" << get<0>(val) << "," << get<1>(val) << "," << get<2>(val) << ")";
}

template <typename T1, typename T2, typename T3, typename T4> void dump_out_aux(const tuple<T1,T2,T3,T3> &val){
  cerr << "(" << get<0>(val) << "," << get<1>(val) << "," << get<2>(val) << "," << get<3>(val) << ")";
}

template <typename T1, typename T2, typename T3, typename T4, typename T5> void dump_out_aux(const tuple<T1,T2,T3,T4,T5> &val){
  cerr << "(" << get<0>(val) << "," << get<1>(val) << "," << get<2>(val) << "," << get<3>(val) << "," << get<4>(val) << ")";
}

// others
void dump_out_aux(int val){
  cerr << val;
}

void dump_out_aux(double val){
  cerr << val;
}

void dump_out_aux(const string &val){
  cerr << val;
}


template <typename T> void dump_out_aux(const T &val){
  cerr << val;
}


template <typename T> void dump_out(const T &val){
  dump_out_aux(val);
}


/*


 */

struct PreMain{
  chrono::system_clock::time_point start, end;
  
  PreMain(){
    start = chrono::system_clock::now();
  }
  ~PreMain(){
    end = chrono::system_clock::now();
    
    int64_t exec_time = static_cast<int64_t>(chrono::duration_cast<chrono::milliseconds>(end - start).count());
    cerr << "\e[33;01m" << exec_time << "ms" << "\e[m" << endl;
  }
}PreMain;
