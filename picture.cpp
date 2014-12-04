#include "picture.h"


picture::picture(void)
{
}


picture::~picture(void)
{
}
void picture::makeMif()
{
	int color[15]={COLOR16,COLOR15,COLOR14,COLOR13,COLOR12,COLOR11,COLOR10,COLOR9,COLOR8,COLOR7,COLOR6,COLOR5,COLOR4,COLOR3,COLOR2};//代表-70到-20db之间用15种颜色表示出

	int color1[2]={COLOR1,COLOR17};//代表额外两种颜色
	int Ecolor[6]={ECOLOR1,ECOLOR2,ECOLOR3,ECOLOR4,ECOLOR5,ECOLOR6};//代表误差的6种颜色，误差是正的使用3种颜色，误差是负的使用3种颜色
	CoInitialize(NULL);
	_ConnectionPtr  sqlSp;
	HRESULT hr=sqlSp.CreateInstance(_uuidof(Connection));
	if(FAILED(hr))
	{
		cout<<"_ConnectionPtr对象指针实例化失败！！！"<<endl;
		return ;
	}
	else {
		try {
			_bstr_t strConnect="Driver={sql server};server=ZHANGZHE-PC;uid=sa;pwd=123456;database=test30;";
			//_bstr_t strConnect="Provider=SQLOLEDB;Server=127.0.0.1,1433;Database=PBMS;uid=sa;pwd=pp471006459;";
			//_bstr_t strConnect="Provider=SQLOLEDB.1;Password=pp471006459;Persist Security Info=True;User ID=sa;"
				//"Initial Catalog=PBMS;Data Source=127.0.0.1,1433";
			//以上这三条strConnect语句都可以用！！看自己喜好选择用吧
			//要注意修改用户名uid、密码pwd、数据库名database，这三个参数均是你自己sql server的数据库信息
			sqlSp->Open(strConnect,"","",adModeUnknown);
		}
		catch(_com_error &e) {
			cout<<e.Description()<<endl;
		}
		_RecordsetPtr m_pRecordset; //指向射线跟踪数据
		if(FAILED(m_pRecordset.CreateInstance( _uuidof( Recordset ))))
		{
			cout<<"记录集对象指针实例化失败！"<<endl;
			return;
		}

		try
		{
			m_pRecordset->Open("SELECT * FROM GridFieldStrenthAddBaseNum",(IDispatch*)sqlSp,adOpenDynamic,adLockOptimistic, adCmdText);//打开数据库，执行SQL语句
		}
		catch (_com_error &e)
		{
			cout << e.Description()<<endl;
		}

		double GStrength,error;//代表读取网格的场强值和误差
		int GID;//射线跟踪计算读取的网格编号
		double Min=10000,Max=-10000;
		double range;
		//首先求出射线跟踪数据的最大值和最小值
		m_pRecordset->MoveFirst();
		while(!m_pRecordset->adoEOF)
		{
			
			GStrength=double(m_pRecordset->GetCollect("GFieldStrength"));
			if(GStrength>Max)
				Max=GStrength;
			/*if(GStrength<Min)
				Min=GStrength;*/
			m_pRecordset->MoveNext();
		}
		range=Max+42;//画颜色时-42是最大值，计算的所有值都减到-42以下
		//////////////
		//给射线跟踪数据画颜色
		int Gcolor,GEcolor;
		m_pRecordset->MoveFirst();
		while(!m_pRecordset->adoEOF)
		{
			GStrength=double(m_pRecordset->GetCollect("GFieldStrength"));	
			GID=m_pRecordset->GetCollect("GId");
			GStrength=GStrength-range;
			if(GStrength>=-90&&GStrength<-45)
				Gcolor=color[int((GStrength+90)*15/45)];
			if(GStrength<-90)
				Gcolor=color1[1];
			if(GStrength>=-45)
				Gcolor=color1[0];
			_RecordsetPtr m_pRecordset1;//用来从射线跟踪结果中读取记录
				if(FAILED(m_pRecordset1.CreateInstance( _uuidof( Recordset ))))
		{
			cout<<"记录集对象指针实例化失败！"<<endl;
			return;
		}
		string Ext;
	stringstream ss;
	Ext.append("SELECT * FROM Grid WHERE GId=");
	ss<<GID;
	Ext.append(ss.str());
	ss.str("");
	ss.clear();
	try 
	{
		m_pRecordset1->Open(Ext.c_str(),(IDispatch*)sqlSp,adOpenDynamic,adLockOptimistic, adCmdText);
	}
	catch (_com_error &e)
	{
		cout << e.Description()<<endl;
	}
	try
		{
			m_pRecordset1->MoveFirst();
			while(!m_pRecordset1->adoEOF)
			{
               
			   m_pRecordset1->PutCollect("GColor",_variant_t(Gcolor));
			   m_pRecordset1->Update();
			   m_pRecordset1->MoveNext();

			}
	    }
			catch (_com_error &e)
	   {
		cout << e.Description()<<endl;
	   }		
			
			
			m_pRecordset->MoveNext();
						
		}
		_RecordsetPtr m_pRecordset1;
		if(FAILED(m_pRecordset1.CreateInstance( _uuidof( Recordset ))))
		{
			cout<<"记录集对象指针实例化失败！"<<endl;
			return;
		}
		try
	{
		m_pRecordset1->Open("SELECT * FROM Grid",(IDispatch*)sqlSp,adOpenDynamic,adLockOptimistic, adCmdText);
	}
	catch (_com_error &e)
		{
			cout << e.Description()<<endl;
		}
	int Gnum=0;
	int count=0;
	m_pRecordset1->MoveFirst();
	while(!m_pRecordset1->adoEOF)
	{
		Gnum++;
		m_pRecordset1->MoveNext();
	}
	m_pRecordset1->Close();
	if(FAILED(m_pRecordset1.CreateInstance( _uuidof( Recordset ))))
		{
			cout<<"记录集对象指针实例化失败！"<<endl;
			return;
		}

	string ext;
	stringstream ss;
	double longitude;
	double latitude;
	ofstream file2("E:\\test30.mif",ios::out);
	file2<<"Version   300"<<endl;
	file2<<"Charset \"WindowsSimpChinese\""<<endl;
	file2<<"Delimiter \",\""<<endl;
	file2<<"CoordSys Earth Projection 1, 104"<<endl;
	file2<<"Columns 5"<<endl;
	file2<<"  TYPE Integer"<<endl;
	file2<<"  SUBTYPE Integer"<<endl;
	file2<<"  NAME Char(60)"<<endl;
	file2<<"  x Decimal(20, 8)"<<endl;
	file2<<"  y Decimal(20, 8)"<<endl;
	file2<<"Data"<<endl;
	file2<<endl;
	
	for(int i=0;i<Gnum;i++)
	{	
		file2<<"Region  1"<<endl;
		file2<<"  5"<<endl;
		ext.append("SELECT * FROM Grid WHERE GId=");
		ss<<i+1;
		cout<<i+1<<endl;
		ext.append(ss.str());
		try 
		{
			m_pRecordset1->Open(ext.c_str(),(IDispatch*)sqlSp,adOpenDynamic,adLockOptimistic, adCmdText);//打开数据库，执行SQL语句
			longitude=m_pRecordset1->GetCollect("GLongitude");
			latitude=m_pRecordset1->GetCollect("GLatitude");
			file2<<fixed<<setprecision(6)<<longitude-UNIT_LONG<<" "<<latitude+UNIT_LAT<<endl;
			file2<<fixed<<setprecision(6)<<longitude-UNIT_LONG<<" "<<latitude-UNIT_LAT<<endl;
			file2<<fixed<<setprecision(6)<<longitude+UNIT_LONG<<" "<<latitude-UNIT_LAT<<endl;
			file2<<fixed<<setprecision(6)<<longitude+UNIT_LONG<<" "<<latitude+UNIT_LAT<<endl;
			file2<<fixed<<setprecision(6)<<longitude-UNIT_LONG<<" "<<latitude+UNIT_LAT<<endl;
		}
		catch (_com_error &e)
		{
			cout << e.Description()<<endl;
		}
		
		file2<<"    Pen (1,2,0) "<<endl;
		/*double s;
		s=double(m_pRecordset1->GetCollect("GFieldStrength"));
		if(double(m_pRecordset1->GetCollect("GFieldStrength"))==0)
		{
			file2<<"    Brush (2,"<<(255*256*256+255*256+255)<<",16777215)"<<endl;
		}
		
		else
		{
			s=s-50;
			s=int(abs(s/50*255));
			if(s>0)
			{
				
				file2<<"    Brush (2,"<<(255*256*256+s*256+0)<<",16777215)"<<endl;
			}
			
		}*/
		file2<<"    Brush (2,"<<int(m_pRecordset1->GetCollect("GColor"))<<",16777215)"<<endl;
		
		file2<<"    Center ";
		file2<<fixed<<setprecision(6)<<longitude<<" "<<latitude<<endl;
		ss.str("");
		ss.clear();
		ext.clear();
		m_pRecordset1->Close();
		
	}








		}
		}