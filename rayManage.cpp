#include "rayManage.h"


void rayManage:: findFinalCrossPoint(float startPointx,float startPointy,float startPointz,float startDirectiona,float startDirectionb,float startDirectionc,int maxGridx,int maxGridy,float coveringDistance,vector<vector<BuildingPoint>> BY,vector<float> HY)//求出最后的交点，得到一些参量
{   
	float crosspointx, crosspointy, crosspointz; //与建筑物求交模块后得到的与建筑的交点，最后作为依据和地面比较，球的最后的交点
    int crossBuildingName; //建筑物的交点所在的建筑物的编号
   int f=0;//标志位，判断射线是否在搜索完所有的网格之后与建筑物相交
   int searchgridnum;//搜索的网格的个数
   double min_distance=10000;//实际中，射线的距离一定比10000小
   int crossPointPosition;//求得的交点位于顶面为1,位于侧面为0

   rayInit m( startPointx, startPointy, startPointz,startDirectiona, startDirectionb, startDirectionc); //射线初始化
   m.rayfinalpointxy(m.get_firstx(),m.get_firsty(),m.get_firstz(),m.get_directiona(),m.get_directionb(),m.get_directionc(), coveringDistance);//求射线的终点坐标
   findGrid q;//定义一个网格对象
   m.setfirstgridx(q.findfirstpointgridx(m.get_firstx(),m.get_directiona())); //求射线的起始点对应的网格x
   m.setfirstgridy(q.findfirstpointgridy(m.get_firsty(),m.get_directionb())); //求射线的起始点对应的网格y
   m.setfinalgridx(q.findpointgridx(m.get_finalx(),m.get_directiona()));   //求射线的终点对应的网格x
   m.setfinalgridy(q.findpointgridy(m.get_finaly(),m.get_directionb()));   //求射线的终点对应的网格y
   q.findallgrid(m.get_firstx(),m.get_firsty(),m.getfirstgridx(),m.getfirstgridy(),m.getfinalgridx(),m.getfinalgridy(),m.get_directiona(),m.get_directionb());//求射线经过所有的网格
   m.setallgridx(q.get_allgridx());//将得到的水平网格编号的集合赋给searchgridx[1000]
   m.setallgridy(q.get_allgridy());//将得到的水平网格编号的集合赋给searchgridy[1000]
   m.setsearchgridnumber();
  
	
	
	//int gridm[1000],gridn[1000];
	memset(gridm,0,sizeof(gridm));//将网格数组初始为零
	memset(gridn,0,sizeof(gridn));
	memset(gridTruem,0,sizeof(gridTruem));
	memset(gridTruen,0,sizeof(gridTruen));
	int *p=m.getallgridx();
	int *qq=m.getallgridy();
    gridNumberTrue=0;//实际网格的数目，考虑到实际地图的范围，网格是有限的
	
	  for(int i=1;i<=m.getsearchgridnumber();i++)
	{       int grid1,grid2;
	        grid1=*p;
			grid2=*qq;

		if( grid1>0&&grid1<maxGridx+1&&grid2>0&&grid2<maxGridy+1)
		{
			gridm[i-1]=grid1;
			gridn[i-1]=grid2;
			   p++;
		       qq++;
		gridNumberTrue++;
		}
		else 
			break;//如果超出范围，就不在记录
		
	  }
	
	  
	   for(int t=1;t<=gridNumberTrue;t++)
	   {
		     Grid grid1;

           int budnumber=0;//一个网格包含的建筑物数
		   float gridCenterX,gridCenterY;//求出网格中心点的坐标
		   if(gridm[t-1]>0)
		   {
			   gridCenterX=2.5*(2*gridm[t-1]-1);
		   }
		   if(gridm[t-1]<0)
		   {
			   int w;
			   w=-gridm[t-1];
			   gridCenterX=-2.5*(2*w-1);
		   }
		   if(gridn[t-1]>0)
		   {
			   gridCenterY=2.5*(2*gridn[t-1]-1);
		   }
		   if(gridn[t-1]<0)
		   {
			   int w;
			   w=-gridn[t-1];
			   gridCenterY=-2.5*(2*w-1);
		   }

		   grid1.GetThisGirdRecord(gridCenterX,gridCenterY);
		   for(int i=0;i<grid1.GBId.size();i++)
		   {
			   if(grid1.GBId[i]!=0)
			   budnumber++;
		   }
		   //int buildingname[4]; 建筑物的编号的数组集合,现在可以用h.GBIB表示
		   if (budnumber==0)
			   continue;
		   double a[10],b[10],c[10],d[10],e[10],flaH[10],linepoint1x[10],linepoint1y[10],linepoint2x[10],linepoint2y[10];//a b c代表坐标，d代表是否相交，e代表距离，flaH代表位于建筑物的位置
		   memset(a,0,sizeof(a));
	       memset(b,0,sizeof(b));
		   memset(c,0,sizeof(c));
		   memset(d,0,sizeof(d));
		   memset(e,0,sizeof(e));
		   memset(flaH,0,sizeof(flaH));
		   memset(linepoint1x,0,sizeof(linepoint1x)); //记录交点所在的面的两个点的坐标，便于求反射射线
		   memset(linepoint1y,0,sizeof(linepoint1y));
		   memset(linepoint2x,0,sizeof(linepoint2x));
		   memset(linepoint2y,0,sizeof(linepoint2y));


		   for(int i=1;i<=grid1.GBId.size();i++)
		   {
			   if(grid1.GBId[i-1]==0)
				   continue;
			  // Building building1;//定义一个建筑物类，用于查找建筑物的折点
			   
			   // building1.GetThisBuildingRecord(grid1.GBId[i-1]);//获得建筑物的折点
			   int pointnumber;
			   //pointnumber=building1.BPoint.size();
			   pointnumber=BY[(grid1.GBId[i-1]-1)].size();

			   float buildingheight;
			   //buildingheight= building1.buildingHeight;
			   buildingheight= HY[(grid1.GBId[i-1]-1)];
			   // h1.getHeightRecord;
			   //buildingheight=h1.height;
			   
			   /*int buildingCrossFlag=0;//从求交函数中得到射线是否与建筑物相交，相交为1
			   float crossx;//从求交函数中得到的交点x坐标
			   float crossy;//从求交函数中得到的交点y坐标
			   float crossz;//从求交函数中得到的交点z坐标
			   int roofFlag;//从求交函数中得到的交点是否位于顶面，在顶面为1，否则为0
			   float sidepoint1[2],sidepoint2[2];//如果交点位于侧面，则侧面所在的线段的顶点
			   */  //暂时作为标注，是求交函数中可以得到的
			  FirstReflection firstReflection1;
			  firstReflection1.buildingCross( startPointx,startPointy,startPointz,startDirectiona, startDirectionb, startDirectionc,BY[(grid1.GBId[i-1]-1)],buildingheight);
			   if(firstReflection1.buildingCrossFlag==0)
				   continue;
			  a[i-1]=firstReflection1.crossX;
			  b[i-1]=firstReflection1.crossY;
			  c[i-1]=firstReflection1.crossZ;
			  double errorx, errory, errorz;
			  errorx=a[i-1]-startPointx;
			  errory=b[i-1]-startPointy;
			  errorz=c[i-1]-startPointz;
			  if(fabs(errorx)<0.0001&&fabs(errory)<0.0001&&fabs(errorz)<0.0001)
				  continue; //主要考虑和初始点重合，由于也在本网格搜索
			  if(errorx*startDirectiona<0||errory*startDirectionb<0||errorz*startDirectionc<0)
				  continue;//满足条件说明射线按相反的方向走了
			   int i0,j0;//中间参数，获得点所在的网格编号
			   i0=q.findpointgridx(a[i-1],m.get_directiona());
			   j0=q.findpointgridy(b[i-1],m.get_directionb());
			   if(i0==gridm[t-1]&&j0==gridn[t-1])
			   {
				   d[i-1]=1;//标志位，表示交点在所在的网格内
				   e[i-1]=sqrt((m.get_firstx()-a[i-1])*(m.get_firstx()-a[i-1])+(m.get_firsty()-b[i-1])*(m.get_firsty()-b[i-1])+(m.get_firstz()-c[i-1])*(m.get_firstz()-c[i-1]));
				   flaH[i-1]=firstReflection1.roofFlag;
				   if( flaH[i-1]==0)
				   {
					   linepoint1x[i-1]=firstReflection1.refPolyPoint[0].x;
					   linepoint1y[i-1]=firstReflection1.refPolyPoint[0].y;
					   linepoint2x[i-1]=firstReflection1.refPolyPoint[1].x;
					   linepoint2y[i-1]=firstReflection1.refPolyPoint[1].y;

			       }
				    }
			   else continue;  //不在网格内，跳出，搜索下一个建筑物
		   }//网格内的建筑物搜索完
		  
		   for(int i=1;i<=grid1.GBId.size();i++)
		   {
			   if(d[i-1]==1)
			   {
				   if(e[i-1]<min_distance)
				   {
					   min_distance=e[i-1];
					  

		            }
				   }
		   }
			   if(min_distance==10000)
				   continue;//无交点在网格中，跳出搜索下一个网格
			   for(int i=1;i<=grid1.GBId.size();i++)
			   {
				   if(e[i-1]==min_distance)
				   {
					   crosspointx=a[i-1];
					   crosspointy=b[i-1];
					   crosspointz=c[i-1];
					   crossBuildingName=grid1.GBId[i-1];
					   crossPointPosition=flaH[i-1];//在顶面为1，否则为0
					   f=1;
					   twoPoint[0].x=linepoint1x[i-1];
					   twoPoint[0].y=linepoint1y[i-1];
					   twoPoint[1].x=linepoint2x[i-1];
					   twoPoint[1].y=linepoint2y[i-1];
					   break;//跳出这里的循环
					   }
			   }
		   
			   break;//跳出网格的循环，求出射线与建筑物的交点
	  }
		   if(f==1&&m.getgroundflag()==1)
		   {
			   //if(m.getd1()>min_distance)  //d1为起始点到地面交点的距离
			   //{
				   finalCrossFlag=1;//有交点
				   finalCrossPosition=0;//落在建筑物上
				   finalCrossPointx=crosspointx;
				   finalCrossPointy=crosspointy;
				   finalCrossPointz=crosspointz;
				   finalCrossBuildingname=crossBuildingName;
				  /* if(crossPointPosition==1)
				   stop=1;
				   if(crossPointPosition==0)
					   stop=0;
					   */
					   
				   finalCrossBuildingPosition=crossPointPosition;
				   finalRayLength=min_distance;
		     /*   }*/
			   //else
			   //{
				  // finalCrossFlag=1;//有交点
				  // finalCrossPosition=1;//落在地面上
				  // finalCrossPointx=m.get_finalx();
				  // finalCrossPointy=m.get_finaly();
				  // finalCrossPointz=m.get_finalz();
				  // finalCrossBuildingname=0;//与地面相交
				  // //stop=0;
				  // finalRayLength=m.getd1();
			   //}
		   }
		    if(f==1&&m.getgroundflag()==0)
			{
				 finalCrossFlag=1;//有交点
				   finalCrossPosition=0;//落在建筑物上
				   finalCrossPointx=crosspointx;
				   finalCrossPointy=crosspointy;
				   finalCrossPointz=crosspointz;
				   finalCrossBuildingname=crossBuildingName;
				  /* if(crossPointPosition==1)
				   stop=1;
				   if(crossPointPosition==0)
					   stop=0;
					   */
					   
				   finalCrossBuildingPosition=crossPointPosition;
				   finalRayLength=min_distance;
			}
			if(f==0&&m.getgroundflag()==1)
			{
				finalCrossFlag=1;//有交点
				finalCrossPosition=1;//落在地面上
				finalCrossPointx=m.get_finalx();
				finalCrossPointy=m.get_finaly();
				finalCrossPointz=m.get_finalz();
				finalCrossBuildingname=0;//与地面相交
				//stop=0;
				finalRayLength=m.getd1();
			}
			if(f==0&&m.getgroundflag()==0)
			{
				finalCrossFlag=0;//无交点
			}

			if(finalCrossFlag==1)
			{
				int gridFinalx,gridFinaly;//交点对应的网格编号
				gridFinalx=q.findpointgridx(finalCrossPointx,startDirectiona);
				gridFinaly=q.findpointgridy(finalCrossPointy,startDirectionb);
				gridNumberStopCross=0;
				for(int i=1;i<=gridNumberTrue;i++)
				{
					gridTruem[i-1]=gridm[i-1];
					gridTruen[i-1]=gridn[i-1];
					gridNumberStopCross++;
					if(gridm[i-1]==gridFinalx&&gridn[i-1]==gridFinaly)
						break;
				}





			}
			}
			float rayManage:: findBuildingRefCofficient(float cosAngle,float frequence)//求建筑物的反射系数
			{


				float sinAngle;
				float jiezhi;//用于求介质的参数
				sinAngle=sqrt(1-cosAngle*cosAngle);
				jiezhi=90000*(-1)/frequence;
				complex temp={0.05-sinAngle*sinAngle,jiezhi};
				complex temp1,temp2,temp3;
				complexCalculate complexCalcu1;
				complexCalcu1.findComplexRoot(temp);
				temp1=complexCalcu1.consequence;
				complexCalcu1.findComplexMulConst(temp1,-1);
				temp1=complexCalcu1.consequence;
				complexCalcu1.findComplexAddConst(temp1,cosAngle);
				temp1=complexCalcu1.consequence;
				complexCalcu1.findComplexRoot(temp);
				temp2=complexCalcu1.consequence;
				complexCalcu1.findComplexAddConst(temp2,cosAngle);
				temp2=complexCalcu1.consequence;
				complexCalcu1.findComplexDivid(temp1,temp2);
				temp3=complexCalcu1.consequence;

				return complexCalcu1.findComplexLength(temp3);
			}
			int rayManage::findPathStop( float pathDistance,float antennaGain,float frequence )//第一次根据距离判断射线的能量是否降到某一阈值，0表示不停止，1表示停止
			{
				float antennaPower=46;//基站发射的起始功率为46dbm，这里是个参数，是可调的
				float baseStationloss=0;//基站的损耗，这里先考虑为0
				float waveLength;//定义波长
				waveLength=300/frequence;//频率以MHZ为单位
				float receivePower;//接收功率
				receivePower=antennaPower-10.9921*2-20*log10( pathDistance)+20*log10(waveLength)+10*log10(antennaGain);//10.9921代表10log4pai
				if(receivePower<-110)//接收端的灵敏度是-109，暂时设为接收端功率的10分之一
					return 1;
				else return 0;
			}
			int rayManage:: findPathRefStop( float pathDistance,float antennaGain,float reflectCofficient,float frequence)//根据距离和反射系数判断射线的能量是否降到某一阈值，0表示不停止，1表示停止
			{
				float antennaPower=46;//基站发射的起始功率为46dbm，这里是个参数，是可调的
				float baseStationloss=0;//基站的损耗，这里先考虑为0
				float receivePower;//接收功率
				float waveLength;//定义波长
				waveLength=300/frequence;//频率以MHZ为单位
				receivePower=antennaPower-10.9921*2-20*log10( pathDistance)+20*log10(waveLength)+10*log10(antennaGain)+20*log10(reflectCofficient);//10.9921代表10log4pai
				if(receivePower<-110)//接收端的灵敏度是-109，暂时设为接收端功率的10分之一
					return 1;
				else return 0;

			}
			void rayManage::findGroundRefDirection(float shootingStartX,float shootingStartY,float shootingStartZ,float shootingDirectionX,float shootingDirectionY,float shootingDirectionZ)//已求出余弦值

			{
				float shootingFinalX;
				float shootingFinalY;
				float shootingFinalZ;
				shootingFinalX=shootingStartX-shootingStartZ*shootingDirectionX/shootingDirectionZ;
				shootingFinalY=shootingStartY-shootingStartZ*shootingDirectionY/shootingDirectionZ;
				shootingFinalZ=0;

				float normalVectorX;
				float normalVectorY;
				float normalVectorZ;
				normalVectorX=0;
				normalVectorY=0;
				normalVectorZ=1;

				float symmetryPointX;
				float symmetryPointY;
				float symmetryPointZ;
				symmetryPointX=2*shootingFinalX-shootingStartX;
				symmetryPointY=2*shootingFinalY-shootingStartY;
				symmetryPointZ=shootingStartZ;


				groundRefDirectionA=symmetryPointX-shootingFinalX;
				groundRefDirectionB=symmetryPointY-shootingFinalY;
				groundRefDirectionC=symmetryPointZ-shootingFinalZ;


				groundRefAngleCos=(shootingDirectionX*normalVectorX+shootingDirectionY*normalVectorY+shootingDirectionZ*normalVectorZ)/sqrt(pow(shootingDirectionX, 2) + pow(shootingDirectionY, 2) + pow(shootingDirectionZ, 2));
				if(groundRefAngleCos<0)
					groundRefAngleCos=-groundRefAngleCos;
			}

			void  rayManage::findBuildingRefDirection( float shootingStartX,float shootingStartY,float shootingStartZ,float shootingFinalX,float shootingFinalY,float shootingFinalZ,float startDirectionA,float startDirectionB,float startDirectionC,TwoDimPointZhang refPolyPoint0,TwoDimPointZhang refPolyPoint1) //求建筑物的反射方向系数，函数中已经求出入射角的余弦值

			{
				struct Line                         /*直线一般方程的三个系数*/
				{
					double a;
					double b;
					double c;
				};
				Line NormalLine;                   //法向量所在直线
				float normalVectorX;
				float normalVectorY;
				float normalVectorZ;
				normalVectorX=refPolyPoint1.y-refPolyPoint0.y;
				normalVectorY=refPolyPoint0.x-refPolyPoint1.x;
				normalVectorZ=0;

				NormalLine.a=refPolyPoint0.x-refPolyPoint1.x;
				NormalLine.b=refPolyPoint0.y-refPolyPoint1.y;
				NormalLine.c=-NormalLine.b*shootingFinalY-NormalLine.a*shootingFinalX;

				float A,B,C;
				A=NormalLine.a*NormalLine.a-NormalLine.b*NormalLine.b;
				B=2*NormalLine.a*NormalLine.b;
				C=NormalLine.a*NormalLine.a+NormalLine.b*NormalLine.b;

				float symmetryPointX;
				float symmetryPointY;
				float symmetryPointZ;
				symmetryPointX=(-A*shootingStartX-B*shootingStartY-2*NormalLine.a*NormalLine.c)/C;
				symmetryPointY=(A*shootingStartY-B*shootingStartX-2*NormalLine.b*NormalLine.c)/C;
				symmetryPointZ=2*shootingFinalZ-shootingStartZ;


				buildingRefDirectionA=symmetryPointX-shootingFinalX;
				buildingRefDirectionB=symmetryPointY-shootingFinalY;
				buildingRefDirectionC=symmetryPointZ-shootingFinalZ;

				//float buildingRefAngleCos;
				buildingRefAngleCos=(startDirectionA*normalVectorX+startDirectionB*normalVectorY+startDirectionC*normalVectorZ)/((sqrt(pow(startDirectionA, 2) + pow(startDirectionB, 2) + pow(startDirectionC, 2)))*(sqrt(pow(normalVectorX, 2) + pow(normalVectorY, 2) + pow(normalVectorZ, 2))));
				if(buildingRefAngleCos<0)
					buildingRefAngleCos=(-1)*buildingRefAngleCos;

			}
			float rayManage::findGroundRefCofficient(float cosAngle,float frequence)//求地面的反射系数的模值，地面的反射系数暂时和建筑物的材质是一样的，最后要根据参数进行调试
			{
				float sinAngle;
				float jiezhi;//用于求介质的参数
				sinAngle=sqrt(1-cosAngle*cosAngle);
				jiezhi=36*(-1)/frequence;
				complex temp={5-sinAngle*sinAngle,jiezhi};
				complex temp1,temp2,temp3;
				complexCalculate complexCalcu1;
				complexCalcu1.findComplexRoot(temp);
				temp1=complexCalcu1.consequence;
				complexCalcu1.findComplexMulConst(temp1,-1);
				temp1=complexCalcu1.consequence;
				complexCalcu1.findComplexAddConst(temp1,cosAngle);
				temp1=complexCalcu1.consequence;
				complexCalcu1.findComplexRoot(temp);
				temp2=complexCalcu1.consequence;
				complexCalcu1.findComplexAddConst(temp2,cosAngle);
				temp2=complexCalcu1.consequence;
				complexCalcu1.findComplexDivid(temp1,temp2);
				temp3=complexCalcu1.consequence;

				return complexCalcu1.findComplexLength(temp3);
			}
			float rayManage:: findPointToLineDistance(float shootingStartx,float shootingStarty,float shootingStartz,float shootingDirectina,float shootingDirectinb,float shootingDirectinc,float pointx,float pointy,float pointz)//求网格中心点上1.5m到直线的距离，输入射线的起点和方向，和网格中心点的坐标
			{
				struct shootingVector 
				{  
					float x;//向量的3个分量的x分量
				    float y;
					float z;

				} lineVector1,lineVector2;//网格上一点到射线起点的向量，射线的向量
				lineVector1.x=pointx-shootingStartx;
				lineVector1.y=pointy-shootingStarty;
				lineVector1.z=pointz-shootingStartz;
				lineVector2.x=shootingDirectina;
				lineVector2.y=shootingDirectinb;
				lineVector2.z=shootingDirectinc;
				float cosValue,sinValue,q1,q2,q3;
				q1=lineVector1.x*lineVector2.x+lineVector1.y*lineVector2.y+lineVector1.z*lineVector2.z;
				q2=sqrt(lineVector1.x*lineVector1.x+lineVector1.y*lineVector1.y+lineVector1.z*lineVector1.z);
				q3=sqrt(lineVector2.x*lineVector2.x+lineVector2.y*lineVector2.y+lineVector2.z*lineVector2.z);
				cosValue=q1/(q2*q3);
				sinValue=sqrt(1-cosValue*cosValue);
				
				float d;
				d=q2*sinValue;
				return d;

			}
			float rayManage::  findShootingLineLength(float shootingStartx,float shootingStarty,float shootingStartz,float shootingDirectina,float shootingDirectinb,float shootingDirectinc,float pointx,float pointy,float pointz)//求点到直线的距离后，需要求射线的长度
			{
				struct shootingVector 
				{  
					float x;//向量的3个分量的x分量
					float y;
					float z;

				} lineVector1,lineVector2;//网格上一点到射线起点的向量，射线的向量
				lineVector1.x=pointx-shootingStartx;
				lineVector1.y=pointy-shootingStarty;
				lineVector1.z=pointz-shootingStartz;
				lineVector2.x=shootingDirectina;
				lineVector2.y=shootingDirectinb;
				lineVector2.z=shootingDirectinc;
				float cosValue,sinValue,q1,q2,q3;
				q1=lineVector1.x*lineVector2.x+lineVector1.y*lineVector2.y+lineVector1.z*lineVector2.z;
				q2=sqrt(lineVector1.x*lineVector1.x+lineVector1.y*lineVector1.y+lineVector1.z*lineVector1.z);
				q3=sqrt(lineVector2.x*lineVector2.x+lineVector2.y*lineVector2.y+lineVector2.z*lineVector2.z);
				cosValue=q1/(q2*q3);
				if(cosValue<0)
					cosValue=-cosValue;
				

				float d;
				d=q2*cosValue;
				return d;
			}
			float rayManage:: findGridCenterxy(int gridNumber)//输入网格编号，求出中心点的坐标，水平和垂直是一样的
			{
				float gridCenterXY;
				if(gridNumber>0)
				{
					gridCenterXY=2.5*(2*gridNumber-1);
				}
				if(gridNumber<0)
				{
					int w;
					w=-gridNumber;
					gridCenterXY=-2.5*(2*w-1);
				}
				return gridCenterXY;
			}
			complex rayManage::findBuildingComplexCofficient(float cosAngle,float frequence)//求建筑物的反射系数,是个复数，是有相位的
			{
				float sinAngle;
				float jiezhi;//用于求介质的参数
				sinAngle=sqrt(1-cosAngle*cosAngle);
				jiezhi=90000*(-1)/frequence;
				complex temp={0.05-sinAngle*sinAngle,jiezhi};
				complex temp1,temp2,temp3;
				complexCalculate complexCalcu1;
				complexCalcu1.findComplexRoot(temp);
				temp1=complexCalcu1.consequence;
				complexCalcu1.findComplexMulConst(temp1,-1);
				temp1=complexCalcu1.consequence;
				complexCalcu1.findComplexAddConst(temp1,cosAngle);
				temp1=complexCalcu1.consequence;
				complexCalcu1.findComplexRoot(temp);
				temp2=complexCalcu1.consequence;
				complexCalcu1.findComplexAddConst(temp2,cosAngle);
				temp2=complexCalcu1.consequence;
				complexCalcu1.findComplexDivid(temp1,temp2);
				temp3=complexCalcu1.consequence;
				return temp3;
			}
			complex rayManage::findGroundComplexCofficient(float cosAngle,float frequence)//求地面的反射系数,是个复数，是有相位的
			{
				float sinAngle;
				float jiezhi;//用于求介质的参数
				sinAngle=sqrt(1-cosAngle*cosAngle);
				jiezhi=36*(-1)/frequence;
				complex temp={5-sinAngle*sinAngle,jiezhi};
				complex temp1,temp2,temp3;
				complexCalculate complexCalcu1;
				complexCalcu1.findComplexRoot(temp);
				temp1=complexCalcu1.consequence;
				complexCalcu1.findComplexMulConst(temp1,-1);
				temp1=complexCalcu1.consequence;
				complexCalcu1.findComplexAddConst(temp1,cosAngle);
				temp1=complexCalcu1.consequence;
				complexCalcu1.findComplexRoot(temp);
				temp2=complexCalcu1.consequence;
				complexCalcu1.findComplexAddConst(temp2,cosAngle);
				temp2=complexCalcu1.consequence;
				complexCalcu1.findComplexDivid(temp1,temp2);
				temp3=complexCalcu1.consequence;
				return temp3;
			}