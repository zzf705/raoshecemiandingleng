#pragma once
#include<iostream>
#include "complex.h"
#include<vector>
using namespace std;


class rayPath
{
public:
	rayPath(void);
	~rayPath(void);

	float  firstPointx,firstPointy,firstPointz;//射线起始点的坐标
	float  firstDirectiona,firstDirectionb,firstDirectionc;
	float  rayGain;

	vector<float>reflecttDirectiona;
	vector<float>reflecttDirectionb;
	vector<float>reflecttDirectionc;
	vector<float>reflecttAngle;
	vector<float>reflecttCoefficient;
	vector<float>crossPointx;
	vector<float>crossPointy;
	vector<float>crossPointz;
	vector<float>rayLength;
	vector<int>searchGridNumberTrue;//记录每次求交模块射线实际经过的网格的个数
	vector<int>searchGridTrueX;//记录每次求交模块射线实际经过的网格的水平编号
	vector<int>searchGridTrueY;//记录每次求交模块射线实际经过的网格的垂直编号
	vector<int>positioniState;
	vector<complex>reflectComplexCoefficient;//存入复的反射系数

};

