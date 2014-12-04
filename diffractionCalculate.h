#pragma once
#include"Building.h"
#include "ShootingRay.h"
#include "rayPath.h"
#include "rayManage.h"
#include"gridPower.h"
#include "GridPowerResult.h"
#include"BuildingPoint.h"
#include<cmath>
class diffractionCalculate
{
public:
	diffractionCalculate(void);
	~diffractionCalculate(void);
	int shuzhiFlag;//竖直棱发生绕射的标志位，1表示发生
	int shuipingFlag;//水平棱发生绕射的标志位，1表示发生
	int diffractionFlag;//是否发生绕射的标志位,1代表发射
	int roofLengdiffractionFlag;//顶棱是否发生绕射的标志位
	float lengPoint1x,lengPoint1y,lengPoint2x,lengPoint2y;//代表顶棱发生绕射时棱端点的坐标值
	float shuzhiLengPositionx,shuzhiLengPositiony;//发生竖直棱绕射时，反射点位于棱边，实际计算时绕射点位于棱上,这两个参数代表绕射点在棱上的位置
	float shuipingLengPositionx,shuipingLengPositiony,shuipingLengPositionz;//水平棱发生绕射时绕射点的位置
	float shuipingLengNormalVectorx,shuipingLengNormalVectory,shuipingLengNormalVectorz;//水平棱指向建筑物外的法向量




	void decideDiffractionOperate(float pointx,float pointy,float pointz,float buildingHeight,
		float incidentDirectina,float incidentDirectinb,float incidentDirectinc,float point1x,float point1y,float point2x,float point2y);
		//参数代表的分别是绕射点的坐标，发射绕射的建筑物信息（建筑物折点，高度），入射射线的方向，绕射点所在面在水平面投影对应线段的端点坐标
	void shuzhiDiffractionOperate(int maxGridx,int maxGridy,float shootingInterval,float baseFrequence,float basePositionx,
		 float basePositiony,float basePositionz,int baseStationNumber,float kuiLength,float incidentDirectina,float incidentDirectinb,float incidentDirectinc,vector<BuildingPoint> oneBPoint,float buildingHeight,float shootingGain,float beforeLength,float beforeCoefficient,vector<vector<BuildingPoint>> BX,vector<float> HX);
	//发生竖直棱绕射时执行的函数，基站的点实际上代表的是绕射点的坐标，然后是绕射射线的入射方向，绕射点所在建筑物的折点列表，建筑物的高度，倒数第3第4两个参数代表的是绕射前走的路径长度和反射系数，最后是所有建筑物的折点列表，建筑物的高度列表
	int decideInsidePolygon(float pointx,float pointy,vector<BuildingPoint> BPoint);//用叉积判断点是否在多边形内，返回值为1的话代表在多边形内

	void shupingDiffractionOperate(int maxGridx,int maxGridy,float shootingInterval,float baseFrequence,float basePositionx,
		float basePositiony,float basePositionz,int baseStationNumber,float kuiLength,float incidentDirectina,float incidentDirectinb,float incidentDirectinc,vector<BuildingPoint> oneBPoint,float buildingHeight,float shootingGain,float beforeLength,float beforeCoefficient,float roofLengPoint1x,
		float roofLengPoint1y,float roofLengPoint2x,float roofLengPoint2y,float vectorx,float vectory,float vectorz,vector<vector<BuildingPoint>> BX,vector<float> HX);//水平棱绕射, oneBPoint代表发射绕射的建筑物的折点列表，buildingHeight代表绕射建筑物的高度，除去最后两个参数，最后7个参数代表发生绕射的棱的两个端点坐标,水平棱的法向量，指向建筑物外，最后两个参数是建筑物的折点列表，建筑物的高度列表
	void decideRoofLengDiffraction(float pointx,float pointy, vector<BuildingPoint> oneBPoint,float buildingHeight);//用来判断射线落到顶面是否会发生绕射，




};

