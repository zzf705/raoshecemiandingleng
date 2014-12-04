#pragma once
#include"rayInit.h"
#include"findGrid.h"
#include"Grid.h"
#include"Building.h"
#include "firstReflectionNew.h"
#include"complex.h"
#include<cmath>
#include"BuildingPoint.h"
#include<iostream>
using namespace std;

/*struct TwoDimPointZhang
{
	double x;
	double y;
};
*/

class  rayManage
{
public:
	
	float finalCrossPointx, finalCrossPointy, finalCrossPointz; //与建筑物求交模块后得到的最终的交点
	int finalCrossFlag;//判断最终是否有交点，1表示有，0表示无
	int finalCrossPosition;//最终的交点标志位，0说明交点在建筑物上，1说明是在地面
	int finalCrossBuildingname; //与建筑物求交模块后得到的最终的交点所在的材质,0表示地面，不为0，为编号的话表示建筑物编号，可以用来查建筑物材质
	int finalCrossBuildingPosition;//0表示交点在侧面，1表示交点在顶面
	int stop;//标志位，判断是否停止跟踪
	float finalRayLength;//最终求得的射线长度
	int gridm[1000],gridn[1000];//考虑无交点的情况，在地图范围内搜索的网格
	int gridNumberTrue;//实际网格的数目，考虑到实际地图的范围，网格是有限的
	int gridTruem[1000], gridTruen[1000];//考虑有交点的情况，在地图范围内搜索的网格
	int gridNumberStopCross;//考虑有交点的情况,到交点就停止记录，实际网格的数目，考虑到实际地图的范围，网格是有限的
	


	struct TwoDimPointZhang
	{
		double x;
		double y;
	};
	TwoDimPointZhang twoPoint[2];//如果交点落在建筑物上对应的边的两个点，为了求反射射线,注意调用求建筑物的反射方向系数时要twoPoint[0]，twoPoint[1]这样调用
	float groundRefDirectionA,groundRefDirectionB,groundRefDirectionC;//地面的反射方向
	float groundRefAngleCos;//地面的入射角的余弦值
	//float groundRefCofficient;//地面的方向系数
	float buildingRefDirectionA,buildingRefDirectionB,buildingRefDirectionC;//建筑物的反射方向
	float buildingRefAngleCos;//建筑物入射角的余弦值
	//float buildingRefCofficient;//建筑物的反射系数
public:
	void findFinalCrossPoint(float startPointx,float startPointy,float startPointz,float startDirectiona,float startDirectionb,float startDirectionc,int maxGridx,int maxGridy,float coveringDistance,vector<vector<BuildingPoint>> BY,vector<float> HY);//求出最后的交点，得到一些参量,输入参数的最后两个指的是地图的水平网格大小和垂直网格大小
	void findGroundRefDirection( float shootingStartX,float shootingStartY,float shootingStartZ,float shootingDirectionA,float shootingDirectionB,float shootingDirectionC);//求地面的反射方向系数，函数中已经求出入射角的余弦值
	float findGroundRefCofficient(float cosAngle,float frequence);//求地面的反射系数的模值，地面的反射系数暂时和建筑物的材质是一样的，最后要根据参数进行调试
	complex findGroundComplexCofficient(float cosAngle,float frequence);//求地面的反射系数,是个复数，是有相位的


	void findBuildingRefDirection( float shootingStartX,float shootingStartY,float shootingStartZ,float shootingFinalX,float shootingFinalY,float shootingFinalZ,float startDirectionA,float startDirectionB,float startDirectionC,TwoDimPointZhang refPolyPoint0,TwoDimPointZhang refPolyPoint1);//求建筑物的反射方向系数，函数中已经求出入射角的余弦值
	float findBuildingRefCofficient(float cosAngle,float frequence);//求建筑物的反射系数的模值
	complex findBuildingComplexCofficient(float cosAngle,float frequence);//求建筑物的反射系数,是个复数，是有相位的
	int findPathStop( float pathDistance,float antennaGain,float frequence ); //第一次根据距离判断射线的能量是否降到某一阈值，0表示不停止，1表示停止
	int findPathRefStop( float pathDistance,float antennaGain,float reflectCofficient,float frequence); //根据距离和反射系数判断射线的能量是否降到某一阈值，0表示不停止，1表示停止
	float findPointToLineDistance(float shootingStartx,float shootingStarty,float shootingStartz,float shootingDirectina,float shootingDirectinb,float shootingDirectinc,float pointx,float pointy,float pointz);//求网格中心点上1.5m到直线的距离，输入射线的起点和方向，和网格中心点的坐标
	float findGridCenterxy(int gridNumber);//输入网格编号，求出中心点的坐标，水平和垂直是一样的
	float findShootingLineLength(float shootingStartx,float shootingStarty,float shootingStartz,float shootingDirectina,float shootingDirectinb,float shootingDirectinc,float pointx,float pointy,float pointz);//求点到直线的距离后，需要求射线的长度






};
