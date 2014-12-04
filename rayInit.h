#pragma once
#include<iostream>
#include<cmath>
using namespace std;


class rayInit
{
private:
	float firstx,firsty,firstz;    //射线起始点坐标
	float directiona,directionb,directionc;   //射线方向系数
	float finalx, finaly,finalz;    //搜索停止时射线终点坐标
	int num;  //搜索的网格个数
	float d1;//射线起点与地面交点的距离,初始值为0
	int groundflag;//判断是否与地面相交的标志
	int firstgridx,firstgridy;  //射线起始点所在的网格
	int finalgridx,finalgridy;  //射线终点所在的网格
	int searchgridx[1000],searchgridy[1000];//射线从起点到终点经过的所有网格水平编号垂直编号集合数组




public:
	rayInit( float,float,float,float,float,float);//射线起始点坐标,方向系数,搜索的网格个数初始化
	float get_firstx();  //获得射线起始点x坐标
	float get_firsty();  //获得射线起始点y坐标
	float get_firstz();  //获得射线起始点z坐标
	float get_directiona();//获得射线方向系数a
	float get_directionb();//获得射线方向系数b
	float get_directionc();//获得射线方向系数c

	void rayfinalpointxy( float,float,float,float,float,float,float coveringLength);//求射线终点坐标,输入参数 射线起始点坐标，方向系数,得到终点坐标，是否与地面相交的标志和射线与地面交点的距离d1

	float get_finalx(); //获得射线终点x坐标
	float get_finaly();  //获得射线终点y坐标
	float get_finalz();  //获得射线终点z坐标,初始值为0
	void setfirstgridx(int n); //求射线起始点所在的网格水平编号，用法，定义一个网格类对象q,射线对象m,括号里写上 q.findpointgridx(m.get_firstx())
	void setfirstgridy(int n); //求射线起始点所在的网格垂直编号
	void setfinalgridx(int n);//求射线终点所在的网格水平编号
	void setfinalgridy(int n);//求射线终点所在的网格垂直编号
	int getfirstgridx(); //返回起点的网格水平编号
	int getfirstgridy();//返回起点的网格垂直编号
	int getfinalgridx();//返回终点的网格水平编号
	int getfinalgridy();//返回终点的网格垂直编号
	//求射线从起始点到终点所在的网格水平编号 用法，定义一个网格类对象q,射线对象m,之前已经定义过，这里可以沿用上面的，先执行q.findallgrid(m.get_firstx(),m.get_firsty(),m.getfirstgridx(),m.getfirstgridy(),m.getfinalgridx(),m.getfinalgridy(),
	//m.getfinalgridz(),m. get_directiona(),m. get_directionb()),求出搜索的网格集合，然后执行获得射线的水平编号，也就是下面的语句，用法：m. setdallgridx(q.get_allgridx());
	void setallgridx(int *p);  //找到搜索的所有网格水平编号集合，并赋值给的 searchgridx[1000]
	void setallgridy(int *p);  //找到搜索的所有网格垂直编号集合，并赋值给的 searchgridy[1000]
	int* getallgridx();  //返回所有的网格水平编号
	int* getallgridy();  //返回所有的网格垂直编号
	void setsearchgridnumber();//得到需要搜索的网格的个数
	int getsearchgridnumber();//返回需要搜索的网格的个数
	int getgroundflag();//返回是否与地面相交的标志
	float getd1();//返回射线起点与地面交点的距离



};


