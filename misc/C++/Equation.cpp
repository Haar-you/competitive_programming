/*

 */


// 二次方程式の実数解
pair<double,double> quadratic_equation(double a, double b, double c){
  double x1 = (-b + sqrt(b*b-4*a*c))/(2*a);
  double x2 = (-b - sqrt(b*b-4*a*c))/(2*a);
  return make_pair(x1,x2);
}

