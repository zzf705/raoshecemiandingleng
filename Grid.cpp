#include "Grid.h"


Grid Grid::getObject(vector<string> param,string sepOut,string sepIn) {
	Grid grid = Grid(param,sepOut,sepIn);
	return grid;
}

vector<Grid> Grid::getObjectSet(vector<vector<string>> param,string sepOut,string sepIn) {
	vector<Grid> gridSet;
	vector<vector<string>>::iterator iter = param.begin();
	while(iter!=param.end()) {
		Grid grid = Grid::getObject(*iter++,sepOut,sepIn);
		gridSet.push_back(grid);
	}
	return gridSet;
}


void Grid::GetThisGirdRecord(int GId)
{
	//_ConnectionPtr sqlSp;
	//DBConnect* dbconnection;
	//_RecordsetPtr m_pRecordset;
	//dbconnection = DBConnGuard::GetAConnect();
	//sqlSp = dbconnection->_connection_ptr;
	////dbCon.getMyConnection(connection);
	//m_pRecordset.CreateInstance(__uuidof(Recordset));

	////////////////////////////////////////////////////////////////////
	CoInitialize(NULL);
	_ConnectionPtr  sqlSp;
	HRESULT hr=sqlSp.CreateInstance(_uuidof(Connection));
	if(FAILED(hr))
	{
		cout<<"cuole"<<endl;
	}
	try {
		_bstr_t strConnect="Driver={sql server};server=ZHANGZHE-PC;uid=sa;pwd=123456;database=test30;";

		sqlSp->Open(strConnect,"","",adModeUnknown);
	}
	catch(_com_error &e) {
		cout<<"cuole"<<endl;

	}
	_RecordsetPtr m_pRecordset;; //记录集对象指针，用来执行SQL语句并记录查询结果
	if(FAILED(m_pRecordset.CreateInstance( _uuidof( Recordset ))))
	{
		cout<<"cuole"<<endl;
	}
	////////////////////////////////////////////////////////////////
	_variant_t Jia;
	string Ext;
	string medm;
	int mBid1,mBid2;
	stringstream ss;
	Ext.append("SELECT * FROM  Grid WHERE GId=");
	ss<<GId;
	Ext.append(ss.str());
	try
	{
		m_pRecordset->Open(Ext.c_str(),(IDispatch*)sqlSp,adOpenDynamic,adLockOptimistic, adCmdText);
		Ext.clear();
		id=GId;
		longitude=m_pRecordset->GetCollect("GLongitude");
		latitude=m_pRecordset->GetCollect("GLatitude");
		GPX=m_pRecordset->GetCollect("GPX");
		GPY=m_pRecordset->GetCollect("GPY");
		Jia=m_pRecordset->GetCollect("GBId");
		if(Jia.vt!=VT_NULL)
		Ext.append(_bstr_t(Jia));
		else
			Ext.append("0;");
		GBId=ChangeTypeTool::stringToIntVector(Ext.c_str(),";");
		sort( GBId.begin(), GBId.end() );
		GBId.erase( unique( GBId.begin(), GBId.end() ), GBId.end() );
		Ext.clear();
		
	}
	catch (_com_error &e)
	{
		cout << e.Description()<<endl;
	}
	m_pRecordset->Close();
	sqlSp->Close();
}


void Grid::GetThisGirdRecord(double GX, double GY)
{
	//_ConnectionPtr sqlSp;
	//DBConnect* dbconnection;
	//_RecordsetPtr m_pRecordset;
	//dbconnection = DBConnGuard::GetAConnect();
	//sqlSp = dbconnection->_connection_ptr;
	////dbCon.getMyConnection(connection);
	//m_pRecordset.CreateInstance(__uuidof(Recordset));

	CoInitialize(NULL);
	_ConnectionPtr  sqlSp;
	HRESULT hr=sqlSp.CreateInstance(_uuidof(Connection));
	if(FAILED(hr))
	{
		cout<<"cuole"<<endl;
	}
	try {
		_bstr_t strConnect="Driver={sql server};server=ZHANGZHE-PC;uid=sa;pwd=123456;database=test30;";

		sqlSp->Open(strConnect,"","",adModeUnknown);
	}
	catch(_com_error &e) {
		cout<<"cuole"<<endl;

	}
	_RecordsetPtr m_pRecordset;; //记录集对象指针，用来执行SQL语句并记录查询结果
	if(FAILED(m_pRecordset.CreateInstance( _uuidof( Recordset ))))
	{
		cout<<"cuole"<<endl;
	}

	string Ext;
	string medm;
	int mBid1,mBid2;
	stringstream ss;
	Ext.append("SELECT * FROM  Grid WHERE GX=");
	ss<<GX;
	Ext.append(ss.str());
	ss.str("");
	Ext.append(" AND GY=");
	ss<<GY;
	Ext.append(ss.str());
	ss.str("");
	try
	{
		m_pRecordset->Open(Ext.c_str(),(IDispatch*)sqlSp,adOpenDynamic,adLockOptimistic, adCmdText);
		Ext.clear();
		id=m_pRecordset->GetCollect("GId");
		longitude=m_pRecordset->GetCollect("GLongitude");
		latitude=m_pRecordset->GetCollect("GLatitude");
		GPX=GX;
		GPY=GY;
		

		/*Ext.append(_bstr_t(m_pRecordset->GetCollect("GBId")));
		GBId=ChangeTypeTool::stringToIntVector(Ext.c_str(),";");
		sort( GBId.begin(), GBId.end() );
		GBId.erase( unique( GBId.begin(), GBId.end() ), GBId.end() );*/
		
	}
	catch (_com_error &e)
	{
		cout << e.Description()<<endl;
	}
	m_pRecordset->Close();
		Ext.append("SELECT * FROM  BuildingGridId WHERE BGridId=");
		ss<<id;
		Ext.append(ss.str());
		ss.str("");
		try
	{
		m_pRecordset->Open(Ext.c_str(),(IDispatch*)sqlSp,adOpenDynamic,adLockOptimistic, adCmdText);
		Ext.clear();
		m_pRecordset->MoveFirst();
		while(!m_pRecordset->adoEOF)
		{
			int buildingNumber;//建筑物编号列表
			buildingNumber=int(m_pRecordset->GetCollect("BId"));
			GBId.push_back(buildingNumber);
			m_pRecordset->MoveNext();
			
		}
		Ext.clear();
		
	}
	catch (_com_error &e)
	{
		cout << e.Description()<<endl;
	}

	m_pRecordset->Close();
	sqlSp->Close();
}
void Grid::PutThisGridStrength(int GId, double GStrength)
{
	//_ConnectionPtr sqlSp;
	//DBConnect* dbconnection;
	//_RecordsetPtr m_pRecordset;
	//dbconnection = DBConnGuard::GetAConnect();
	//sqlSp = dbconnection->_connection_ptr;
	////dbCon.getMyConnection(connection);
	//m_pRecordset.CreateInstance(__uuidof(Recordset));

	CoInitialize(NULL);
	_ConnectionPtr  sqlSp;
	HRESULT hr=sqlSp.CreateInstance(_uuidof(Connection));
	if(FAILED(hr))
	{
		cout<<"cuole"<<endl;
	}
	try {
		_bstr_t strConnect="Driver={sql server};server=ZHANGZHE-PC;uid=sa;pwd=123456;database=test30;";

		sqlSp->Open(strConnect,"","",adModeUnknown);
	}
	catch(_com_error &e) {
		cout<<"cuole"<<endl;

	}
	_RecordsetPtr m_pRecordset;; //记录集对象指针，用来执行SQL语句并记录查询结果
	if(FAILED(m_pRecordset.CreateInstance( _uuidof( Recordset ))))
	{
		cout<<"cuole"<<endl;
	}



	int color[9]={COLOR1,COLOR2,COLOR3,COLOR4,COLOR5,COLOR6,COLOR7,COLOR8,COLOR9};
	string Ext;
	string medm;
	int mBid1,mBid2;
	stringstream ss;
	Ext.append("SELECT * FROM  Grid WHERE GId=");
	ss<<GId;
	Ext.append(ss.str());
	try
	{
		m_pRecordset->Open(Ext.c_str(),(IDispatch*)sqlSp,adOpenDynamic,adLockOptimistic, adCmdText);
		Ext.clear();
		if(GStrength!=0)
		{
			m_pRecordset->PutCollect("GRealSNR",_variant_t(double(GStrength)));
			m_pRecordset->Update();
		}
		else
		{
			m_pRecordset->PutCollect("GRealSNR",_variant_t(0));
			m_pRecordset->Update();
		}

	}
	catch (_com_error &e)
	{
		cout << e.Description()<<endl;
	}
	ss.clear();
	ss.str("");
}
void Grid::addThisGridStrengthToNew(int GId, double GStrength,int AId)//将场强结果放到GridFieldStrenthAddBaseNum表中
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
		m_pRecordset->Open("SELECT * FROM  GridFieldStrenthAddBaseNum",(IDispatch*)sqlSp,adOpenDynamic,adLockOptimistic, adCmdText);
		
	}
	catch (_com_error &e)
	{
		cout << e.Description()<<endl;
	}
	try
	{
	m_pRecordset->AddNew();
	m_pRecordset->PutCollect("Id",_variant_t(Id));
	Id++;
	m_pRecordset->PutCollect("GId",_variant_t(GId));
	m_pRecordset->PutCollect("GFieldStrength",_variant_t( 10*log10(GStrength*1000)));
	m_pRecordset->PutCollect("AId",_variant_t(AId));
	m_pRecordset->Update();
	m_pRecordset->Close();
	sqlSp->Close();

		
	}
	catch (_com_error &e)
	{
		cout << e.Description()<<endl;
	}
}
