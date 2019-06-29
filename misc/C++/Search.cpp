/*


 */


// 下に凸の三分探索
double ternary_search_downwards(double lb, double ub, const function<double(double)> &f){
  double t1,t2;
  REP(i,200){
    t1 = lb+(ub-lb)/3;
    t2 = lb+(ub-lb)/3*2;
    
    if(f(t1) < f(t2)){
      ub = t2;
    }else{
      lb = t1;
    }
  }
 
  return lb;
}
 
// 上に凸の三分探索
double ternary_search_upwards(double lb, double ub, const function<double(double)> &f){
  double t1,t2;
  REP(i,200){
    t1 = lb+(ub-lb)/3;
    t2 = lb+(ub-lb)/3*2;
    
    if(f(t1) > f(t2)){
      ub = t2;
    }else{
      lb = t1;
    }
  }
 
  return lb;
}
