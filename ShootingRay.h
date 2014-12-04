#pragma once
#include<iostream>
#include <sstream>
#include <string>
#include<math.h>
#include"Building.h"
#include"diffractionCalculate.h"
using namespace std;
#import "C:\\program files\\common files\\system\\ado\\msado15.dll"  no_namespace rename("EOF", "adoEOF")

#define pi 3.14



class ShootingRay
{
public:
	ShootingRay(void);
	~ShootingRay(void);

	float Rx,Ry,Rz,Rgain;
	int shootingNumber;//获得射线的数目
	/*void shootingGain(float directionAngle,float downInclineAngle,float horizonDivision,float verticalDivision);*/
	void shootingGainAllDirection(float directionAngle,float downInclineAngle,float horizonRange, float verticalRange,
		float horizonDivision,float verticalDivision);//射线发射是全向的
	void GetRecord(int id);
	void shuzhiDiffractionShootingRay(float pointx,float pointy,float pointz,vector<BuildingPoint> oneBPoint,
		float incidentDirectina,float incidentDirectinb,float incidentDirectinc,float shootingInterval);//竖直棱射线发射
	void GetDiffractionRecord(int id);//从绕射射线发射表中得到射线的方向系数
	void shuiPingDiffractionShootingRay(float pointx,float pointy,float pointz,float buildingHeight,
		float incidentDirectina,float incidentDirectinb,float incidentDirectinc,float shootingInterval,float vectorx,float vectory,float vectorz,
		float point1x,float point1y,float point2x,float point2y);//水平棱发生绕射的位置坐标，建筑物，入射射线的方向，射线间隔，棱的法向量，指向建筑物外,棱的端点坐标

};

