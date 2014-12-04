#include "diffractionCalculate.h"


diffractionCalculate::diffractionCalculate(void)
{
}


diffractionCalculate::~diffractionCalculate(void)
{
}
void diffractionCalculate::decideDiffractionOperate(float pointx,float pointy,float pointz,float buildingHeight,
		float incidentDirectina,float incidentDirectinb,float incidentDirectinc,float point1x,float point1y,float point2x,float point2y)
		//��������ķֱ������������꣬��������Ľ�������Ϣ���������۵㣬�߶ȣ����������ߵķ����������������ˮƽ��ͶӰ��Ӧ�߶εĶ˵�����
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
		 diffractionFlag=0;//�����ֱ���ˮƽ��ͬʱ�������䣬ѡ����ֱ�⣬�ܵ�˼·�����ж��Ƿ�ᷢ�����䣬�ᷢ���Ļ�Ȼ���ж���ֱ�⣬��������ֱ��Ļ����ͷ���ˮƽ��
}
void diffractionCalculate::shuzhiDiffractionOperate(int maxGridx,int maxGridy,float shootingInterval,float baseFrequence,float basePositionx,
		 float basePositiony,float basePositionz,int baseStationNumber,float kuiLength,float incidentDirectina,float incidentDirectinb,float incidentDirectinc,vector<BuildingPoint> oneBPoint,float buildingHeight,float shootingGain,float beforeLength,float beforeCoefficient,vector<vector<BuildingPoint>> BX,vector<float> HX)
	//������ֱ������ʱִ�еĺ�������վ�ĵ�ʵ���ϴ���������������꣬����������������������ǰ�ߵ�·�����Ⱥͷ���ϵ��
{
	int mapMaxGridX,mapMaxGridY;//��ͼ��ˮƽ����ʹ�ֱ�����С��������Ϊģ����������
	mapMaxGridX=maxGridx;
	mapMaxGridY=maxGridy;


	float  rayInterval;//�������߼������ʱ��дģ�麯��ʱ��Ҫ�õ�
	rayInterval=shootingInterval;
	float interFrequence;//��վ��Ӧ����������Ƶ��
	interFrequence=baseFrequence;//��mhzΪ��λ
	float baseStationPositionx, baseStationPositiony, baseStationPositionz;//��վ��λ�ü��߶�
	baseStationPositionx=basePositionx;
	baseStationPositiony=basePositiony;
	baseStationPositionz=basePositionz;
	float coveringRange=1000;//����С�����ǰ뾶
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

	if(raymanage1.finalCrossFlag==0)//�뽨�����޽���
			continue;
		if(raymanage1.finalCrossFlag==1&&raymanage1.finalCrossPosition==0&&raymanage1.finalCrossBuildingPosition==1)//���ڽ�����Ķ���
			continue;
		if(raymanage1.findPathStop(raymanage1.finalRayLength,shooting.rayGain,interFrequence)==1)//·����ĳ���һ��ֵ
			continue;
		//������·���д�ŷ�����λ�úͱ��η���ĳ���
		shooting.crossPointx.push_back(raymanage1.finalCrossPointx);
		shooting.crossPointy.push_back(raymanage1.finalCrossPointy);
		shooting.crossPointz.push_back(raymanage1.finalCrossPointz);
		shooting.positioniState.push_back(raymanage1.finalCrossBuildingname);
		shooting.rayLength.push_back(raymanage1.finalRayLength);
		//���䷽��ͷ���ϵ��
		if(raymanage1.finalCrossFlag==1&&raymanage1.finalCrossPosition==1)//���ڵ���
		{
			raymanage1.findGroundRefDirection(shooting.firstPointx,shooting.firstPointy,shooting.firstPointz,shooting.firstDirectiona,shooting.firstDirectionb,shooting.firstDirectionc);
			float refCoefficientLength;//����ϵ����ģֵ
			refCoefficientLength=raymanage1.findGroundRefCofficient(raymanage1.groundRefAngleCos,interFrequence);
			complex refCoefficient;//���ķ���ϵ��
			refCoefficient=raymanage1.findGroundComplexCofficient(raymanage1.groundRefAngleCos,interFrequence);
			shooting.reflecttDirectiona.push_back(raymanage1.groundRefDirectionA);
			shooting.reflecttDirectionb.push_back(raymanage1.groundRefDirectionB);
			shooting.reflecttDirectionc.push_back(raymanage1.groundRefDirectionC);
			shooting.reflecttCoefficient.push_back(refCoefficientLength);//���뷴��ϵ����ģֵ
			shooting.reflectComplexCoefficient.push_back(refCoefficient);//���븴�ķ���ϵ��
			//gridPower gridpower1;
			//gridpower1.findGroundGridPowerFirst(raymanage1.finalCrossPointx,raymanage1.finalCrossPointy,shooting[num].firstPointx,shooting[num].firstPointy,shooting[num].firstPointz,shooting[num].firstDirectiona,shooting[num].firstDirectionb,shooting[num].firstDirectionc,raymanage1.finalRayLength,shooting[num].rayGain,gridNumber);

		}
		
		if(raymanage1.finalCrossFlag==1&&raymanage1.finalCrossPosition==0)//���ڽ��������
		{
			//������ķ��䷽������ǵ�����ֵ��֪
			raymanage1.findBuildingRefDirection(shooting.firstPointx,shooting.firstPointy,shooting.firstPointz,raymanage1.finalCrossPointx,raymanage1.finalCrossPointy,raymanage1.finalCrossPointz,shooting.firstDirectiona,shooting.firstDirectionb,shooting.firstDirectionc,raymanage1.twoPoint[0],raymanage1.twoPoint[1]);
			float refCoefficientLength;//����ϵ����ģֵ
			refCoefficientLength=raymanage1.findBuildingRefCofficient(raymanage1.buildingRefAngleCos,interFrequence);//�����ﷴ��ϵ����ģֵ
			complex refCoefficient;//���ķ���ϵ��
			refCoefficient=raymanage1.findBuildingComplexCofficient(raymanage1.buildingRefAngleCos,interFrequence);//�����︴�ķ���ϵ��
			shooting.reflecttDirectiona.push_back(raymanage1.buildingRefDirectionA);
			shooting.reflecttDirectionb.push_back(raymanage1.buildingRefDirectionB);
			shooting.reflecttDirectionc.push_back(raymanage1.buildingRefDirectionC);
			shooting.reflecttCoefficient.push_back(refCoefficientLength);//���뷴��ϵ����ģֵ
			shooting.reflectComplexCoefficient.push_back(refCoefficient);//���븴�ķ���ϵ��
		}
			//����ÿ�����ߵĵ�����������������
		int maxRefNum=10;//���ķ������,��ʱ�Ĺ������Ȳ��Ե���
		for(int refNum=1;refNum<=maxRefNum;refNum++)
		{
			rayManage raymanage2;
			//�����
			
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

			//�ж�����ֹͣ����
			if(raymanage2.finalCrossFlag==0)//�뽨�����޽���
				break;
			if(raymanage2.finalCrossFlag==1&&raymanage2.finalCrossPosition==0&&raymanage2.finalCrossBuildingPosition==1)//���ڽ�����Ķ���
				break;
			//����˴η���·��
			shooting.rayLength.push_back(raymanage2.finalRayLength);
			//�ж�·������Ƿ񳬹�һ��ֵ
			float totalDistance=0;//��������ܵ�·��
			int totalNumber=0;
			totalNumber=shooting.rayLength.size();
			for(int i=1;i<=totalNumber;i++)
			
				{
					totalDistance=totalDistance+shooting.rayLength[i-1];
			}
			float totalRefCoefficient=1;//������߷���ϵ���ĳ˻�
			int totalRefNumber;
			totalRefNumber=shooting.reflecttCoefficient.size();
			for(int i=1;i<=totalRefNumber;i++)
				{
					 totalRefCoefficient= totalRefCoefficient*shooting.reflecttCoefficient[i-1];

			}
			if(raymanage2.findPathRefStop(totalDistance,shooting.rayGain,totalRefCoefficient,interFrequence)==1)
				break;
			//������·���д�ŷ�����λ��
			shooting.crossPointx.push_back(raymanage2.finalCrossPointx);
			shooting.crossPointy.push_back(raymanage2.finalCrossPointy);
			shooting.crossPointz.push_back(raymanage2.finalCrossPointz);
			shooting.positioniState.push_back(raymanage2.finalCrossBuildingname);
			//���䷽��ͷ���ϵ��
			if(raymanage2.finalCrossFlag==1&&raymanage2.finalCrossPosition==1)//���ڵ���
			{
				//������䷽�򣬲��Ѿ��������ǵ�����ֵ
				raymanage2.findGroundRefDirection(shooting.crossPointx[refNum],shooting.crossPointy[refNum],shooting.crossPointz[refNum],shooting.reflecttDirectiona[refNum],shooting.reflecttDirectionb[refNum],shooting.reflecttDirectionc[refNum]);
				//��˴ε���ķ���ϵ������Ҫ֪�������
				float refCoefficientLength;//����ϵ����ģֵ
				refCoefficientLength=raymanage2.findGroundRefCofficient(raymanage2.groundRefAngleCos,interFrequence);
				complex refCoefficient;//���ķ���ϵ��
				refCoefficient=raymanage2.findGroundComplexCofficient(raymanage2.groundRefAngleCos,interFrequence);
				shooting.reflecttDirectiona.push_back(raymanage2.groundRefDirectionA);
				shooting.reflecttDirectionb.push_back(raymanage2.groundRefDirectionB);
				shooting.reflecttDirectionc.push_back(raymanage2.groundRefDirectionC);
				shooting.reflecttCoefficient.push_back(refCoefficientLength);//���뷴��ϵ����ģֵ
				shooting.reflectComplexCoefficient.push_back(refCoefficient);//���븴�ķ���ϵ��


				//gridPower gridpower1;
				//gridpower1.findGroundGridPowerSecond(raymanage2.finalCrossPointx,raymanage2.finalCrossPointy,shooting[num].crossPointx[refNum-1],shooting[num].crossPointy[refNum-1],shooting[num].crossPointz[refNum-1],
				//	shooting[num].reflecttDirectiona[refNum-1],shooting[num].reflecttDirectionb[refNum-1],shooting[num].reflecttDirectionc[refNum-1],totalDistance,shooting[num].rayGain,totalRefCoefficient,gridNumber);

			}
			if(raymanage2.finalCrossFlag==1&&raymanage2.finalCrossPosition==0)//���ڽ��������
			{
				//������ķ��䷽������ǵ�����ֵ��֪
				raymanage2.findBuildingRefDirection(shooting.crossPointx[refNum],shooting.crossPointy[refNum],shooting.crossPointz[refNum],raymanage2.finalCrossPointx,raymanage2.finalCrossPointy,raymanage2.finalCrossPointz,shooting.reflecttDirectiona[refNum],shooting.reflecttDirectionb[refNum],shooting.reflecttDirectionc[refNum],raymanage2.twoPoint[0],raymanage2.twoPoint[1]);
				float refCoefficientLength;//����ϵ����ģֵ
				refCoefficientLength=raymanage2.findBuildingRefCofficient(raymanage2.buildingRefAngleCos,interFrequence);//�����ﷴ��ϵ����ģֵ
				complex refCoefficient;//���ķ���ϵ��
				refCoefficient=raymanage2.findBuildingComplexCofficient(raymanage2.buildingRefAngleCos,interFrequence);//�����︴�ķ���ϵ��
				shooting.reflecttDirectiona.push_back(raymanage2.buildingRefDirectionA);
				shooting.reflecttDirectionb.push_back(raymanage2.buildingRefDirectionB);
				shooting.reflecttDirectionc.push_back(raymanage2.buildingRefDirectionC);
				shooting.reflecttCoefficient.push_back(refCoefficientLength);//���뷴��ϵ����ģֵ
				shooting.reflectComplexCoefficient.push_back(refCoefficient);//���븴�ķ���ϵ��
			}
		}

		gridPower  gridPower4;
			int shootingRecordFlag;//���ڼ�¼����
			shootingRecordFlag=num;
			gridPower4.gridAllPowerDiffractionCalculate(shooting,rayInterval,interFrequence,shootingRecordFlag, kuiLength, beforeLength,beforeCoefficient);
		

	}//������������ִ����ķֺ�

	

}
int diffractionCalculate::decideInsidePolygon(float pointx,float pointy,vector<BuildingPoint> BPoint)//�ò���жϵ��Ƿ��ڶ�����ڣ�����ֵΪ1�Ļ������ڶ������
{
	double x0,y0,med,resulty;//��Ҫ�жϵĵ�
		 x0=pointx;
		 y0= pointy;
		  vector<double> crosspointy;//������������y����
			   int n1,insideFlag;//n1�����ж����Ľ����ظ��ĸ�����insideFlag=1Ϊ���ڶ������
			   n1=0;
			   insideFlag=0;
			   for(int i=0;i<=BPoint.size()-2;i++)
			   {
				   double x1,y1, x2,y2;//������¼��ȡ���ݵĵ�
				   x1=BPoint[i].px;y1=BPoint[i].py;
				   x2=BPoint[i+1].px;y2=BPoint[i+1].py;
				   //ʹx1С��x2,ʹy1С��y2
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
					//�жϵ��Ƿ����߶���
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
			   //���ظ��Ľ������
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
		float roofLengPoint1y,float roofLengPoint2x,float roofLengPoint2y,float vectorx,float vectory,float vectorz,vector<vector<BuildingPoint>> BX,vector<float> HX)//ˮƽ������,���7�������������������������˵�����,ˮƽ��ķ�������ָ��������
{

	int mapMaxGridX,mapMaxGridY;//��ͼ��ˮƽ����ʹ�ֱ�����С��������Ϊģ����������
	mapMaxGridX=maxGridx;
	mapMaxGridY=maxGridy;


	float  rayInterval;//�������߼������ʱ��дģ�麯��ʱ��Ҫ�õ�
	rayInterval=shootingInterval;
	float interFrequence;//��վ��Ӧ����������Ƶ��
	interFrequence=baseFrequence;//��mhzΪ��λ
	float baseStationPositionx, baseStationPositiony, baseStationPositionz;//��վ��λ�ü��߶�
	baseStationPositionx=basePositionx;
	baseStationPositiony=basePositiony;
	baseStationPositionz=basePositionz;
	float coveringRange=1000;//����С�����ǰ뾶
	

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

		if(raymanage1.finalCrossFlag==0)//�뽨�����޽���
			continue;
		if(raymanage1.finalCrossFlag==1&&raymanage1.finalCrossPosition==0&&raymanage1.finalCrossBuildingPosition==1)//���ڽ�����Ķ���
			continue;
		if(raymanage1.findPathStop(raymanage1.finalRayLength,shooting.rayGain,interFrequence)==1)//·����ĳ���һ��ֵ
			continue;
		//������·���д�ŷ�����λ�úͱ��η���ĳ���
		shooting.crossPointx.push_back(raymanage1.finalCrossPointx);
		shooting.crossPointy.push_back(raymanage1.finalCrossPointy);
		shooting.crossPointz.push_back(raymanage1.finalCrossPointz);
		shooting.positioniState.push_back(raymanage1.finalCrossBuildingname);
		shooting.rayLength.push_back(raymanage1.finalRayLength);
		//���䷽��ͷ���ϵ��
		if(raymanage1.finalCrossFlag==1&&raymanage1.finalCrossPosition==1)//���ڵ���
		{
			raymanage1.findGroundRefDirection(shooting.firstPointx,shooting.firstPointy,shooting.firstPointz,shooting.firstDirectiona,shooting.firstDirectionb,shooting.firstDirectionc);
			float refCoefficientLength;//����ϵ����ģֵ
			refCoefficientLength=raymanage1.findGroundRefCofficient(raymanage1.groundRefAngleCos,interFrequence);
			complex refCoefficient;//���ķ���ϵ��
			refCoefficient=raymanage1.findGroundComplexCofficient(raymanage1.groundRefAngleCos,interFrequence);
			shooting.reflecttDirectiona.push_back(raymanage1.groundRefDirectionA);
			shooting.reflecttDirectionb.push_back(raymanage1.groundRefDirectionB);
			shooting.reflecttDirectionc.push_back(raymanage1.groundRefDirectionC);
			shooting.reflecttCoefficient.push_back(refCoefficientLength);//���뷴��ϵ����ģֵ
			shooting.reflectComplexCoefficient.push_back(refCoefficient);//���븴�ķ���ϵ��
			//gridPower gridpower1;
			//gridpower1.findGroundGridPowerFirst(raymanage1.finalCrossPointx,raymanage1.finalCrossPointy,shooting[num].firstPointx,shooting[num].firstPointy,shooting[num].firstPointz,shooting[num].firstDirectiona,shooting[num].firstDirectionb,shooting[num].firstDirectionc,raymanage1.finalRayLength,shooting[num].rayGain,gridNumber);

		}

		if(raymanage1.finalCrossFlag==1&&raymanage1.finalCrossPosition==0)//���ڽ��������
		{
			//������ķ��䷽������ǵ�����ֵ��֪
			raymanage1.findBuildingRefDirection(shooting.firstPointx,shooting.firstPointy,shooting.firstPointz,raymanage1.finalCrossPointx,raymanage1.finalCrossPointy,raymanage1.finalCrossPointz,shooting.firstDirectiona,shooting.firstDirectionb,shooting.firstDirectionc,raymanage1.twoPoint[0],raymanage1.twoPoint[1]);
			float refCoefficientLength;//����ϵ����ģֵ
			refCoefficientLength=raymanage1.findBuildingRefCofficient(raymanage1.buildingRefAngleCos,interFrequence);//�����ﷴ��ϵ����ģֵ
			complex refCoefficient;//���ķ���ϵ��
			refCoefficient=raymanage1.findBuildingComplexCofficient(raymanage1.buildingRefAngleCos,interFrequence);//�����︴�ķ���ϵ��
			shooting.reflecttDirectiona.push_back(raymanage1.buildingRefDirectionA);
			shooting.reflecttDirectionb.push_back(raymanage1.buildingRefDirectionB);
			shooting.reflecttDirectionc.push_back(raymanage1.buildingRefDirectionC);
			shooting.reflecttCoefficient.push_back(refCoefficientLength);//���뷴��ϵ����ģֵ
			shooting.reflectComplexCoefficient.push_back(refCoefficient);//���븴�ķ���ϵ��
		}
		//����ÿ�����ߵĵ�����������������
		int maxRefNum=10;//���ķ������,��ʱ�Ĺ������Ȳ��Ե���
		for(int refNum=1;refNum<=maxRefNum;refNum++)
		{
			rayManage raymanage2;
			//�����

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

			//�ж�����ֹͣ����
			if(raymanage2.finalCrossFlag==0)//�뽨�����޽���
				break;
			if(raymanage2.finalCrossFlag==1&&raymanage2.finalCrossPosition==0&&raymanage2.finalCrossBuildingPosition==1)//���ڽ�����Ķ���
				break;
			//����˴η���·��
			shooting.rayLength.push_back(raymanage2.finalRayLength);
			//�ж�·������Ƿ񳬹�һ��ֵ
			float totalDistance=0;//��������ܵ�·��
			int totalNumber=0;
			totalNumber=shooting.rayLength.size();
			for(int i=1;i<=totalNumber;i++)

			{
				totalDistance=totalDistance+shooting.rayLength[i-1];
			}
			float totalRefCoefficient=1;//������߷���ϵ���ĳ˻�
			int totalRefNumber;
			totalRefNumber=shooting.reflecttCoefficient.size();
			for(int i=1;i<=totalRefNumber;i++)
			{
				totalRefCoefficient= totalRefCoefficient*shooting.reflecttCoefficient[i-1];

			}
			if(raymanage2.findPathRefStop(totalDistance,shooting.rayGain,totalRefCoefficient,interFrequence)==1)
				break;
			//������·���д�ŷ�����λ��
			shooting.crossPointx.push_back(raymanage2.finalCrossPointx);
			shooting.crossPointy.push_back(raymanage2.finalCrossPointy);
			shooting.crossPointz.push_back(raymanage2.finalCrossPointz);
			shooting.positioniState.push_back(raymanage2.finalCrossBuildingname);
			//���䷽��ͷ���ϵ��
			if(raymanage2.finalCrossFlag==1&&raymanage2.finalCrossPosition==1)//���ڵ���
			{
				//������䷽�򣬲��Ѿ��������ǵ�����ֵ
				raymanage2.findGroundRefDirection(shooting.crossPointx[refNum],shooting.crossPointy[refNum],shooting.crossPointz[refNum],shooting.reflecttDirectiona[refNum],shooting.reflecttDirectionb[refNum],shooting.reflecttDirectionc[refNum]);
				//��˴ε���ķ���ϵ������Ҫ֪�������
				float refCoefficientLength;//����ϵ����ģֵ
				refCoefficientLength=raymanage2.findGroundRefCofficient(raymanage2.groundRefAngleCos,interFrequence);
				complex refCoefficient;//���ķ���ϵ��
				refCoefficient=raymanage2.findGroundComplexCofficient(raymanage2.groundRefAngleCos,interFrequence);
				shooting.reflecttDirectiona.push_back(raymanage2.groundRefDirectionA);
				shooting.reflecttDirectionb.push_back(raymanage2.groundRefDirectionB);
				shooting.reflecttDirectionc.push_back(raymanage2.groundRefDirectionC);
				shooting.reflecttCoefficient.push_back(refCoefficientLength);//���뷴��ϵ����ģֵ
				shooting.reflectComplexCoefficient.push_back(refCoefficient);//���븴�ķ���ϵ��


				//gridPower gridpower1;
				//gridpower1.findGroundGridPowerSecond(raymanage2.finalCrossPointx,raymanage2.finalCrossPointy,shooting[num].crossPointx[refNum-1],shooting[num].crossPointy[refNum-1],shooting[num].crossPointz[refNum-1],
				//	shooting[num].reflecttDirectiona[refNum-1],shooting[num].reflecttDirectionb[refNum-1],shooting[num].reflecttDirectionc[refNum-1],totalDistance,shooting[num].rayGain,totalRefCoefficient,gridNumber);

			}
			if(raymanage2.finalCrossFlag==1&&raymanage2.finalCrossPosition==0)//���ڽ��������
			{
				//������ķ��䷽������ǵ�����ֵ��֪
				raymanage2.findBuildingRefDirection(shooting.crossPointx[refNum],shooting.crossPointy[refNum],shooting.crossPointz[refNum],raymanage2.finalCrossPointx,raymanage2.finalCrossPointy,raymanage2.finalCrossPointz,shooting.reflecttDirectiona[refNum],shooting.reflecttDirectionb[refNum],shooting.reflecttDirectionc[refNum],raymanage2.twoPoint[0],raymanage2.twoPoint[1]);
				float refCoefficientLength;//����ϵ����ģֵ
				refCoefficientLength=raymanage2.findBuildingRefCofficient(raymanage2.buildingRefAngleCos,interFrequence);//�����ﷴ��ϵ����ģֵ
				complex refCoefficient;//���ķ���ϵ��
				refCoefficient=raymanage2.findBuildingComplexCofficient(raymanage2.buildingRefAngleCos,interFrequence);//�����︴�ķ���ϵ��
				shooting.reflecttDirectiona.push_back(raymanage2.buildingRefDirectionA);
				shooting.reflecttDirectionb.push_back(raymanage2.buildingRefDirectionB);
				shooting.reflecttDirectionc.push_back(raymanage2.buildingRefDirectionC);
				shooting.reflecttCoefficient.push_back(refCoefficientLength);//���뷴��ϵ����ģֵ
				shooting.reflectComplexCoefficient.push_back(refCoefficient);//���븴�ķ���ϵ��
			}
		}

		gridPower  gridPower4;
		int shootingRecordFlag;//���ڼ�¼����
		shootingRecordFlag=num;
		gridPower4.gridAllPowerDiffractionCalculate(shooting,rayInterval,interFrequence,shootingRecordFlag, kuiLength, beforeLength,beforeCoefficient);


	}//������������ִ����ķֺ�

	
}
void diffractionCalculate::decideRoofLengDiffraction(float pointx,float pointy,vector<BuildingPoint> oneBPoint,float buildingHeight)//�����ж������䵽�����Ƿ�ᷢ������
{
	roofLengdiffractionFlag=0;
	//for(int i=0;i<oneBPoint.size()-1;i++)
		for(int i=3;i<4;i++)//ֻ���ǽ�����100��1����
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
		float d1=sqrt((pointx-lengPoint1x)*(pointx-lengPoint1x)+(pointy-lengPoint1y)*(pointy-lengPoint1y));//������淴�����������˵�ľ���
		float d2=sqrt((lengPoint1x-lengPoint2x)*(lengPoint1x-lengPoint2x)+(lengPoint1y-lengPoint2y)*(lengPoint1y-lengPoint2y));//�������������ĳ���
		float vectorLine1x,vectorLine1y,vectorLine1z;//�������˵�ָ���淴��������
		float vectorLine2x,vectorLine2y,vectorLine2z;//�������˵�ָ������Ҷ˵������
		vectorLine1x=pointx-lengPoint1x;
		vectorLine1y=pointy-lengPoint1y;
		vectorLine1z=0;
		vectorLine2x=lengPoint2x-lengPoint1x;
		vectorLine2y=lengPoint2y-lengPoint1y;
		vectorLine2z=0;
		float cosAngle=(vectorLine1x*vectorLine2x+vectorLine2x*vectorLine2y)/(sqrt(d1)*sqrt(d2));//vectorline1��vectorline2�����нǵ�����ֵ
		if(cosAngle<0)
			cosAngle=-cosAngle;
		float d3=d1*cosAngle;//line1��line2�ϵ�ͶӰ����
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
