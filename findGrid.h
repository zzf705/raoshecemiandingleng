#pragma once
#include<iostream>
class findGrid
{
private:
	int m[1000],n[1000]; //按射线方向网格水平编号，垂直编号
	int x[802],y[802];   //网格位置
	float gridx0,gridy0; //网格编号的参考坐标xy,
public:
	findGrid();              //对网格中的xy数组进行初始化
	int findfirstpointgridx(float x0,float a);//求射线起始点所在的网格的水平编号，输入参数是起始点的x坐标，水平方向系数，考虑起始点可能在网格的顶点上，棱上或网格内
	int findfirstpointgridy(float y0,float b);//求射线起始点所在的网格的垂直编号，输入参数是起始点的y坐标，垂直方向系数
	int findpointgridx( float x0,float a); //求一个终点所在的水平网格编号，考虑在端点的情况对于射线类应该调用1次，终点x坐标
	int findpointgridy(float y0,float b); //求一个终点所在的垂直网格编号，考虑在端点的情况，对于射线类应该调用1次，终点y坐标
	void findallgrid(float x0, float y0, int i, int j,int h, int k,float a, float b); // 求出按射线方向网格水平编号，垂直编号输入参数分别是起点坐标的xy值，起始网格编号，终止网格编号，射线的斜率
	int* get_allgridx();   //返回按射线方向网格水平编号数组的首个元素地址
	int* get_allgridy();   //返回按射线方向网格垂直编号

};

