#include "diffractionCalculate.h"


diffractionCalculate::diffractionCalculate(void)
{
}


diffractionCalculate::~diffractionCalculate(void)
{
}
void diffractionCalculate::decideDiffractionOperate(float pointx,float pointy,float pointz,float buildingHeight,
		float incidentDirectina,float incidentDirectinb,float incidentDirectinc,float point1x,float point1y,float point2x,float point2y)
		//参数代表的分别是绕射点的坐标，发射绕射的建筑物信息（建筑物折点，高度），入射射线的方向，绕射点所在面在水平面投影对应线段的端点坐标
{
	 shuzhiFlag=0;
	 shuipingFlag=0;
	 diffractionFlag=1;
	 if((fabs(pointz-buildingHeight))<0.02)
		 shuipingFlag=1;
	 if(((sqrt((pointx-point1x)*(pointx-point1x)+(pointy-point1y)*(pointy-point1y)))<0.02||(sqrt((pointx-point2x)*(pointx-point2x)+(pointy-point2y)*(pointy-point2y)))<0.02)&&incidentDirectinc<0)
		 shuzhiFlag=1;
	 if(shuipingFlag==1)
	 {
		 shuipingLengPositionx=pointx;
		 shuipingLengPositiony=pointy;
		 shuipingLengPositionz=buildingHeight;
		 shuipingLengNormalVectorx=incidentDirectinb;
		 shuipingLengNormalVectory=-incidentDirectina;
		 shuipingLengNormalVectorz=0;
	 }
	 if(shuzhiFlag==1)
	 {
		 if(sqrt((pointx-point1x)*(pointx-point1x)+(pointy-point1y)*(pointy-point1y))<0.02)
		 {
			 shuzhiLengPositionx=point1x;
			 shuzhiLengPositiony=point1y;
		 }
		 else
		 {
			 shuzhiLengPositionx=point2x;
			 shuzhiLengPositiony=point2y;
		 }
	 }
	 if(shuipingFlag==0&&shuzhiFlag==0)
		 diffractionFlag=0;//如果竖直棱和水平棱同时发生绕射，选择竖直棱，总的思路是先判断是否会发生绕射，会发生的话然后判断竖直棱，不发生竖直棱的话，就发生水平棱
}
void diffractionCalculate::shuzhiDiffractionOperate(int maxGridx,int maxGridy,float shootingInterval,float baseFrequence,float basePositionx,
		 float basePositiony,float basePositionz,int baseStationNumber,float kuiLength,float incidentDirectina,float incidentDirectinb,float incidentDirectinc,vector<BuildingPoint> oneBPoint,float buildingHeight,float shootingGain,float beforeLength,float beforeCoefficient,vector<vector<BuildingPoint>> BX,vector<float> HX)
	//发生竖直棱绕射时执行的函数，基站的点实际上代表的是绕射点的坐标，最后两个参数代表的是绕射前走的路径长度和反射系数
{
	int mapMaxGridX,mapMaxGridY;//地图的水平网格和垂直网格大小，将来作为模块的输入参数
	mapMaxGridX=maxGridx;
	mapMaxGridY=maxGridy;


	float  rayInterval;//定义射线间隔，到时候写模块函数时需要用到
	rayInterval=shootingInterval;
	float interFrequence;//基站对应扇区的中心频率
	interFrequence=baseFrequence;//以mhz为单位
	float baseStationPositionx, baseStationPositiony, baseStationPositionz;//基站的位置及高度
	baseStationPositionx=basePositionx;
	baseStationPositiony=basePositiony;
	baseStationPositionz=basePositionz;
	float coveringRange=1000;//代表小区覆盖半径
	///////////////////////////////////////////////////////////////////////
	

	ShootingRay shooting1;
	shooting1.shuzhiDiffractionShootingRay(baseStationPositionx,baseStationPositiony,baseStationPositionz,oneBPoint, incidentDirectina, incidentDirectinb, incidentDirectinc,shootingInterval);
	int rayNumber=shooting1.shootingNumber;
	for(int num=0;num<rayNumber;num++)
	{   
		cout<<num<< "        "<<baseStationNumber<<endl;
		shooting1.GetDiffractionRecord(num+1);
		rayPath shooting;
		shooting.firstPointx=baseStationPositionx;
		shooting.firstPointy=baseStationPositiony;
		shooting.firstPointz=baseStationPositionz;
		shooting.firstDirectiona=shooting1.Rx;
		shooting.firstDirectionb=shooting1.Ry;
		shooting.firstDirectionc=shooting1.Rz;
		shooting.rayGain=shootingGain;

		shooting.crossPointx.push_back(shooting.firstPointx);
		shooting.crossPointy.push_back(shooting.firstPointy);
		shooting.crossPointz.push_back(shooting.firstPointz);
		shooting.reflecttDirectiona.push_back(shooting.firstDirectiona);
		shooting.reflecttDirectionb.push_back(shooting.firstDirectionb);
		shooting.reflecttDirectionc.push_back(shooting.firstDirectionc);


		rayManage raymanage1;
		raymanage1.findFinalCrossPoint(shooting.firstPointx,shooting.firstPointy,shooting.firstPointz,shooting.firstDirectiona,shooting.firstDirectionb,shooting.firstDirectionc,mapMaxGridX,mapMaxGridY,coveringRange,BX,HX);
	if(raymanage1.finalCrossFlag==0)
	{
		shooting.searchGridNumberTrue.push_back(raymanage1.gridNumberTrue);
		for(int i=1;i<=raymanage1.gridNumberTrue;i++)
		{ 
			shooting.searchGridTrueX.push_back(raymanage1.gridm[i-1]);
			shooting.searchGridTrueY.push_back(raymanage1.gridn[i-1]);
		}
	}
	if(raymanage1.finalCrossFlag==1)
	{
		shooting.searchGridNumberTrue.push_back(raymanage1.gridNumberStopCross);
		for(int i=1;i<=raymanage1.gridNumberStopCross;i++)
		{ 
			shooting.searchGridTrueX.push_back(raymanage1.gridTruem[i-1]);
			shooting.searchGridTrueY.push_back(raymanage1.gridTruen[i-1]);
		}

	}

	if(raymanage1.finalCrossFlag==0)//与建筑物无交点
			continue;
		if(raymanage1.finalCrossFlag==1&&raymanage1.finalCrossPosition==0&&raymanage1.finalCrossBuildingPosition==1)//落在建筑物的顶面
			continue;
		if(raymanage1.findPathStop(raymanage1.finalRayLength,shooting.rayGain,interFrequence)==1)//路径损耗超过一定值
			continue;
		//在射线路径中存放反射点的位置和本次反射的长度
		shooting.crossPointx.push_back(raymanage1.finalCrossPointx);
		shooting.crossPointy.push_back(raymanage1.finalCrossPointy);
		shooting.crossPointz.push_back(raymanage1.finalCrossPointz);
		shooting.positioniState.push_back(raymanage1.finalCrossBuildingname);
		shooting.rayLength.push_back(raymanage1.finalRayLength);
		//求反射方向和反射系数
		if(raymanage1.finalCrossFlag==1&&raymanage1.finalCrossPosition==1)//落在地面
		{
			raymanage1.findGroundRefDirection(shooting.firstPointx,shooting.firstPointy,shooting.firstPointz,shooting.firstDirectiona,shooting.firstDirectionb,shooting.firstDirectionc);
			float refCoefficientLength;//反射系数的模值
			refCoefficientLength=raymanage1.findGroundRefCofficient(raymanage1.groundRefAngleCos,interFrequence);
			complex refCoefficient;//复的反射系数
			refCoefficient=raymanage1.findGroundComplexCofficient(raymanage1.groundRefAngleCos,interFrequence);
			shooting.reflecttDirectiona.push_back(raymanage1.groundRefDirectionA);
			shooting.reflecttDirectionb.push_back(raymanage1.groundRefDirectionB);
			shooting.reflecttDirectionc.push_back(raymanage1.groundRefDirectionC);
			shooting.reflecttCoefficient.push_back(refCoefficientLength);//存入反射系数的模值
			shooting.reflectComplexCoefficient.push_back(refCoefficient);//存入复的反射系数
			//gridPower gridpower1;
			//gridpower1.findGroundGridPowerFirst(raymanage1.finalCrossPointx,raymanage1.finalCrossPointy,shooting[num].firstPointx,shooting[num].firstPointy,shooting[num].firstPointz,shooting[num].firstDirectiona,shooting[num].firstDirectionb,shooting[num].firstDirectionc,raymanage1.finalRayLength,shooting[num].rayGain,gridNumber);

		}
		
		if(raymanage1.finalCrossFlag==1&&raymanage1.finalCrossPosition==0)//落在建筑物侧面
		{
			//求建筑物的反射方向，入射角的余弦值已知
			raymanage1.findBuildingRefDirection(shooting.firstPointx,shooting.firstPointy,shooting.firstPointz,raymanage1.finalCrossPointx,raymanage1.finalCrossPointy,raymanage1.finalCrossPointz,shooting.firstDirectiona,shooting.firstDirectionb,shooting.firstDirectionc,raymanage1.twoPoint[0],raymanage1.twoPoint[1]);
			float refCoefficientLength;//反射系数的模值
			refCoefficientLength=raymanage1.findBuildingRefCofficient(raymanage1.buildingRefAngleCos,interFrequence);//建筑物反射系数的模值
			complex refCoefficient;//复的反射系数
			refCoefficient=raymanage1.findBuildingComplexCofficient(raymanage1.buildingRefAngleCos,interFrequence);//求建筑物复的反射系数
			shooting.reflecttDirectiona.push_back(raymanage1.buildingRefDirectionA);
			shooting.reflecttDirectionb.push_back(raymanage1.buildingRefDirectionB);
			shooting.reflecttDirectionc.push_back(raymanage1.buildingRefDirectionC);
			shooting.reflecttCoefficient.push_back(refCoefficientLength);//存入反射系数的模值
			shooting.reflectComplexCoefficient.push_back(refCoefficient);//存入复的反射系数
		}
			//进行每条射线的迭代，设置最大反射次数
		int maxRefNum=10;//最大的反射次数,暂时改过来，先测试迭代
		for(int refNum=1;refNum<=maxRefNum;refNum++)
		{
			rayManage raymanage2;
			//求反射点
			
			raymanage2.findFinalCrossPoint(shooting.crossPointx[refNum],shooting.crossPointy[refNum],shooting.crossPointz[refNum],shooting.reflecttDirectiona[refNum],shooting.reflecttDirectionb[refNum],shooting.reflecttDirectionc[refNum],mapMaxGridX,mapMaxGridY,coveringRange,BX,HX);
			if(raymanage2.finalCrossFlag==0)
	{
		shooting.searchGridNumberTrue.push_back(raymanage2.gridNumberTrue);
		for(int i=1;i<=raymanage2.gridNumberTrue;i++)
		{ 
			shooting.searchGridTrueX.push_back(raymanage2.gridm[i-1]);
			shooting.searchGridTrueY.push_back(raymanage2.gridn[i-1]);
		}
	}
	if(raymanage2.finalCrossFlag==1)
	{
		shooting.searchGridNumberTrue.push_back(raymanage2.gridNumberStopCross);
		for(int i=1;i<=raymanage2.gridNumberStopCross;i++)
		{ 
			shooting.searchGridTrueX.push_back(raymanage2.gridTruem[i-1]);
			shooting.searchGridTrueY.push_back(raymanage2.gridTruen[i-1]);
			
		}

	}

			//判断射线停止条件
			if(raymanage2.finalCrossFlag==0)//与建筑物无交点
				break;
			if(raymanage2.finalCrossFlag==1&&raymanage2.finalCrossPosition==0&&raymanage2.finalCrossBuildingPosition==1)//落在建筑物的顶面
				break;
			//存入此次反射路径
			shooting.rayLength.push_back(raymanage2.finalRayLength);
			//判断路径损耗是否超过一定值
			float totalDistance=0;//求出射线总的路径
			int totalNumber=0;
			totalNumber=shooting.rayLength.size();
			for(int i=1;i<=totalNumber;i++)
			
				{
					totalDistance=totalDistance+shooting.rayLength[i-1];
			}
			float totalRefCoefficient=1;//求出射线反射系数的乘积
			int totalRefNumber;
			totalRefNumber=shooting.reflecttCoefficient.size();
			for(int i=1;i<=totalRefNumber;i++)
				{
					 totalRefCoefficient= totalRefCoefficient*shooting.reflecttCoefficient[i-1];

			}
			if(raymanage2.findPathRefStop(totalDistance,shooting.rayGain,totalRefCoefficient,interFrequence)==1)
				break;
			//在射线路径中存放反射点的位置
			shooting.crossPointx.push_back(raymanage2.finalCrossPointx);
			shooting.crossPointy.push_back(raymanage2.finalCrossPointy);
			shooting.crossPointz.push_back(raymanage2.finalCrossPointz);
			shooting.positioniState.push_back(raymanage2.finalCrossBuildingname);
			//求反射方向和反射系数
			if(raymanage2.finalCrossFlag==1&&raymanage2.finalCrossPosition==1)//落在地面
			{
				//求出反射方向，并已经求出入射角的余弦值
				raymanage2.findGroundRefDirection(shooting.crossPointx[refNum],shooting.crossPointy[refNum],shooting.crossPointz[refNum],shooting.reflecttDirectiona[refNum],shooting.reflecttDirectionb[refNum],shooting.reflecttDirectionc[refNum]);
				//求此次地面的发射系数，需要知道入射角
				float refCoefficientLength;//反射系数的模值
				refCoefficientLength=raymanage2.findGroundRefCofficient(raymanage2.groundRefAngleCos,interFrequence);
				complex refCoefficient;//复的反射系数
				refCoefficient=raymanage2.findGroundComplexCofficient(raymanage2.groundRefAngleCos,interFrequence);
				shooting.reflecttDirectiona.push_back(raymanage2.groundRefDirectionA);
				shooting.reflecttDirectionb.push_back(raymanage2.groundRefDirectionB);
				shooting.reflecttDirectionc.push_back(raymanage2.groundRefDirectionC);
				shooting.reflecttCoefficient.push_back(refCoefficientLength);//存入反射系数的模值
				shooting.reflectComplexCoefficient.push_back(refCoefficient);//存入复的反射系数


				//gridPower gridpower1;
				//gridpower1.findGroundGridPowerSecond(raymanage2.finalCrossPointx,raymanage2.finalCrossPointy,shooting[num].crossPointx[refNum-1],shooting[num].crossPointy[refNum-1],shooting[num].crossPointz[refNum-1],
				//	shooting[num].reflecttDirectiona[refNum-1],shooting[num].reflecttDirectionb[refNum-1],shooting[num].reflecttDirectionc[refNum-1],totalDistance,shooting[num].rayGain,totalRefCoefficient,gridNumber);

			}
			if(raymanage2.finalCrossFlag==1&&raymanage2.finalCrossPosition==0)//落在建筑物侧面
			{
				//求建筑物的反射方向，入射角的余弦值已知
				raymanage2.findBuildingRefDirection(shooting.crossPointx[refNum],shooting.crossPointy[refNum],shooting.crossPointz[refNum],raymanage2.finalCrossPointx,raymanage2.finalCrossPointy,raymanage2.finalCrossPointz,shooting.reflecttDirectiona[refNum],shooting.reflecttDirectionb[refNum],shooting.reflecttDirectionc[refNum],raymanage2.twoPoint[0],raymanage2.twoPoint[1]);
				float refCoefficientLength;//反射系数的模值
				refCoefficientLength=raymanage2.findBuildingRefCofficient(raymanage2.buildingRefAngleCos,interFrequence);//建筑物反射系数的模值
				complex refCoefficient;//复的反射系数
				refCoefficient=raymanage2.findBuildingComplexCofficient(raymanage2.buildingRefAngleCos,interFrequence);//求建筑物复的反射系数
				shooting.reflecttDirectiona.push_back(raymanage2.buildingRefDirectionA);
				shooting.reflecttDirectionb.push_back(raymanage2.buildingRefDirectionB);
				shooting.reflecttDirectionc.push_back(raymanage2.buildingRefDirectionC);
				shooting.reflecttCoefficient.push_back(refCoefficientLength);//存入反射系数的模值
				shooting.reflectComplexCoefficient.push_back(refCoefficient);//存入复的反射系数
			}
		}

		gridPower  gridPower4;
			int shootingRecordFlag;//用于记录射线
			shootingRecordFlag=num;
			gridPower4.gridAllPowerDiffractionCalculate(shooting,rayInterval,interFrequence,shootingRecordFlag, kuiLength, beforeLength,beforeCoefficient);
		

	}//代表所有射线执行完的分号

	

}
int diffractionCalculate::decideInsidePolygon(float pointx,float pointy,vector<BuildingPoint> BPoint)//用叉积判断点是否在多边形内，返回值为1的话代表在多边形内
{
	double x0,y0,med,resulty;//需要判断的点
		 x0=pointx;
		 y0= pointy;
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
					return insideFlag;
	
	/*int i;
	float sideX,sideY,polyVertexX,polyVertexY,crossProduct;
	float sideX0,sideY0,polyVertexX0,polyVertexY0,crossProduct0;
	float sideXF,sideYF,polyVertexXF,polyVertexYF,crossProductF;

	sideX0=BPoint[1].px-BPoint[0].px;
	sideY0=BPoint[1].py-BPoint[0].py;
	polyVertexX0=pointx-BPoint[0].px;
	polyVertexY0=pointy-BPoint[0].py;
	crossProduct0=sideX0*polyVertexY0-sideY0*polyVertexX0;

	for(i=1;i<BPoint.size()-1;i++)
	{
		sideX=BPoint[i+1].px-BPoint[i].px;
		sideY=BPoint[i+1].py-BPoint[i].py;
		polyVertexX=pointx-BPoint[i].px;
		polyVertexY=pointy-BPoint[i].py;
		crossProduct=sideX*polyVertexY-sideY*polyVertexX;

		if(crossProduct0*crossProduct<0)
		{
			return 0;
		}
	}

	sideXF=BPoint[0].px-BPoint[i].px;
	sideYF=BPoint[0].py-BPoint[i].py;
	polyVertexXF=pointx-BPoint[i].px;
	polyVertexYF=pointy-BPoint[i].py;
	crossProductF=sideXF*polyVertexYF-polyVertexXF*sideYF;

	if(crossProduct0*crossProductF<0)
		{
			return 0;
		}

	return 1;*/

}




void diffractionCalculate:: shupingDiffractionOperate(int maxGridx,int maxGridy,float shootingInterval,float baseFrequence,float basePositionx,
		float basePositiony,float basePositionz,int baseStationNumber,float kuiLength,float incidentDirectina,float incidentDirectinb,float incidentDirectinc,vector<BuildingPoint> oneBPoint,float buildingHeight,float shootingGain,float beforeLength,float beforeCoefficient,float roofLengPoint1x,
		float roofLengPoint1y,float roofLengPoint2x,float roofLengPoint2y,float vectorx,float vectory,float vectorz,vector<vector<BuildingPoint>> BX,vector<float> HX)//水平棱绕射,最后7个参数代表发生绕射的棱的两个端点坐标,水平棱的法向量，指向建筑物外
{

	int mapMaxGridX,mapMaxGridY;//地图的水平网格和垂直网格大小，将来作为模块的输入参数
	mapMaxGridX=maxGridx;
	mapMaxGridY=maxGridy;


	float  rayInterval;//定义射线间隔，到时候写模块函数时需要用到
	rayInterval=shootingInterval;
	float interFrequence;//基站对应扇区的中心频率
	interFrequence=baseFrequence;//以mhz为单位
	float baseStationPositionx, baseStationPositiony, baseStationPositionz;//基站的位置及高度
	baseStationPositionx=basePositionx;
	baseStationPositiony=basePositiony;
	baseStationPositionz=basePositionz;
	float coveringRange=1000;//代表小区覆盖半径
	

	ShootingRay shooting1;
	//shooting1.shuiPingDiffractionShootingRay();
	shooting1.shuiPingDiffractionShootingRay(baseStationPositionx,baseStationPositiony,baseStationPositionz,buildingHeight, incidentDirectina, incidentDirectinb, incidentDirectinc,
		shootingInterval,vectorx,vectory,vectorz,roofLengPoint1x,roofLengPoint1y,roofLengPoint2x,roofLengPoint2y);
	int rayNumber=shooting1.shootingNumber;
	for(int num=0;num<rayNumber;num++)
	{   
		cout<<num<< "        "<<baseStationNumber<<endl;
		shooting1.GetDiffractionRecord(num+1);
		rayPath shooting;
		shooting.firstPointx=baseStationPositionx;
		shooting.firstPointy=baseStationPositiony;
		shooting.firstPointz=baseStationPositionz;
		shooting.firstDirectiona=shooting1.Rx;
		shooting.firstDirectionb=shooting1.Ry;
		shooting.firstDirectionc=shooting1.Rz;
		shooting.rayGain=shootingGain;

		shooting.crossPointx.push_back(shooting.firstPointx);
		shooting.crossPointy.push_back(shooting.firstPointy);
		shooting.crossPointz.push_back(shooting.firstPointz);
		shooting.reflecttDirectiona.push_back(shooting.firstDirectiona);
		shooting.reflecttDirectionb.push_back(shooting.firstDirectionb);
		shooting.reflecttDirectionc.push_back(shooting.firstDirectionc);


		rayManage raymanage1;
		raymanage1.findFinalCrossPoint(shooting.firstPointx,shooting.firstPointy,shooting.firstPointz,shooting.firstDirectiona,shooting.firstDirectionb,shooting.firstDirectionc,mapMaxGridX,mapMaxGridY,coveringRange,BX,HX);
		if(raymanage1.finalCrossFlag==0)
		{
			shooting.searchGridNumberTrue.push_back(raymanage1.gridNumberTrue);
			for(int i=1;i<=raymanage1.gridNumberTrue;i++)
			{ 
				shooting.searchGridTrueX.push_back(raymanage1.gridm[i-1]);
				shooting.searchGridTrueY.push_back(raymanage1.gridn[i-1]);
			}
		}
		if(raymanage1.finalCrossFlag==1)
		{
			shooting.searchGridNumberTrue.push_back(raymanage1.gridNumberStopCross);
			for(int i=1;i<=raymanage1.gridNumberStopCross;i++)
			{ 
				shooting.searchGridTrueX.push_back(raymanage1.gridTruem[i-1]);
				shooting.searchGridTrueY.push_back(raymanage1.gridTruen[i-1]);
			}

		}

		if(raymanage1.finalCrossFlag==0)//与建筑物无交点
			continue;
		if(raymanage1.finalCrossFlag==1&&raymanage1.finalCrossPosition==0&&raymanage1.finalCrossBuildingPosition==1)//落在建筑物的顶面
			continue;
		if(raymanage1.findPathStop(raymanage1.finalRayLength,shooting.rayGain,interFrequence)==1)//路径损耗超过一定值
			continue;
		//在射线路径中存放反射点的位置和本次反射的长度
		shooting.crossPointx.push_back(raymanage1.finalCrossPointx);
		shooting.crossPointy.push_back(raymanage1.finalCrossPointy);
		shooting.crossPointz.push_back(raymanage1.finalCrossPointz);
		shooting.positioniState.push_back(raymanage1.finalCrossBuildingname);
		shooting.rayLength.push_back(raymanage1.finalRayLength);
		//求反射方向和反射系数
		if(raymanage1.finalCrossFlag==1&&raymanage1.finalCrossPosition==1)//落在地面
		{
			raymanage1.findGroundRefDirection(shooting.firstPointx,shooting.firstPointy,shooting.firstPointz,shooting.firstDirectiona,shooting.firstDirectionb,shooting.firstDirectionc);
			float refCoefficientLength;//反射系数的模值
			refCoefficientLength=raymanage1.findGroundRefCofficient(raymanage1.groundRefAngleCos,interFrequence);
			complex refCoefficient;//复的反射系数
			refCoefficient=raymanage1.findGroundComplexCofficient(raymanage1.groundRefAngleCos,interFrequence);
			shooting.reflecttDirectiona.push_back(raymanage1.groundRefDirectionA);
			shooting.reflecttDirectionb.push_back(raymanage1.groundRefDirectionB);
			shooting.reflecttDirectionc.push_back(raymanage1.groundRefDirectionC);
			shooting.reflecttCoefficient.push_back(refCoefficientLength);//存入反射系数的模值
			shooting.reflectComplexCoefficient.push_back(refCoefficient);//存入复的反射系数
			//gridPower gridpower1;
			//gridpower1.findGroundGridPowerFirst(raymanage1.finalCrossPointx,raymanage1.finalCrossPointy,shooting[num].firstPointx,shooting[num].firstPointy,shooting[num].firstPointz,shooting[num].firstDirectiona,shooting[num].firstDirectionb,shooting[num].firstDirectionc,raymanage1.finalRayLength,shooting[num].rayGain,gridNumber);

		}

		if(raymanage1.finalCrossFlag==1&&raymanage1.finalCrossPosition==0)//落在建筑物侧面
		{
			//求建筑物的反射方向，入射角的余弦值已知
			raymanage1.findBuildingRefDirection(shooting.firstPointx,shooting.firstPointy,shooting.firstPointz,raymanage1.finalCrossPointx,raymanage1.finalCrossPointy,raymanage1.finalCrossPointz,shooting.firstDirectiona,shooting.firstDirectionb,shooting.firstDirectionc,raymanage1.twoPoint[0],raymanage1.twoPoint[1]);
			float refCoefficientLength;//反射系数的模值
			refCoefficientLength=raymanage1.findBuildingRefCofficient(raymanage1.buildingRefAngleCos,interFrequence);//建筑物反射系数的模值
			complex refCoefficient;//复的反射系数
			refCoefficient=raymanage1.findBuildingComplexCofficient(raymanage1.buildingRefAngleCos,interFrequence);//求建筑物复的反射系数
			shooting.reflecttDirectiona.push_back(raymanage1.buildingRefDirectionA);
			shooting.reflecttDirectionb.push_back(raymanage1.buildingRefDirectionB);
			shooting.reflecttDirectionc.push_back(raymanage1.buildingRefDirectionC);
			shooting.reflecttCoefficient.push_back(refCoefficientLength);//存入反射系数的模值
			shooting.reflectComplexCoefficient.push_back(refCoefficient);//存入复的反射系数
		}
		//进行每条射线的迭代，设置最大反射次数
		int maxRefNum=10;//最大的反射次数,暂时改过来，先测试迭代
		for(int refNum=1;refNum<=maxRefNum;refNum++)
		{
			rayManage raymanage2;
			//求反射点

			raymanage2.findFinalCrossPoint(shooting.crossPointx[refNum],shooting.crossPointy[refNum],shooting.crossPointz[refNum],shooting.reflecttDirectiona[refNum],shooting.reflecttDirectionb[refNum],shooting.reflecttDirectionc[refNum],mapMaxGridX,mapMaxGridY,coveringRange,BX,HX);
			if(raymanage2.finalCrossFlag==0)
			{
				shooting.searchGridNumberTrue.push_back(raymanage2.gridNumberTrue);
				for(int i=1;i<=raymanage2.gridNumberTrue;i++)
				{ 
					shooting.searchGridTrueX.push_back(raymanage2.gridm[i-1]);
					shooting.searchGridTrueY.push_back(raymanage2.gridn[i-1]);
				}
			}
			if(raymanage2.finalCrossFlag==1)
			{
				shooting.searchGridNumberTrue.push_back(raymanage2.gridNumberStopCross);
				for(int i=1;i<=raymanage2.gridNumberStopCross;i++)
				{ 
					shooting.searchGridTrueX.push_back(raymanage2.gridTruem[i-1]);
					shooting.searchGridTrueY.push_back(raymanage2.gridTruen[i-1]);

				}

			}

			//判断射线停止条件
			if(raymanage2.finalCrossFlag==0)//与建筑物无交点
				break;
			if(raymanage2.finalCrossFlag==1&&raymanage2.finalCrossPosition==0&&raymanage2.finalCrossBuildingPosition==1)//落在建筑物的顶面
				break;
			//存入此次反射路径
			shooting.rayLength.push_back(raymanage2.finalRayLength);
			//判断路径损耗是否超过一定值
			float totalDistance=0;//求出射线总的路径
			int totalNumber=0;
			totalNumber=shooting.rayLength.size();
			for(int i=1;i<=totalNumber;i++)

			{
				totalDistance=totalDistance+shooting.rayLength[i-1];
			}
			float totalRefCoefficient=1;//求出射线反射系数的乘积
			int totalRefNumber;
			totalRefNumber=shooting.reflecttCoefficient.size();
			for(int i=1;i<=totalRefNumber;i++)
			{
				totalRefCoefficient= totalRefCoefficient*shooting.reflecttCoefficient[i-1];

			}
			if(raymanage2.findPathRefStop(totalDistance,shooting.rayGain,totalRefCoefficient,interFrequence)==1)
				break;
			//在射线路径中存放反射点的位置
			shooting.crossPointx.push_back(raymanage2.finalCrossPointx);
			shooting.crossPointy.push_back(raymanage2.finalCrossPointy);
			shooting.crossPointz.push_back(raymanage2.finalCrossPointz);
			shooting.positioniState.push_back(raymanage2.finalCrossBuildingname);
			//求反射方向和反射系数
			if(raymanage2.finalCrossFlag==1&&raymanage2.finalCrossPosition==1)//落在地面
			{
				//求出反射方向，并已经求出入射角的余弦值
				raymanage2.findGroundRefDirection(shooting.crossPointx[refNum],shooting.crossPointy[refNum],shooting.crossPointz[refNum],shooting.reflecttDirectiona[refNum],shooting.reflecttDirectionb[refNum],shooting.reflecttDirectionc[refNum]);
				//求此次地面的发射系数，需要知道入射角
				float refCoefficientLength;//反射系数的模值
				refCoefficientLength=raymanage2.findGroundRefCofficient(raymanage2.groundRefAngleCos,interFrequence);
				complex refCoefficient;//复的反射系数
				refCoefficient=raymanage2.findGroundComplexCofficient(raymanage2.groundRefAngleCos,interFrequence);
				shooting.reflecttDirectiona.push_back(raymanage2.groundRefDirectionA);
				shooting.reflecttDirectionb.push_back(raymanage2.groundRefDirectionB);
				shooting.reflecttDirectionc.push_back(raymanage2.groundRefDirectionC);
				shooting.reflecttCoefficient.push_back(refCoefficientLength);//存入反射系数的模值
				shooting.reflectComplexCoefficient.push_back(refCoefficient);//存入复的反射系数


				//gridPower gridpower1;
				//gridpower1.findGroundGridPowerSecond(raymanage2.finalCrossPointx,raymanage2.finalCrossPointy,shooting[num].crossPointx[refNum-1],shooting[num].crossPointy[refNum-1],shooting[num].crossPointz[refNum-1],
				//	shooting[num].reflecttDirectiona[refNum-1],shooting[num].reflecttDirectionb[refNum-1],shooting[num].reflecttDirectionc[refNum-1],totalDistance,shooting[num].rayGain,totalRefCoefficient,gridNumber);

			}
			if(raymanage2.finalCrossFlag==1&&raymanage2.finalCrossPosition==0)//落在建筑物侧面
			{
				//求建筑物的反射方向，入射角的余弦值已知
				raymanage2.findBuildingRefDirection(shooting.crossPointx[refNum],shooting.crossPointy[refNum],shooting.crossPointz[refNum],raymanage2.finalCrossPointx,raymanage2.finalCrossPointy,raymanage2.finalCrossPointz,shooting.reflecttDirectiona[refNum],shooting.reflecttDirectionb[refNum],shooting.reflecttDirectionc[refNum],raymanage2.twoPoint[0],raymanage2.twoPoint[1]);
				float refCoefficientLength;//反射系数的模值
				refCoefficientLength=raymanage2.findBuildingRefCofficient(raymanage2.buildingRefAngleCos,interFrequence);//建筑物反射系数的模值
				complex refCoefficient;//复的反射系数
				refCoefficient=raymanage2.findBuildingComplexCofficient(raymanage2.buildingRefAngleCos,interFrequence);//求建筑物复的反射系数
				shooting.reflecttDirectiona.push_back(raymanage2.buildingRefDirectionA);
				shooting.reflecttDirectionb.push_back(raymanage2.buildingRefDirectionB);
				shooting.reflecttDirectionc.push_back(raymanage2.buildingRefDirectionC);
				shooting.reflecttCoefficient.push_back(refCoefficientLength);//存入反射系数的模值
				shooting.reflectComplexCoefficient.push_back(refCoefficient);//存入复的反射系数
			}
		}

		gridPower  gridPower4;
		int shootingRecordFlag;//用于记录射线
		shootingRecordFlag=num;
		gridPower4.gridAllPowerDiffractionCalculate(shooting,rayInterval,interFrequence,shootingRecordFlag, kuiLength, beforeLength,beforeCoefficient);


	}//代表所有射线执行完的分号

	
}
void diffractionCalculate::decideRoofLengDiffraction(float pointx,float pointy,vector<BuildingPoint> oneBPoint,float buildingHeight)//用来判断射线落到顶面是否会发生绕射
{
	roofLengdiffractionFlag=0;
	//for(int i=0;i<oneBPoint.size()-1;i++)
		for(int i=3;i<4;i++)//只考虑建筑物100的1个棱
	{
		float point1x,point1y,point2x,point2y,directionx,directiony,directionz;
		point1x=oneBPoint[i].px;
		point1y=oneBPoint[i].py;
		point2x=oneBPoint[i+1].px;
		point2y=oneBPoint[i+1].py;
		directionx=point2x-point1x;
		directiony=point2y-point1y;
		rayManage q1;
		if(q1.findPointToLineDistance(point1x,point1y,0,directionx,directiony,0,pointx,pointy,0)<0.02)
		{
			roofLengdiffractionFlag=1;
			lengPoint1x=point1x;
			lengPoint1y=point1y;
			lengPoint2x=point2x;
			lengPoint2y=point2y;

		}

	}
	if(roofLengdiffractionFlag==1)
	{
		float d1=sqrt((pointx-lengPoint1x)*(pointx-lengPoint1x)+(pointy-lengPoint1y)*(pointy-lengPoint1y));//求出顶面反射点与棱的左侧端点的距离
		float d2=sqrt((lengPoint1x-lengPoint2x)*(lengPoint1x-lengPoint2x)+(lengPoint1y-lengPoint2y)*(lengPoint1y-lengPoint2y));//求出发生绕射棱的长度
		float vectorLine1x,vectorLine1y,vectorLine1z;//由棱的左端点指向顶面反射点的向量
		float vectorLine2x,vectorLine2y,vectorLine2z;//由棱的左端点指向棱的右端点的向量
		vectorLine1x=pointx-lengPoint1x;
		vectorLine1y=pointy-lengPoint1y;
		vectorLine1z=0;
		vectorLine2x=lengPoint2x-lengPoint1x;
		vectorLine2y=lengPoint2y-lengPoint1y;
		vectorLine2z=0;
		float cosAngle=(vectorLine1x*vectorLine2x+vectorLine2x*vectorLine2y)/(sqrt(d1)*sqrt(d2));//vectorline1与vectorline2向量夹角的余弦值
		if(cosAngle<0)
			cosAngle=-cosAngle;
		float d3=d1*cosAngle;//line1在line2上的投影长度
		float ratio;
		ratio=d3/d2;
		shuipingLengPositionx=(lengPoint2x-lengPoint1x)*ratio+lengPoint1x;
		shuipingLengPositiony=(lengPoint2y-lengPoint1y)*ratio+lengPoint1y;
		shuipingLengPositionz=buildingHeight;
		float normalVectorx, normalVectory, normalVectorz;
		normalVectorx=vectorLine2y;
		normalVectory=-vectorLine2x;
		normalVectorz=0;
		if(normalVectorx*vectorLine1x+normalVectory*vectorLine1y>0)
		{

			normalVectorx=-normalVectorx;
			normalVectory=-normalVectory;
			
		}
		shuipingLengNormalVectorx=normalVectorx;
		shuipingLengNormalVectory=normalVectory;
		shuipingLengNormalVectorz=normalVectorz;


	}
}
