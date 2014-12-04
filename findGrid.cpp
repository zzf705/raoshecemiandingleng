#include "findGrid.h"

findGrid::findGrid()
{
	x[0+400]=0;
	for(int p=-400;p<=-1;p++)
	{
		x[p+400]=p*5;
	}
	for(int p=1;p<=401;p++)
	{
		x[p+400]=(p-1)*5;
	}
	y[0+400]=0;
	for(int p=-400;p<=-1;p++)
	{
		y[p+400]=p*5;
	}
	for(int p=1;p<=401;p++)
	{
		y[p+400]=(p-1)*5;
	}
	gridx0=0;  //网格编号的参考坐标xy.每次都要改
	gridy0=0;  //网格编号的参考坐标xy每次都要改
	memset(m,0,sizeof(m));
	memset(n,0,sizeof(n));
	//m[1000]={0,0};
	//n[1000]={0,0};
}
int findGrid::findpointgridx (float x0,float a)   //x0的值不在格点边上
{
	int i;
	float t; 
	x0=x0-gridx0;
	//判断x0是否能被5整除
	if(x0<0)
		t=-x0;
	else t=x0;
	int a1;
	a1=(int) t;
	float c1;
	c1=a1-t;
	int d1=1;
	if(c1==0&&a1%5==0)
		d1=0;
	if(d1==0)  //在顶点的情况
	{           
		int b1;   //求出x方向的编号
		b1=(int) x0;
		b1=b1/5;
		if(b1>0)
		{
			if(a<0)
				i=b1+1;
			else if(a>0)
				i=b1;
		}
		if(b1==0)
		{
			if(a<0)
				i=b1+1;
			else if(a>0)
				i=b1-1;
		}
		if(b1<0)
		{
			if(a<0)
				i=b1;
			else if(a>0)
				i=b1-1;
		}
	}
	if(d1!=0) //不在顶点的情况
	{

		if(x0>0)      //求出x方向的编号
		{
			int b1;  
			b1=(int) x0;
			b1=b1/5;
			i=b1+1;
		}
		if(x0<0)
		{
			int b1;  
			float x3;
			x3=-x0;
			b1=(int) x3;
			b1=b1/5;
			i=b1+1;
			i=-i;
		}
	}

	return i;
}
int findGrid::findpointgridy(float y0,float b)  //y0的值不在格点边上
{        
	int j;
	float m ;
	y0=y0-gridy0;
	//判断y0是否能被5整除
	if(y0<0)
		m=-y0;
	else m=y0;
	int a2;
	a2=(int) m;
	float c2;
	c2=a2-m;
	int d2=1;
	if(c2==0&&a2%5==0)
		d2=0;
	if(d2==0)    //在顶点的情况
	{
		int b2;   //求出y方向的编号
		b2=(int) y0;
		b2=b2/5;
		if(b2>0)
		{
			if(b<0)
				j=b2+1;
			else if(b>0)
				j=b2;
		}
		if(b2==0)
		{
			if(b<0)
				j=b2+1;
			else if(b>0)
				j=b2-1;
		}
		if(b2<0)
		{
			if(b<0)
				j=b2;
			else if(b>0)
				j=b2-1;
		}
	}
	if(d2!=0)
	{  
		if(y0>0)      //求出y方向的编号
		{
			int b2;  
			b2=(int) y0;
			b2=b2/5;
			j=b2+1;
		}
		if(y0<0)
		{
			int b2;  
			float y3;
			y3=-y0;
			b2=(int) y3;
			b2=b2/5;
			j=b2+1;
			j=-j;
		}
		return j;
	} 
}

void findGrid:: findallgrid(float x0, float y0, int i, int j,int h, int k,float a, float b) //输入参数分别是起点坐标的xy值，起始网格编号，终止网格编号，射线的斜率
{    
	m[0]=i;
	n[0]=j;
	int firstEqualFinal=0;//判断射线起始网格和终点网格是否位于同一个网格，是的话为1，不是的话为0
	if(i==h&&j==k)//如果射线的起点和终点位于同一个网格的话，一开始就停止
		firstEqualFinal=1;
	if(firstEqualFinal==0)
	{
		float len;
	len=b/a;
	if(len<0)
		len=-len;
	float x1,D;
	if (a>0&&b>0)
	{
		x1=x0+a/b*(y[j+400]-y0);
		D=b/a*(x[i+1+400]-x1);

		for(int p=1;p<=1000;p++)
		{
			if(D<5)
			{ 
				if (m[p-1]==-1)
				{
					m[p]=m[p-1]+2;
				}
				else m[p]=m[p-1]+1;
				n[p]=n[p-1];
				if(m[p]==h&&n[p]==k)
				{
					break;
				}
				D=D+len*5;
				continue;
			}
			if(D==5)
			{
				if (m[p-1]==-1)
				{
					m[p]=m[p-1]+2;
				}
				else m[p]=m[p-1]+1;
				if (n[p-1]==-1)
				{
					n[p]=n[p-1]+2;
				}
				else n[p]=n[p-1]+1;
				if(m[p]==h&&n[p]==k)
				{
					break;
				}
				D=D+(len-1)*5;
				continue;

			}
			if(D>5)
			{
				m[p]=m[p-1];
				if (n[p-1]==-1)
				{
					n[p]=n[p-1]+2;
				}
				else n[p]=n[p-1]+1;
				if(m[p]==h&&n[p]==k)
				{
					break;
				}
				D=D-5;
				continue;
			}

		}
	}
	if (a!=0&&b==0)
	{
		for(int p=1;p<=1000;p++)
		{
			if(a>0)
			{ 
				if (m[p-1]==-1)
					m[p]=m[p-1]+2;
				else m[p]=m[p-1]+1;
				n[p]=n[p-1];
				if(m[p]==h&&n[p]==k)
				{
					break;
				}
			}
			if(a<0)
			{ 
				if (m[p-1]==1)
					m[p]=m[p-1]-2;
				else m[p]=m[p-1]-1;
				n[p]=n[p-1];
				if(m[p]==h&&n[p]==k)
				{
					break;
				}
			}


		}
	}
	if (a==0&&b!=0)
	{
		for(int p=1;p<=1000;p++)
		{
			if(b>0)
			{ 
				m[p]=m[p-1];
				if (n[p-1]==-1)
					n[p]=n[p-1]+2;
				else n[p]=n[p-1]+1;
				if(m[p]==h&&n[p]==k)
				{
					break;
				}

			}
			if(b<0)
			{ 
				m[p]=m[p-1];
				if (n[p-1]==1)
					n[p]=n[p-1]-2;
				else n[p]=n[p-1]-1;
				if(m[p]==h&&n[p]==k)
				{
					break;
				}

			}


		}
	}
	if (a>0&&b<0)
	{

		x1=x0+a/b*(y[j+400+1]-y0);
		D=b/a*(x[i+1+400]-x1)*(-1);
		for(int p=1;p<=1000;p++)
		{
			if(D<5)
			{
				if (m[p-1]==-1)
				{
					m[p]=m[p-1]+2;
				}
				else m[p]=m[p-1]+1;
				n[p]=n[p-1];
				if(m[p]==h&&n[p]==k)
				{
					break;
				}
				D=D+len*5;
				continue;
			}
			if(D==5)
			{
				if (m[p-1]==-1)
				{
					m[p]=m[p-1]+2;
				}
				else m[p]=m[p-1]+1;
				if (n[p-1]==1)
				{
					n[p]=n[p-1]-2;
				}
				else n[p]=n[p-1]-1;
				if(m[p]==h&&n[p]==k)
				{
					break;
				}
				D=D+(len-1)*5;
				continue;
			}
			if(D>5)
			{
				m[p]=m[p-1];
				if (n[p-1]==1)
				{
					n[p]=n[p-1]-2;
				}
				else n[p]=n[p-1]-1;
				if(m[p]==h&&n[p]==k)
				{
					break;
				}
				D=D-5;
				continue;
			}

		}
	}
	if (a<0&&b<0)
	{

		x1=x0+a/b*(y[j+400+1]-y0);
		D=b/a*(x[i+400]-x1)*(-1);
		for(int p=1;p<=1000;p++)
		{
			if(D<5)
			{
				if (m[p-1]==1)
				{
					m[p]=m[p-1]-2;
				}
				else m[p]=m[p-1]-1;
				n[p]=n[p-1];
				if(m[p]==h&&n[p]==k)
				{
					break;
				}
				D=D+len*5;
				continue;
			}
			if(D==5)
			{
				if (m[p-1]==1)
				{
					m[p]=m[p-1]-2;
				}
				else m[p]=m[p-1]-1;
				if (n[p-1]==1)
				{
					n[p]=n[p-1]-2;
				}
				else n[p]=n[p-1]-1;
				if(m[p]==h&&n[p]==k)
				{
					break;
				}
				D=D+(len-1)*5;
				continue;
			}
			if(D>5)
			{
				m[p]=m[p-1];
				if (n[p-1]==1)
				{
					n[p]=n[p-1]-2;
				}
				else n[p]=n[p-1]-1;
				if(m[p]==h&&n[p]==k)
				{
					break;
				}
				D=D-5;
				continue;
			}
		}
	}
	
	if (a<0&&b>0)
	{

		x1=x0+a/b*(y[j+400]-y0);
		D=b/a*(x[i+400]-x1);
		for(int p=1;p<=1000;p++)
		{


			if(n[0]<0)
			{
				int mn;
				mn=1;
			}
			if(p==999)
			{
				int aaaaa;
			}
			if(D<5)
			{
				if (m[p-1]==1)
				{
					m[p]=m[p-1]-2;
				}
				else m[p]=m[p-1]-1;
				n[p]=n[p-1];
				if(m[p]==h&&n[p]==k)
				{
					break;
				}
				D=D+len*5;
				continue;
			}
			if(D==5)
			{
				if (m[p-1]==1)
				{
					m[p]=m[p-1]-2;
				}
				else m[p]=m[p-1]-1;
				if (n[p-1]==-1)
				{
					n[p]=n[p-1]+2;
				}
				else n[p]=n[p-1]+1;
				if(m[p]==h&&n[p]==k)
				{
					break;
				}
				D=D+(len-1)*5;
				continue;
			}
			if(D>5)
			{
				m[p]=m[p-1];
				if (n[p-1]==-1)
				{
					n[p]=n[p-1]+2;
				}
				else n[p]=n[p-1]+1;
				if(m[p]==h&&n[p]==k)
				{
					break;
				}
				D=D-5;
				continue;
			}

		}
	}
}
}
int* findGrid:: get_allgridx()   //返回按射线方向网格水平编号
{
	return &m[0];
}
int* findGrid::get_allgridy()   //返回按射线方向网格垂直编号
{
	return &n[0];
}
int findGrid::findfirstpointgridx(float x0,float a)//求射线起始点所在的网格的水平编号，输入参数是起始点的x坐标，水平方向系数，考虑起始点可能在网格的顶点上，棱上或网格内
{
	int i;
	float t; 
	x0=x0-gridx0;  //判断x0是否能被5整除
	if(x0<0)
		t=-x0;
	else t=x0;
	int a1;
	a1=(int) t;
	float c1;
	c1=a1-t;
	int d1=1;
	if(c1==0&&a1%5==0)
		d1=0;
	if(d1==0)  //在顶点的情况
	{           
		int b1;   //求出x方向的编号
		b1=(int) x0;
		b1=b1/5;
		if(b1>0)
		{
			if(a>0)
				i=b1+1;
			else if(a<0)
				i=b1;
		}
		if(b1==0)
		{
			if(a>0)
				i=b1+1;
			else if(a<0)
				i=b1-1;
		}
		if(b1<0)
		{
			if(a>0)
				i=b1;
			else if(a<0)
				i=b1-1;
		}
	}
	if(d1!=0) //不在顶点的情况
	{

		if(x0>0)      //求出x方向的编号
		{
			int b1;  
			b1=(int) x0;
			b1=b1/5;
			i=b1+1;
		}
		if(x0<0)
		{
			int b1;  
			float x3;
			x3=-x0;
			b1=(int) x3;
			b1=b1/5;
			i=b1+1;
			i=-i;
		}
	}
	return i;
}
int findGrid::findfirstpointgridy(float y0,float b)//求射线起始点所在的网格的垂直编号，输入参数是起始点的y坐标，垂直方向系数
{        
	int j;
	float m ;
	y0=y0-gridy0;
	//判断y0是否能被5整除
	if(y0<0)
		m=-y0;
	else m=y0;
	int a2;
	a2=(int) m;
	float c2;
	c2=a2-m;
	int d2=1;
	if(c2==0&&a2%5==0)
		d2=0;
	if(d2==0)    //在顶点的情况
	{
		int b2;   //求出y方向的编号
		b2=(int) y0;
		b2=b2/5;
		if(b2>0)
		{
			if(b>0)
				j=b2+1;
			else if(b<0)
				j=b2;
		}
		if(b2==0)
		{
			if(b>0)
				j=b2+1;
			else if(b<0)
				j=b2-1;
		}
		if(b2<0)
		{
			if(b>0)
				j=b2;
			else if(b<0)
				j=b2-1;
		}
	}
	if(d2!=0)
	{  
		if(y0>0)      //求出y方向的编号
		{
			int b2;  
			b2=(int) y0;
			b2=b2/5;
			j=b2+1;
		}
		if(y0<0)
		{
			int b2;  
			float y3;
			y3=-y0;
			b2=(int) y3;
			b2=b2/5;
			j=b2+1;
			j=-j;
		}
		return j;
	} 
}

