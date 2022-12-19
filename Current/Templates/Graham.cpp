struct Point
{
    ll x, y;
    int id;

    ll dist(const Point& p)
    {
        return (x - p.x) * (x - p.x) + (y - p.y) * (y - p.y);
    }
} pts[MAXN];
stack<Point> scan;

int orientation(const Point& p1, const Point& p2, const Point& p3)
{
    ll v = (p2.y - p1.y) * (p3.x - p2.x) - (p2.x - p1.x) * (p3.y - p2.y);
    if (v < 0) return -1;
    if (v > 0) return 1;
    return 0;
}

Point before()
{
    Point tmp = scan.top();
    scan.pop();
    Point ret = scan.top();
    scan.push(tmp);
    return ret;
}

void graham()
{
    sort(pts + 1, pts + 1 + N, [](const Point& p1, const Point& p2)
    {
        return pll(p1.y, p1.x) < pll(p2.y, p2.x);
    });

    sort(pts + 2, pts + 1 + N, [](const Point& p1, const Point& p2)
    {
        int x = orientation(pts[1], p1, p2);
        if (x == 0) return pts[1].dist(p1) < pts[1].dist(p2);
        return x > 0;
    });

    scan.push(pts[1]);
    scan.push(pts[2]);
    scan.push(pts[3]);

    for (int i = 4; i <= N; i++)
    {
        while (!scan.empty() && !orientation(before(), scan.top(), pts[i])) scan.pop();
        scan.push(pts[i]);
    }
}