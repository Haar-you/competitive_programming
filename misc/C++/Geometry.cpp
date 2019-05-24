#include<bits/stdc++.h>
using namespace std;

/*
  pt (point, vector) class
 */

class pt{
public:
  double x, y;
  pt(): x(0), y(0){}
  pt(double x, double y): x(x), y(y){}
  double size() const {return sqrt(x*x+y*y);}
  double size_sq() const {return x*x+y*y;}
  static pt polar(double r, double ang){
    return pt(r*cos(ang), r*sin(ang));
  }
};

pt operator+(const pt &a, const pt &b){return pt(a.x+b.x, a.y+b.y);}
pt operator-(const pt &a, const pt &b){return pt(a.x-b.x, a.y-b.y);}
pt operator-(const pt &a){return pt(-a.x, -a.y);}
pt operator*(const pt &a, const double k){return pt(a.x*k, a.y*k);}
pt operator*(const double k, const pt &a){return pt(a.x*k, a.y*k);}
pt operator/(const pt &a, const double k){return pt(a.x/k, a.y/k);}

bool operator==(const pt &a, const pt &b){return a.x==b.x and a.y==b.y;}
bool operator!=(const pt &a, const pt &b){return !(a==b);}

bool operator<(const pt &a, const pt &b){return a.x<b.x or (a.x==b.x and a.y<b.y);}

istream& operator>>(istream &is, pt &a){is >> a.x >> a.y; return is;}
ostream& operator<<(ostream &os, const pt &a){os << "(" << a.x << "," << a.y << ")"; return os;}

double dot(const pt &a, const pt &b){return a.x*b.x+a.y*b.y;}
double cross(const pt &a, const pt &b){return a.x*b.y-a.y*b.x;}

pt unit(const pt &a){return a / a.size();} // 単位ベクトル
pt normal(const pt &p){return pt(-p.y,p.x);} // 法線ベクトル

double angle(const pt &a, const pt &b){
  return atan2(b.y-a.y, b.x-a.x);
}

double distance_pts(const pt &a, const pt &b){
  return sqrt((a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y));
}

/*
  line class
 */

class line{
public:
  pt from, to;
  line(): from(), to(){}
  line(const pt &from, const pt &to): from(from), to(to){}
  pt diff() const {return to-from;}
  double size() const {return diff().size();}
};

/*
  ccw
 */

enum CCW{
	 ONLINE_BACK = -2,
	 COUNTER_CLOCKWISE = -1,
	 ON_SEGMENT = 0,
	 CLOCKWISE = 1,
	 ONLINE_FRONT = 2
};

CCW ccw(const pt &p0, const pt &p1, const pt &p2){
  double cr = cross(p1-p0, p2-p0);
  double d = dot(p1-p0, p2-p0);

  if(fabs(cr) < eps){
    if(d < 0) return ONLINE_BACK;
    else if((p2-p0).size() > (p1-p0).size()) return ONLINE_FRONT;
    else return ON_SEGMENT;
  }else if(cr >= eps){
    return COUNTER_CLOCKWISE;
  }else{
    return CLOCKWISE;
  }
}


/*
  http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_1_A
*/
pt projection(const line &l, const pt &p){
  return l.from + dot(unit(l.to-l.from), p-l.from) * unit(l.to-l.from);
}

/*
  http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_1_B
 */
pt reflection(const line &l, const pt &p){
  return p + (projection(l,p)-p)*2;
}

/*
  http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_2_A
 */
bool parallel(const line &a, const line &b){
  return fabs(cross(a.diff(), b.diff())) < eps;
}

bool orthogonal(const line &a, const line &b){
  return fabs(dot(a.diff(), b.diff())) < eps;
}



/*
  http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_2_B
 */
bool intersect_segments(const line &a, const line &b){
  return
    ccw(a.from,a.to,b.from) * ccw(a.from,a.to,b.to) <= 0 and
    ccw(b.from,b.to,a.from) * ccw(b.from,b.to,a.to) <= 0;
}



/*
  http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_2_C
 */
bool crosspoint_segments(const line &a, const line &b, pt &ret){
  double cr = cross(a.diff(), b.diff());
  double t1 = cross(b.from-a.from, b.diff()) / cr;
  double t2 = cross(b.from-a.from, a.diff()) / cr;

  if(fabs(cr) < eps) return false; // parallel;
  if(t1 < 0 or t1 > 1 or t2 < 0 or t2 > 1) return false; // no crosspoint

  ret = a.from + a.diff() * t1;
  return true;
}

/*
  http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_2_D
 */
double distance_segment_point(const line &l, const pt &p){
  if(dot(l.diff(), p-l.from) < eps) return (p-l.from).size();
  if(dot(-l.diff(), p-l.to) < eps) return (p-l.to).size();
  return fabs(cross(l.diff(), p-l.from)) / l.size();
}

double distance_segments(const line &l1, const line &l2){
  if(intersect_segments(l1,l2)) return 0;
  return min({
	      distance_segment_point(l1, l2.from),
	      distance_segment_point(l1, l2.to),
	      distance_segment_point(l2, l1.from),
	      distance_segment_point(l2, l1.to)
    });
}


/*
  http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_3_A
 */
double area(const vector<pt> &ps){
  double ret = 0;
  int n = (int)ps.size();
  REP(i,n){
    ret += (ps[i].x-ps[(i+1)%n].x) * (ps[i].y+ps[(i+1)%n].y);
  }
  ret = fabs(ret) / 2;
  return ret;
}

double area(double a, double b, double c){
  double s = (a+b+c)/2;
  return sqrt(s*(s-a)*(s-b)*(s-c));
}


/*
  http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_4_B
*/
double convex_diameter(const vector<pt> &ps){
  int n = (int)ps.size();
  int i = min_element(ALL(ps), [](const pt &a, const pt &b){return a.y < b.y;}) - ps.begin();
  int j = max_element(ALL(ps), [](const pt &a, const pt &b){return a.y < b.y;}) - ps.begin();

  double ret = (ps[i]-ps[j]).size();

  REP(k,2*n){
    if(cross(ps[(i+1)%n]-ps[i], ps[(j+1)%n]-ps[j]) >= eps){
      (++j) %= n;
    }else{
      (++i) %= n;
    }
    chmax(ret, (ps[i]-ps[j]).size());
  }

  return ret;
}

/*
  http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_3_B
 */
bool is_convex(const vector<pt> &ps){
  int n = ps.size();
  vector<CCW> temp;

  REP(i,n){
    CCW c = ccw(ps[i], ps[(i+1)%n], ps[(i+2)%n]);
    
    if(c == CLOCKWISE or c == COUNTER_CLOCKWISE){
      if(temp.empty()) temp.push_back(c);
      else if(temp.back() != c) return false;
    }
  }
  return true;
}

/*
  http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_3_C
*/
// 周囲上はoutside判定される
bool is_point_in_polygon(const vector<pt> &polygon, const pt &p){
  int n = polygon.size();

  double d = 0.0;
  REP(i,n){
    double a = angle(polygon[i],p);
    double b = angle(polygon[(i+1)%n],p);
    if(a < eps) a += 2*M_PI;
    if(b < eps) b += 2*M_PI;
    double ang = b-a;
    if(fabs(ang) > M_PI){
      if(ang < eps) ang += 2*M_PI;
      else ang -= 2*M_PI;
    }
    
    d += ang;
  }

  dump(d);

  if(fabs(fabs(d)-2*M_PI) < eps) return true;
  return false;
}

/*
  http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_4_C
 */
enum crosspoint_status{
		LEFTSIDE,
		RIGHTSIDE,
		OVERLAPPED,
		CROSSED
};

crosspoint_status crosspoint_line_segment(const line &l, const line &s, pt &ret){
  double a = cross(l.diff(), s.from-l.from);
  double b = cross(l.diff(), s.to-l.from);

  if(fabs(a) < eps and fabs(b) < eps) return OVERLAPPED;
  if(a < 0 and b < 0) return RIGHTSIDE;
  if(a > 0 and b > 0) return LEFTSIDE;
  ret = s.from + s.diff() * cross(l.diff(),l.from-s.from) / cross(l.diff(),s.diff());
  return CROSSED;
}

void convex_cut(const vector<pt> &ps, const line &l, vector<pt> &left, vector<pt> &right){
  int n = ps.size();

  REP(i,n){
    pt cp;
    switch(crosspoint_line_segment(l, line(ps[i], ps[(i+1)%n]), cp)){
    case LEFTSIDE:{
      left.push_back(ps[i]);
      break;
    }
    case RIGHTSIDE:{
      right.push_back(ps[i]);
      break;
    }
    case OVERLAPPED:{
      right.push_back(ps[i]);
      left.push_back(ps[i]);
      break;
    }
    case CROSSED:{
      if(ccw(l.from,l.to,ps[i]) == CLOCKWISE){
	right.push_back(ps[i]);
      }else{
	left.push_back(ps[i]);
      }

      left.push_back(cp);
      right.push_back(cp);
      break;
    }
    }
  }
}

/*
  convex hull
  [問題例]
  https://onlinejudge.u-aizu.ac.jp/challenges/sources/PCK/Prelim/0342?year=2016 (凸包/最小全域木)
  https://atcoder.jp/contests/agc021/tasks/agc021_b (凸包)
  https://codeforces.com/contest/1143/problem/F (式変形/上側凸包)
 */

vector<pt> upper_hull(vector<pt> pts, bool upper=true){
  sort(ALL(pts), [](const pt &a, const pt &b){return (a.x < b.x) or (a.x == b.x and a.y < b.y);});
  if(upper) reverse(ALL(pts));
  
  vector<pt> ret;

  ret.push_back(pts.back());
  pts.pop_back();
  
  while(not pts.empty()){
    auto s = pts.back();
    pts.pop_back();

    if(ret.size() == 1){
      ret.push_back(s);
    }else{
      auto p = *(ret.end()-2);
      auto q = ret.back();

      if(cross(q-p, s-p) <= 0){
	ret.push_back(s);
      }else{
	ret.pop_back();
	pts.push_back(s);
      }
    }
  }

  return ret;
}

vector<pt> convex_hull(const vector<pt> &pts){
  vector<pt> ret = upper_hull(pts);
  auto lower = upper_hull(pts, false);

  ret.pop_back();
  lower.pop_back();

  for(auto &p : lower) ret.push_back(p);

  return ret;
}


/*
  circle class
 */
class circle{
public:
  pt center;
  double radius;
  circle(): center(), radius(0){}
  circle(const pt &center, double radius): center(center), radius(radius){}
};

/*
  https://onlinejudge.u-aizu.ac.jp/courses/library/4/CGL/all/CGL_7_A
*/
enum circle_intersection_status{
				SAME = -1,
				INSIDE = 0,
				INSCRIBED = 1,
				INTERSECT = 2,
				CIRCUMSCRIBED = 3,
				OUTSIDE = 4
};

circle_intersection_status intersect_circles(const circle &a, const circle &b){
  double d = (a.center-b.center).size();
  if(fabs(a.radius+b.radius-d) < eps) return CIRCUMSCRIBED;
  else if(a.radius+b.radius < d) return OUTSIDE;
  else if(a.radius+b.radius > d and d-fabs(a.radius-b.radius) > eps) return INTERSECT;
  else if(fabs(d-fabs(a.radius-b.radius)) < eps) return INSCRIBED;
  else if(fabs(a.radius-b.radius) > d) return INSIDE;
  return SAME;
}

/*
  https://onlinejudge.u-aizu.ac.jp/courses/library/4/CGL/all/CGL_7_D
 */
double distance_line_point(const line &l, const pt &p){
  return fabs(cross(l.diff(),p-l.from)/l.size());
}

vector<pt> crosspoint_circle_line(const circle &c, const line &l){
  double d = distance_line_point(l,c.center);
  if(d-c.radius >= eps) return {};

  pt n = normal(l.diff());
  pt b = l.from + l.diff() * cross(n,c.center+n-l.from) / cross(n,l.diff());

  if(fabs(d-c.radius) < eps) return {b};

  double a = sqrt(c.radius*c.radius-d*d);
  return {
	  b + unit(l.diff()) * a,
	  b - unit(l.diff()) * a
  };
}

/*
  https://onlinejudge.u-aizu.ac.jp/courses/library/4/CGL/all/CGL_7_E
 */
vector<pt> crosspoint_circles(const circle &a, const circle &b){
  double d = (a.center-b.center).size();
  double x = acos((a.radius*a.radius+d*d-b.radius*b.radius)/(2*d*a.radius));
  double t = atan2(b.center.y-a.center.y,b.center.x-a.center.x);
  
  if(fabs(a.radius+b.radius-d) < eps) return {a.center + pt::polar(a.radius,t)}; // if circumscribed
  else if(fabs(fabs(a.radius-b.radius)-d) < eps) return {a.center + pt::polar(a.radius,t)}; // if inscribed
  else if(a.radius+b.radius > d and d-fabs(a.radius-b.radius) > eps){// if intersect
    return {
	    a.center + pt::polar(a.radius,t+x),
	    a.center + pt::polar(a.radius,t-x)
    };
  }
  
  return {};
}

/*
  https://onlinejudge.u-aizu.ac.jp/courses/library/4/CGL/all/CGL_7_F
 */
vector<pt> tangent_circle(const circle &c, const pt &p){
  double d = (p-c.center).size();

  if(d < c.radius-eps) return {};
  else if(fabs(d-c.radius) < eps) return {p};

  double a = acos(c.radius/d);
  double t = atan2(p.y-c.center.y, p.x-c.center.x);
  return {c.center + pt::polar(c.radius,t+a), c.center + pt::polar(c.radius,t-a)};
}

/*
  https://onlinejudge.u-aizu.ac.jp/courses/library/4/CGL/all/CGL_7_G
 */
vector<pt> common_tangent_circle(const circle &a, const circle &b){
  double d = (b.center-a.center).size();
  pt n = unit(b.center-a.center);

  pt cc = b.center - a.center;
  double r = a.radius - b.radius;
  double R = a.radius + b.radius;
  
  if(fabs(a.radius+b.radius-d) < eps){
    return {
	    a.center + (cc*r + normal(cc) * sqrt(cc.size_sq()-r*r)) * a.radius / cc.size_sq(),
	    a.center + (cc*r - normal(cc) * sqrt(cc.size_sq()-r*r)) * a.radius / cc.size_sq(),
	    a.center + n * a.radius
    };
  }else if(a.radius+b.radius-d < eps){
    return {
	    a.center + (cc*r + normal(cc) * sqrt(cc.size_sq()-r*r)) * a.radius / cc.size_sq(),
	    a.center + (cc*r - normal(cc) * sqrt(cc.size_sq()-r*r)) * a.radius / cc.size_sq(),
	    a.center + (cc*R + normal(cc) * sqrt(cc.size_sq()-R*R)) * a.radius / cc.size_sq(),
	    a.center + (cc*R - normal(cc) * sqrt(cc.size_sq()-R*R)) * a.radius / cc.size_sq()	    
    };
  }else if(a.radius+b.radius-d > eps and d-fabs(a.radius-b.radius) > eps){
    return {
	    a.center + (cc*r + normal(cc) * sqrt(cc.size_sq()-r*r)) * a.radius / cc.size_sq(),
	    a.center + (cc*r - normal(cc) * sqrt(cc.size_sq()-r*r)) * a.radius / cc.size_sq()	    
    };
  }else if(fabs(fabs(a.radius-b.radius)-d) < eps){
    return {
	    a.radius>b.radius ? a.center+n*a.radius : b.center-n*b.radius
    };
  }

  return {};
}


/*
  https://onlinejudge.u-aizu.ac.jp/courses/library/4/CGL/all/CGL_7_H
*/
double angle_diff(const pt &a, const pt &b){
  double ret = atan2(b.y,b.x) - atan2(a.y,a.x);
  if(ret < -M_PI) ret += 2*M_PI;
  else if(ret > M_PI) ret -= 2*M_PI;
  return ret;
}


vector<pt> crosspoint_circle_segment(const circle &cl, const line &s){
  double r = cl.radius;
  const pt &c = cl.center;

  double d1 = (c-s.from).size();
  double d2 = (c-s.to).size();
  double v = distance_segment_point(s,c);
  pt n = normal(s.diff());
  double m = sqrt(r*r-v*v);
  pt k = s.from + s.diff() * cross(n,c+n-s.from) / cross(n,s.diff());

  if(d1 < r and d2 < r) return {}; // if inside
  else if(fabs(d1-r) < eps and fabs(d2-r) < eps) return {s.from, s.to};
  else if((d1-r)*(d2-r) < eps){
    double b = dot(unit(s.diff()), s.from-c);
    double a = (s.from-c).size_sq() - r*r;
    double x = sqrt(b*b-a);
    return {s.from + unit(s.diff()) * (-b-x>=0 ? -b-x : -b+x)};
  }
  else if(fabs(v-r) < eps) return {k};
  else if(v > r) return {}; // if outside
  
  return {
	  k - unit(s.diff()) * m,
	  k + unit(s.diff()) * m
  };
}

double area_intesection_circle_polygon(const circle &cl, const vector<pt> &ps){
  int n = ps.size();
  double ret = 0.0;

  REP(i,n){
    double temp = 0.0;

    double r = cl.radius;
    const pt &c = cl.center;

    const pt &p1 = ps[i];
    const pt &p2 = ps[(i+1)%n];

    auto res = crosspoint_circle_segment(cl,line(p1,p2));

    double d1 = (p1-c).size();
    double d2 = (p2-c).size();
    
    if(res.size() == 0){
      if(d1 < r and d2 < r){ // if inside
	temp += cross(p1-c,p2-c)/2;
      }else{ // if outside
	temp += r*r*angle_diff(p1-c,p2-c)/2;
      }
    }else if(res.size() == 1){
      pt &q = res[0];
      if(d1 >= r and d2 >= r){
	temp += r*r*angle_diff(p1-c,p2-c)/2;
      }else if(d1 >= r){
	temp += r*r*angle_diff(p1-c,q-c)/2 + cross(q-c,p2-c)/2;
      }else{
	temp += cross(p1-c,q-c)/2 + r*r*angle_diff(q-c,p2-c)/2;
      }
    }else{
      pt &q1 = res[0];
      pt &q2 = res[1];
      temp +=
	r*r*angle_diff(p1-c,q1-c)/2 +
	cross(q1-c,q2-c)/2 +
	r*r*angle_diff(q2-c,p2-c)/2;
    }
    
    ret += temp;
  }

  return ret;
}




int main(){
  

  
  return 0;
}
