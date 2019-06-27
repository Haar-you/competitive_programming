//#include<bits/stdc++.h>

//#include <sys/types.h>
//#include <unistd.h>
#include <boost/format.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>

#include <boost/core/demangle.hpp>

using namespace std;


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
template <typename... T> void dump_out_aux(const tuple<T...> &val);

template <typename T> void dump_out_aux(const list<T> &val);
template <typename T> void dump_out_aux(const forward_list<T> &val);

template <typename T> void dump_out_aux(const multiset<T> &val);
template <typename T> void dump_out_aux(const unordered_multiset<T> &val);
template <typename T, typename U> void dump_out_aux(const multimap<T,U> &val);
template <typename T, typename U> void dump_out_aux(const unordered_multimap<T,U> &val);

template <typename T> void dump_out_aux(const complex<T> &val);

#if __cplusplus >= 201703L
template <typename T> void dump_out_aux(const optional<T> &val);
template <typename... T> void dump_out_aux(const variant<T...> &val);
void dump_out_aux(const any &val);
#endif

void dump_out_aux(bool val);
void dump_out_aux(int val);
void dump_out_aux(double val);
void dump_out_aux(const string &val);
void dump_out_aux(char val);

template <typename T, size_t N> void dump_out_aux(const T (&val)[N]);

template <typename T> void dump_out_aux(const T &val);

#define dump(...) dump_aux(__LINE__, __PRETTY_FUNCTION__, (#__VA_ARGS__), __VA_ARGS__)

template <class T> void dump_show_name_val(const string &name, const T &val){
  cerr << "    \e[32;1m" << boost::core::demangle(typeid(val).name()) << "\e[37m" << " " << name << " = ";
  dump_out_aux(val);
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
  cerr << "\e[47;30;2m" << "L" << line <<  ": in " << func << "\e[m" << endl;

  vector<string> valnames;
  boost::algorithm::split(valnames, name, boost::is_any_of(","));
  reverse(ALL(valnames));

  dump_aux_aux(valnames, vals...);
}





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

void show_size(size_t size){
  cerr << "\e[31m" << "[" << size << "]\e[37m";
}

template <typename T> void show_size(const T &val){
  show_size(val.size());
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
  int N = val.size();
  stack<T> temp(val);

  cerr << "{";
  REP(i,N){
    if(i) cerr << ",";
    auto x = temp.top(); temp.pop();
    dump_out_aux(x);
  }
  cerr << "}";
  show_size(val);
}

// queue
template <typename T> void dump_out_aux(const queue<T> &val){
  int N = val.size();
  queue<T> temp(val);

  cerr << "{";
  REP(i,N){
    if(i) cerr << ",";
    auto x = temp.front(); temp.pop();
    dump_out_aux(x);
  }
  cerr << "}";
  show_size(val);
}

// priority_queue
template <typename T> void dump_out_aux(const priority_queue<T> &val){
  int N = val.size();
  priority_queue<T> temp(val);

  cerr << "{";
  REP(i,N){
    if(i) cerr << ",";
    auto x = temp.top(); temp.pop();
    dump_out_aux(x);
  }
  cerr << "}";
  show_size(val);
}

template <typename T, typename Container, typename Compare> void dump_out_aux(const priority_queue<T,Container,Compare> &val){
  int N = val.size();
  priority_queue<T,Container,Compare> temp(val);

  cerr << "{";
  REP(i,N){
    if(i) cerr << ",";
    auto x = temp.top(); temp.pop();
    dump_out_aux(x);
  }
  cerr << "}";
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
  cerr << "(";
  dump_out_aux(val.fst);
  cerr<< ",";
  dump_out_aux(val.snd);
  cerr << ")";
}

// tuple

template <typename T, size_t N>
struct TuplePrintHelper{
  static void print(const T &val){
    TuplePrintHelper<T,N-1>::print(val);
    cerr << ",";
    dump_out_aux(get<N-1>(val));
  }
};

template <typename T>
struct TuplePrintHelper<T,1>{
  static void print(const T &val){
    dump_out_aux(get<0>(val));
  }
};



template <typename... T> void dump_out_aux(const tuple<T...> &val){
  cerr << "(";
  TuplePrintHelper<tuple<T...>, sizeof...(T)>::print(val);
  cerr << ")";
}


// list
template <typename T> void dump_out_aux(const list<T> &val){
  out_container(ALL(val));
  show_size(val);
}

// forward_list
template <typename T> void dump_out_aux(const forward_list<T> &val){
  out_container(ALL(val));
  show_size(((size_t)distance(ALL(val))));
}


// multiset
template <typename T> void dump_out_aux(const multiset<T> &val){
  out_container(ALL(val));
  show_size(val);
}

// unordered_multiset
template <typename T> void dump_out_aux(const unordered_multiset<T> &val){
  out_container(ALL(val));
  show_size(val);
}


// multimap
template <typename T, typename U> void dump_out_aux(const multimap<T,U> &val){
  out_container(ALL(val));
  show_size(val);
}


// unordered_multimap
template <typename T, typename U> void dump_out_aux(const unordered_multimap<T,U> &val){
  out_container(ALL(val));
  show_size(val);
}

// complex number
template <typename T> void dump_out_aux(const complex<T> &val){
  cerr << val.real() << (val.imag() < 0 ? "" : "+") << val.imag() << "i";
}

#if __cplusplus >= 201703L
// optional
template <typename T> void dump_out_aux(const optional<T> &val){
  if(val.has_value()){
    dump_out_aux(val.value());
  }else{
    cerr << "none";
  }
}

// variant
template <typename T, size_t N>
struct VariantPrintHelper{
  static void print(const T &val){
    auto p = get_if<N-1>(&val);
    if(p){
      cerr << "\e[32m<" << boost::core::demangle(typeid(variant_alternative_t<N-1,T>).name()) << ">\e[37m";
      dump_out_aux(*p);
    }else{
      VariantPrintHelper<T,N-1>::print(val);
    }
  }
};

template <typename T>
struct VariantPrintHelper<T,1>{
  static void print(const T &val){
    auto p = get_if<0>(&val);
    if(p){
      cerr << "\e[32m<" << boost::core::demangle(typeid(variant_alternative_t<0,T>).name()) << ">\e[37m";
      dump_out_aux(*p);
    }
  }
};

template <typename... T> void dump_out_aux(const variant<T...> &val){
  VariantPrintHelper<variant<T...>, sizeof...(T)>::print(val);
}

// any
void dump_out_aux(const any &val){
  if(val.has_value()){
    cerr << "has_value";
  }else{
    cerr << "none";
  }
}

#endif


// others
void dump_out_aux(bool val){
  if(val){
    cerr << "True";
  }else{
    cerr << "False";
  }
}

void dump_out_aux(int val){
  cerr << val;
}

void dump_out_aux(double val){
  cerr << val;
}

void dump_out_aux(const string &val){
  cerr << "\"" << val << "\"";
  show_size(val);
}

void dump_out_aux(char val){
  cerr << "'" << val << "'";
}



// array
template <typename T, size_t N> void dump_out_aux(const T (&val)[N]){
  cerr << "{";
  REP(i,(int)N){
    if(i) cerr << ",";
    cerr << val[i];
  }
  cerr << "}";
  show_size((size_t)N);
}


template <typename T> void dump_out_aux(const T &val){
  cerr << val;
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
