#pragma once
#include"picture.h"
#include "ShootingRay.h"
#include "rayPath.h"
#include "rayManage.h"
#include"gridPower.h"
#include "GridPowerResult.h"
#include"empiricalFormula.h"
#include"BuildingPoint.h"
class basestationShooting
{
public:
	 void basestationOperate(int maxGridx,int maxGridy,float shootingInterval,float baseFrequence,float basePositionx,
		 float basePositiony,float basePositionz,float fangWeiJiao,float xiaQingJiao,float shuipingRange,float shuizhiRange,int baseStationNumber,float kuiLength,vector<vector<BuildingPoint>> BX,vector<float> HX);
	 //网格水平最大编号，垂直最大编号，射线间隔，基站频率，基站位置，方位角，下倾角，水平辐射范围，竖直辐射范围
};

