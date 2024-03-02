using Linear::lineLineIntersection;
struct DirLine {
  Point p, v;
  Tf ang;
  DirLine() {}
  /// Directed line containing point P in the direction v
  DirLine(Point p, Point v) : p(p), v(v) { ang = atan2(v.y, v.x); }
  bool operator<(const DirLine& u) const { return ang < u.ang; }
};
// returns true if point p is on the ccw-left side of ray l
bool onLeft(DirLine l, Point p) { return dcmp(cross(l.v, p - l.p)) >= 0; }

// Given a set of directed lines returns a polygon such that
// the polygon is the intersection by halfplanes created by the
// left side of the directed lines. MAY CONTAIN DUPLICATE POINTS
int halfPlaneIntersection(vector<DirLine>& li, Polygon& poly) {
  int n = li.size();
  sort(li.begin(), li.end());

  int first, last;
  Point* p = new Point[n];
  DirLine* q = new DirLine[n];
  q[first = last = 0] = li[0];

  for (int i = 1; i < n; i++) {
    while (first < last && !onLeft(li[i], p[last - 1])) last--;
    while (first < last && !onLeft(li[i], p[first])) first++;
    q[++last] = li[i];

    if (dcmp(cross(q[last].v, q[last - 1].v)) == 0) {
      last--;
      if (onLeft(q[last], li[i].p)) q[last] = li[i];
    }

    if (first < last)
      lineLineIntersection(q[last - 1].p, q[last - 1].v, q[last].p, q[last].v,
                           p[last - 1]);
  }

  while (first < last && !onLeft(q[first], p[last - 1])) last--;
  if (last - first <= 1) {
    delete[] p;
    delete[] q;
    poly.clear();
    return 0;
  }
  lineLineIntersection(q[last].p, q[last].v, q[first].p, q[first].v, p[last]);

  int m = 0;
  poly.resize(last - first + 1);
  for (int i = first; i <= last; i++) poly[m++] = p[i];
  delete[] p;
  delete[] q;
  return m;
}
