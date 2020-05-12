#pragma once

#include <string>
#include <vector>

#include <unordered_map>
#include <unordered_set>

#include "DeductionUtil.h"

using EncryptKeyTpe = int;
using EKT = EncryptKeyTpe;

class DataStorage
{
public:
	DataStorage();
	~DataStorage();

	bool AddUser(int user_id);
	bool DelUser(int user_id);

	//bool AddCompany(some info;);
	//bool AddCompany(some info;);

	std::vector<DeductionInfo> GetDedctList(int user_id);
	bool AddDeduction(int user_id, int company_id);
	bool RemoveDeduction(int user_id, int company_id);

	void FlushData();

private:
	void LoadData();

	std::string Encryt(EKT key, std::string& data) { return data; };
	std::string Decryt(EKT key, std::string& data) { return data; };

	std::unordered_map<int, std::unordered_set<unsigned int>> dd_table;//user_id, company_id
	std::unordered_map<int, std::string> company_table;//company_id, company_name

	EKT key;
};

