typedef vector<Point> Polygon;
// removes redundant colinear points
// polygon can't be all colinear points
Polygon RemoveCollinear(const Polygon &poly) {
  Polygon ret;
  int n = poly.size();
  for (int i = 0; i < n; i++) {
    Point a = poly[i];
    Point b = poly[(i + 1) % n];
    Point c = poly[(i + 2) % n];
    if (dcmp(cross(b - a, c - b)) != 0 && (ret.empty() || b != ret.back()))
      ret.push_back(b);
  }
  return ret;
}
// returns the signed area of polygon p of n vertices
Tf signedPolygonArea(const Polygon &p) {
  Tf ret = 0;
  for (int i = 0; i < (int)p.size() - 1; i++)
    ret += cross(p[i] - p[0], p[i + 1] - p[0]);
  return ret / 2;
}
// given a polygon p of n vertices, generates the convex hull in in CCW
// Tested on https://acm.timus.ru/problem.aspx?space=1&num=1185
// Caution: when all points are colinear AND removeRedundant == false
// output will be contain duplicate points (from upper hull) at back
Polygon convexHull(Polygon p, bool removeRedundant) {
  int check = removeRedundant ? 0 : -1;
  sort(p.begin(), p.end());
  p.erase(unique(p.begin(), p.end()), p.end());

  int n = p.size();
  Polygon ch(n + n);
  int m = 0;  // preparing lower hull
  for (int i = 0; i < n; i++) {
    while (m > 1 &&
           dcmp(cross(ch[m - 1] - ch[m - 2], p[i] - ch[m - 1])) <= check)
      m--;
    ch[m++] = p[i];
  }
  int k = m;  // preparing upper hull
  for (int i = n - 2; i >= 0; i--) {
    while (m > k &&
           dcmp(cross(ch[m - 1] - ch[m - 2], p[i] - ch[m - 2])) <= check)
      m--;
    ch[m++] = p[i];
  }
  if (n > 1) m--;
  ch.resize(m);
  return ch;
}
// returns inside = -1, on = 0, outside = 1
int pointInPolygon(const Polygon &p, Point o) {
  using Linear::onSegment;
  int wn = 0, n = p.size();
  for (int i = 0; i < n; i++) {
    int j = (i + 1) % n;
    if (onSegment(o, Segment(p[i], p[j])) || o == p[i]) return 0;
    int k = dcmp(cross(p[j] - p[i], o - p[i]));
    int d1 = dcmp(p[i].y - o.y);
    int d2 = dcmp(p[j].y - o.y);
    if (k > 0 && d1 <= 0 && d2 > 0) wn++;
    if (k < 0 && d2 <= 0 && d1 > 0) wn--;
  }
  return wn ? -1 : 1;
}
// Given a simple polygon p, and a line l, returns (x, y)
// x = longest segment of l in p, y = total length of l in p.
pair<Tf, Tf> linePolygonIntersection(Line l, const Polygon &p) {
  using Linear::lineLineIntersection;
  int n = p.size();
  vector<pair<Tf, int>> ev;
  for (int i = 0; i < n; ++i) {
    Point a = p[i], b = p[(i + 1) % n], z = p[(i - 1 + n) % n];
    int ora = orient(l.a, l.b, a), orb = orient(l.a, l.b, b),
        orz = orient(l.a, l.b, z);
    if (!ora) {
      Tf d = dot(a - l.a, l.b - l.a);
      if (orz && orb) {
        if (orz != orb) ev.emplace_back(d, 0);
        // else  // Point Touch
      } else if (orz)
        ev.emplace_back(d, orz);
      else if (orb)
        ev.emplace_back(d, orb);
    } else if (ora == -orb) {
      Point ins;
      lineLineIntersection(l, Line(a, b), ins);
      ev.emplace_back(dot(ins - l.a, l.b - l.a), 0);
    }
  }
  sort(ev.begin(), ev.end());

  Tf ans = 0, len = 0, last = 0, tot = 0;
  bool active = false;
  int sign = 0;
  for (auto &qq : ev) {
    int tp = qq.second;
    Tf d = qq.first;  /// current Segment is (last, d)
    if (sign) {       /// On Border
      len += d - last;
      tot += d - last;
      ans = max(ans, len);
      if (tp != sign) active = !active;
      sign = 0;
    } else {
      if (active) {  /// Strictly Inside
        len += d - last;
        tot += d - last;
        ans = max(ans, len);
      }
      if (tp == 0)
        active = !active;
      else
        sign = tp;
    }
    last = d;
    if (!active) len = 0;
  }
  ans /= length(l.b - l.a);
  tot /= length(l.b - l.a);
  return {ans, tot};
}
