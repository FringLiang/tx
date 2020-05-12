#include "database.h"

#include <iostream>

using namespace std;


DataStorage::DataStorage()
	:key()//pass by function ::main ?
{
	LoadData();
}

DataStorage::~DataStorage()
{
}

bool DataStorage::AddUser(int user_id)
{
	auto it = dd_table.find(user_id);
	if (it != dd_table.end())
	{
		//log error
		return false;
	}
	
	dd_table.emplace(user_id, std::unordered_set<unsigned int>());
	return true;
}

bool DataStorage::DelUser(int user_id)
{
	auto it = dd_table.find(user_id);
	if (it == dd_table.end())
	{
		//log error
		return false;
	}

	dd_table.erase(it);
	return true;
}

std::vector<DeductionInfo> DataStorage::GetDedctList(int user_id)
{
	auto it = dd_table.find(user_id);
	if (it!= dd_table.end())
	{
		auto& company_ids = it->second;
		std::vector<DeductionInfo> result;
		result.reserve(company_ids.size());
		for (auto id : company_ids)
		{
			//assert company_table contain company with id
			result.push_back(DeductionInfo{ id, company_table[id] });
		}
		return result;
	}

	//log error
	return std::vector<DeductionInfo>();
}

bool DataStorage::AddDeduction(int user_id, int company_id)
{
	auto it = dd_table.find(user_id);
	if (it == dd_table.end())
	{
		//log error
		return false;
	}

	it->second.insert(company_id);
	return true;
}

bool DataStorage::RemoveDeduction(int user_id, int company_id)
{
	auto it = dd_table.find(user_id);
	if (it == dd_table.end())
	{
		//log error
		return false;
	}

	it->second.erase(company_id);
	return true;
}

void DataStorage::LoadData()
{
	std::string raw_data;//= read from external source
	std::string decryt_data = Decryt(key, raw_data);

	//assume dd_table and company_table construnct by decryt_data
	dd_table =
	{
		{100,{1,2,3}},
		{111,{2,3}},
		{222,{1}},
		{333,{3}},
	};
	company_table =
	{
		{1, "富土康一"},
		{2, "富土康二"},
		{3, "富土康三"},
		{4, "富土康四"},
	};
}

void DataStorage::FlushData()
{
	cout << "dd table" << "\n";
	for (auto& info : dd_table)
	{
		//Encryt(key, info data to string) to disk
	}

	cout << "company info table" << "\n";
	for (auto& info : company_table)
	{
		//Encryt(key, info data to string) to disk
	}
}
