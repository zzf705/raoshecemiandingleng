#include "complex.h"


void complexCalculate::findComplexRoot(complex x)//计算复数的开根号
{
	float length;
	float angle;
	float ratio;
	length=sqrt((x.real)*(x.real)+(x.img)*(x.img));
	ratio=x.img/x.real;
	angle=atan(ratio);
	length=sqrt(length);
	angle=angle/2;
	consequence.real=length*cos(angle);
	consequence.img=length*sin(angle);
}
void complexCalculate::findComplexMulConst(complex x,float coefficient)//计算复数乘以一个常数
{
	consequence.real=x.real*coefficient;
	consequence.img=x.img*coefficient;

}
void complexCalculate::findComplexAddConst(complex x,float coefficient)//计算复数乘以一个常数
{
	consequence.real=x.real+coefficient;
	consequence.img=x.img;
}
void complexCalculate::findComplexDivid(complex x,complex y)//计算两个复数相除
{
	consequence.real=(x.real*y.real+x.img*y.img)/(y.real*y.real+y.img*y.img);
	consequence.img=(x.img*y.real-x.real*y.img)/(y.real*y.real+y.img*y.img);
}
float complexCalculate::findComplexLength(complex x)//计算复数的开根号
{
	float length;
	length=sqrt((x.real)*(x.real)+(x.img)*(x.img));
	return length;
}
void complexCalculate::findComplexMulComplex(complex x,complex y)//用于计算两个复数相乘
{
	consequence.real=x.real*y.real-x.img*y.img;
	consequence.img=x.img*y.real+x.real*y.img;

}
void complexCalculate::findComplexAddComplex(complex x,complex y)//用于计算两个复数相加
{
	consequence.real=x.real+y.real;
	consequence.img=x.img+y.img;

}