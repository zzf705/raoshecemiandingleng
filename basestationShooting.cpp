#include "basestationShooting.h"


void basestationShooting:: basestationOperate(int maxGridx,int maxGridy,float shootingInterval,float baseFrequence,float basePositionx,
		 float basePositiony,float basePositionz,float fangWeiJiao,float xiaQingJiao,float shuipingRange,float shuizhiRange,int baseStationNumber,float kuiLength,vector<vector<BuildingPoint>> BX,vector<float> HX)
	 //网格水平最大编号，垂直最大编号，射线间隔，基站频率，基站位置，方位角，下倾角，水平辐射范围，竖直辐射范围
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
	

	//每次执行基站函数，将GridFieldStrenth表清零，因为这个表的结果只代表一个基站
	CoInitialize(NULL);
	_ConnectionPtr  sqlSp;
	HRESULT hr=sqlSp.CreateInstance(_uuidof(Connection));
	if(FAILED(hr))
	{
		cout<<"_ConnectionPtr对象指针实例化失败！！！"<<endl;
		return ;
	}
	else 
	{
		try 
		{
			_bstr_t strConnect="Driver={sql server};server=ZHANGZHE-PC;uid=sa;pwd=123456;database=test30;";//和数据库连接
			sqlSp->Open(strConnect,"","",adModeUnknown);
		}
			catch(_com_error &e) {
				cout<<e.Description()<<endl;
			}
	}
	_RecordsetPtr m_pRecordset;
	if(FAILED(m_pRecordset.CreateInstance( _uuidof( Recordset ))))
	{
		cout<<"记录集对象指针实例化失败！"<<endl;
		return;
	}
	
	try
	{
		m_pRecordset->Open("SELECT * FROM  GridFieldStrenth",(IDispatch*)sqlSp,adOpenDynamic,adLockOptimistic, adCmdText);
		m_pRecordset->MoveFirst();
		while(!m_pRecordset->adoEOF) 
		{
			m_pRecordset->Delete(adAffectCurrent);
			m_pRecordset->Update();
			m_pRecordset->MoveFirst();
		}
	}
	catch (_com_error &e)
	{
		cout << e.Description()<<endl;
	}
	



	//////////////////////////////////////////////////////////////

	ShootingRay shooting1;
	shooting1.shootingGainAllDirection(fangWeiJiao,xiaQingJiao,shuipingRange,shuizhiRange,rayInterval,rayInterval);
	int rayNumber=shooting1.shootingNumber;
	for(int num=0;num<rayNumber;num++)
	{   
		cout<<num<< "        "<<baseStationNumber<<endl;
		shooting1.GetRecord(num+1);
		rayPath shooting;
		shooting.firstPointx=baseStationPositionx;
		shooting.firstPointy=baseStationPositiony;
		shooting.firstPointz=baseStationPositionz;
		shooting.firstDirectiona=shooting1.Rx;
		shooting.firstDirectionb=shooting1.Ry;
		shooting.firstDirectionc=shooting1.Rz;
		shooting.rayGain=shooting1.Rgain;

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
		{   
			/*if(raymanage1.finalCrossBuildingname==100)
			{
			diffractionCalculate h1;
			h1.decideRoofLengDiffraction(raymanage1.finalCrossPointx,raymanage1.finalCrossPointy,BX[raymanage1.finalCrossBuildingname-1],HX[raymanage1.finalCrossBuildingname-1]);
		if(h1.roofLengdiffractionFlag==1)
		{
			float diffractioncoefficient1=0.5;
			h1.shupingDiffractionOperate(maxGridx,maxGridy,shootingInterval,baseFrequence,h1.shuipingLengPositionx,h1.shuipingLengPositiony,h1.shuipingLengPositionz,
			baseStationNumber,kuiLength,shooting.firstDirectiona,shooting.firstDirectionb,shooting.firstDirectionc,BX[raymanage1.finalCrossBuildingname-1],HX[raymanage1.finalCrossBuildingname-1],
			shooting.rayGain,raymanage1.finalRayLength,diffractioncoefficient1,h1.lengPoint1x,h1.lengPoint1y,h1.lengPoint2x,h1.lengPoint2y,h1.shuipingLengNormalVectorx,h1.shuipingLengNormalVectory,h1.shuipingLengNormalVectorz,BX,HX);
		}
			}*/
			continue;
		
		}
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
			shooting.reflecttDirectionc.push_back(raymanage1.groundRefDirectionC);;
			shooting.reflecttCoefficient.push_back(refCoefficientLength);//存入反射系数的模值
			shooting.reflectComplexCoefficient.push_back(refCoefficient);//存入复的反射系数
			//gridPower gridpower1;
			//gridpower1.findGroundGridPowerFirst(raymanage1.finalCrossPointx,raymanage1.finalCrossPointy,shooting[num].firstPointx,shooting[num].firstPointy,shooting[num].firstPointz,shooting[num].firstDirectiona,shooting[num].firstDirectionb,shooting[num].firstDirectionc,raymanage1.finalRayLength,shooting[num].rayGain,gridNumber);

		}
		
		if(raymanage1.finalCrossFlag==1&&raymanage1.finalCrossPosition==0)//落在建筑物侧面
		{

			if(raymanage1.finalCrossBuildingname==100&&raymanage1.twoPoint[0].x==BX[99][4].px&&
				raymanage1.twoPoint[0].y==BX[99][4].py&&raymanage1.twoPoint[1].x==BX[99][5].px&&
				raymanage1.twoPoint[1].y==BX[99][5].py)//回落到建筑物100的一个指定的棱上
			{
			diffractionCalculate diffractioncalculate1;
			diffractioncalculate1.decideDiffractionOperate(raymanage1.finalCrossPointx,raymanage1.finalCrossPointy,raymanage1.finalCrossPointz,HX[raymanage1.finalCrossBuildingname-1],
				shooting.firstDirectiona,shooting.firstDirectionb,shooting.firstDirectionc,raymanage1.twoPoint[0].x,raymanage1.twoPoint[0].y,raymanage1.twoPoint[1].x,raymanage1.twoPoint[1].y);
			if(diffractioncalculate1.diffractionFlag==1)
			{
				 float diffractionCoefficient1=0.5;
				/*if(diffractioncalculate1.shuzhiFlag==1)
				{
					diffractioncalculate1.shuzhiDiffractionOperate(maxGridx,maxGridy,shootingInterval,baseFrequence,diffractioncalculate1.shuzhiLengPositionx,diffractioncalculate1.shuzhiLengPositiony,raymanage1.finalCrossPointz,
						baseStationNumber,kuiLength,shooting.firstDirectiona,shooting.firstDirectionb,shooting.firstDirectionc,BX[raymanage1.finalCrossBuildingname-1],HX[raymanage1.finalCrossBuildingname-1],
						shooting.rayGain,raymanage1.finalRayLength,diffractionCoefficient1,BX,HX);

				}
				else */
				 if(diffractioncalculate1.shuipingFlag==1)
					{
						diffractioncalculate1.shupingDiffractionOperate(maxGridx,maxGridy,shootingInterval,baseFrequence,diffractioncalculate1.shuipingLengPositionx,diffractioncalculate1.shuipingLengPositiony,diffractioncalculate1.shuipingLengPositionz,
					baseStationNumber,kuiLength,shooting.firstDirectiona,shooting.firstDirectionb,shooting.firstDirectionc,BX[raymanage1.finalCrossBuildingname-1],HX[raymanage1.finalCrossBuildingname-1],
					shooting.rayGain,raymanage1.finalRayLength,diffractionCoefficient1,raymanage1.twoPoint[0].x,raymanage1.twoPoint[0].y,raymanage1.twoPoint[1].x,raymanage1.twoPoint[1].y,diffractioncalculate1.shuipingLengNormalVectorx,diffractioncalculate1.shuipingLengNormalVectory,diffractioncalculate1.shuipingLengNormalVectorz,BX,HX);
				continue;
				 }
			}			
			}
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
				
				{

//					diffractionCalculate h2;
//					h2.decideRoofLengDiffraction(raymanage2.finalCrossPointx,raymanage2.finalCrossPointy,BX[raymanage2.finalCrossBuildingname-1],HX[raymanage2.finalCrossBuildingname-1]);
//					if(h2.roofLengdiffractionFlag==1)
//					{
//
//						float diffractioncoefficient2=0.5;
//						//存入此次反射路径
//			shooting.rayLength.push_back(raymanage2.finalRayLength);
//			//判断路径损耗是否超过一定值
//			float totalDistance1=0;//求出射线总的路径
//			int totalNumber1=0;
//			totalNumber1=shooting.rayLength.size();
//			for(int i=1;i<=totalNumber1;i++)
//			
//				{
//					totalDistance1=totalDistance1+shooting.rayLength[i-1];
//			}
//			float totalRefCoefficient1=1;//求出射线反射系数的乘积
//			int totalRefNumber1;
//			totalRefNumber1=shooting.reflecttCoefficient.size();
//			for(int i=1;i<=totalRefNumber1;i++)
//				{
//					 totalRefCoefficient1= totalRefCoefficient1*shooting.reflecttCoefficient[i-1];
//
//			}
//						h2.shupingDiffractionOperate(maxGridx,maxGridy,shootingInterval,baseFrequence,h2.shuipingLengPositionx,h2.shuipingLengPositiony,h2.shuipingLengPositionz,
//						baseStationNumber,kuiLength,shooting.reflecttDirectiona[refNum],shooting.reflecttDirectionb[refNum],shooting.reflecttDirectionc[refNum]
//
//,BX[raymanage2.finalCrossBuildingname-1],HX[raymanage2.finalCrossBuildingname-1],
//						shooting.rayGain,totalDistance1,diffractioncoefficient2* totalRefCoefficient1,h2.lengPoint1x,h2.lengPoint1y,h2.lengPoint2x,h2.lengPoint2y,h2.shuipingLengNormalVectorx,h2.shuipingLengNormalVectory,h2.shuipingLengNormalVectorz,BX,HX);
//					}


					break;



			}
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
				/*diffractionCalculate diffractioncalculate2;
			diffractioncalculate2.decideDiffractionOperate(raymanage2.finalCrossPointx,raymanage2.finalCrossPointy,raymanage2.finalCrossPointz,HX[raymanage2.finalCrossBuildingname-1],
				shooting.reflecttDirectiona[refNum],shooting.reflecttDirectionb[refNum],shooting.reflecttDirectionc[refNum],raymanage2.twoPoint[0].x,raymanage2.twoPoint[0].y,raymanage2.twoPoint[1].x,raymanage2.twoPoint[1].y);
			if(diffractioncalculate2.diffractionFlag==1)
			{
				 float diffractionCoefficient2=0.5;
				if(diffractioncalculate2.shuzhiFlag==1)
				{
					diffractioncalculate2.shuzhiDiffractionOperate(maxGridx,maxGridy,shootingInterval,baseFrequence,diffractioncalculate2.shuzhiLengPositionx,diffractioncalculate2.shuzhiLengPositiony,raymanage2.finalCrossPointz,
						baseStationNumber,kuiLength,shooting.reflecttDirectiona[refNum],shooting.reflecttDirectionb[refNum],shooting.reflecttDirectionc[refNum]

,BX[raymanage2.finalCrossBuildingname-1],HX[raymanage2.finalCrossBuildingname-1],
						shooting.rayGain,totalDistance,diffractionCoefficient2*totalRefCoefficient,BX,HX);

				}
				else 
					diffractioncalculate2.shupingDiffractionOperate(maxGridx,maxGridy,shootingInterval,baseFrequence,diffractioncalculate2.shuipingLengPositionx,diffractioncalculate2.shuipingLengPositiony,diffractioncalculate2.shuipingLengPositionz,
					baseStationNumber,kuiLength,shooting.reflecttDirectiona[refNum],shooting.reflecttDirectionb[refNum],shooting.reflecttDirectionc[refNum]

,BX[raymanage2.finalCrossBuildingname-1],HX[raymanage2.finalCrossBuildingname-1],
					shooting.rayGain,totalDistance,diffractionCoefficient2*totalRefCoefficient,raymanage2.twoPoint[0].x,raymanage2.twoPoint[0].y,raymanage2.twoPoint[1].x,raymanage2.twoPoint[1].y,diffractioncalculate2.shuipingLengNormalVectorx,diffractioncalculate2.shuipingLengNormalVectory,diffractioncalculate2.shuipingLengNormalVectorz,BX,HX);
				break;
			}			*/
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
		gridPower4.gridAllPowerCalculate(shooting,rayInterval,interFrequence,shootingRecordFlag, kuiLength);


	}//代表所有射线执行完的分号

	//计算一个基站在所有网格的场强值

	////计算一个基站在所有网格的场强值

	//
	vector<int>haveCalculateNumberGrid;//已经计算过的网格编号的列表，放到vector中，每次计算时进行一个比较
	haveCalculateNumberGrid.clear();
	int sameFlag;//是否重复的标志位，如果重复，则为1，不重复，为0
	int havePowerNumber=0;//接下来用来记录有功率的网格个数

	if(FAILED(m_pRecordset.CreateInstance( _uuidof( Recordset ))))
	{
		cout<<"记录集对象指针实例化失败！"<<endl;
		return;
	}
	try
	{
		m_pRecordset->Open("SELECT * FROM  GridFieldStrenth",(IDispatch*)sqlSp,adOpenDynamic,adLockOptimistic, adCmdText);
		m_pRecordset->MoveFirst();
		while(!m_pRecordset->adoEOF) 
		{
			sameFlag=0;
			int GID;//网格编号
			GID=int(m_pRecordset->GetCollect("GId"));
			for(int i=0;i<haveCalculateNumberGrid.size();i++)
			{
				if(GID==haveCalculateNumberGrid[i])
				{
					sameFlag=1;
					break;

				}

			}
			if(sameFlag==0)
			{
				_RecordsetPtr m_pRecordset1;
				if(FAILED(m_pRecordset1.CreateInstance( _uuidof( Recordset ))))
				{
					cout<<"记录集对象指针实例化失败！"<<endl;
					return;
				}
				string Ext;
				string medm;
				int mBid1,mBid2;
				stringstream ss;
				Ext.append("SELECT * FROM  GridFieldStrenth WHERE GId=");
				ss<<GID;
				Ext.append(ss.str());
				complex receiveElecFiledStrength;	
				GridPowerResult gridNumber;
				try
				{
					m_pRecordset1->Open(Ext.c_str(),(IDispatch*)sqlSp,adOpenDynamic,adLockOptimistic, adCmdText);
					Ext.clear();
					ss.str("");
					ss.clear();
					m_pRecordset1->MoveFirst();
					while(!m_pRecordset1->adoEOF) 
					{

						receiveElecFiledStrength.real=double(m_pRecordset1->GetCollect("GCReal"));
						receiveElecFiledStrength.img=double(m_pRecordset1->GetCollect("GCImg"));
						gridNumber.gridFinalPower.push_back(receiveElecFiledStrength);
						m_pRecordset1->MoveNext();
					}
				}
				catch (_com_error &e)
				{
					cout << e.Description()<<endl;
				}
				cout<<GID<<endl;	
				gridNumber.findGridFinalTotalPower(interFrequence);

				Grid grid2;
				grid2.addThisGridStrengthToNew(GID,gridNumber.gridFinalTotalPower,baseStationNumber);
				havePowerNumber++;
				haveCalculateNumberGrid.push_back(GID);
				m_pRecordset1->Close();
			}
			m_pRecordset->MoveNext();
		}

	}
	catch (_com_error &e)
	{
		cout << e.Description()<<endl;
	}
	picture picture1;
	 picture1.makeMif();

}