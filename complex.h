#pragma once
#include<iostream>
#include<vector>
#include<cmath>
using namespace std;

class complex
{
public:

	float real;
    float img;
};


class complexCalculate
{
public:
	complex consequence;//计算结果
public:
	void findComplexRoot(complex x);//计算复数的开根号
	void findComplexMulConst(complex x,float coefficient);//计算复数乘以一个常数
	void findComplexAddConst(complex x,float coefficient);//计算复数乘以一个常数
	void findComplexDivid(complex x,complex y);//计算两个复数相除
	float findComplexLength(complex x);//计算复数的模值
	void findComplexMulComplex(complex x,complex y);//用于计算两个复数相乘
	void findComplexAddComplex(complex x,complex y);//用于计算两个复数相加
	
};

