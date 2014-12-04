#include "ShootingRay.h"


ShootingRay::ShootingRay(void)
{
}


ShootingRay::~ShootingRay(void)
{
}

//void ShootingRay::shootingGain(float directionAngle,float downInclineAngle,float horizonDivision,float verticalDivision)
//{  
//	CoInitialize(NULL);
//	_ConnectionPtr  sqlSp;
//	HRESULT hr=sqlSp.CreateInstance(_uuidof(Connection));
//	if(FAILED(hr))
//	{
//		cout<<"_ConnectionPtr对象指针实例化失败！！！"<<endl;
//		return ;
//	}
//	else 
//	{
//		try {
//			_bstr_t strConnect="Driver={sql server};server=127.0.0.1,1433;uid=sa;pwd=12345678;database=MapData3;";
//			sqlSp->Open(strConnect,"","",adModeUnknown);
//		}
//		catch(_com_error &e) {
//			cout<<e.Description()<<endl;
//		}
//	}
//	_RecordsetPtr m_pRecordset;
//	if(FAILED(m_pRecordset.CreateInstance( _uuidof( Recordset ))))
//		{
//			cout<<"记录集对象指针实例化失败！"<<endl;
//			return;
//		}
//	try {
//			m_pRecordset->Open("SELECT * FROM  RayShooting",(IDispatch*)sqlSp,adOpenDynamic,adLockOptimistic, adCmdText);
//		}
//		catch (_com_error &e)
//		{
//			cout << e.Description()<<endl;
//		}
//
//
//	float verticalAngle=downInclineAngle+90;
//	float angleX, angleZ;
//	int count,countTemp,countTemp1,countTemp2;
//	count=0;
//
//	//把发射的射线空间上分成四部分，分别用for循环求出每条射线的方向向量和增益
//	for(angleX=directionAngle;angleX<directionAngle+60;angleX=angleX+horizonDivision)
//		for(angleZ=verticalAngle;angleZ<verticalAngle+15;angleZ=angleZ+verticalDivision)
//		{
//			Rx = sin(angleZ*pi/180)*cos(angleX*pi/180);
//			Ry = sin(angleZ*pi/180)*sin(angleX*pi/180);
//			Rz = cos(angleZ*pi/180);
//			Rgain=gainMax-0.1*(angleX-directionAngle)-0.1*(angleZ-verticalAngle);
//			
//			m_pRecordset->AddNew();
//			m_pRecordset->PutCollect("RId",count+1);
//			m_pRecordset->PutCollect("RDirecX",Rx);
//			m_pRecordset->PutCollect("RDirecY",Ry);
//			m_pRecordset->PutCollect("RDirecZ",Rz);
//			m_pRecordset->PutCollect("RGain",Rgain);
//			m_pRecordset->Update();
//			count = count + 1;
//		}
//		countTemp=count;
//
//	for(angleX=directionAngle;angleX<directionAngle+60;angleX=angleX+horizonDivision)
//		for(angleZ=verticalAngle;angleZ>verticalAngle-15;angleZ=angleZ-verticalDivision)
//		{
//			x[countTemp] = sin(angleZ*pi/180)*cos(angleX*pi/180);
//			y[countTemp] = sin(angleZ*pi/180)*sin(angleX*pi/180);
//			z[countTemp] = cos(angleZ*pi/180);
//			gain[countTemp]=gainMax-0.1*(angleX-directionAngle)-0.1*(verticalAngle-angleZ);
//
//			//cout<<x[countTemp]<<'\n'<<y[countTemp]<<'\n'<<z[countTemp]<<'\n'<<gain[countTemp]<<endl;
//			countTemp = countTemp + 1; 
//		}
//		countTemp1=countTemp;
//
//	for(angleX=directionAngle;angleX>directionAngle-60;angleX=angleX-horizonDivision)
//		for(angleZ=verticalAngle;angleZ<verticalAngle+15;angleZ=angleZ+verticalDivision)
//		{
//			x[countTemp1] = sin(angleZ*pi/180)*cos(angleX*pi/180);
//			y[countTemp1] = sin(angleZ*pi/180)*sin(angleX*pi/180);
//			z[countTemp1] = cos(angleZ*pi/180);
//			gain[countTemp1]=gainMax-0.1*(directionAngle-angleX)-0.1*(angleZ-verticalAngle);
//
//		//	cout<<x[countTemp1]<<'\n'<<y[countTemp1]<<'\n'<<z[countTemp1]<<'\n'<<gain[countTemp1]<<endl;
//			countTemp1 = countTemp1 + 1; 
//		}
//		countTemp2=countTemp1;
//
//	for(angleX=directionAngle;angleX>directionAngle-60;angleX=angleX-horizonDivision)
//		for(angleZ=verticalAngle;angleZ>verticalAngle-15;angleZ=angleZ-verticalDivision)
//		{
//			x[countTemp2] = sin(angleZ*pi/180)*cos(angleX*pi/180);
//			y[countTemp2] = sin(angleZ*pi/180)*sin(angleX*pi/180);
//			z[countTemp2] = cos(angleZ*pi/180);
//			gain[countTemp2]=gainMax-0.1*(directionAngle-angleX)-0.1*(verticalAngle-angleZ);
//
//			//cout<<x[countTemp2]<<'\n'<<y[countTemp2]<<'\n'<<z[countTemp2]<<'\n'<<gain[countTemp2]<<endl;
//			countTemp2 = countTemp2 + 1; 
//		}
//		shootingNumber=countTemp2;
//}
void ShootingRay::shootingGainAllDirection(float directionAngle,float downInclineAngle,float horizonRange, float verticalRange,
	float horizonDivision,float verticalDivision) 
{

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
		try {
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
	try {
			m_pRecordset->Open("SELECT * FROM  RayShooting",(IDispatch*)sqlSp,adOpenDynamic,adLockOptimistic, adCmdText);
		}
		catch (_com_error &e)
		{
			cout << e.Description()<<endl;
		}
	try
	{
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
		

	float verticalAngle=downInclineAngle+90;
	float angleX, angleZ;
	
	int count=0;
	float horizonGain[111]={0,0,0,0,0,0,0.10,0.20,0.30,0.50,0.60,0.70,0.75,0.80,0.90,1.00,1.10,1.15,1.20,1.25,1.30,
		1.35,1.40,1.45,1.50,1.55,1.60,1.70,1.80,1.90,2.00,2.10,2.30,2.50,2.70,2.90,3.00,3.20,3.40,3.60,3.80,
		4.00,4.20,4.40,4.60,4.80,5.00,5.20,5.40,5.60,5.80,6.00,6.30,6.60,6.90,7.20,7.50,7.80,8.20,8.50,8.80,
		9.00,9.30,9.70,10.1,10.5,10.8,11.1,11.4,11.7,12.0,12.3,12.7,12.9,13.2,13.5,13.8,14.1,14.4,14.7,15.0,
		15.3,15.6,15.9,16.2,16.5,16.8,17.1,17.4,17.7,18.0,18.3,18.7,19.1,19.5,19.9,20.4,20.9,21.4,21.9,22.4,
		23.0,23.3,23.6,23.8,24.0,25.0,26.0,27.0,28.0,30.0};
	float verticalGain[61]={0,0.5,1.5,3.0,5.0,10.0,15.0,20.0,17.5,20.0,22.5,     
		30.0,25.0,20.0,17.5,16.0,17.5,20.0,22.5,30.0,23.0,
		23.0,25.0,30.0,25.0,30.0,25.0,30.0,23.0,22.0,21.0,
		25.0,25.0,22.5,21.0,20.0,19.0,20.0,21.0,23.0,25.0,
		20.0,20.5,21.0,21.5,22.0,22.5,23.0,23.5,24.0,24.5,
		25.0,26.0,27.0,28.0,29.0,30.0,29.0,28.0,27.0,26.0};

	for(angleX=directionAngle-horizonRange/2;angleX<=directionAngle+horizonRange/2;angleX=angleX+horizonDivision)
		//for(angleZ=verticalAngle-verticalRange/2;angleZ<=verticalAngle+verticalRange/2;angleZ=angleZ+verticalDivision)
		for(angleZ=verticalAngle+verticalRange/2;angleZ>90;angleZ=angleZ-verticalDivision)
		{
			float gainMax=17.4;
			int count1;
			int count2;
			count1=int(fabs(angleX-directionAngle));
			count2=int(fabs(angleZ-verticalAngle));
			Rx = sin(angleZ*pi/180)*sin(angleX*pi/180);
			Ry = sin(angleZ*pi/180)*cos(angleX*pi/180)*(-1);
			Rz = cos(angleZ*pi/180);
			Rgain=gainMax-(horizonGain[count1]+verticalGain[count2]);;//是比值，没有换成分贝

		//	cout<<x[count]<<'\t'<<y[count]<<'\t'<<z[count]<<'\t'<<gain[count]<<endl;
			count=count+1;
			m_pRecordset->AddNew();
			m_pRecordset->PutCollect("RId",count);
			m_pRecordset->PutCollect("RDirecX",Rx);
			m_pRecordset->PutCollect("RDirecY",Ry);
			m_pRecordset->PutCollect("RDirecZ",Rz);
			m_pRecordset->PutCollect("RGain",Rgain);
			m_pRecordset->Update();
			m_pRecordset->MoveNext();
		}

		shootingNumber=count;
}

void ShootingRay::GetRecord(int id)
{
	CoInitialize(NULL);
	_ConnectionPtr  sqlSp;
	HRESULT hr=sqlSp.CreateInstance(_uuidof(Connection));//
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
	string Ext;
	stringstream ss;
	Ext.append("SELECT * FROM  RayShooting WHERE RId=");
	ss<<id;
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
	Ext.clear();
	Rx=double(m_pRecordset->GetCollect("RDirecX"));
	Ry=double(m_pRecordset->GetCollect("RDirecY"));
	Rz=double(m_pRecordset->GetCollect("RDirecZ"));
	Rgain=double(m_pRecordset->GetCollect("RGain"));
	m_pRecordset->Close();
	
	
	//为了检验哪条射线出了问题
	/*Ext.append("SELECT * FROM  RayShooting WHERE RId=");
	ss<<1;
	Ext.append(ss.str());
	try 
	{
		m_pRecordset->Open(Ext.c_str(),(IDispatch*)sqlSp,adOpenDynamic,adLockOptimistic, adCmdText);
	}
	catch (_com_error &e)
	{
		cout << e.Description()<<endl;
	}
	ss.str("");
	ss.clear();
	Ext.clear();
	try
	{
	
		
		m_pRecordset->PutCollect("RNumRecord",id);
		m_pRecordset->Update();
		}
	catch (_com_error &e)
	{
		cout << e.Description()<<endl;
		m_pRecordset->Close();	
	m_pRecordset->Close();
	sqlSp->Close();
}

*/


	/*if(FAILED(m_pRecordset.CreateInstance( _uuidof( Recordset ))))
		{
			cout<<"记录集对象指针实例化失败！"<<endl;
			return;
		}
	
	try {
			m_pRecordset->Open("SELECT * FROM  RayShooting",(IDispatch*)sqlSp,adOpenDynamic,adLockOptimistic, adCmdText);
		}
		catch (_com_error &e)
		{
			cout << e.Description()<<endl;
		}
	try
	{
		m_pRecordset->MoveFirst();
		m_pRecordset->AddNew();
		m_pRecordset->PutCollect("RNumRecord",id);
		m_pRecordset->Update();
		}
	catch (_com_error &e)
	{
		cout << e.Description()<<endl;
		m_pRecordset->Close();	
	m_pRecordset->Close();
	sqlSp->Close();
} */
	



}
void ShootingRay::shuzhiDiffractionShootingRay(float pointx,float pointy,float pointz,vector<BuildingPoint> oneBPoint,
		float incidentDirectina,float incidentDirectinb,float incidentDirectinc,float shootingInterval)//竖直棱射线发射
{
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
		try {
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
	try {
			m_pRecordset->Open("SELECT * FROM  diffractionRayShooting",(IDispatch*)sqlSp,adOpenDynamic,adLockOptimistic, adCmdText);
		}
		catch (_com_error &e)
		{
			cout << e.Description()<<endl;
		}
	try
	{
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
	float cosAngle=incidentDirectinc/(sqrt(incidentDirectina*incidentDirectina+incidentDirectinb*incidentDirectinb+incidentDirectinc*incidentDirectinc));//代表球坐标系下coa(sita)，一定是小于0的
	float sinAngle=sqrt(1-cosAngle*cosAngle);
	vector<float> shootingAngle;//同来存储满足发射的fai值
	float R=0.5*pointz;
	for(float fai=0;fai<360;fai=fai+shootingInterval)
	{
		float ciclePointx=pointx+R*sinAngle*sin(fai*3.14/180);
		float ciclePointy=pointy+R*sinAngle*cos(fai*3.14/180);
		diffractionCalculate diffractioncalculate1;
		if(diffractioncalculate1.decideInsidePolygon(ciclePointx,ciclePointy,oneBPoint)==1)
			shootingAngle.push_back(fai);
	}
		int count=0;
		for(int i=0;i<shootingAngle.size();i++)
		{
			Rx = sinAngle*sin(shootingAngle[i-1]*pi/180);
			Ry = sinAngle*cos(shootingAngle[i-1]*pi/180);
			Rz = cosAngle;
			count=count+1;
			m_pRecordset->AddNew();
			m_pRecordset->PutCollect("RId",count);
			m_pRecordset->PutCollect("RDirecX",Rx);
			m_pRecordset->PutCollect("RDirecY",Ry);
			m_pRecordset->PutCollect("RDirecZ",Rz);
			m_pRecordset->Update();
			m_pRecordset->MoveNext();

		}
		shootingNumber=count;
	

}
void  ShootingRay::GetDiffractionRecord(int id)//从绕射射线发射表中得到射线的方向系数
{
	CoInitialize(NULL);
	_ConnectionPtr  sqlSp;
	HRESULT hr=sqlSp.CreateInstance(_uuidof(Connection));//
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
	string Ext;
	stringstream ss;
	Ext.append("SELECT * FROM  diffractionRayShooting WHERE RId=");
	ss<<id;
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
	Ext.clear();
	Rx=double(m_pRecordset->GetCollect("RDirecX"));
	Ry=double(m_pRecordset->GetCollect("RDirecY"));
	Rz=double(m_pRecordset->GetCollect("RDirecZ"));
	//Rgain=double(m_pRecordset->GetCollect("RGain"));
	m_pRecordset->Close();
	


}
void ShootingRay::shuiPingDiffractionShootingRay(float pointx,float pointy,float pointz,float buildingHeight,
	float incidentDirectina,float incidentDirectinb,float incidentDirectinc,float shootingInterval,float vectorx,float vectory,float vectorz,
	float point1x,float point1y,float point2x,float point2y)//水平棱发射函数
{
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
		try {
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
	try {
		m_pRecordset->Open("SELECT * FROM  diffractionRayShooting",(IDispatch*)sqlSp,adOpenDynamic,adLockOptimistic, adCmdText);
	}
	catch (_com_error &e)
	{
		cout << e.Description()<<endl;
	}
	try
	{
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
	//棱的向量
	float vectorLine1x, vectorLine1y, vectorLine1z;//由点1指向点2
	vectorLine1x=point2x-point1x;
	vectorLine1y=point2y-point1y;
	vectorLine1z=0;
	//求出入射线与棱的夹角和绕射圆盘中心点的位置
	float cosAngle=(vectorLine1x*incidentDirectina+vectorLine1y*incidentDirectinb)/(sqrt(vectorLine1x*vectorLine1x+vectorLine1y*vectorLine1y)*sqrt(incidentDirectina*incidentDirectina+incidentDirectinb*incidentDirectinb+incidentDirectinc*incidentDirectinc));
	float circularPointx,circularPointy,circularPointz;//绕射圆盘中心点的坐标
	if(cosAngle<0)
	{
		circularPointx=0.5*(point1x+pointx);
		circularPointy=0.5*(point1y+pointy);
		circularPointz=buildingHeight;
		cosAngle=-cosAngle;
	}
	else
	{
		circularPointx=0.5*(point2x+pointx);
		circularPointy=0.5*(point2y+pointy);
		circularPointz=buildingHeight;

	}
	float d1=sqrt((pointx-circularPointx)*(pointx-circularPointx)+(pointy-circularPointy)*(pointy-circularPointy));//绕射点到绕射圆盘中心点的距离
	float sinAngle=sqrt((1-cosAngle*cosAngle));
	if(cosAngle==0)
	{
		shootingNumber=0;
	}
	if(cosAngle!=0)
	{
		float tanAngle=sinAngle/cosAngle;
		float R=d1*tanAngle;//绕射圆盘半径
		
		float cosx=vectorx/sqrt((vectorx*vectorx+vectory*vectory));//法向量在x轴正方向的分量
		float cosy=vectory/sqrt((vectorx*vectorx+vectory*vectory));//法向量在y轴正方向的分量
		//求出绕射圆盘上点的坐标
		int count=0;
		for(float m=91;m<180;m=m+shootingInterval)
		{			
			Rx=R*sin(m*3.14/180)*cosx+circularPointx-pointx;
			Ry=R*sin(m*3.14/180)*cosy+circularPointy-pointy;
			Rz=R*cos(m*3.14/180)+circularPointz-pointz;
			count++;
			m_pRecordset->AddNew();
			m_pRecordset->PutCollect("RId",count);
			m_pRecordset->PutCollect("RDirecX",Rx);
			m_pRecordset->PutCollect("RDirecY",Ry);
			m_pRecordset->PutCollect("RDirecZ",Rz);
			m_pRecordset->Update();
			m_pRecordset->MoveNext();

		}
		shootingNumber=count;

	}




}
