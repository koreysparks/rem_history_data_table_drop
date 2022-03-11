#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <dlfcn.h>
#include <string.h>
#include <string>
#include <unistd.h>


#include "db.hpp"

using std::string;

struct OrderInfo
{
	int orderCount;
	int orderQty;
	int execQty;
	double execPueim;
};

class CCalcTrade
{
public:
	CCalcTrade(CDB* db);
	virtual ~CCalcTrade();

	void Run();

	void converTimeStamp(unsigned long long inttimeStamp, tm& tmResult, unsigned int& nanoSsec);
	void loadResult();
	unsigned long long int stol(string& str);

private:
	CDB* m_db;

	map<string, OrderInfo>						m_order; //�������ɽ�����

	map<string, int>							m_orderTimeCount;  // ����ʱ��ͳ��
	map<string, vector<pair<string, int> > >	m_orderPeakResult; // ����ʱ����������
};

