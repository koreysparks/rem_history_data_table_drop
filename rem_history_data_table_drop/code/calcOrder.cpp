#include "calcOrder.h"

#include <iostream>
#include <fstream>
#include <sstream> 
using namespace std;

CCalcTrade::CCalcTrade(CDB* db)
	:m_db(db)
{}

CCalcTrade::~CCalcTrade()
{}


void CCalcTrade::Run()
{
	vector<string> tables;
	m_db->query("show tables;");
	
	// 查询到的数据，只有一个表名字段
	vector<map<string, string> > tablesFileds = m_db->getData();

	for(size_t p = 0; p < tablesFileds.size(); ++p)
	{
		map<string, string> oneRow = tablesFileds[p];
		for(map<string, string>::const_iterator iter = oneRow.begin(); iter != oneRow.end(); ++iter)
		{
			tables.push_back(iter->second);
			printf("---------- table:%s--------------------------\n", iter->second.c_str());

		}
	}

	string commend; 
	CDB::Sleep(10);
	cout << "input all need drop table name:" << endl;
	cin >> commend;
	vector<string> dropTables;

	// 按输入字符过滤删除
	for(size_t i = 0; i < tables.size(); ++i)
	{
		if(string::npos != tables[i].find(commend))
		{
			dropTables.push_back(tables[i]);
			printf("---------- %s drop table:%s--------------------------\n", m_db->getDbHost().c_str(), tables[i].c_str());
		}
			
	}

	cout << "are sure drop these table? (y/n)" << endl;
	cin >> commend;
	if(commend != "y")
	{
		return;
	}

	for(size_t i = 0; i < dropTables.size(); ++i)
	{
		m_db->query(string("drop table ") + dropTables[i] + ";");
	}

	cout << "drop  table finish" << endl;
	CDB::Sleep(1000);

}

void CCalcTrade::converTimeStamp(unsigned long long int timeStamp, tm& tmResult, unsigned int& nanoSec)
{
	unsigned int sec;
	char* p = (char*)(&timeStamp);
	memcpy(&sec, p + 4, 4);
	memcpy(&nanoSec, p, 4);

#ifdef _WIN32
	time_t tt32 = (time_t)sec;
	localtime_s(&tmResult, &tt32);
#else
	time_t tt32 = (time_t)sec;
	localtime_r(&tt32, &tmResult);
#endif
	return;
}

unsigned long long int CCalcTrade::stol(string& str)
{
	unsigned long long int result;
	istringstream is(str.c_str());
	is >> result;
	return result;
}



