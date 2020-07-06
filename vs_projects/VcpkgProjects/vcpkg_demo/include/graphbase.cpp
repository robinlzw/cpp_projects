#include "graphbase.h"
#include <cmath>
#include <cstdlib>

double dist(PointEx p1, PointEx p2) {
    return(sqrt((p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y)));
}

bool equalPoint(PointEx p1, PointEx p2) {
    return ((fabs(p1.x - p2.x)<EP) && (fabs(p1.y - p2.y)<EP));
}

double multiply(PointEx sp, PointEx ep, PointEx op) {
    return((sp.x - op.x)*(ep.y - op.y) - (ep.x - op.x)*(sp.y - op.y));
}

double dotMultiply(PointEx p1, PointEx p2, PointEx p0) {
    return ((p1.x - p0.x)*(p2.x - p0.x) + (p1.y - p0.y)*(p2.y - p0.y));
}

bool online(LineSegment l, PointEx p) {
    return((multiply(l.endPoint, p, l.startPoint) == 0)
           && (((p.x - l.startPoint.x)*(p.x - l.endPoint.x) <= 0) && ((p.y - l.startPoint.y)*(p.y - l.endPoint.y) <= 0)));
}

PointEx rotate(PointEx o, double d, PointEx p) {
    PointEx tp;
    p.x -= o.x;
    p.y -= o.y;
    tp.x = p.x*cos(d) - p.y*sin(d) + o.x;
    tp.y = p.y*cos(d) + p.x*sin(d) + o.y;
    return tp;
}

double angle(PointEx o, PointEx s, PointEx e) {
    double cosfi, fi, norm;
    double dsx = s.x - o.x;
    double dsy = s.y - o.y;
    double dex = e.x - o.x;
    double dey = e.y - o.y;

    cosfi = dsx*dex + dsy*dey;
    norm = (dsx*dsx + dsy*dsy)*(dex*dex + dey*dey);
    cosfi /= sqrt(norm);

    if (cosfi >= 1.0) return 0;
    if (cosfi <= -1.0) return -3.1415926;

    fi = acos(cosfi);
    if (dsx*dey - dsy*dex > 0) return fi;      // 说明矢量os 在矢量 oe的顺时针方向
    return -fi;
}

double relation(PointEx p, LineSegment l) {
    LineSegment tl;
    tl.startPoint = l.startPoint;
    tl.endPoint = p;
    return dotMultiply(tl.endPoint, l.endPoint, l.startPoint) / (dist(l.startPoint, l.endPoint)*dist(l.startPoint, l.endPoint));
}

PointEx perpendicular(PointEx p, LineSegment l) {
    double r = relation(p, l);
    PointEx tp;
    tp.x = l.startPoint.x + r*(l.endPoint.x - l.startPoint.x);
    tp.y = l.startPoint.y + r*(l.endPoint.y - l.startPoint.y);
    return tp;
}

Beeline perpendicularInSegment(LineSegment&l, PointEx&p) {
    Beeline beeline;
    if (abs(l.startPoint.x - l.endPoint.x) < EP){//平行于y轴
        beeline.a = 0;
        beeline.b = 1;
        beeline.c = -p.y;
    } else if(abs(l.startPoint.y - l.endPoint.y) <EP ) {//平行于x轴
        beeline.a = 1;
        beeline.b = 0;
        beeline.c = -p.x;
    } else {//即不平行于x轴又不平行于y轴
        double a = (l.startPoint.x - l.endPoint.x) / (l.endPoint.y - l.startPoint.y);
        double b = p.y - a*p.x;
        if (a < 0){
            beeline.a = -a;
            beeline.b = 1;
            beeline.c = -b;
        } else if(a > 0) {
            beeline.a = a;
            beeline.b = -1;
            beeline.c = b;
        }
    }
    return beeline;
}

double pToLinesegDist(PointEx p, LineSegment l, PointEx &np) {
    double r = relation(p, l);
    if (r<0) {
        np = l.startPoint;
        return dist(p, l.startPoint);
    }
    if (r>1) {
        np = l.endPoint;
        return dist(p, l.endPoint);
    }
    np = perpendicular(p, l);
    return dist(p, np);
}

double pToLDist(PointEx p, LineSegment l) {
    return fabs(multiply(p, l.endPoint, l.startPoint)) / dist(l.startPoint, l.endPoint);
}

double pToPointSet(int vcount, PointEx pointset[], PointEx p, PointEx &q) {
    int i;
    double cd = double(INF), td;
    LineSegment l;
    PointEx tq, cq;

    for (i = 0; i < vcount - 1; i++) {
        l.startPoint = pointset[i];

        l.endPoint = pointset[i + 1];
        td = pToLinesegDist(p, l, tq);
        if (td < cd) {
            cd = td;
            cq = tq;
        }
    }
    q = cq;
    return cd;
}

bool circleInsidePolygon(int vcount, PointEx center, double radius, PointEx polygon[]) {
    PointEx q;
    double d;
    q.x = 0;
    q.y = 0;
    d = pToPointSet(vcount, polygon, center, q);
    if (d < radius || fabs(d - radius) < EP)
        return true;
    else
        return false;
}

double cosine(LineSegment l1, LineSegment l2) {
    return (((l1.endPoint.x - l1.startPoint.x)*(l2.endPoint.x - l2.startPoint.x)
        + (l1.endPoint.y - l1.startPoint.y)*(l2.endPoint.y - l2.startPoint.y)) / (dist(l1.endPoint, l1.startPoint)*dist(l2.endPoint, l2.startPoint)));
}

double lsAngle(LineSegment l1, LineSegment l2) {
    PointEx o, s, e;
    o.x = o.y = 0;
    s.x = l1.endPoint.x - l1.startPoint.x;
    s.y = l1.endPoint.y - l1.startPoint.y;
    e.x = l2.endPoint.x - l2.startPoint.x;
    e.y = l2.endPoint.y - l2.startPoint.y;
    return angle(o, s, e);
}

bool intersect(LineSegment u, LineSegment v) {
    return((__max(u.startPoint.x, u.endPoint.x) >= __min(v.startPoint.x, v.endPoint.x)) &&                     //排斥实验
           (__max(v.startPoint.x, v.endPoint.x) >= __min(u.startPoint.x, u.endPoint.x)) &&
           (__max(u.startPoint.y, u.endPoint.y) >= __min(v.startPoint.y, v.endPoint.y)) &&
           (__max(v.startPoint.y, v.endPoint.y) >= __min(u.startPoint.y, u.endPoint.y)) &&
           (multiply(v.startPoint, u.endPoint, u.startPoint)*multiply(u.endPoint, v.endPoint, u.startPoint) >= 0) &&         //跨立实验
           (multiply(u.startPoint, v.endPoint, v.startPoint)*multiply(v.endPoint, u.endPoint, v.startPoint) >= 0));
}

bool intersectA(LineSegment u, LineSegment v) {
    return	((intersect(u, v)) &&
             (!online(u, v.startPoint)) &&
             (!online(u, v.endPoint)) &&
             (!online(v, u.endPoint)) &&
             (!online(v, u.startPoint)));
}

bool intersectL(LineSegment u, LineSegment v) {
    return multiply(u.startPoint, v.endPoint, v.startPoint)*multiply(v.endPoint, u.endPoint, v.startPoint) >= 0;
}

Beeline makeLine(PointEx p1, PointEx p2) {
    Beeline tl;
    int sign = 1;
    tl.a = p2.y - p1.y;
    if (tl.a < 0) {
        sign = -1;
        tl.a = sign*tl.a;
    }
    tl.b = sign*(p1.x - p2.x);
    tl.c = sign*(p1.y*p2.x - p1.x*p2.y);
    return tl;
}

double slope(Beeline l) {
    if (fabs(l.a) < 1e-20)
        return 0;
    if (fabs(l.b) < 1e-20)
        return INF;
    return -(l.a / l.b);
}

double alpha(Beeline l) {
    if (fabs(l.a) < EP)
        return 0;
    if (fabs(l.b)< EP)
        return PI / 2;
    double k = slope(l);
    if (k>0)
        return atan(k);
    else
        return PI + atan(k);
}

PointEx symmetry(Beeline l, PointEx p) {
    PointEx tp;
    tp.x = ((l.b*l.b - l.a*l.a)*p.x - 2 * l.a*l.b*p.y - 2 * l.a*l.c) / (l.a*l.a + l.b*l.b);
    tp.y = ((l.a*l.a - l.b*l.b)*p.y - 2 * l.a*l.b*p.x - 2 * l.b*l.c) / (l.a*l.a + l.b*l.b);
    return tp;
}

bool lineIntersect(Beeline l1, Beeline l2, PointEx &p) {
    double d = l1.a*l2.b - l2.a*l1.b;
    if (fabs(d) < EP) // 不相交
        return false;
    p.x = (l2.c*l1.b - l1.c*l2.b) / d;
    p.y = (l2.a*l1.c - l1.a*l2.c) / d;
    return true;
}

bool intersection(LineSegment l1, LineSegment l2, PointEx &inter) {
    Beeline ll1, ll2;
    ll1 = makeLine(l1.startPoint, l1.endPoint);
    ll2 = makeLine(l2.startPoint, l2.endPoint);
    if (lineIntersect(ll1, ll2, inter))
        return online(l1, inter);
    else
        return false;
}

bool isSimple(int vcount, PointEx polygon[]) {
    int i, cn;
    LineSegment l1, l2;
    for (i = 0; i < vcount; i++) {
        l1.startPoint = polygon[i];
        l1.endPoint = polygon[(i + 1) % vcount];
        cn = vcount - 3;
        while (cn) {
            l2.startPoint = polygon[(i + 2) % vcount];
            l2.endPoint = polygon[(i + 3) % vcount];
            if (intersect(l1, l2))
                break;
            cn--;
        }
        if (cn)
            return false;
    }
    return true;
}

void checkConvex(int vcount, PointEx polygon[], bool bc[]) {
    int i, index = 0;
    PointEx tp = polygon[0];
    for (i = 1; i < vcount; i++){ // 寻找第一个凸顶点
        if (polygon[i].y < tp.y || (polygon[i].y == tp.y&&polygon[i].x < tp.x)) {
            tp = polygon[i];
            index = i;
        }
    }
    int count = vcount - 1;
    bc[index] = 1;
    while (count){ // 判断凸凹性
        if (multiply(polygon[(index + 1) % vcount], polygon[(index + 2) % vcount], polygon[index]) >= 0)
            bc[(index + 1) % vcount] = 1;
        else
            bc[(index + 1) % vcount] = 0;
        index++;
        count--;
    }
}

bool isConvex(int vcount, PointEx polygon[]) {
    bool bc[MAXV];
    checkConvex(vcount, polygon, bc);
    for (int i = 0; i < vcount; i++) // 逐一检查顶点，是否全部是凸顶点
    if (!bc[i])
        return false;
    return true;
}

double areaOfPolygon(int vcount, PointEx polygon[]) {
    int i;
    double s;
    if (vcount < 3)
        return 0;
    s = polygon[0].y*(polygon[vcount - 1].x - polygon[1].x);
    for (i = 1; i < vcount; i++)
        s += polygon[i].y*(polygon[(i - 1)].x - polygon[(i + 1) % vcount].x);
    return s / 2;
}

bool isConterClock(int vcount, PointEx polygon[]) {
    return areaOfPolygon(vcount, polygon)>0;
}

bool isCcwize(int vcount, PointEx polygon[]) {
    int i, index;
    PointEx a, b, v;
    v = polygon[0];
    index = 0;
    for (i = 1; i < vcount; i++) // 找到最低且最左顶点，肯定是凸顶点
    {
        if (polygon[i].y < v.y || polygon[i].y == v.y && polygon[i].x<v.x) {
            index = i;
        }
    }
    a = polygon[(index - 1 + vcount) % vcount]; // 顶点v的前一顶点
    b = polygon[(index + 1) % vcount]; // 顶点v的后一顶点
    return multiply(v, b, a)>0;
}

int insidePolygon(int vcount, PointEx Polygon[], PointEx q) {
    int c = 0, i, n;
    LineSegment l1, l2;
    bool bintersect_a, bonline1, bonline2, bonline3;
    double r1, r2;

    l1.startPoint = q;
    l1.endPoint = q;
    l1.endPoint.x = double(INF);
    n = vcount;
    for (i = 0; i<vcount; i++) {
        l2.startPoint = Polygon[i];
        l2.endPoint = Polygon[(i + 1) % n];
        if (online(l2, q))
            return 1; // 如果点在边上，返回1
        if ((bintersect_a = intersectA(l1, l2)) || // 相交且不在端点
            ((bonline1 = online(l1, Polygon[(i + 1) % n])) && // 第二个端点在射线上
            ((!(bonline2 = online(l1, Polygon[(i + 2) % n]))) && /* 前一个端点和后一个端点在射线两侧 */
            ((r1 = multiply(Polygon[i], Polygon[(i + 1) % n], l1.startPoint)*multiply(Polygon[(i + 1) % n], Polygon[(i + 2) % n], l1.startPoint))>0) ||
            (bonline3 = online(l1, Polygon[(i + 2) % n])) &&     /* 下一条边是水平线，前一个端点和后一个端点在射线两侧  */
            ((r2 = multiply(Polygon[i], Polygon[(i + 2) % n], l1.startPoint)*multiply(Polygon[(i + 2) % n],
            Polygon[(i + 3) % n], l1.startPoint)) > 0)
            ))) {
            c++;
        }
    }
    if (c % 2 == 1)
        return 0;
    else
        return 2;
}

bool insideConvexPolygon(int vcount, PointEx polygon[], PointEx q) {
    PointEx p;
    LineSegment l;
    int i;
    p.x = 0; p.y = 0;
    for (i = 0; i < vcount; i++){ // 寻找一个肯定在多边形polygon内的点p：多边形顶点平均值
        p.x += polygon[i].x;
        p.y += polygon[i].y;
    }
    p.x /= vcount;
    p.y /= vcount;

    for (i = 0; i < vcount; i++) {
        l.startPoint = polygon[i]; l.endPoint = polygon[(i + 1) % vcount];
        if (multiply(p, l.endPoint, l.startPoint)*multiply(q, l.endPoint, l.startPoint) < 0) /* 点p和点q在边l的两侧，说明点q肯定在多边形外 */
            break;
    }
    return (i == vcount);
}

void grahamScan(PointEx PointSet[], PointEx ch[], int n, int &len) {
    int i, j, k = 0, top = 2;
    PointEx tmp;
    // 选取PointSet中y坐标最小的点PointSet[k]，如果这样的点有多个，则取最左边的一个
    for (i = 1; i < n; i++)
    if (PointSet[i].y < PointSet[k].y || (PointSet[i].y == PointSet[k].y) && (PointSet[i].x < PointSet[k].x))
        k = i;
    tmp = PointSet[0];
    PointSet[0] = PointSet[k];
    PointSet[k] = tmp; // 现在PointSet中y坐标最小的点在PointSet[0]
    for (i = 1; i < n - 1; i++) /* 对顶点按照相对PointSet[0]的极角从小到大进行排序，极角相同的按照距离PointSet[0]从近到远进行排序 */
    {
        k = i;
        for (j = i + 1; j<n; j++)
        if (multiply(PointSet[j], PointSet[k], PointSet[0])>0 ||  // 极角更小
            (multiply(PointSet[j], PointSet[k], PointSet[0]) == 0) && /* 极角相等，距离更短 */
            dist(PointSet[0], PointSet[j]) < dist(PointSet[0], PointSet[k])
            )
            k = j;
        tmp = PointSet[i];
        PointSet[i] = PointSet[k];
        PointSet[k] = tmp;
    }
    ch[0] = PointSet[0];
    ch[1] = PointSet[1];
    ch[2] = PointSet[2];
    for (i = 3; i < n; i++) {
        while (multiply(PointSet[i], ch[top], ch[top - 1]) >= 0)
            top--;
        ch[++top] = PointSet[i];
    }
    len = top + 1;
}

void convexClosure(PointEx PointSet[], PointEx ch[], int n, int &len) {
    int top = 0, i, index, first;
    double curmax, curcos, curdis;
    PointEx tmp;
    LineSegment l1, l2;
    bool use[MAXV];
    tmp = PointSet[0];
    index = 0;
    // 选取y最小点，如果多于一个，则选取最左点
    for (i = 1; i < n; i++) {
        if (PointSet[i].y < tmp.y || PointSet[i].y == tmp.y&&PointSet[i].x < tmp.x) {
            index = i;
        }
        use[i] = false;
    }
    tmp = PointSet[index];
    first = index;
    use[index] = true;

    index = -1;
    ch[top++] = tmp;
    tmp.x -= 100;
    l1.startPoint = tmp;
    l1.endPoint = ch[0];
    l2.startPoint = ch[0];

    while (index != first) {
        curmax = -100;
        curdis = 0;
        // 选取与最后一条确定边夹角最小的点，即余弦值最大者
        for (i = 0; i<n; i++) {
            if (use[i])continue;
            l2.endPoint = PointSet[i];
            curcos = cosine(l1, l2); // 根据cos值求夹角余弦，范围在 （-1 -- 1 ）
            if (curcos>curmax || fabs(curcos - curmax)<1e-6 && dist(l2.startPoint, l2.endPoint)>curdis) {
                curmax = curcos;
                index = i;
                curdis = dist(l2.startPoint, l2.endPoint);
            }
        }
        use[first] = false;            //清空第first个顶点标志，使最后能形成封闭的hull
        use[index] = true;
        ch[top++] = PointSet[index];
        l1.startPoint = ch[top - 2];
        l1.endPoint = ch[top - 1];
        l2.startPoint = ch[top - 1];
    }
    len = top - 1;
}

bool linesegInsidePolygon(int vcount, PointEx polygon[], LineSegment l) {
    // 判断线端l的端点是否不都在多边形内
    if (!insidePolygon(vcount, polygon, l.startPoint) || !insidePolygon(vcount, polygon, l.endPoint))
        return false;
    int top = 0, i, j;
    PointEx PointSet[MAXV], tmp;
    LineSegment s;

    for (i = 0; i < vcount; i++) {
        s.startPoint = polygon[i];
        s.endPoint = polygon[(i + 1) % vcount];
        if (online(s, l.startPoint)) //线段l的起始端点在线段s上
            PointSet[top++] = l.startPoint;
        else if (online(s, l.endPoint)) //线段l的终止端点在线段s上
            PointSet[top++] = l.endPoint;
        else {
            if (online(l, s.startPoint)) //线段s的起始端点在线段l上
                PointSet[top++] = s.startPoint;
            else if (online(l, s.endPoint)) // 线段s的终止端点在线段l上
                PointSet[top++] = s.endPoint;
            else {
                if (intersect(l, s)) // 这个时候如果相交，肯定是内交，返回false
                    return false;
            }
        }
    }

    for (i = 0; i < top - 1; i++) /* 冒泡排序，x坐标小的排在前面；x坐标相同者，y坐标小的排在前面 */
    {
        for (j = i + 1; j<top; j++) {
            if (PointSet[i].x>PointSet[j].x || fabs(PointSet[i].x - PointSet[j].x)<EP && PointSet[i].y>PointSet[j].y) {
                tmp = PointSet[i];
                PointSet[i] = PointSet[j];
                PointSet[j] = tmp;
            }
        }
    }

    for (i = 0; i < top - 1; i++) {
        tmp.x = (PointSet[i].x + PointSet[i + 1].x) / 2; //得到两个相邻交点的中点
        tmp.y = (PointSet[i].y + PointSet[i + 1].y) / 2;
        if (!insidePolygon(vcount, polygon, tmp))
            return false;
    }
    return true;
}

void addPosPart(double x, double y, double w, double &xtr, double &ytr, double &wtr) {
    if (fabs(wtr + w) < 1e-10) return; // detect zero regions
    xtr = (wtr*xtr + w*x) / (wtr + w);
    ytr = (wtr*ytr + w*y) / (wtr + w);
    wtr = w + wtr;
    return;
}

void addNegPart(double x, double y, double w, double &xtl, double &ytl, double &wtl) {
    if (fabs(wtl + w) < 1e-10)
        return; // detect zero regions

    xtl = (wtl*xtl + w*x) / (wtl + w);
    ytl = (wtl*ytl + w*y) / (wtl + w);
    wtl = w + wtl;
    return;
}

void addRegion(double x1, double y1, double x2, double y2, double &xtr, double &ytr, double &wtr, double &xtl, double &ytl, double &wtl) {
    if (fabs(x1 - x2)< 1e-10)
        return;

    if (x2 > x1) {
        addPosPart((x2 + x1) / 2, y1 / 2, (x2 - x1) * y1, xtr, ytr, wtr); /* rectangle 全局变量变化处 */
        addPosPart((x1 + x2 + x2) / 3, (y1 + y1 + y2) / 3, (x2 - x1)*(y2 - y1) / 2, xtr, ytr, wtr);
        // triangle 全局变量变化处
    } else {
        addNegPart((x2 + x1) / 2, y1 / 2, (x2 - x1) * y1, xtl, ytl, wtl);
        // rectangle 全局变量变化处
        addNegPart((x1 + x2 + x2) / 3, (y1 + y1 + y2) / 3, (x2 - x1)*(y2 - y1) / 2, xtl, ytl, wtl);
        // triangle  全局变量变化处
    }
}

PointEx cgSimple(int vcount, PointEx polygon[]) {
    double xtr, ytr, wtr, xtl, ytl, wtl;
    //注意： 如果把xtr,ytr,wtr,xtl,ytl,wtl改成全局变量后这里要删去
    PointEx p1, p2, tp;
    xtr = ytr = wtr = 0.0;
    xtl = ytl = wtl = 0.0;
    for (int i = 0; i < vcount; i++) {
        p1 = polygon[i];
        p2 = polygon[(i + 1) % vcount];
        addRegion(p1.x, p1.y, p2.x, p2.y, xtr, ytr, wtr, xtl, ytl, wtl); //全局变量变化处
    }
    tp.x = (wtr*xtr + wtl*xtl) / (wtr + wtl);
    tp.y = (wtr*ytr + wtl*ytl) / (wtr + wtl);
    return tp;
}

PointEx gravityCenter(int vcount, PointEx polygon[]) {
    PointEx tp;
    double x, y, s, x0, y0, cs, k;
    x = 0; y = 0; s = 0;
    for (int i = 1; i < vcount - 1; i++) {
        x0 = (polygon[0].x + polygon[i].x + polygon[i + 1].x) / 3;
        y0 = (polygon[0].y + polygon[i].y + polygon[i + 1].y) / 3; //求当前三角形的重心
        cs = multiply(polygon[i], polygon[i + 1], polygon[0]) / 2;
        //三角形面积可以直接利用该公式求解
        if (fabs(s) < 1e-20) {
            x = x0; y = y0; s += cs;
            continue;
        }
        k = cs / s; //求面积比例
        x = (x + k*x0) / (1 + k);
        y = (y + k*y0) / (1 + k);
        s += cs;
    }
    tp.x = x;
    tp.y = y;
    return tp;
}

PointEx aPointInsidepoly(int vcount, PointEx polygon[]) {
    PointEx v, a, b, r;
    int i, index;
    v = polygon[0];
    index = 0;
    for (i = 1; i < vcount; i++) //寻找一个凸顶点
    {
        if (polygon[i].y < v.y) {
            v = polygon[i];
            index = i;
        }
    }
    a = polygon[(index - 1 + vcount) % vcount]; //得到v的前一个顶点
    b = polygon[(index + 1) % vcount]; //得到v的后一个顶点
    PointEx tri[3], q;
    tri[0] = a; tri[1] = v; tri[2] = b;
    double md = INF;
    int in1 = index;
    bool bin = false;
    for (i = 0; i < vcount; i++) //寻找在三角形avb内且离顶点v最近的顶点q
    {
        if (i == index)continue;
        if (i == (index - 1 + vcount) % vcount)continue;
        if (i == (index + 1) % vcount)continue;
        if (!insideConvexPolygon(3, tri, polygon[i]))continue;
        bin = true;
        if (dist(v, polygon[i]) < md) {
            q = polygon[i];
            md = dist(v, q);
        }
    }
    if (!bin) //没有顶点在三角形avb内，返回线段ab中点
    {
        r.x = (a.x + b.x) / 2;
        r.y = (a.y + b.y) / 2;
        return r;
    }
    r.x = (v.x + q.x) / 2; //返回线段vq的中点
    r.y = (v.y + q.y) / 2;
    return r;
}

void pointTangentpoly(int vcount, PointEx polygon[], PointEx p, PointEx &rp, PointEx &lp) {
    LineSegment ep, en;
    bool blp, bln;
    rp = polygon[0];
    lp = polygon[0];
    for (int i = 1; i<vcount; i++) {
        ep.startPoint = polygon[(i + vcount - 1) % vcount];
        ep.endPoint = polygon[i];
        en.startPoint = polygon[i];
        en.endPoint = polygon[(i + 1) % vcount];
        blp = multiply(ep.endPoint, p, ep.startPoint) >= 0;                // p is to the left of pre edge
        bln = multiply(en.endPoint, p, en.startPoint) >= 0;                // p is to the left of next edge
        if (!blp&&bln) {
            if (multiply(polygon[i], rp, p)>0)           // polygon[i] is above rp
                rp = polygon[i];
        }
        if (blp&&!bln) {
            if (multiply(lp, polygon[i], p) > 0)           // polygon[i] is below lp
                lp = polygon[i];
        }
    }
}

bool coreExist(int vcount, PointEx polygon[], PointEx &p) {
    int i, j, k;
    LineSegment l;
    Beeline lineset[MAXV];
    for (i = 0; i < vcount; i++) {
        lineset[i] = makeLine(polygon[i], polygon[(i + 1) % vcount]);
    }
    for (i = 0; i < vcount; i++) {
        for (j = 0; j < vcount; j++) {
            if (i == j)continue;
            if (lineIntersect(lineset[i], lineset[j], p)) {
                for (k = 0; k<vcount; k++) {
                    l.startPoint = polygon[k];
                    l.endPoint = polygon[(k + 1) % vcount];
                    if (multiply(p, l.endPoint, l.startPoint)>0)
                        //多边形顶点按逆时针方向排列，核肯定在每条边的左侧或边上
                        break;
                }
                if (k == vcount)             //找到了一个核上的点
                    break;
            }
        }
        if (j < vcount) break;
    }
    if (i < vcount)
        return true;
    else
        return false;
}
bool pointInCircle(PointEx o, double r, PointEx p) {
    double d2 = (p.x - o.x)*(p.x - o.x) + (p.y - o.y)*(p.y - o.y);
    double r2 = r*r;
    return d2 < r2 || fabs(d2 - r2) < EP;
}

bool coCircle(PointEx p1, PointEx p2, PointEx p3, PointEx &q, double &r) {
    double x12 = p2.x - p1.x;
    double y12 = p2.y - p1.y;
    double x13 = p3.x - p1.x;
    double y13 = p3.y - p1.y;
    double z2 = x12*(p1.x + p2.x) + y12*(p1.y + p2.y);
    double z3 = x13*(p1.x + p3.x) + y13*(p1.y + p3.y);
    double d = 2.0*(x12*(p3.y - p2.y) - y12*(p3.x - p2.x));
    if (fabs(d) < EP) //共线，圆不存在
        return false;
    q.x = (y13*z2 - y12*z3) / d;
    q.y = (x12*z3 - x13*z2) / d;
    r = dist(p1, q);
    return true;
}

PointEx rect4th(PointEx a, PointEx b, PointEx c) {
    PointEx d;
    if (fabs(dotMultiply(a, b, c)) < EP) // 说明c点是直角拐角处
    {
        d.x = a.x + b.x - c.x;
        d.y = a.y + b.y - c.y;
    }
    if (fabs(dotMultiply(a, c, b)) < EP) // 说明b点是直角拐角处
    {
        d.x = a.x + c.x - b.x;
        d.y = a.y + c.y - b.x;
    }
    if (fabs(dotMultiply(c, b, a)) < EP) // 说明a点是直角拐角处
    {
        d.x = c.x + b.x - a.x;
        d.y = c.y + b.y - a.y;
    }
    return d;
}

int circleRelation(PointEx p1, double r1, PointEx p2, double r2) {
    double d = sqrt((p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y));

    if (fabs(d - r1 - r2) < EP) // 必须保证前两个if先被判定！
        return 2;
    if (fabs(d - fabs(r1 - r2)) < EP)
        return 4;
    if (d > r1 + r2)
        return 1;
    if (d < fabs(r1 - r2))
        return 5;
    if (fabs(r1 - r2) < d && d < r1 + r2)
        return 3;
    return 0; // indicate an error!
}

bool circleRecRelation(PointEx pc, double r, PointEx pr1, PointEx pr2, PointEx pr3, PointEx pr4) {
    if (pr1.x < pc.x && pc.x < pr2.x && pr3.y < pc.y && pc.y < pr2.y) {
        LineSegment line1(pr1, pr2);
        LineSegment line2(pr2, pr3);
        LineSegment line3(pr3, pr4);
        LineSegment line4(pr4, pr1);
        if (r < pToLDist(pc, line1) && r < pToLDist(pc, line2) && r < pToLDist(pc, line3) && r < pToLDist(pc, line4))
            return true;
    }
    return false;
}

double p2PlaneDist(double x, double y, double z, double a, double b, double c, double d) {
    return fabs(a*x + b*y + c*z + d) / sqrt(a*a + b*b + c*c);
}

bool sameSide(PointEx p1, PointEx p2, Beeline line) {
    return (line.a * p1.x + line.b * p1.y + line.c) *
        (line.a * p2.x + line.b * p2.y + line.c) > 0;
}

void reflect(double a1, double b1, double c1, double a2, double b2, double c2, double &a, double &b, double &c) {
    double n, m;
    double tpb, tpa;
    tpb = b1*b2 + a1*a2;
    tpa = a2*b1 - a1*b2;
    m = (tpb*b1 + tpa*a1) / (b1*b1 + a1*a1);
    n = (tpa*b1 - tpb*a1) / (b1*b1 + a1*a1);
    if (fabs(a1*b2 - a2*b1) < 1e-20) {
        a = a2; b = b2; c = c2;
        return;
    }
    double xx, yy; //(xx,yy)是入射线与镜面的交点。
    xx = (b1*c2 - b2*c1) / (a1*b2 - a2*b1);
    yy = (a2*c1 - a1*c2) / (a1*b2 - a2*b1);
    a = n;
    b = -m;
    c = m*yy - xx*n;
}

bool r2Inr1(double A, double B, double C, double D) {
    double X, Y, L, K, DMax;
    if (A < B) {
        double tmp = A;
        A = B;
        B = tmp;
    }
    if (C < D) {
        double tmp = C;
        C = D;
        D = tmp;
    }
    if (A > C && B > D)                 // trivial case
        return true;
    else
    if (D >= B)
        return false;
    else {
        X = sqrt(A * A + B * B);         // outer rectangle's diagonal
        Y = sqrt(C * C + D * D);         // inner rectangle's diagonal
        if (Y < B) // check for marginal conditions
            return true; // the inner rectangle can freely rotate inside
        else
        if (Y > X)
            return false;
        else {
            L = (B - sqrt(Y * Y - A * A)) / 2;
            K = (A - sqrt(Y * Y - B * B)) / 2;
            DMax = sqrt(L * L + K * K);
            if (D >= DMax)
                return false;
            else
                return true;
        }
    }
}

void c2Point(PointEx p1, double r1, PointEx p2, double r2, PointEx &rp1, PointEx &rp2) {
    double a, b, r;
    a = p2.x - p1.x;
    b = p2.y - p1.y;
    r = (a*a + b*b + r1*r1 - r2*r2) / 2;
    if (a == 0 && b != 0) {
        rp1.y = rp2.y = r / b;
        rp1.x = sqrt(r1*r1 - rp1.y*rp1.y);
        rp2.x = -rp1.x;
    } else if (a != 0 && b == 0) {
        rp1.x = rp2.x = r / a;
        rp1.y = sqrt(r1*r1 - rp1.x*rp2.x);
        rp2.y = -rp1.y;
    } else if (a != 0 && b != 0) {
        double delta;
        delta = b*b*r*r - (a*a + b*b)*(r*r - r1*r1*a*a);
        rp1.y = (b*r + sqrt(delta)) / (a*a + b*b);
        rp2.y = (b*r - sqrt(delta)) / (a*a + b*b);
        rp1.x = (r - b*rp1.y) / a;
        rp2.x = (r - b*rp2.y) / a;
    }

    rp1.x += p1.x;
    rp1.y += p1.y;
    rp2.x += p1.x;
    rp2.y += p1.y;
}

int clPoint(PointEx p, double r, double a, double b, double c, PointEx &rp1, PointEx &rp2) {
    int res = 0;

    c = c + a*p.x + b*p.y;
    double tmp;
    if (a == 0 && b != 0) {
        tmp = -c / b;
        if (r*r < tmp*tmp)
            res = 0;
        else if (r*r == tmp*tmp) {
            res = 1;
            rp1.y = tmp;
            rp1.x = 0;
        } else {
            res = 2;
            rp1.y = rp2.y = tmp;
            rp1.x = sqrt(r*r - tmp*tmp);
            rp2.x = -rp1.x;
        }
    } else if (a != 0 && b == 0) {
        tmp = -c / a;
        if (r*r < tmp*tmp)
            res = 0;
        else if (r*r == tmp*tmp) {
            res = 1;
            rp1.x = tmp;
            rp1.y = 0;
        } else {
            res = 2;
            rp1.x = rp2.x = tmp;
            rp1.y = sqrt(r*r - tmp*tmp);
            rp2.y = -rp1.y;
        }
    } else if (a != 0 && b != 0) {
        double delta;
        delta = b*b*c*c - (a*a + b*b)*(c*c - a*a*r*r);
        if (delta < 0)
            res = 0;
        else if (delta == 0) {
            res = 1;
            rp1.y = -b*c / (a*a + b*b);
            rp1.x = (-c - b*rp1.y) / a;
        } else {
            res = 2;
            rp1.y = (-b*c + sqrt(delta)) / (a*a + b*b);
            rp2.y = (-b*c - sqrt(delta)) / (a*a + b*b);
            rp1.x = (-c - b*rp1.y) / a;
            rp2.x = (-c - b*rp2.y) / a;
        }
    }
    rp1.x += p.x;
    rp1.y += p.y;
    rp2.x += p.x;
    rp2.y += p.y;
    return res;
}

void inCircle(PointEx p1, PointEx p2, PointEx p3, PointEx &rp, double &r) {
    double dx31, dy31, dx21, dy21, d31, d21, a1, b1, c1;
    dx31 = p3.x - p1.x;
    dy31 = p3.y - p1.y;
    dx21 = p2.x - p1.x;
    dy21 = p2.y - p1.y;

    d31 = sqrt(dx31*dx31 + dy31*dy31);
    d21 = sqrt(dx21*dx21 + dy21*dy21);
    a1 = dx31*d21 - dx21*d31;
    b1 = dy31*d21 - dy21*d31;
    c1 = a1*p1.x + b1*p1.y;

    double dx32, dy32, dx12, dy12, d32, d12, a2, b2, c2;
    dx32 = p3.x - p2.x;
    dy32 = p3.y - p2.y;
    dx12 = -dx21;
    dy12 = -dy21;

    d32 = sqrt(dx32*dx32 + dy32*dy32);
    d12 = d21;
    a2 = dx12*d32 - dx32*d12;
    b2 = dy12*d32 - dy32*d12;
    c2 = a2*p2.x + b2*p2.y;

    rp.x = (c1*b2 - c2*b1) / (a1*b2 - a2*b1);
    rp.y = (c2*a1 - c1*a2) / (a1*b2 - a2*b1);
    r = fabs(dy21*rp.x - dx21*rp.y + dx21*p1.y - dy21*p1.x) / d21;
}

void cutPoint(PointEx p, double r, PointEx sp, PointEx &rp1, PointEx &rp2) {
    PointEx p2;
    p2.x = (p.x + sp.x) / 2;
    p2.y = (p.y + sp.y) / 2;

    double dx2, dy2, r2;
    dx2 = p2.x - p.x;
    dy2 = p2.y - p.y;
    r2 = sqrt(dx2*dx2 + dy2*dy2);
    c2Point(p, r, p2, r2, rp1, rp2);
}

int rotat(LineSegment l1, LineSegment l2) {
    double dx1, dx2, dy1, dy2;
    dx1 = l1.startPoint.x - l1.endPoint.x;
    dy1 = l1.startPoint.y - l1.endPoint.y;
    dx2 = l2.startPoint.x - l2.endPoint.x;
    dy2 = l2.startPoint.y - l2.endPoint.y;

    double d;
    d = dx1*dy2 - dx2*dy1;
    if (d == 0)
        return 0;
    else if (d > 0)
        return -1;
    else
        return 1;
}

int IsPointInBoundingBox(int x1, int y1, int x2, int y2, int px, int py)
{
	int left, top, right, bottom; // Bounding Box For Line Segment
	// For Bounding Box
	if (x1 < x2)
	{
		left = x1;
		right = x2;
	}
	else {
		left = x2;
		right = x1;
	}

	if (y1 < y2)
	{
		top = y1;
		bottom = y2;
	}
	else {
		top = y1;
		bottom = y2;
	}

	if ((px + 0.01) >= left && (px - 0.01) <= right &&
		(py + 0.01) >= top && (py - 0.01) <= bottom) {
		return 1;
	}
	else {
		return 0;
	}
}

/*
int LineSegmentIntersection(int l1x1, int l1y1, int l1x2, int l1y2,
	int l2x1, int l2y1, int l2x2, int l2y2,
	float *m1, float *c1, float *m2, float *c2,
	int* intersection_X, int* intersection_Y)
{
	int dx, dy;
	dx = l1x2 - l1x1;
	dy = l1y2 - l1y1;

	*m1 = dy / dx;
	// y = mx + c
	// intercept c = y - mx

	*c1 = l1y1 - *m1 * l1x1; // which is same as y2 - slope * x2


	dx = l2x2 - l2x1;
	dy = l2y2 - l2y1;

	*m2 = dy / dx;
	// y = mx + c
	// intercept c = y - mx

	*c2 = l2y1 - *m2 * l2x1; // which is same as y2 - slope * x2


	if ((*m1 - *m2) == 0)
		return 0;
	else
	{
		*intersection_X = (*c2 - *c1) / (*m1 - *m2);
		*intersection_Y = *m1 * *intersection_X + *c1;
	}

	if (IsPointInBoundingBox(l1x1, l1y1, l1x2, l1y2, *intersection_X, *intersection_Y) == 1 &&
		IsPointInBoundingBox(l2x1, l2y1, l2x2, l2y2, *intersection_X, *intersection_Y) == 1)
	{
		return 1;
	}
	else
		return 0;
}
*/