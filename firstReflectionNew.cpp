
#include "firstReflectionNew.h"
TwoDimPoint FirstReflection:: getCross(line line1, line line2)//求两条线段的交点
{
	
	TwoDimPoint CrossP;
	//y = a * x + b;
	if ((line1.point1.x - line1.point2.x) != 0 && (line2.point1.x - line2.point2.x) != 0)
	{
		float a1 = (line1.point1.y - line1.point2.y) / (line1.point1.x - line1.point2.x);
		float b1 = line1.point1.y - a1 * (line1.point1.x);

		float a2 = (line2.point1.y - line2.point2.y) / (line2.point1.x - line2.point2.x);
		float b2 = line2.point1.y - a2 * (line2.point1.x);

		if (a1 != a2)
		{
			if(a2==0)
			{
				CrossP.x = (b1 - b2) / (a2 - a1);
				CrossP.y =line2.point1.y;
			}
			else
		    {
			    CrossP.x = (b1 - b2) / (a2 - a1);
				CrossP.y=a2 * CrossP.x + b2;
			   // CrossP.y = a1 * CrossP.x + b1;
				
		    }
		}
		else
		{
			CrossP.x = 9999999999999;
			CrossP.y = 9999999999999;
		}
	}
	else if ((line1.point1.x - line1.point2.x) == 0 && (line2.point1.x - line2.point2.x) != 0)
	{
		float a2 = (line2.point1.y - line2.point2.y) / (line2.point1.x - line2.point2.x);
		float b2 = line2.point1.y - a2 * (line2.point1.x);
		CrossP.x = line1.point1.x;
		CrossP.y = a2*CrossP.x + b2;
	}
	else if ((line1.point1.x - line1.point2.x) != 0 && (line2.point1.x - line2.point2.x) == 0)
	{
		float a1 = (line1.point1.y - line1.point2.y) / (line1.point1.x - line1.point2.x);
		float b1 = line1.point1.y - a1 * (line1.point1.x);
		CrossP.x = line2.point1.x;
		CrossP.y = a1*CrossP.x + b1;
	}
	else if ((line1.point1.x - line1.point2.x) == 0 && (line2.point1.x - line2.point2.x) == 0)
	{
		CrossP.x = 9999999999999;
		CrossP.y = 9999999999999;
	}
	return CrossP;
}




void FirstReflection::buildingCross(float shootingStartX,float shootingStartY,float shootingStartZ,float shootingDirectionX,float shootingDirectionY,float shootingDirectionZ,vector<BuildingPoint> BPoint,float buildingHeight)
{
	line line1;
	line line2;   //是否应该有线2
	TwoDimPoint CointP;
	TwoDimPoint buildingvertex;//射线与建筑物顶面的交点
	
	int sideFlag=0;
	float X,Y,Z;
	float x,y,z;

	for(int k=0;k<BPoint.size();k++)
	{
		TwoDimPoint temp;
		temp.x=BPoint[k].px;
		temp.y=BPoint[k].py;
		polyPoint.push_back(temp);
	}
	line1.point1.x = shootingStartX;
	line1.point1.y = shootingStartY;
	line1.point2.x = shootingStartX + shootingDirectionX;
	line1.point2.y = shootingStartY + shootingDirectionY;

	//float buildingHeight=15;
/*
	printf("请输入建筑物高度:");                      //这里应该调用建筑物高度的vector
	scanf_s("%f", &h);
*/

	//求射线与建筑物侧面的交点
	refPolyPoint[0].x = 0;
	refPolyPoint[0].y = 0;
	refPolyPoint[1].x = 0;
	refPolyPoint[1].y = 0;
	float little = 9999999999;
	for (int i = 0; i < polyPoint.size()-1; i++)
	{
		if (i != polyPoint.size() - 2)
		{
			line2.point1.x = polyPoint[i].x;
			line2.point1.y = polyPoint[i].y;
			line2.point2.x = polyPoint[i + 1].x;
			line2.point2.y = polyPoint[i + 1].y;
		}
		else
		{
			line2.point1.x = polyPoint[i].x;
			line2.point1.y = polyPoint[i].y;
			line2.point2.x = polyPoint[0].x;
			line2.point2.y = polyPoint[0].y;
		}
		CointP = getCross(line1, line2);	
		
			
			if (min(line2.point1.x, line2.point2.x) <= CointP.x && CointP.x <= max(line2.point1.x, line2.point2.x)&&min(line2.point1.y, line2.point2.y) <= CointP.y && CointP.y <= max(line2.point1.y, line2.point2.y))
			{

				float distant;
				if(shootingDirectionX!=0)				
				z = shootingStartZ + shootingDirectionZ / shootingDirectionX *(CointP.x - shootingStartX);
				else 
				z = shootingStartZ + shootingDirectionZ / shootingDirectionY *(CointP.y - shootingStartY);

				if (z < buildingHeight&&z>0)//必须满足大于0
				{
					if((fabs(CointP.x-shootingStartX)>0.01||fabs(CointP.y-shootingStartY)>0.01||fabs(z-shootingStartZ)>0.01)
						&&((CointP.x-shootingStartX)*shootingDirectionX>=0)&&((CointP.y-shootingStartY)*shootingDirectionY>=0)&&((z-shootingStartZ)*shootingDirectionZ>0))//保证方向正确，同时求出的交点不会在原点
		       {
					sideFlag=1;
					distant = sqrt(pow(CointP.x - line1.point1.x, 2) + pow(CointP.y - line1.point1.y, 2) + pow(z - shootingStartZ, 2));
					if (distant <= little)
					{
						little = distant;
						X = CointP.x;
						Y = CointP.y;
						Z = z;

						refPolyPoint[0].x = line2.point1.x;
						refPolyPoint[0].y = line2.point1.y;
						refPolyPoint[1].x = line2.point2.x;
						refPolyPoint[1].y = line2.point2.y;
					}
				}
			}
		}
	}

	//求射线与建筑物顶面的交点
	if (shootingDirectionZ != 0)
	{
		z = buildingHeight;
		float t = (z - shootingStartZ) / shootingDirectionZ;
		x = shootingStartX + shootingDirectionX*t;
		y = shootingStartY + shootingDirectionY*t;
		double x0,y0,med,resulty;//需要判断的点
		 x0=x;
		 y0=y;
		  vector<double> crosspointy;//用于求出交点的y坐标
			   int n1,insideFlag;//n1用来判断最后的交点重复的个数，insideFlag=1为点在多边形内
			   n1=0;
			   insideFlag=0;
			   for(int i=0;i<=BPoint.size()-2;i++)
			   {
				   double x1,y1, x2,y2;//用来记录读取数据的点
				   x1=BPoint[i].px;y1=BPoint[i].py;
				   x2=BPoint[i+1].px;y2=BPoint[i+1].py;
				   //使x1小于x2,使y1小于y2
				   if(x1>x2)
				   {
					   med=x1;
					   x1=x2;
					   x2=med;

				   }
				    if(y1>y2)
				   {
					   med=y1;
					   y1=y2;
					   y2=med;

				   }
					//判断点是否在线段上
					if(x1!=x2)
					{
						if(x0>=x1&&x0<=x2)
						{

							if(y1==y2)
						{
							if(y1<=y0)
							{
								crosspointy.push_back(y1);
							}

						}
							if(y1!=y2)
						{
							resulty=(BPoint[i].py-BPoint[i+1].py)*x0/(BPoint[i].px-BPoint[i+1].px)+(BPoint[i].px*BPoint[i+1].py-BPoint[i+1].px*BPoint[i].py)/(BPoint[i].px-BPoint[i+1].px);
							if(resulty>=y1&&resulty<=y2&&resulty<=y0)
							{
								crosspointy.push_back(resulty);
							}
							

						}
						}
					}
			   }
			   //求重复的交点个数
					int q;
					q=crosspointy.size();
					q=q-2;
					for(int i=0;i<=q;i++)
					{
						int m=crosspointy.size()-1;
						for(int j=1;j<=m;j++)
						{
							if(i+j<=m)
							{
								if(crosspointy[i]==crosspointy[i+j])
								{
									n1++;
								}

							}
						}
									
					}
					int pointNumber;
					pointNumber=crosspointy.size()-n1;
					if(pointNumber>0&&pointNumber%2==1)
						insideFlag=1;


					if (insideFlag==1&&(fabs(x-shootingStartX)>0.01||fabs(y-shootingStartY)>0.01||fabs(z-shootingStartZ)>0.01)
						&&((x-shootingStartX)*shootingDirectionX>=0)&&((y-shootingStartY)*shootingDirectionY>=0)&&((z-shootingStartZ)*shootingDirectionZ>0))
		{
			//保证方向正确，同时求出的交点不会在原点
			
			           
						   roofFlag=1;
			            
			
		}


		 /*buildingvertex.x = x;
		 buildingvertex.y = y;
*//*
		if (vertexInside( buildingvertex) == 1)
		{
			
			roofFlag=1;
			
		}*/

		else
		{
			roofFlag=0;
		}
	}
	else
	{
		roofFlag=0;
	}
	
	//综合侧面和顶面，判断射线与建筑物是否相交，若相交给出交点。同时给出标志位的值。

	if (sideFlag == 1 && roofFlag == 1)
	{
		float L1 = sqrt(pow((X - shootingStartX), 2) + pow((Y - shootingStartY), 2) + pow((Z - shootingStartZ), 2));
		float L2 = sqrt(pow((x - shootingStartX), 2) + pow((y - shootingStartY), 2) + pow((z - shootingStartZ), 2));
		if (L1 < L2)
		{
			crossX = X;
			crossY = Y;
			crossZ = Z;				
			roofFlag=0;
			buildingCrossFlag=1;
			
		}
		else
		{
			crossX = x;
			crossY = y;
			crossZ = z;	
			roofFlag=1;
			sideFlag=0;
			buildingCrossFlag=1;
			
		}
	}
	else if (sideFlag == 1 && roofFlag == 0)
	{
		crossX = X;
		crossY = Y;
		crossZ = Z;		
		buildingCrossFlag=1;
		    
	}

	else if (sideFlag == 0 && roofFlag == 1)
	{
		crossX = x;
		crossY = y;
		crossZ = z;		
		buildingCrossFlag=1;
		   
	}
	else 
	{
	    buildingCrossFlag=0;
	}

}
int FirstReflection::vertexInside(TwoDimPoint vertex)
{
	float sideX,sideY,polyVertexX,polyVertexY,crossProduct;
	float sideX0,sideY0,polyVertexX0,polyVertexY0,crossProduct0;
	float sideXF,sideYF,polyVertexXF,polyVertexYF,crossProductF;
	int i;

	sideX0=polyPoint[1].x-polyPoint[0].x;
	sideY0=polyPoint[1].y-polyPoint[0].y;
	polyVertexX0=vertex.x-polyPoint[0].x;
	polyVertexY0=vertex.y-polyPoint[0].y;
	crossProduct0=sideX0*polyVertexY0-sideY0*polyVertexX0;

	for(i=1;i<polyPoint.size()-1;i++)
	{
		sideX=polyPoint[i+1].x-polyPoint[i].x;
		sideY=polyPoint[i+1].y-polyPoint[i].y;
		polyVertexX=vertex.x-polyPoint[i].x;
		polyVertexY=vertex.y-polyPoint[i].y;
		crossProduct=sideX*polyVertexY-sideY*polyVertexX;

		if(crossProduct0*crossProduct<0)
		{
			return 0;
		}
	}

	sideXF=polyPoint[0].x-polyPoint[i].x;
	sideYF=polyPoint[0].y-polyPoint[i].y;
	polyVertexXF=vertex.x-polyPoint[i].x;
	polyVertexYF=vertex.y-polyPoint[i].y;
	crossProductF=sideXF*polyVertexYF-polyVertexXF*sideYF;

	if(crossProduct0*crossProductF<0)
	{
		return 0;
	}

	return 1;

}