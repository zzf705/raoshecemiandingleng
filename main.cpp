#pragma once
#include"basestationShooting.h"



void main()
{
	int mapMaxGridX,mapMaxGridY;//地图的水平网格和垂直网格大小，将来作为模块的输入参数
	/*mapMaxGridX=275;
	mapMaxGridY=261;*/
	//求出网格编号的最大值和最小值
	
	
	//float interFrequence;//基站对应扇区的中心频率
	//interFrequence=900;//以mhz为单位
	//float  rayInterval;//定义射线间隔，到时候写模块函数时需要用到
	//rayInterval=2;
	//float baseStationPositionx, baseStationPositiony, baseStationPositionz;//基站的位置及高度
	//baseStationPositionx=621.5;
	//baseStationPositiony=655.5;
	//baseStationPositionz=25;
	//float coveringRange=1000;//代表小区覆盖半径
	/////////////////////////////////////////////////////////////////////



	//GridFieldStrenthAddBaseNum射线功率记录表（一个网格可能对应多个基站的结果）初始化清零
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
		m_pRecordset->Open("SELECT * FROM  GridFieldStrenthAddBaseNum",(IDispatch*)sqlSp,adOpenDynamic,adLockOptimistic, adCmdText);
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
	//grid表将网格表里每个网格对应的场强值清零，同时找到网格最大值和最小值

	m_pRecordset->Close();
	double GDotX;
	double GDotY;
	double XM=0,YM=0;
	
	try
	{
	m_pRecordset->Open("SELECT * FROM  Grid",(IDispatch*)sqlSp,adOpenDynamic,adLockOptimistic, adCmdText);
	m_pRecordset->MoveFirst();
	while(!m_pRecordset->adoEOF)
	{
		m_pRecordset->PutCollect("GRealSNR",double(0));//根据廖林的表改的，名字以后要改
		//求出网格编号的最大值和最小值
		GDotX=double(m_pRecordset->GetCollect("GX"));
			if(GDotX>XM)
			{
				XM=GDotX;
			}
			GDotY=double(m_pRecordset->GetCollect("GY"));
			if(GDotY>YM)
			{
				YM=GDotY;
			}
		m_pRecordset->MoveNext();

		m_pRecordset->Update();
	}
	
	}
	catch (_com_error &e)
	{
		cout << e.Description()<<endl;
	}
	m_pRecordset->Close();
	mapMaxGridX=int((XM+2.5)/5);
	mapMaxGridY=int((YM+2.5)/5);
	//将建筑物对应的折点全部存储到vector中
	vector<vector<BuildingPoint>> allBPoints;//所有建筑物的折点列表
	vector<BuildingPoint> oneBPoints;//一个建筑物的折点列表
	BuildingPoint oneBPoint;//一个折点
	int Bid;
	int BidM=0;//建筑物最大编号
	/////////////////得到建筑物最大编号////////////////////////////////////
	try {
			
			//m_pRecordset->Open("SELECT * FROM  BuildingPoint",(IDispatch*)sqlSp,adOpenDynamic,adLockOptimistic, adCmdText);
			m_pRecordset->Open("SELECT * FROM  Building",(IDispatch*)sqlSp,adOpenDynamic,adLockOptimistic, adCmdText);
		}
		catch (_com_error &e)
		{
			cout << e.Description()<<endl;
		}
		m_pRecordset->MoveFirst();
		while(!m_pRecordset->adoEOF)
		{
			Bid=int(m_pRecordset->GetCollect("BId"));
			if(Bid>BidM)
			{
				BidM=Bid;
			}
			m_pRecordset->MoveNext();
		}
		m_pRecordset->Close();
		//将所有建筑物的折点存储下来
		
		for(Bid=1;Bid<=BidM;Bid++)
		{
			string Ext1;
			Ext1.append("SELECT * FROM  BuildingPoint WHERE PBuildingId=");
			stringstream sss;
			sss<<Bid;
			Ext1.append(sss.str());	
			Ext1.append("order by PId");
			if(FAILED(m_pRecordset.CreateInstance( _uuidof( Recordset ))))
	{
		cout<<"记录集对象指针实例化失败！"<<endl;
		return;
	}
			try {
			m_pRecordset->Open(Ext1.c_str(),(IDispatch*)sqlSp,adOpenDynamic,adLockOptimistic, adCmdText);		

			sss.str("");
			sss.clear();
			Ext1.clear();
			while((!m_pRecordset->adoEOF))
			{
				oneBPoint.px=double(m_pRecordset->GetCollect("PX"));
				oneBPoint.py=double(m_pRecordset->GetCollect("PY"));
				oneBPoints.push_back(oneBPoint);				
				m_pRecordset->MoveNext();
			}
			allBPoints.push_back(oneBPoints);			
			oneBPoints.clear();
			
			}
			catch (_com_error &e)
		{
			cout << e.Description()<<endl;
		}

		}
		m_pRecordset->Close();
		//将所有建筑物的高度记录下来
		vector<float> allBuildingHeight;
		for(Bid=1;Bid<=BidM;Bid++)
		{
			string Ext1;
			Ext1.append("SELECT * FROM  Building WHERE BId=");
			stringstream sss;
			sss<<Bid;
			Ext1.append(sss.str());	
			if(FAILED(m_pRecordset.CreateInstance( _uuidof( Recordset ))))
	{
		cout<<"记录集对象指针实例化失败！"<<endl;
		return;
	}
			try {
			m_pRecordset->Open(Ext1.c_str(),(IDispatch*)sqlSp,adOpenDynamic,adLockOptimistic, adCmdText);		

			sss.str("");
			sss.clear();
			Ext1.clear();
			while((!m_pRecordset->adoEOF))
			{
				
				allBuildingHeight.push_back(float(m_pRecordset->GetCollect("BHeight")));	
				m_pRecordset->MoveNext();
				
			}
						
			}
			catch (_com_error &e)
		{
			cout << e.Description()<<endl;
		}

		}
		m_pRecordset->Close();
		


		//从小区（基站）表中读取基站的信息，运行基站程序

	//CoInitialize(NULL);
	//_ConnectionPtr  sqlSp;
	//HRESULT hr=sqlSp.CreateInstance(_uuidof(Connection));
	//if(FAILED(hr))
	//{
	//	cout<<"_ConnectionPtr对象指针实例化失败！！！"<<endl;
	//	return ;
	//}
	//else {
	//	try {
	//		_bstr_t strConnect="Driver={sql server};server=ZHANGZHE-PC;uid=sa;pwd=123456;database=test30;";
	//		//_bstr_t strConnect="Provider=SQLOLEDB;Server=127.0.0.1,1433;Database=PBMS;uid=sa;pwd=pp471006459;";
	//		//_bstr_t strConnect="Provider=SQLOLEDB.1;Password=pp471006459;Persist Security Info=True;User ID=sa;"
	//			//"Initial Catalog=PBMS;Data Source=127.0.0.1,1433";
	//		//以上这三条strConnect语句都可以用！！看自己喜好选择用吧
	//		//要注意修改用户名uid、密码pwd、数据库名database，这三个参数均是你自己sql server的数据库信息
	//		sqlSp->Open(strConnect,"","",adModeUnknown);
	//	}
	//	catch(_com_error &e) {
	//		cout<<e.Description()<<endl;
	//	}
	//	_RecordsetPtr m_pRecordset; //记录集对象指针，用来执行SQL语句并记录查询结果
	//	if(FAILED(m_pRecordset.CreateInstance( _uuidof( Recordset ))))
	//	{
	//		cout<<"记录集对象指针实例化失败！"<<endl;
	//		return;
	//	}

		try
		{
			m_pRecordset->Open("SELECT * FROM  Area",(IDispatch*)sqlSp,adOpenDynamic,adLockOptimistic, adCmdText);
		}
		catch (_com_error &e)
		{
			cout << e.Description()<<endl;
		}
		m_pRecordset->MoveFirst();
		while(!m_pRecordset->adoEOF)
		{
			float AHeight;
			AHeight=float(m_pRecordset->GetCollect("AHeight"));
			if(AHeight!=0)
			{
			    float AFreq,AAspectAngle,ADeclineAngle,AX,AY,ALength;
				int AId;
				AFreq=float(m_pRecordset->GetCollect("AFreqType"));
				AAspectAngle=float(m_pRecordset->GetCollect("AAspectAngle"));
				ADeclineAngle=float(m_pRecordset->GetCollect("ADeclineAngle"));
				AX=float(m_pRecordset->GetCollect("AX"));
				AY=float(m_pRecordset->GetCollect("AY"));
				AId=int(m_pRecordset->GetCollect("AId"));
				ALength=float(m_pRecordset->GetCollect("ALength"));//馈线长度
				basestationShooting basestationshooting1;
	basestationshooting1.basestationOperate(mapMaxGridX,mapMaxGridY,1,AFreq,AX,AY,AHeight,AAspectAngle,ADeclineAngle,220,110,AId,ALength,allBPoints,allBuildingHeight);
				
			}
			
			m_pRecordset->MoveNext();
		}


	/*basestationShooting basestationshooting1;
	basestationshooting1.basestationOperate(mapMaxGridX,mapMaxGridY,2,900,285,286,25,0,45,360,80,1);
	basestationShooting basestationshooting2;
 	basestationshooting2.basestationOperate(mapMaxGridX,mapMaxGridY,2,900,285,851,25,0,45,360,80,2);
	basestationShooting basestationshooting3;
 	basestationshooting2.basestationOperate(mapMaxGridX,mapMaxGridY,2,900,851,285,25,0,45,360,80,3);
	basestationShooting basestationshooting4;
 	basestationshooting2.basestationOperate(mapMaxGridX,mapMaxGridY,2,900,851,851,25,0,45,360,80,4);*/

	//////////////////////////////////////////////////////////

	
	//从GridFieldStrenthAddBaseNum表中找到每个网格对应的最大场强值

	int havePowerNumber=0;


	for(int num=0;num<mapMaxGridX*mapMaxGridY;num++)
		{   
			double maxStrength=-9999999;//为了找到每个网格对应的最大场强值
			int number=0;
			/*CoInitialize(NULL);
			_ConnectionPtr  sqlSp;
			HRESULT hr=sqlSp.CreateInstance(_uuidof(Connection));
			if(FAILED(hr))
			{
				cout<<"_ConnectionPtr对象指针实例化失败！！！"<<endl;
				return ;
			}
			else 
			{
				try {
					_bstr_t strConnect="Driver={sql server};server=ZHANGZHE-PC,1433;uid=sa;pwd=123456;database=MapData6;";
					sqlSp->Open(strConnect,"","",adModeUnknown);
				}
				catch(_com_error &e) {
					cout<<e.Description()<<endl;
				}
			}
			_RecordsetPtr m_pRecordset;
			*/
			if(FAILED(m_pRecordset.CreateInstance( _uuidof( Recordset ))))
				{
					cout<<"记录集对象指针实例化失败！"<<endl;
					return;
				}

			
			string Ext;
			string medm;
			int mBid1,mBid2;
			stringstream ss;
			Ext.append("SELECT * FROM GridFieldStrenthAddBaseNum WHERE GId=");
			ss<<num+1;
			Ext.append(ss.str());			
			try
			{
				m_pRecordset->Open(Ext.c_str(),(IDispatch*)sqlSp,adOpenDynamic,adLockOptimistic, adCmdText);
				Ext.clear();
				ss.str("");
				ss.clear();
				m_pRecordset->MoveFirst();
				while(!m_pRecordset->adoEOF) 
				{
					number++;	
					double gridPower;
					gridPower=double(m_pRecordset->GetCollect("GFieldStrength"));
					if(gridPower>=maxStrength)
						maxStrength=gridPower;
					m_pRecordset->MoveNext();
				}
			}
			catch (_com_error &e)
			{
				cout << e.Description()<<endl;
			}


			if(number==0)
				continue;
			cout<<num<<endl;

			Grid grid2;
			grid2.PutThisGridStrength(num+1,maxStrength);
			havePowerNumber++;
		}

	//使用经验公式求出每个网格的路径损耗值,将结果放入到grid表中的场强值中

	//先将结果之前射线跟踪的结果清零



	m_pRecordset->Close();
	








}