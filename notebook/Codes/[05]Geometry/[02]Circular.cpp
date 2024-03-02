// Extremely inaccurate for finding near touches
// compute intersection of line l with circle c
// The intersections are given in order of the ray (l.a, l.b), Tf Ti same
vector<Point> circleLineIntersection(Circle c, Line l) {
  vector<Point> ret;
  Point b = l.b - l.a, a = l.a - c.o;
  Tf A = dot(b, b), B = dot(a, b);
  Tf C = dot(a, a) - c.r * c.r, D = B * B - A * C;
  if (D < -EPS) return ret;
  ret.push_back(l.a + b * (-B - sqrt(D + EPS)) / A);
  if (D > EPS) ret.push_back(l.a + b * (-B + sqrt(D)) / A);
  return ret;
}
// signed area of intersection of circle(c.o, c.r) &&
// triangle(c.o, s.a, s.b) [cross(a-o, b-o)/2]
Tf circleTriangleIntersectionArea(Circle c, Segment s) {
  using Linear::distancePointSegment;
  Tf OA = length(c.o - s.a);
  Tf OB = length(c.o - s.b);
  // sector
  if (dcmp(distancePointSegment(c.o, s) - c.r) >= 0)
    return angleBetween(s.a - c.o, s.b - c.o) * (c.r * c.r) / 2.0;
  // triangle
  if (dcmp(OA - c.r) <= 0 && dcmp(OB - c.r) <= 0)
    return cross(c.o - s.b, s.a - s.b) / 2.0;
  // three part: (A, a) (a, b) (b, B)
  vector<Point> Sect = circleLineIntersection(c, s);
  return circleTriangleIntersectionArea(c, Segment(s.a, Sect[0])) +
         circleTriangleIntersectionArea(c, Segment(Sect[0], Sect[1])) +
         circleTriangleIntersectionArea(c, Segment(Sect[1], s.b));
}
// area of intersecion of circle(c.o, c.r) && simple polyson(p[])
Tf circlePolyIntersectionArea(Circle c, Polygon p) {
  Tf res = 0;
  int n = p.size();
  for (int i = 0; i < n; ++i)
    res += circleTriangleIntersectionArea(c, Segment(p[i], p[(i + 1) % n]));
  return abs(res);
}
// locates circle c2 relative to c1
// interior             (d < R - r)         ----> -2
// interior tangents (d = R - r)         ----> -1
// concentric        (d = 0)
// secants             (R - r < d < R + r) ---->  0
// exterior tangents (d = R + r)         ---->  1
// exterior             (d > R + r)         ---->  2
int circleCirclePosition(Circle c1, Circle c2) {
  Tf d = length(c1.o - c2.o);
  int in = dcmp(d - abs(c1.r - c2.r)), ex = dcmp(d - (c1.r + c2.r));
  return in < 0 ? -2 : in == 0 ? -1 : ex == 0 ? 1 : ex > 0 ? 2 : 0;
}
// compute the intersection points between two circles c1 && c2, Tf Ti same
vector<Point> circleCircleIntersection(Circle c1, Circle c2) {
  vector<Point> ret;
  Tf d = length(c1.o - c2.o);
  if (dcmp(d) == 0) return ret;
  if (dcmp(c1.r + c2.r - d) < 0) return ret;
  if (dcmp(abs(c1.r - c2.r) - d) > 0) return ret;

  Point v = c2.o - c1.o;
  Tf co = (c1.r * c1.r + sqLength(v) - c2.r * c2.r) / (2 * c1.r * length(v));
  Tf si = sqrt(abs(1.0 - co * co));
  Point p1 = scale(rotatePrecise(v, co, -si), c1.r) + c1.o;
  Point p2 = scale(rotatePrecise(v, co, si), c1.r) + c1.o;

  ret.push_back(p1);
  if (p1 != p2) ret.push_back(p2);
  return ret;
}
// intersection area between two circles c1, c2
Tf circleCircleIntersectionArea(Circle c1, Circle c2) {
  Point AB = c2.o - c1.o;
  Tf d = length(AB);
  if (d >= c1.r + c2.r) return 0;
  if (d + c1.r <= c2.r) return PI * c1.r * c1.r;
  if (d + c2.r <= c1.r) return PI * c2.r * c2.r;

  Tf alpha1 = acos((c1.r * c1.r + d * d - c2.r * c2.r) / (2.0 * c1.r * d));
  Tf alpha2 = acos((c2.r * c2.r + d * d - c1.r * c1.r) / (2.0 * c2.r * d));
  return c1.sector(2 * alpha1) + c2.sector(2 * alpha2);
}
// returns tangents from a point p to circle c, Tf Ti same
vector<Point> pointCircleTangents(Point p, Circle c) {
  vector<Point> ret;
  Point u = c.o - p;
  Tf d = length(u);
  if (d < c.r)
    ;
  else if (dcmp(d - c.r) == 0) {
    ret = {rotate(u, PI / 2)};
  } else {
    Tf ang = asin(c.r / d);
    ret = {rotate(u, -ang), rotate(u, ang)};
  }
  return ret;
}
// returns the points on tangents that touches the circle, Tf Ti Same
vector<Point> pointCircleTangencyPoints(Point p, Circle c) {
  Point u = p - c.o;
  Tf d = length(u);
  if (d < c.r)
    return {};
  else if (dcmp(d - c.r) == 0)
    return {c.o + u};
  else {
    Tf ang = acos(c.r / d);
    u = u / length(u) * c.r;
    return {c.o + rotate(u, -ang), c.o + rotate(u, ang)};
  }
}
// for two circles c1 && c2, returns two list of points a && b
// such that a[i] is on c1 && b[i] is c2 && for every i
// Line(a[i], b[i]) is a tangent to both circles
// CAUTION: a[i] = b[i] in case they touch | -1 for c1 = c2
int circleCircleTangencyPoints(Circle c1, Circle c2, vector<Point> &a,
                               vector<Point> &b) {
  a.clear(), b.clear();
  int cnt = 0;
  if (dcmp(c1.r - c2.r) < 0) {
    swap(c1, c2);
    swap(a, b);
  }
  Tf d2 = sqLength(c1.o - c2.o);
  Tf rdif = c1.r - c2.r, rsum = c1.r + c2.r;
  if (dcmp(d2 - rdif * rdif) < 0) return 0;
  if (dcmp(d2) == 0 && dcmp(c1.r - c2.r) == 0) return -1;

  Tf base = angle(c2.o - c1.o);
  if (dcmp(d2 - rdif * rdif) == 0) {
    a.push_back(c1.point(base));
    b.push_back(c2.point(base));
    cnt++;
    return cnt;
  }

  Tf ang = acos((c1.r - c2.r) / sqrt(d2));
  a.push_back(c1.point(base + ang));
  b.push_back(c2.point(base + ang));
  cnt++;
  a.push_back(c1.point(base - ang));
  b.push_back(c2.point(base - ang));
  cnt++;

  if (dcmp(d2 - rsum * rsum) == 0) {
    a.push_back(c1.point(base));
    b.push_back(c2.point(PI + base));
    cnt++;
  } else if (dcmp(d2 - rsum * rsum) > 0) {
    Tf ang = acos((c1.r + c2.r) / sqrt(d2));
    a.push_back(c1.point(base + ang));
    b.push_back(c2.point(PI + base + ang));
    cnt++;
    a.push_back(c1.point(base - ang));
    b.push_back(c2.point(PI + base - ang));
    cnt++;
  }
  return cnt;
}
