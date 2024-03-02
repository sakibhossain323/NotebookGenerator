typedef double Tf;
typedef double Ti;  /// use long long for exactness
const Tf PI = acos(-1), EPS = 1e-9;
int dcmp(Tf x) { return abs(x) < EPS ? 0 : (x < 0 ? -1 : 1); }

struct Point {
  Ti x, y;
  Point(Ti x = 0, Ti y = 0) : x(x), y(y) {}

  Point operator+(const Point& u) const { return Point(x + u.x, y + u.y); }
  Point operator-(const Point& u) const { return Point(x - u.x, y - u.y); }
  Point operator*(const LL u) const { return Point(x * u, y * u); }
  Point operator*(const Tf u) const { return Point(x * u, y * u); }
  Point operator/(const Tf u) const { return Point(x / u, y / u); }

  bool operator==(const Point& u) const {
    return dcmp(x - u.x) == 0 && dcmp(y - u.y) == 0;
  }
  bool operator!=(const Point& u) const { return !(*this == u); }
  bool operator<(const Point& u) const {
    return dcmp(x - u.x) < 0 || (dcmp(x - u.x) == 0 && dcmp(y - u.y) < 0);
  }
};
Ti dot(Point a, Point b) { return a.x * b.x + a.y * b.y; }
Ti cross(Point a, Point b) { return a.x * b.y - a.y * b.x; }
Tf length(Point a) { return sqrt(dot(a, a)); }
Ti sqLength(Point a) { return dot(a, a); }
Tf distance(Point a, Point b) { return length(a - b); }
Tf angle(Point u) { return atan2(u.y, u.x); }

// returns angle between oa, ob in (-PI, PI]
Tf angleBetween(Point a, Point b) {
  Tf ans = angle(b) - angle(a);
  return ans <= -PI ? ans + 2 * PI : (ans > PI ? ans - 2 * PI : ans);
}
// Rotate a ccw by rad radians, Tf Ti same
Point rotate(Point a, Tf rad) {
  return Point(a.x * cos(rad) - a.y * sin(rad),
               a.x * sin(rad) + a.y * cos(rad));
}
// rotate a ccw by angle th with cos(th) = co && sin(th) = si, tf ti same
Point rotatePrecise(Point a, Tf co, Tf si) {
  return Point(a.x * co - a.y * si, a.y * co + a.x * si);
}
Point rotate90(Point a) { return Point(-a.y, a.x); }
// scales vector a by s such that length of a becomes s, Tf Ti same
Point scale(Point a, Tf s) { return a / length(a) * s; }
// returns an unit vector perpendicular to vector a, Tf Ti same
Point normal(Point a) {
  Tf l = length(a);
  return Point(-a.y / l, a.x / l);
}
// returns 1 if c is left of ab, 0 if on ab && -1 if right of ab
int orient(Point a, Point b, Point c) { return dcmp(cross(b - a, c - a)); }
/// Use as sort(v.begin(), v.end(), polarComp(O, dir))
/// Polar comparator around O starting at direction dir
struct polarComp {
  Point O, dir;
  polarComp(Point O = Point(0, 0), Point dir = Point(1, 0)) : O(O), dir(dir) {}
  bool half(Point p) {
    return dcmp(cross(dir, p)) < 0 ||
           (dcmp(cross(dir, p)) == 0 && dcmp(dot(dir, p)) > 0);
  }
  bool operator()(Point p, Point q) {
    return make_tuple(half(p), 0) < make_tuple(half(q), cross(p, q));
  }
};
struct Segment {
  Point a, b;
  Segment(Point aa, Point bb) : a(aa), b(bb) {}
};
typedef Segment Line;
struct Circle {
  Point o;
  Tf r;
  Circle(Point o = Point(0, 0), Tf r = 0) : o(o), r(r) {}
  // returns true if point p is in || on the circle
  bool contains(Point p) { return dcmp(sqLength(p - o) - r * r) <= 0; }
  // returns a point on the circle rad radians away from +X CCW
  Point point(Tf rad) {
    static_assert(is_same<Tf, Ti>::value);
    return Point(o.x + cos(rad) * r, o.y + sin(rad) * r);
  }
  // area of a circular sector with central angle rad
  Tf area(Tf rad = PI + PI) { return rad * r * r / 2; }
  // area of the circular sector cut by a chord with central angle alpha
  Tf sector(Tf alpha) { return r * r * 0.5 * (alpha - sin(alpha)); }
};
