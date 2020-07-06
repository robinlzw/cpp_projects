#ifndef _GRAPHBASE_lzw_H_
#define _GRAPHBASE_lzw_H_


/* 常用的常量定义 */
const double INF = 1E200;
const double EP = 1E-10;
const int MAXV = 300;
const double PI = 3.14159265358979323846;

//点
struct PointEx {
	double x;
	double y;
	PointEx(double a = 0, double b = 0) {
		x = a;
		y = b;
	}
};

//线段
struct LineSegment {
	PointEx startPoint;
	PointEx endPoint;
	LineSegment(PointEx a, PointEx b) {
		startPoint = a;
		endPoint = b;
	}
	LineSegment() {
	}
};

//直线
//直线的解析方程 a*x+b*y+c=0  为统一表示，约定 a >= 0
struct Beeline
{
	double a;
	double b;
	double c;
	Beeline(double d1 = 1, double d2 = -1, double d3 = 0) {
		a = d1; b = d2; c = d3;
	}
};

/************************************************************************/
/* 点的基本运算                                                           */
/************************************************************************/
//1.计算两点之间的坐标
double dist(PointEx p1, PointEx p2);
//2.判断两个点是否重合
bool equalPoint(PointEx p1, PointEx p2);

//3.r=multiply(sp,ep,op),得到(sp->op)和(ep->op)的叉积
//r > 0：ep在矢量opsp的逆时针方向；
//r = 0：opspep三点共线；
//r < 0：ep在矢量opsp的顺时针方向
double multiply(PointEx sp, PointEx ep, PointEx op);

/*4.r=dotmultiply(p1,p2,op),得到矢量(p1-op)和(p2-op)的点积，如果两个矢量都非零矢量
r<0：两矢量夹角为锐角；
r=0：两矢量夹角为直角；
r>0：两矢量夹角为钝角*/
double dotMultiply(PointEx p1, PointEx p2, PointEx p0);

/*5.判断点p是否在线段l上
条件：(p在线段l所在的直线上) && (点p在以线段l为对角线的矩形内)*/
bool online(LineSegment l, PointEx p);

//6.返回点p以点o为圆心逆时针旋转d(单位：弧度)后所在的位置
PointEx rotate(PointEx o, double d, PointEx p);

/*7. 返回顶角在o点，起始边为os，终止边为oe的夹角(单位：弧度)
角度小于pi，返回正值
角度大于pi，返回负值
可以用于求线段之间的夹角
原理：
r = dotmultiply(s,e,o) / (dist(o,s)*dist(o,e))
r'= multiply(s,e,o)

r >= 1	angle = 0;
r <= -1	angle = -PI
-1<r<1 && r'>0	angle = arccos(r)
-1<r<1 && r'<=0	angle = -arccos(r)
*/
double angle(PointEx o, PointEx s, PointEx e);


/************************************************************************/
/* 线段及直线的基本运算                                         */
/************************************************************************/

/* 判断点与线段的关系,用途很广泛
本函数是根据下面的公式写的，P是点C到线段AB所在直线的垂足

AC dot AB
r =     ---------
||AB||^2
(Cx-Ax)(Bx-Ax) + (Cy-Ay)(By-Ay)
= -------------------------------
L^2

r has the following meaning:

r=0      P = A
r=1      P = B
r<0		 P is on the backward extension of AB
r>1      P is on the forward extension of AB
0<r<1	 P is interior to AB
*/
double relation(PointEx p, LineSegment l);

// 求点C到线段AB所在直线的垂足 P
PointEx perpendicular(PointEx p, LineSegment l);

//过线段一点并且垂直于线段的直线
Beeline perpendicularInSegment(LineSegment&l, PointEx&p);

/* 求点p到线段l的最短距离,并返回线段上距该点最近的点np
注意：np是线段l上到点p最近的点，不一定是垂足 */
double pToLinesegDist(PointEx p, LineSegment l, PointEx &np);

// 求点p到线段l所在直线的距离,请注意本函数与上个函数的区别
double pToLDist(PointEx p, LineSegment l);

/* 计算点到折线集的最近距离,并返回最近点.
注意：调用的是ptolineseg()函数 */
double pToPointSet(int vcount, PointEx pointset[], PointEx p, PointEx &q);

/* 判断圆是否在多边形内.ptolineseg()函数的应用2 */
bool circleInsidePolygon(int vcount, PointEx center, double radius, PointEx polygon[]);

/* 返回两个矢量l1和l2的夹角的余弦(-1 --- 1)注意：如果想从余弦求夹角的话，注意反余弦函数的定义域是从 0到pi */
double cosine(LineSegment l1, LineSegment l2);

// 返回线段l1与l2之间的夹角 单位：弧度 范围(-pi，pi)
double lsAngle(LineSegment l1, LineSegment l2);

// 如果线段u和v相交(包括相交在端点处)时，返回true
//
//判断P1P2跨立Q1Q2的依据是：( P1 - Q1 ) × ( Q2 - Q1 ) * ( Q2 - Q1 ) × ( P2 - Q1 ) >= 0。
//判断Q1Q2跨立P1P2的依据是：( Q1 - P1 ) × ( P2 - P1 ) * ( P2 - P1 ) × ( Q2 - P1 ) >= 0。
bool intersect(LineSegment u, LineSegment v);

//  (线段u和v相交)&&(交点不是双方的端点) 时返回true
bool intersectA(LineSegment u, LineSegment v);

// 线段v所在直线与线段u相交时返回true；方法：判断线段u是否跨立线段v
bool intersectL(LineSegment u, LineSegment v);

// 根据已知两点坐标，求过这两点的直线解析方程： a*x+b*y+c = 0  (a >= 0)
Beeline makeLine(PointEx p1, PointEx p2);

// 根据直线解析方程返回直线的斜率k,水平线返回 0,竖直线返回 1e200
double slope(Beeline l);

// 返回直线的倾斜角alpha ( 0 - pi)
double alpha(Beeline l);

// 求点p关于直线l的对称点
PointEx symmetry(Beeline l, PointEx p);

// 如果两条直线 l1(a1*x+b1*y+c1 = 0), l2(a2*x+b2*y+c2 = 0)相交，返回true，且返回交点p
bool lineIntersect(Beeline l1, Beeline l2, PointEx &p);

// 如果线段l1和l2相交，返回true且交点由(inter)返回，否则返回false
bool intersection(LineSegment l1, LineSegment l2, PointEx &inter);

/************************************************************************/
/* 多边形常用算法
/************************************************************************/
//如果无特别说明，输入多边形顶点要求按逆时针排列


/*
返回值：输入的多边形是简单多边形，返回true
要 求：输入顶点序列按逆时针排序
说 明：简单多边形定义：
1：循环排序中相邻线段对的交是他们之间共有的单个点
2：不相邻的线段不相交
本程序默认第一个条件已经满足
*/
bool isSimple(int vcount, PointEx polygon[]);

// 返回值：按输入顺序返回多边形顶点的凸凹性判断，bc[i]=1,iff:第i个顶点是凸顶点
void checkConvex(int vcount, PointEx polygon[], bool bc[]);

// 返回值：多边形polygon是凸多边形时，返回true
bool isConvex(int vcount, PointEx polygon[]);

// 返回多边形面积(signed)；输入顶点按逆时针排列时，返回正值；否则返回负值
double areaOfPolygon(int vcount, PointEx polygon[]);

// 如果输入顶点按逆时针排列，返回true
bool isConterClock(int vcount, PointEx polygon[]);

// 另一种判断多边形顶点排列方向的方法
bool isCcwize(int vcount, PointEx polygon[]);

/********************************************************************************************
射线法判断点q与多边形polygon的位置关系，要求polygon为简单多边形，顶点逆时针排列
如果点在多边形内：   返回0
如果点在多边形边上： 返回1
如果点在多边形外：	返回2
*********************************************************************************************/
int insidePolygon(int vcount, PointEx Polygon[], PointEx q);

//点q是凸多边形polygon内时，返回true；注意：多边形polygon一定要是凸多边形
bool insideConvexPolygon(int vcount, PointEx polygon[], PointEx q); // 可用于三角形！

/**********************************************
寻找凸包的graham 扫描法
PointSet为输入的点集；
ch为输出的凸包上的点集，按照逆时针方向排列;
n为PointSet中的点的数目
len为输出的凸包上的点的个数
**********************************************/
void grahamScan(PointEx PointSet[], PointEx ch[], int n, int &len);

// 卷包裹法求点集凸壳，参数说明同graham算法
void convexClosure(PointEx PointSet[], PointEx ch[], int n, int &len);
/*********************************************************************************************
判断线段是否在简单多边形内(注意：如果多边形是凸多边形，下面的算法可以化简)
必要条件一：线段的两个端点都在多边形内；
必要条件二：线段和多边形的所有边都不内交；
用途：	1. 判断折线是否在简单多边形内
2. 判断简单多边形是否在另一个简单多边形内
**********************************************************************************************/
bool linesegInsidePolygon(int vcount, PointEx polygon[], LineSegment l);

/*********************************************************************************************
求任意简单多边形polygon的重心
需要调用下面几个函数：
void addPosPart(); 增加右边区域的面积
void addNegPart(); 增加左边区域的面积
void addRegion(); 增加区域面积
在使用该程序时，如果把xtr,ytr,wtr,xtl,ytl,wtl设成全局变量就可以使这些函数的形式得到化简,
但要注意函数的声明和调用要做相应变化
**********************************************************************************************/
void addPosPart(double x, double y, double w, double &xtr, double &ytr, double &wtr);
void addNegPart(double x, double y, double w, double &xtl, double &ytl, double &wtl);
void addRegion(double x1, double y1, double x2, double y2, double &xtr, double &ytr,
	double &wtr, double &xtl, double &ytl, double &wtl);


PointEx cgSimple(int vcount, PointEx polygon[]);

// 求凸多边形的重心,要求输入多边形按逆时针排序
PointEx gravityCenter(int vcount, PointEx polygon[]);


/************************************************
给定一简单多边形，找出一个肯定在该多边形内的点
定理1	：每个多边形至少有一个凸顶点
定理2	：顶点数>=4的简单多边形至少有一条对角线
结论	： x坐标最大，最小的点肯定是凸顶点
y坐标最大，最小的点肯定是凸顶点
************************************************/
PointEx aPointInsidepoly(int vcount, PointEx polygon[]);

/***********************************************************************************************
求从多边形外一点p出发到一个简单多边形的切线,如果存在返回切点,其中rp点是右切点,lp是左切点
注意：p点一定要在多边形外 ,输入顶点序列是逆时针排列
原 理：	如果点在多边形内肯定无切线;凸多边形有唯一的两个切点,凹多边形就可能有多于两个的切点;
如果polygon是凸多边形，切点只有两个只要找到就可以,可以化简此算法
如果是凹多边形还有一种算法可以求解:先求凹多边形的凸包,然后求凸包的切线
/***********************************************************************************************/
void pointTangentpoly(int vcount, PointEx polygon[], PointEx p, PointEx &rp, PointEx &lp);

// 如果多边形polygon的核存在，返回true，返回核上的一点p.顶点按逆时针方向输入
bool coreExist(int vcount, PointEx polygon[], PointEx &p);


/************************************************************************/
/* 圆的基本运算                                                                     */
/************************************************************************/
/******************************************************************************
返回值	： 点p在圆内(包括边界)时，返回true
用途	： 因为圆为凸集，所以判断点集，折线，多边形是否在圆内时，
只需要逐一判断点是否在圆内即可。
*******************************************************************************/
bool pointInCircle(PointEx o, double r, PointEx p);

/******************************************************************************
用 途	：求不共线的三点确定一个圆
输 入	：三个点p1,p2,p3
返回值	：如果三点共线，返回false；反之，返回true。圆心由q返回，半径由r返回
*******************************************************************************/
bool coCircle(PointEx p1, PointEx p2, PointEx p3, PointEx &q, double &r);

/************************************************************************/
/* 矩形的基本运算                                                      */
/************************************************************************/
/*
说明：因为矩形的特殊性，常用算法可以化简：
1.判断矩形是否包含点
只要判断该点的横坐标和纵坐标是否夹在矩形的左右边和上下边之间。
2.判断线段、折线、多边形是否在矩形中
因为矩形是个凸集，所以只要判断所有端点是否都在矩形中就可以了。
3.判断圆是否在矩形中
圆在矩形中的充要条件是：圆心在矩形中且圆的半径小于等于圆心到矩形四边的距离的最小值。
*/
// 已知矩形的三个顶点(a,b,c)，计算第四个顶点d的坐标. 注意：已知的三个顶点可以是无序的
PointEx rect4th(PointEx a, PointEx b, PointEx c);

//两圆关系：
/* 两圆：
相离： return 1；
外切： return 2；
相交： return 3；
内切： return 4；
内含： return 5；
*/
int circleRelation(PointEx p1, double r1, PointEx p2, double r2);

//判断圆是否在矩形内：
// 判定圆是否在矩形内，是就返回true（设矩形水平，且其四个顶点由左上开始按顺时针排列）
// 调用ptoldist函数，在第4页
bool circleRecRelation(PointEx pc, double r, PointEx pr1, PointEx pr2, PointEx pr3, PointEx pr4);

//点到平面的距离：
//点到平面的距离,平面用一般式表示ax+by+cz+d=0
double p2PlaneDist(double x, double y, double z, double a, double b, double c, double d);

//点是否在直线同侧：
//两个点是否在直线同侧，是则返回true
bool sameSide(PointEx p1, PointEx p2, Beeline line);

//镜面反射线：
// 已知入射线、镜面，求反射线。
// a1,b1,c1为镜面直线方程(a1 x + b1 y + c1 = 0 ,下同)系数;
//a2,b2,c2为入射光直线方程系数;
//a,b,c为反射光直线方程系数.
// 光是有方向的，使用时注意：入射光向量:<-b2,a2>；反射光向量:<b,-a>.
// 不要忘记结果中可能会有"negative zeros"
void reflect(double a1, double b1, double c1, double a2, double b2, double c2, double &a, double &b, double &c);

//矩形包含：
// 矩形2（C，D）是否在1（A，B）内
bool r2Inr1(double A, double B, double C, double D);

//两圆交点：
// 两圆已经相交（相切）
void  c2Point(PointEx p1, double r1, PointEx p2, double r2, PointEx &rp1, PointEx &rp2);

//圆和直线关系：
//0----相离 1----相切 2----相交
int clPoint(PointEx p, double r, double a, double b, double c, PointEx &rp1, PointEx &rp2);

//内切圆：
void inCircle(PointEx p1, PointEx p2, PointEx p3, PointEx &rp, double &r);

//求切点：
// p---圆心坐标， r---圆半径， sp---圆外一点， rp1,rp2---切点坐标
void cutPoint(PointEx p, double r, PointEx sp, PointEx &rp1, PointEx &rp2);

//线段的左右旋：
/* l2在l1的左/右方向（l1为基准线）
返回	0	： 重合；
返回	1	： 右旋；
返回	–1 ： 左旋；
*/
int rotat(LineSegment l1, LineSegment l2);



int IsPointInBoundingBox(int x1, int y1, int x2, int y2, int px, int py);

/*
int LineIntersection(int l1x1, int l1y1, int l1x2, int l1y2,
	int l2x1, int l2y1, int l2x2, int l2y2,
	int *m1, int *c1, int *m2, int *c2,
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

}
*/

/*
int LineSegmentIntersection(int l1x1, int l1y1, int l1x2, int l1y2,
	int l2x1, int l2y1, int l2x2, int l2y2,
	float *m1, float *c1, float *m2, float *c2,
	int* intersection_X, int* intersection_Y);
	*/


#endif // !_GRAPHBASE_H_
