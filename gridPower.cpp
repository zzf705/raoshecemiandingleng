#include "gridPower.h"


//void gridPower::findGroundGridPowerFirst(float groundCrossPointx,float groundCrossPointy,float shootingStartx,float shootingStarty,float shootingStartz,
//	float shootingDirectiona,float shootingDirectionb,float shootingDirectionc,float shootingLength,float antennaGain,gridPowerResult gridNumber[])//射线刚开始就落地计算网格功率
//{
//	findGrid findgrid1;
//	int q1,q2;
//	q1=findgrid1.findpointgridx(groundCrossPointx,shootingDirectiona);
//	q2=findgrid1.findpointgridy(groundCrossPointy,shootingDirectionb);
//	float gridCenterX, gridCenterY;
//	rayManage raymanage1;
//	gridCenterX=raymanage1.findGridCenterxy(q1);//求出网格中心点的横坐标
//	gridCenterY=raymanage1.findGridCenterxy(q2);//求出网格中心点的纵坐标
//	float receiveBallR;
//	receiveBallR=3.14*shootingLength*3/(180*sqrt(3.0));
//	float pointDistance;//点到直线的距离
//	pointDistance=raymanage1.findPointToLineDistance(shootingStartx,shootingStarty,shootingStartz,shootingDirectiona,shootingDirectionb,shootingDirectionc,gridCenterX,gridCenterY,0);
//	if(pointDistance<receiveBallR)
//	{
//		float antennaPower=46;//基站发射的起始功率为46dbm，这里是个参数，是可调的
//		float baseStationloss=0;//基站的损耗，这里先考虑为0
//		float receivePower;//接收功率
//		receivePower=antennaPower-10.9921-20*log10( shootingLength)+antennaGain;//10.9921代表10log4pai
//		receivePower=exp(log(10.0)*(receivePower/10));
//		int gridId;
//		//Grid grid1;
//		//gridId=grid1.findGridId(gridCenterX,gridCenterY);
//		 //gridId=3;//暂时赋值，需要改的
//		//只有在贾其所给的地图范围内才可以向网格中存取功率
//		//这个是需要根据地图的大小而改变的
//		if(gridCenterX>0&&gridCenterX<55&&gridCenterY>0&&gridCenterY<75)
//		{
//			Grid grid1;
//		grid1.GetThisGirdRecord(gridCenterX,gridCenterY);
//		gridId=grid1.id;
//		//cout<<gridId<<endl;
//		 
//
////		gridNumber[gridId].gridFinalPower.push_back(receivePower);//将射线落地后的网格功率放入到向量中，以便最后求和
//		}
//		
//	}
//	
//
//
//}
////射线迭代时如果落到地面，计算对地面网格的贡献
//void gridPower::findGroundGridPowerSecond(float groundCrossPointx,float groundCrossPointy,float shootingStartx,float shootingStarty,float shootingStartz,
//	float shootingDirectiona,float shootingDirectionb,float shootingDirectionc,float shootingLength,float antennaGain,float totalRefCoefficient,gridPowerResult gridNumber[])
//{
//	
//	findGrid findgrid1;
//	int q1,q2;
//	q1=findgrid1.findpointgridx(groundCrossPointx,shootingDirectiona);
//	q2=findgrid1.findpointgridy(groundCrossPointy,shootingDirectionb);
//	float gridCenterX, gridCenterY;
//	rayManage raymanage1;
//	gridCenterX=raymanage1.findGridCenterxy(q1);//求出网格中心点的横坐标
//	gridCenterY=raymanage1.findGridCenterxy(q2);//求出网格中心点的纵坐标
//	float receiveBallR;
//	receiveBallR=3.14*shootingLength*3/(180*sqrt(3.0));
//	float pointDistance;//点到直线的距离
//	pointDistance=raymanage1.findPointToLineDistance(shootingStartx,shootingStarty,shootingStartz,shootingDirectiona,shootingDirectionb,shootingDirectionc,gridCenterX,gridCenterY,0);
//	if(pointDistance<receiveBallR)
//	{
//		float antennaPower=46;//基站发射的起始功率为46dbm，这里是个参数，是可调的
//		float baseStationloss=0;//基站的损耗，这里先考虑为0
//		float receivePower;//接收功率
//		receivePower=antennaPower-10.9921-20*log10(shootingLength)+antennaGain+20*log10(totalRefCoefficient);//10.9921代表10log4pai
//		receivePower=exp(log(10.0)*(receivePower/10));
//		int gridId;
//		//只有在贾其所给的地图范围内才可以向网格中存取功率
//		//这个是需要根据地图的大小而改变的
//		if(gridCenterX>0&&gridCenterX<55&&gridCenterY>0&&gridCenterY<75)
//		{
//		Grid grid1;
//		grid1.GetThisGirdRecord(gridCenterX,gridCenterY);
//		gridId=grid1.id;
//		//cout<<gridId<<endl;
////		gridNumber[gridId].gridFinalPower.push_back(receivePower);//将射线落地后的网格功率放入到向量中，以便最后求和
//		}
//	}
//	 
//
//
//}

void gridPower::gridAllPowerCalculate(rayPath raypath1,float rayInterval,float frequence,int rayRecord,float kuixian)//计算射线对所有网格的功率
{
	int Id=1;
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
			_bstr_t strConnect="Driver={sql server};server=ZHANGZHE-PC;uid=sa;pwd=123456;database=test30;";
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
		
	}
	catch (_com_error &e)
	{
		cout << e.Description()<<endl;
	}

	int lineNumber;//一条射线的线段数
	lineNumber=raypath1.searchGridNumberTrue.size();
	for(int i=1;i<=lineNumber;i++)
	{
		int lineGridNumber;//一个线段包含的网格数
		lineGridNumber=raypath1.searchGridNumberTrue[i-1];
		float lineLengthBefore=0;//在计算接收球半径时用于计算之前的路径长度
		int totalNumber;
		int lineGridNumberBefore=0;//在搜索网格编号时能够保证从线段编号处运行
		complex totalCoefficienrt={1,0};//用来记录复的反射系数,初始值设置为1
		totalNumber=i-1;
		for(int q=1;q<=totalNumber;q++)
		{
			lineLengthBefore=lineLengthBefore+raypath1.rayLength[q-1];
			complexCalculate complexcalculate2;
			complexcalculate2.findComplexMulComplex(totalCoefficienrt,raypath1.reflectComplexCoefficient[q-1]);
			totalCoefficienrt=complexcalculate2.consequence;
			lineGridNumberBefore=lineGridNumberBefore+raypath1.searchGridNumberTrue[q-1];
		}
		for(int j=1;j<=lineGridNumber;j++)
		{
			int gridX,gridY;//用于记录网格编号
			gridX=raypath1.searchGridTrueX[lineGridNumberBefore+j-1];
			gridY=raypath1.searchGridTrueY[lineGridNumberBefore+j-1];
			rayManage raymanage3;
			float gridCenterX, gridCenterY;
			gridCenterX=raymanage3.findGridCenterxy(gridX);//求出网格中心点的横坐标
			gridCenterY=raymanage3.findGridCenterxy(gridY);//求出网格中心点的纵坐标
			float pointDistance;//点到直线的距离
			pointDistance=raymanage3.findPointToLineDistance(raypath1.crossPointx[i-1],raypath1.crossPointy[i-1],raypath1.crossPointz[i-1],
				raypath1.reflecttDirectiona[i-1],raypath1.reflecttDirectionb[i-1],raypath1.reflecttDirectionc[i-1],gridCenterX,gridCenterY,1.5);
			float lineLengthAfter;//针对本段射线的长度
			lineLengthAfter=raymanage3.findShootingLineLength(raypath1.crossPointx[i-1],raypath1.crossPointy[i-1],raypath1.crossPointz[i-1],
				raypath1.reflecttDirectiona[i-1],raypath1.reflecttDirectionb[i-1],raypath1.reflecttDirectionc[i-1],gridCenterX,gridCenterY,1.5);
			float lineLengthFinal;//射线路径的总长度
			lineLengthFinal=lineLengthAfter+lineLengthBefore;
			float receiveBallR;
			receiveBallR=3.14*lineLengthFinal*rayInterval/(180*sqrt(3.0));
			if(pointDistance<receiveBallR)
			{
				/*
				float antennaPower=46;//基站发射的起始功率为46dbm，这里是个参数，是可调的
				float baseStationloss=0;//基站的损耗，这里先考虑为0
				float receivePower;//接收功率
				receivePower=antennaPower-10.9921-20*log10( lineLengthFinal)+raypath1.rayGain;//10.9921代表10log4pai
				receivePower=exp(log(10.0)*(receivePower/10));				
				*/
				//Grid grid1;
				//gridId=grid1.findGridId(gridCenterX,gridCenterY);
				//gridId=3;//暂时赋值，需要改的
				//只有在贾其所给的地图范围内才可以向网格中存取功率
				//这个是需要根据地图的大小而改变的
				//if(gridCenterX>0&&gridCenterX<55&&gridCenterY>0&&gridCenterY<75)
				float waveLength;//定义波长
				waveLength=300/frequence;//频率以MHZ为单位
				double shootingGain;//射线的增益值由分贝换成实际值，2.302585代表ln10
				shootingGain=exp(2.302585*raypath1.rayGain/10);
				float kuixianLoss;//先求出馈线值，然后再由分贝转换成实际值
				if(frequence==900)
					 
					{
						kuixianLoss=kuixian/100*7.22;
				     kuixianLoss=exp(2.302585*kuixianLoss/10);
				}
				if(frequence==1800)
					 
					{
						kuixianLoss=kuixian/100*11.3;
				     kuixianLoss=exp(2.302585*kuixianLoss/10);
				}

				complex receiveElecFiledStrength;//得到接收到的电场强度值，发射功率仍然以46dbm为参考，这里的单位换成w,39.8w
				receiveElecFiledStrength.real=(sqrt(30*39.8*shootingGain/kuixianLoss))*cos(6.28*lineLengthFinal/waveLength)/lineLengthFinal;
				receiveElecFiledStrength.img=(-1)*(sqrt(30*39.8*shootingGain/kuixianLoss))*sin(6.28*lineLengthFinal/waveLength)/lineLengthFinal;
				complexCalculate complexcalculate3;
				complexcalculate3.findComplexMulComplex(receiveElecFiledStrength,totalCoefficienrt);//接收到的电场强度乘以反射系数
				receiveElecFiledStrength=complexcalculate3.consequence;//得到最终的电场强度
				    int gridId;
					Grid grid1;
					grid1.GetThisGirdRecord(gridCenterX,gridCenterY);
					gridId=grid1.id;
					//cout<<gridId<<endl;

					try
	                {	
						m_pRecordset->AddNew();
						m_pRecordset->PutCollect("Id",_variant_t(Id));
						Id++;
						m_pRecordset->PutCollect("GId",_variant_t(gridId));
						m_pRecordset->PutCollect("GCReal",_variant_t(receiveElecFiledStrength.real));
						m_pRecordset->PutCollect("GCImg",_variant_t(receiveElecFiledStrength.img));
						m_pRecordset->PutCollect("GRS",_variant_t(rayRecord));
						m_pRecordset->Update();
						}
					catch (_com_error &e)
	{
		cout << e.Description()<<endl;
	}
	   // 		gridNumber[gridId].gridFinalPower.push_back(receiveElecFiledStrength);//将射线落地后的网格功率放入到向量中，以便最后求和
				//gridNumber[gridId].shootingRecord.push_back(rayRecord);//当一个网格有功率值时用于判断是哪根射线的贡献

			}
		}
	}
}
void gridPower::gridRayLook(rayPath raypath1,float rayInterval,float frequence,int rayRecord,float kuixian)//把射线投影轨迹用不同颜色划出来
	{
	
		int color[17]={ COLOR1, COLOR17, COLOR2, COLOR16, COLOR3, COLOR15, COLOR4, COLOR14, COLOR5, COLOR13, COLOR6, COLOR12, COLOR7, COLOR11, COLOR8, COLOR10, COLOR9};
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
			_bstr_t strConnect="Driver={sql server};server=ZHANGZHE-PC;uid=sa;pwd=123456;database=test30;";
			sqlSp->Open(strConnect,"","",adModeUnknown);
		}
			catch(_com_error &e) {
				cout<<e.Description()<<endl;
			}
	}
	_RecordsetPtr m_pRecordset;
	vector<int> RayGridColor;//用来存储每个网格的颜色
	vector<int> RayGridNumber;//用来存储按射线搜索方向的网格编号
	int colorBefore;//网格之前的颜色
	int colorNow;//网格现在的颜色
	int lineNumber;//一条射线的线段数
	lineNumber=raypath1.searchGridNumberTrue.size();
	for(int i=1;i<=lineNumber;i++)
	{
		int lineGridNumber;//一个线段包含的网格数
		lineGridNumber=raypath1.searchGridNumberTrue[i-1];
		float lineLengthBefore=0;//在计算接收球半径时用于计算之前的路径长度
		int totalNumber;
		int lineGridNumberBefore=0;//在搜索网格编号时能够保证从线段编号处运行
		complex totalCoefficienrt={1,0};//用来记录复的反射系数,初始值设置为1
		totalNumber=i-1;
		for(int q=1;q<=totalNumber;q++)
		{			
			lineGridNumberBefore=lineGridNumberBefore+raypath1.searchGridNumberTrue[q-1];
		}
		for(int j=1;j<=lineGridNumber;j++)
		{
			int gridX,gridY;//用于记录网格编号
			gridX=raypath1.searchGridTrueX[lineGridNumberBefore+j-1];
			gridY=raypath1.searchGridTrueY[lineGridNumberBefore+j-1];
			rayManage raymanage3;
			float gridCenterX, gridCenterY;
			gridCenterX=raymanage3.findGridCenterxy(gridX);//求出网格中心点的横坐标
			gridCenterY=raymanage3.findGridCenterxy(gridY);//求出网格中心点的纵坐标
			
				    int gridId;
					Grid grid1;
					grid1.GetThisGirdRecord(gridCenterX,gridCenterY);
					gridId=grid1.id;
					if(gridId==33800)

					{
						int aaa;
					    aaa=1;
					}
					if(gridId==32235)

					{
						int baa;
					    baa=1;
					}
					//cout<<gridId<<endl;
					RayGridNumber.push_back(gridId);
					
	if(FAILED(m_pRecordset.CreateInstance( _uuidof( Recordset ))))
	{
		cout<<"记录集对象指针实例化失败！"<<endl;
		return;
	}
	string Ext;
	stringstream ss;
	Ext.append("SELECT * FROM  Grid WHERE GId=");
	ss<<gridId;
	Ext.append(ss.str());
	ss.str("");
	ss.clear();
	try 
	{
		m_pRecordset->Open(Ext.c_str(),(IDispatch*)sqlSp,adOpenDynamic,adLockOptimistic, adCmdText);
	}
	catch (_com_error &e)
	{
		cout << e.Description()<<endl;
	}
	try
		{
			colorBefore=int(m_pRecordset->GetCollect("GColor"));
			colorNow=color[i];
			RayGridColor.push_back(colorBefore);	
              
			   m_pRecordset->PutCollect("GColor",_variant_t(colorNow));
			   m_pRecordset->Update();
			  // m_pRecordset1->MoveNext();

			
	    }
			catch (_com_error &e)
	   {
		cout << e.Description()<<endl;
	   }		
			

			}
		}
	//将原来的颜色恢复过来
	//for(int i=1;i<=RayGridNumber.size();i++)
	//{
	//	int id=RayGridNumber[i-1];
	//	if(FAILED(m_pRecordset.CreateInstance( _uuidof( Recordset ))))
	//{
	//	cout<<"记录集对象指针实例化失败！"<<endl;
	//	return;
	//}
	//	string Ext;
	//	stringstream ss;
	//Ext.append("SELECT * FROM  Grid WHERE GId=");
	//ss<<id;
	//Ext.append(ss.str());
	//ss.str("");
	//ss.clear();
	//try 
	//{
	//	m_pRecordset->Open(Ext.c_str(),(IDispatch*)sqlSp,adOpenDynamic,adLockOptimistic, adCmdText);
	//}
	//catch (_com_error &e)
	//{
	//	cout << e.Description()<<endl;
	//}
	//try
	//	{
	//		
 //             if(RayGridColor[i-1]!=0&&RayGridColor[i-1]!=16777215)
	//		   {
	//			   m_pRecordset->PutCollect("GColor",_variant_t(RayGridColor[i-2]));
	//		  }
	//		  else
	//		  {
	//		  m_pRecordset->PutCollect("GColor",_variant_t(RayGridColor[i-1]));
	//		  }
	//		   m_pRecordset->Update();
	//		  // m_pRecordset1->MoveNext();

	//		
	//    }
	//		catch (_com_error &e)
	//   {
	//	cout << e.Description()<<endl;
	//   }		


	//}




	}
	void gridPower::gridAllPowerDiffractionCalculate(rayPath raypath1,float rayInterval,float frequence,int rayRecord,float kuixian,float lengthBefore,float coefficientBefore)//用于计算绕射射线射线对所有网格的贡献,最后一个参数代表射线间隔，便于计算接收球,频率以MHZ为单位,rayRecord用于计算网格功率值是哪根射线贡献的，最后两个参数代表绕射前射线走的的距离和射线经历的反射系数，用于功率的计算
{
	int Id=1;
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
			_bstr_t strConnect="Driver={sql server};server=ZHANGZHE-PC;uid=sa;pwd=123456;database=test30;";
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
		
	}
	catch (_com_error &e)
	{
		cout << e.Description()<<endl;
	}

	int lineNumber;//一条射线的线段数
	lineNumber=raypath1.searchGridNumberTrue.size();
	for(int i=1;i<=lineNumber;i++)
	{
		int lineGridNumber;//一个线段包含的网格数
		lineGridNumber=raypath1.searchGridNumberTrue[i-1];
		float lineLengthBefore=0;//在计算接收球半径时用于计算之前的路径长度
		int totalNumber;
		int lineGridNumberBefore=0;//在搜索网格编号时能够保证从线段编号处运行
		complex totalCoefficienrt={1,0};//用来记录复的反射系数,初始值设置为1
		totalNumber=i-1;
		for(int q=1;q<=totalNumber;q++)
		{
			lineLengthBefore=lineLengthBefore+raypath1.rayLength[q-1];
			complexCalculate complexcalculate2;
			complexcalculate2.findComplexMulComplex(totalCoefficienrt,raypath1.reflectComplexCoefficient[q-1]);
			totalCoefficienrt=complexcalculate2.consequence;
			lineGridNumberBefore=lineGridNumberBefore+raypath1.searchGridNumberTrue[q-1];
		}
		    complexCalculate complexcalculate4;
			complexcalculate4.findComplexMulConst(totalCoefficienrt,coefficientBefore);
			totalCoefficienrt=complexcalculate4.consequence;
		for(int j=1;j<=lineGridNumber;j++)
		{
			int gridX,gridY;//用于记录网格编号
			gridX=raypath1.searchGridTrueX[lineGridNumberBefore+j-1];
			gridY=raypath1.searchGridTrueY[lineGridNumberBefore+j-1];
			rayManage raymanage3;
			float gridCenterX, gridCenterY;
			gridCenterX=raymanage3.findGridCenterxy(gridX);//求出网格中心点的横坐标
			gridCenterY=raymanage3.findGridCenterxy(gridY);//求出网格中心点的纵坐标
			float pointDistance;//点到直线的距离
			pointDistance=raymanage3.findPointToLineDistance(raypath1.crossPointx[i-1],raypath1.crossPointy[i-1],raypath1.crossPointz[i-1],
				raypath1.reflecttDirectiona[i-1],raypath1.reflecttDirectionb[i-1],raypath1.reflecttDirectionc[i-1],gridCenterX,gridCenterY,1.5);
			float lineLengthAfter;//针对本段射线的长度
			lineLengthAfter=raymanage3.findShootingLineLength(raypath1.crossPointx[i-1],raypath1.crossPointy[i-1],raypath1.crossPointz[i-1],
				raypath1.reflecttDirectiona[i-1],raypath1.reflecttDirectionb[i-1],raypath1.reflecttDirectionc[i-1],gridCenterX,gridCenterY,1.5);
			float lineLengthFinal;//射线路径的总长度
			lineLengthFinal=lineLengthAfter+lineLengthBefore+lengthBefore;
			float receiveBallR;
			receiveBallR=3.14*lineLengthFinal*rayInterval/(180*sqrt(3.0));
			if(pointDistance<receiveBallR)
			{
				/*
				float antennaPower=46;//基站发射的起始功率为46dbm，这里是个参数，是可调的
				float baseStationloss=0;//基站的损耗，这里先考虑为0
				float receivePower;//接收功率
				receivePower=antennaPower-10.9921-20*log10( lineLengthFinal)+raypath1.rayGain;//10.9921代表10log4pai
				receivePower=exp(log(10.0)*(receivePower/10));				
				*/
				//Grid grid1;
				//gridId=grid1.findGridId(gridCenterX,gridCenterY);
				//gridId=3;//暂时赋值，需要改的
				//只有在贾其所给的地图范围内才可以向网格中存取功率
				//这个是需要根据地图的大小而改变的
				//if(gridCenterX>0&&gridCenterX<55&&gridCenterY>0&&gridCenterY<75)
				float waveLength;//定义波长
				waveLength=300/frequence;//频率以MHZ为单位
				double shootingGain;//射线的增益值由分贝换成实际值，2.302585代表ln10
				shootingGain=exp(2.302585*raypath1.rayGain/10);
				float kuixianLoss;//先求出馈线值，然后再由分贝转换成实际值
				if(frequence==900)
					 
					{
						kuixianLoss=kuixian/100*7.22;
				     kuixianLoss=exp(2.302585*kuixianLoss/10);
				}
				if(frequence==1800)
					 
					{
						kuixianLoss=kuixian/100*11.3;
				     kuixianLoss=exp(2.302585*kuixianLoss/10);
				}

				complex receiveElecFiledStrength;//得到接收到的电场强度值，发射功率仍然以46dbm为参考，这里的单位换成w,39.8w
				receiveElecFiledStrength.real=(sqrt(30*39.8*shootingGain/kuixianLoss))*cos(6.28*lineLengthFinal/waveLength)/lineLengthFinal;
				receiveElecFiledStrength.img=(-1)*(sqrt(30*39.8*shootingGain/kuixianLoss))*sin(6.28*lineLengthFinal/waveLength)/lineLengthFinal;
				complexCalculate complexcalculate3;
				complexcalculate3.findComplexMulComplex(receiveElecFiledStrength,totalCoefficienrt);//接收到的电场强度乘以反射系数
				receiveElecFiledStrength=complexcalculate3.consequence;//得到最终的电场强度
				    int gridId;
					Grid grid1;
					grid1.GetThisGirdRecord(gridCenterX,gridCenterY);
					gridId=grid1.id;
					//cout<<gridId<<endl;

					try
	                {	
						m_pRecordset->AddNew();
						m_pRecordset->PutCollect("Id",_variant_t(Id));
						Id++;
						m_pRecordset->PutCollect("GId",_variant_t(gridId));
						m_pRecordset->PutCollect("GCReal",_variant_t(receiveElecFiledStrength.real));
						m_pRecordset->PutCollect("GCImg",_variant_t(receiveElecFiledStrength.img));
						m_pRecordset->PutCollect("GRS",_variant_t(rayRecord));
						m_pRecordset->Update();
						}
					catch (_com_error &e)
	{
		cout << e.Description()<<endl;
	}
	   // 		gridNumber[gridId].gridFinalPower.push_back(receiveElecFiledStrength);//将射线落地后的网格功率放入到向量中，以便最后求和
				//gridNumber[gridId].shootingRecord.push_back(rayRecord);//当一个网格有功率值时用于判断是哪根射线的贡献

			}
		}
	}




}





