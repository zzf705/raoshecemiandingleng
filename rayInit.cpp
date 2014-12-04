#include "rayInit.h"



void rayInit::rayfinalpointxy(float x0,float y0,float z0,float a,float b,float c,float coveringLength)
{
	float groundx,groundy;//射线若与地面相交的交点坐标
	float d; //地面交点与源点的水平距离finalx，finaly是网格搜索的终点坐标
	if(c>=0)
	{

		finalx=x0+a*coveringLength/(sqrt(a*a+b*b));
		finaly=y0+b*coveringLength/(sqrt(a*a+b*b));
		groundflag=0;
	}
	if(c<0)
	{
		groundx=(-a)*z0/c+x0;//射线若与地面相交的交点坐标
		groundy=(-b)*z0/c+y0;
		//
		
		
		d=sqrt((groundx-x0)*(groundx-x0)+(groundy-y0)*(groundy-y0));
		if (d>=coveringLength)//搜索只在1km进行
		{

			finalx=x0+a*coveringLength/(sqrt(a*a+b*b));
			finaly=y0+b*coveringLength/(sqrt(a*a+b*b));
			groundflag=0;
		}
		else
		{
			finalx=groundx;
			finaly=groundy;
			groundflag=1;
			d1=sqrt((groundx-x0)*(groundx-x0)+(groundy-y0)*(groundy-y0)+(finalz-z0)*(finalz-z0));
		}
		
		//else groundflag=0;

	}
}
int rayInit::getgroundflag()//返回是否与地面相交的标志
{
	return groundflag;
}

void rayInit::setsearchgridnumber() //得到需要搜索的网格的个数
{

	for(int i=1;i<=1000;i++)
	{
		if(searchgridx[i-1]!=0&&searchgridy[i-1]!=0)
			num=num+1;
		else break;
	}

}


float rayInit::get_firstx()
{
	return firstx;
}
float rayInit::get_firsty()
{
	return firsty;
}
float rayInit::get_firstz()
{
	return firstz;
}
float rayInit::get_finalx()
{
	return finalx;
}
float rayInit::get_finaly()
{
	return finaly;
}
float rayInit::get_finalz()
{
	return finalz;
}
void rayInit::setfirstgridx(int n)
{
	firstgridx=n;
}
void rayInit::setfirstgridy(int n)
{
	firstgridy=n;
}
void rayInit::setfinalgridx(int n)
{
	finalgridx=n;
}
void rayInit::setfinalgridy(int n)
{
	finalgridy=n;
}
int rayInit::getfirstgridx()
{
	return firstgridx;
}
int rayInit::getfirstgridy()
{
	return firstgridy;
}
int rayInit::getfinalgridx()
{
	return finalgridx;
}
int rayInit::getfinalgridy()
{
	return finalgridy;
}
float rayInit::get_directiona() //获得射线方向系数a
{
	return directiona;
}
float rayInit::get_directionb() //获得射线方向系数b
{
	return directionb;
}

float rayInit::get_directionc() //获得射线方向系数c
{
	return directionc;
}
void rayInit::setallgridx(int *p)  //找到搜索的所有网格水平编号集合，并赋值给的 searchgridx[1000]
{
	for(int i=1;i<=1000;i++)
	{
		searchgridx[i-1]=*p;
		p++;
	}
}
void rayInit::setallgridy(int *p) //找到搜索的所有网格垂直编号集合，并赋值给的 searchgridy[1000]
{ 
	for(int i=1;i<=1000;i++)
	{
		searchgridy[i-1]=*p;
		p++;
	}
}
int* rayInit::getallgridx()  //返回所有的网格水平编号
{
	return &searchgridx[0];
}
int* rayInit::getallgridy() //返回所有的网格垂直编号
{
	return &searchgridy[0];
}


rayInit::rayInit( float a,float b,float c,float d,float e,float f)
{
	firstx=a;
	firsty=b;
	firstz=c;    
	directiona=d;
	directionb=e;
	directionc=f;
	num=0;//射线方向系数
	d1=0;
	finalz=0;//若与地面相交z值为0
	memset(searchgridx,0,sizeof(searchgridx));
	memset(searchgridy,0,sizeof(searchgridy));
	//searchgridx[1000]={0};
	//searchgridy[1000]={0};
}
int rayInit:: getsearchgridnumber()//返回需要搜索的网格的个数
{
	return num;
}
float rayInit::getd1()//返回射线起点与地面交点的距离
{
	return d1;
}

