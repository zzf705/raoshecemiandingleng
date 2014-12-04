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
	int shootingNumber;//������ߵ���Ŀ
	/*void shootingGain(float directionAngle,float downInclineAngle,float horizonDivision,float verticalDivision);*/
	void shootingGainAllDirection(float directionAngle,float downInclineAngle,float horizonRange, float verticalRange,
		float horizonDivision,float verticalDivision);//���߷�����ȫ���
	void GetRecord(int id);
	void shuzhiDiffractionShootingRay(float pointx,float pointy,float pointz,vector<BuildingPoint> oneBPoint,
		float incidentDirectina,float incidentDirectinb,float incidentDirectinc,float shootingInterval);//��ֱ�����߷���
	void GetDiffractionRecord(int id);//���������߷�����еõ����ߵķ���ϵ��
	void shuiPingDiffractionShootingRay(float pointx,float pointy,float pointz,float buildingHeight,
		float incidentDirectina,float incidentDirectinb,float incidentDirectinc,float shootingInterval,float vectorx,float vectory,float vectorz,
		float point1x,float point1y,float point2x,float point2y);//ˮƽ�ⷢ�������λ�����꣬������������ߵķ������߼������ķ�������ָ��������,��Ķ˵�����

};

