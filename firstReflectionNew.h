
#pragma once
#include <iostream>
#include<vector>
#include <windows.h>
#include <math.h>
#include "BuildingPoint.h"
#include "line.h"
using namespace std;

//全局变量最好不要定义，用类，所以定义一个边类
/*struct TwoDimPoint{
	float x;
	float y;
};
 struct line
{
	TwoDimPoint point1;
	TwoDimPoint point2;
};
 vector<TwoDimPoint> polyPoint;

 */

class FirstReflection
{
	public:
		vector<TwoDimPoint> polyPoint;
		float crossX;
		float crossY;
		float crossZ;
		TwoDimPoint	refPolyPoint[2];//反射点所在平面对应的线的两个端点
		int buildingCrossFlag;
		int roofFlag;
		void buildingCross(float shootingStartX,float shootingStartY,float shootingStartZ,float shootingDirectionX,float shootingDirectionY,float shootingDirectionZ,vector<BuildingPoint>BPoint,float buildingHeight);
		
	private:
		TwoDimPoint getCross(line line1, line line2);
		//int vertex_triangle(TwoDimPoint pa, TwoDimPoint pb, TwoDimPoint pc, TwoDimPoint vertex0);	
		//int vertex_polygon(TwoDimPoint vertex0);                               //把多边形分解成多个三角形		
		int vertexInside(TwoDimPoint vertex);//判断点是否在多边形内
};

