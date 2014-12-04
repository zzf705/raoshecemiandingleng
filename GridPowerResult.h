#pragma once
#include<iostream>
#include "complex.h"
#include<cmath>
#include<vector>
using namespace std;


class GridPowerResult
{
public:

	vector<complex> gridFinalPower;//向量名
	double gridFinalTotalPower;
	double gridPowerLoss;//网格接收点对应的路径损耗
	void findGridFinalTotalPower( float frequence);//求出每个网格的功率，将vector中的功率相加,频率以mhz为单位
};

