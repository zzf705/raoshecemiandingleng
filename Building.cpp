#include "Building.h"



Building Building::getObject(vector<string> param,string sepOut,string sepIn) {
	Building building = Building(param,sepOut,sepIn);
	return building;
}

vector<Building> Building::getObjectSet(vector<vector<string>> param,string sepOut,string sepIn) {
	vector<Building> buildingSet;
	vector<vector<string>>::iterator iter = param.begin();
	while(iter!=param.end()) {
		Building building = Building::getObject(*iter++,sepOut,sepIn);
		buildingSet.push_back(building);
	}
	return buildingSet;
}

void Building::GetThisBuildingRecord(int BId)
{
	id=BId;
	
	//_ConnectionPtr sqlSp;
	//DBConnect* dbconnection;
	//_RecordsetPtr m_pRecordset;
	//dbconnection = DBConnGuard::GetAConnect();
	//sqlSp = dbconnection->_connection_ptr;
	////dbCon.getMyConnection(connection);
	//m_pRecordset.CreateInstance(__uuidof(Recordset));

	//////////////////////////////////////////////////////////////////

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
	///////////////////////////////////////////////////////////////////////
	string Ext;
	BuildingPoint BP;
	stringstream ss;
	Ext.append("SELECT * FROM  BuildingPoint WHERE PBuildingId=");
	ss<<BId;
	Ext.append(ss.str());
	ss.str("");
	ss.clear();
	try
	{
		m_pRecordset->Open(Ext.c_str(),(IDispatch*)sqlSp,adOpenDynamic,adLockOptimistic, adCmdText);
		m_pRecordset->MoveFirst();
		while(!m_pRecordset->adoEOF)
		{
			
			BP.longitude=double(m_pRecordset->GetCollect("PLongitude"));
			BP.latitude=double(m_pRecordset->GetCollect("PLatitude"));
			BP.id=int(m_pRecordset->GetCollect("PId"));
			BP.px=double(m_pRecordset->GetCollect("PX"));
			BP.py=double(m_pRecordset->GetCollect("PY"));
			BP.buildingId=int(m_pRecordset->GetCollect("PBuildingId"));
			BPoint.push_back(BP);
			m_pRecordset->MoveNext();
			
		}
		Ext.clear();

	}
	catch (_com_error &e)
	{
		cout << e.Description()<<endl;
	}
	
	m_pRecordset->Close();
	//查找建筑物的高度
	
	Ext.append("SELECT * FROM  Building WHERE BId=");
	ss<<BId;
	Ext.append(ss.str());
	ss.str("");
	ss.clear();
	try
	{
		m_pRecordset->Open(Ext.c_str(),(IDispatch*)sqlSp,adOpenDynamic,adLockOptimistic, adCmdText);
		
			
			buildingHeight=float(m_pRecordset->GetCollect("BHeight"));
			
		
		Ext.clear();

	}
	catch (_com_error &e)
	{
		cout << e.Description()<<endl;
	}

	/*sqlSp->Close();
	m_pRecordset->Close();*/
}

