#include <iostream>
#include <cmath>
#include <algorithm>
#include <fstream>
using namespace std;
#define NO_LIMITTED 1000000;


namespace lzw_closed_point_pair {
	//point(x, y)
	typedef struct Point
	{
		float x, y;		
	}Point;

	static float Distance(Point a, Point b)
	{
		return sqrt((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y));
	}

	static bool CompareX(Point a, Point b)
	{
		return a.x < b.x;//if a.x is smaller, make a front
	}

	static float ClosestPoints(Point points[], int length, Point &a, Point &b)
	{
		float distance;//the shortest distance
		float d1, d2;//each shortest distance after splited
		Point a1, a2, b1, b2;
		int i = 0, j = 0, k = 0;
		if (length < 2)//less than 2 points in the point-set
		{
			return NO_LIMITTED;//cannot reach out
		}
		else if (length == 2)
		{
			a = points[0];
			b = points[1];
			distance = Distance(points[0], points[1]);
		}
		else
		{
			Point *pts1 = new Point[length];
			Point *pts2 = new Point[length];

			sort(points, points + length, CompareX);
			float middleX = points[(length - 1) / 2].x;
			for (i = 0; i < length / 2; i++)
			{
				pts1[i] = points[i];
			}
			for (int j = 0, i = length / 2; i < length; i++)
			{
				pts2[j++] = points[i];
			}
			d1 = ClosestPoints(pts1, length / 2, a1, b1);
			d2 = ClosestPoints(pts2, length - length / 2, a2, b2);
			if (d1 < d2)
			{
				distance = d1; a = a1, b = b1;
			}
			else { distance = d2; a = a2; b = b2; }

			Point *pts3 = new Point[length];
			for (k = 0, i = 0; i < length; i++)
			{
				if (abs(points[i].x - middleX) <= distance)
				{
					pts3[k++] = points[i];
				}
			}
			for (i = 0; i < k; i++)
			{
				for (j = i + 1; j < i + 7 && j < k; j++)
				{
					if (Distance(pts3[i], pts3[j]) < distance)
					{
						distance = Distance(pts3[i], pts3[j]);
						a = pts3[i];
						b = pts3[j];
					}
				}
			}
		}
		return distance;
	}
}