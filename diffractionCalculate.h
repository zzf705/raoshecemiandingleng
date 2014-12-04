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
	int shuzhiFlag;//��ֱ�ⷢ������ı�־λ��1��ʾ����
	int shuipingFlag;//ˮƽ�ⷢ������ı�־λ��1��ʾ����
	int diffractionFlag;//�Ƿ�������ı�־λ,1������
	int roofLengdiffractionFlag;//�����Ƿ�������ı�־λ
	float lengPoint1x,lengPoint1y,lengPoint2x,lengPoint2y;//�����ⷢ������ʱ��˵������ֵ
	float shuzhiLengPositionx,shuzhiLengPositiony;//������ֱ������ʱ�������λ����ߣ�ʵ�ʼ���ʱ�����λ������,������������������������ϵ�λ��
	float shuipingLengPositionx,shuipingLengPositiony,shuipingLengPositionz;//ˮƽ�ⷢ������ʱ������λ��
	float shuipingLengNormalVectorx,shuipingLengNormalVectory,shuipingLengNormalVectorz;//ˮƽ��ָ��������ķ�����




	void decideDiffractionOperate(float pointx,float pointy,float pointz,float buildingHeight,
		float incidentDirectina,float incidentDirectinb,float incidentDirectinc,float point1x,float point1y,float point2x,float point2y);
		//��������ķֱ������������꣬��������Ľ�������Ϣ���������۵㣬�߶ȣ����������ߵķ����������������ˮƽ��ͶӰ��Ӧ�߶εĶ˵�����
	void shuzhiDiffractionOperate(int maxGridx,int maxGridy,float shootingInterval,float baseFrequence,float basePositionx,
		 float basePositiony,float basePositionz,int baseStationNumber,float kuiLength,float incidentDirectina,float incidentDirectinb,float incidentDirectinc,vector<BuildingPoint> oneBPoint,float buildingHeight,float shootingGain,float beforeLength,float beforeCoefficient,vector<vector<BuildingPoint>> BX,vector<float> HX);
	//������ֱ������ʱִ�еĺ�������վ�ĵ�ʵ���ϴ���������������꣬Ȼ�����������ߵ����䷽����������ڽ�������۵��б�������ĸ߶ȣ�������3��4�������������������ǰ�ߵ�·�����Ⱥͷ���ϵ������������н�������۵��б�������ĸ߶��б�
	int decideInsidePolygon(float pointx,float pointy,vector<BuildingPoint> BPoint);//�ò���жϵ��Ƿ��ڶ�����ڣ�����ֵΪ1�Ļ������ڶ������

	void shupingDiffractionOperate(int maxGridx,int maxGridy,float shootingInterval,float baseFrequence,float basePositionx,
		float basePositiony,float basePositionz,int baseStationNumber,float kuiLength,float incidentDirectina,float incidentDirectinb,float incidentDirectinc,vector<BuildingPoint> oneBPoint,float buildingHeight,float shootingGain,float beforeLength,float beforeCoefficient,float roofLengPoint1x,
		float roofLengPoint1y,float roofLengPoint2x,float roofLengPoint2y,float vectorx,float vectory,float vectorz,vector<vector<BuildingPoint>> BX,vector<float> HX);//ˮƽ������, oneBPoint����������Ľ�������۵��б�buildingHeight�������佨����ĸ߶ȣ���ȥ����������������7�������������������������˵�����,ˮƽ��ķ�������ָ�������⣬������������ǽ�������۵��б�������ĸ߶��б�
	void decideRoofLengDiffraction(float pointx,float pointy, vector<BuildingPoint> oneBPoint,float buildingHeight);//�����ж������䵽�����Ƿ�ᷢ�����䣬




};

