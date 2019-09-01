#ifndef __PROGTEST__
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cctype>
#include <cmath>
#include <cassert>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <list>
#include <algorithm>
#include <functional>
#include <memory>
using namespace std;
#endif /* __PROGTEST__ */

struct Land;
struct LandOwner
{
	string name;
	vector<Land*> lands;
};
struct Land
{
	string city;
	string addr;
	string region;
    string org_name;
	unsigned int id;
    unsigned int index;
	LandOwner *owner;
};

class CIterator;
class CLandRegister
{
private:

	unsigned int increment = 0;

	static bool compareCityAddr (const Land *land1, const Land *land2)
	{
		string str1 = land1->city;
		string str2 = land2->city;
		string str3 = land1->addr;
		string str4 = land2->addr;

		if (str1.compare(str2) == 0)
			return str3.compare(str4) < 0;

		return str1.compare(str2) < 0;
	}

	static bool compareRegionId (const Land *land1, const Land *land2)
	{
		string str1 = land1->region;
		string str2 = land2->region;

		int num1 = land1->id;
		int num2 = land2->id;

		if (str1.compare(str2) == 0)
			return  num1 < num2;

		return str1.compare(str2) < 0;
	}

	static bool compareOwner (const LandOwner *owner1, const LandOwner *owner2)
	{
		string str1 = owner1->name;
		string str2 = owner2->name;
        
		return str1.compare(str2) < 0;
	}

	static bool compareIndex (const Land *land1, const Land *land2)
	{
		int num1 = land1->index;
		int num2 = land2->index;
        
		return num1 < num2;
	}

	int binarySearchOwner (vector<LandOwner*> v, const string &toFind) const;
	int binarySearchCA (vector<Land*> v, const string &city, const string &addr) const;
	int binarySearchRI (vector<Land*> v, const string &region, unsigned int &id) const;

public:
	~CLandRegister(void);
	bool Add(const string &city, const string &addr, const string &region, unsigned int id);
	bool Del(const string &city, const string &addr);
	bool Del(const string &region, unsigned int id);
	bool NewOwner(const string &city, const string &addr, const string &owner);
	bool NewOwner(const string &region, unsigned int id, const string &owner);
	bool GetOwner(const string &city, const string &addr, string &owner) const;
	bool GetOwner(const string &region, unsigned int id, string &owner) const;
	unsigned Count(const string &owner) const;
	CIterator ListByAddr(void) const;
	CIterator ListByOwner(const string &owner) const;

	vector<Land*> cityAddrList;
	vector<Land*> regionIdList;
	vector<LandOwner*> ownerList;

};

class CIterator
{
private:
	unsigned current_pos = 0;
public:
	vector<Land*> m_land;

	bool AtEnd(void) const
	{
		if (current_pos == m_land.size())
			return true;

		return false;
	}
	void Next(void)
	{
		current_pos++;
	}
	string City(void) const
	{
		return m_land[current_pos]->city;
	}
	string Addr(void) const
	{
		return m_land[current_pos]->addr;
	}
	string Region(void) const
	{
		return m_land[current_pos]->region;
	}
	string Owner(void) const
	{
		return m_land[current_pos]->org_name;
	}
	unsigned ID(void) const
	{
		return m_land[current_pos]->id;
	}

};

CLandRegister::~CLandRegister(void)
{
	for (unsigned i = 0; i < cityAddrList.size(); i++)
	{
		if (cityAddrList[i] != nullptr)
			delete cityAddrList[i];
	}

	for (unsigned i = 0; i < ownerList.size(); i++)
	{
		if (ownerList[i] != nullptr)
			delete ownerList[i];
	}
}

bool CLandRegister::Add(const string &city, const string &addr, const string &region, unsigned int id)
{
	increment++;

	Land *land = new Land;
	land->city = city;
	land->addr = addr;
	land->region = region;
	land->id = id;
	land->org_name = "";
	land->index = increment;



	if (cityAddrList.size() == 0)
	{
		LandOwner *owner = new LandOwner;
		owner->name = "";
		land->owner = owner;

		owner->lands.push_back(land);
		ownerList.push_back(owner);
		cityAddrList.push_back(land);
		regionIdList.push_back(land);

		return true;
	}

	else if (binary_search(cityAddrList.begin(), cityAddrList.end(), land, compareCityAddr) ||
	 		 binary_search(regionIdList.begin(), regionIdList.end(), land, compareRegionId))
	{
		delete land;
		return false;
	}

	else
	{
		land->owner = ownerList[0];

		auto ownerIt = upper_bound(ownerList[0]->lands.begin(), ownerList[0]->lands.end(), land, compareRegionId);
		auto cityAddrIt = upper_bound(cityAddrList.begin(), cityAddrList.end(), land, compareCityAddr);
		auto regionIdIt = upper_bound(regionIdList.begin(), regionIdList.end(), land, compareRegionId);

		ownerList[0]->lands.insert(ownerIt, land);
		cityAddrList.insert(cityAddrIt, land);
		regionIdList.insert(regionIdIt, land);

		return true;
	}  
}

bool CLandRegister::Del(const string &city, const string &addr)
{
	int indexCA = binarySearchCA(cityAddrList, city, addr);

	if (indexCA == -1)
		return false;

	int indexRI = binarySearchRI(regionIdList, cityAddrList[indexCA]->region, cityAddrList[indexCA]->id);
	int index = binarySearchRI(cityAddrList[indexCA]->owner->lands, cityAddrList[indexCA]->region, cityAddrList[indexCA]->id);
	cityAddrList[indexCA]->owner->lands.erase(cityAddrList[indexCA]->owner->lands.begin() + index);

	delete cityAddrList[indexCA];

	cityAddrList.erase(cityAddrList.begin() + indexCA);
	regionIdList.erase(regionIdList.begin() + indexRI);

	return true;
}

bool CLandRegister::Del(const string &region, unsigned int id)
{
	int indexRI = binarySearchRI(regionIdList, region, id );

	if (indexRI == -1)
		return false;

	int indexCA = binarySearchCA(cityAddrList,  regionIdList[indexRI]->city, regionIdList[indexRI]->addr);

	int index = binarySearchRI(regionIdList[indexRI]->owner->lands, region, id );
	regionIdList[indexRI]->owner->lands.erase(regionIdList[indexRI]->owner->lands.begin() + index);

	delete regionIdList[indexRI];

	cityAddrList.erase(cityAddrList.begin() + indexCA);
	regionIdList.erase(regionIdList.begin() + indexRI);

	return true;
}

bool CLandRegister::GetOwner(const string &city, const string &addr, string &owner) const
{

	int index = binarySearchCA(cityAddrList, city, addr);

	if (index == -1)
		return false;

	owner = cityAddrList[index]->org_name;

	return true;
}

bool CLandRegister::GetOwner(const string &region, unsigned int id, string &owner) const
{
	int index = binarySearchRI(regionIdList, region, id);

	if (index == -1)
		return false;

	owner = regionIdList[index]->org_name;
	return true;
}

bool CLandRegister::NewOwner(const string &city, const string &addr, const string &owner)
{
	string str = owner;

	transform(str.begin(), str.end(), str.begin(), ::tolower);

	int indexCA = binarySearchCA(cityAddrList, city, addr);

	if (indexCA == -1)
		return false;

	if (str.compare(cityAddrList[indexCA]->owner->name) == 0)
		return false;

	increment++;

	int index = binarySearchRI(cityAddrList[indexCA]->owner->lands, cityAddrList[indexCA]->region, cityAddrList[indexCA]->id);
	cityAddrList[indexCA]->owner->lands.erase(cityAddrList[indexCA]->owner->lands.begin() + index);

	int indexOwner = binarySearchOwner(ownerList, str);

	if (indexOwner == -1)
	{
		LandOwner *ownr = new LandOwner;
		ownr->name = str;
		cityAddrList[indexCA]->owner = ownr;
		cityAddrList[indexCA]->org_name = owner;
		cityAddrList[indexCA]->index = increment;
		cityAddrList[indexCA]->owner->lands.push_back(cityAddrList[indexCA]);

		auto ownerIt = upper_bound(ownerList.begin(), ownerList.end(), ownr, compareOwner);
		ownerList.insert(ownerIt, ownr);
	}
	else
	{
		cityAddrList[indexCA]->owner = ownerList[indexOwner];
		cityAddrList[indexCA]->org_name = owner;
		cityAddrList[indexCA]->index = increment;

		auto it = upper_bound(cityAddrList[indexCA]->owner->lands.begin(), cityAddrList[indexCA]->owner->lands.end(), cityAddrList[indexCA], compareRegionId);
		ownerList[indexOwner]->lands.insert(it, cityAddrList[indexCA]);
	}

	return true;
}

bool CLandRegister::NewOwner(const string &region, unsigned int id, const string &owner)
{
	string str = owner;
	transform(str.begin(), str.end(), str.begin(), ::tolower);

	int indexRI = binarySearchRI(regionIdList, region, id);

	if (indexRI == -1)
	 	return false;

	if (str.compare(regionIdList[indexRI]->owner->name) == 0)
	    return false;

	increment++;

	int index = binarySearchRI(regionIdList[indexRI]->owner->lands, region, id );
	regionIdList[indexRI]->owner->lands.erase(regionIdList[indexRI]->owner->lands.begin() + index);


	int indexOwner = binarySearchOwner(ownerList, str);

	if (indexOwner == -1)
	{
		LandOwner *ownr = new LandOwner;
		ownr->name = str;
		regionIdList[indexRI]->owner = ownr;
		regionIdList[indexRI]->owner->lands.push_back(regionIdList[indexRI]);
		regionIdList[indexRI]->org_name = owner;
		regionIdList[indexRI]->index = increment;

		auto ownerIt = upper_bound(ownerList.begin(), ownerList.end(), ownr, compareOwner);
		ownerList.insert(ownerIt, ownr);
	}
	else
	{
		regionIdList[indexRI]->owner = ownerList[indexOwner];
		regionIdList[indexRI]->org_name = owner;
		regionIdList[indexRI]->index = increment;

		auto it = upper_bound(regionIdList[indexRI]->owner->lands.begin(), regionIdList[indexRI]->owner->lands.end(), regionIdList[indexRI], compareRegionId);
		ownerList[indexOwner]->lands.insert(it, regionIdList[indexRI]);
    }

	return true;
}

unsigned CLandRegister::Count(const string &owner) const
{
	string str = owner;
	transform(str.begin(), str.end(), str.begin(), ::tolower);
	
	int index = binarySearchOwner(ownerList, str);

	if (index == -1)
		return false;

	return ownerList[index]->lands.size();
}

CIterator CLandRegister::ListByAddr(void) const
{
	CIterator iterator;

	iterator.m_land = cityAddrList;

	return iterator;
}

CIterator CLandRegister::ListByOwner(const string &owner) const
{
	CIterator iterator;

	string str = owner;
	transform(str.begin(), str.end(), str.begin(), ::tolower);

	int index = binarySearchOwner(ownerList, str);

	if (index == -1)
		return iterator;

	iterator.m_land = ownerList[index]->lands;

	sort(iterator.m_land.begin(), iterator.m_land.end(), compareIndex);

	return iterator;
}

int CLandRegister::binarySearchOwner (vector<LandOwner*> v, const string &toFind) const
{
	int first = 0, last = v.size() - 1;
	string str1 = toFind;
	while (first <= last)
	{
		int middle = first + (last - first) / 2;

		if (v[middle]->name.compare(str1) == 0)
			return middle;

		else if (v[middle]->name.compare(str1) < 0)
			first = middle + 1;

		else
			last = middle - 1;

	}

	return -1;
}

int CLandRegister::binarySearchCA (vector<Land*> v, const string &city, const string &addr) const
{
	int first = 0, last = v.size() - 1;

	while (first <= last)
	{
		int middle = first + (last - first) / 2;

		if (v[middle]->city.compare(city) == 0)
		{
			if (v[middle]->addr.compare(addr) == 0)
				return middle;
			else if (v[middle]->addr.compare(addr) < 0)
				first = middle + 1;
			else
				last = middle - 1;
		}

		else if (v[middle]->city.compare(city) < 0)
			first = middle + 1;

		else
			last = middle - 1;

	}
	return -1;
}

int CLandRegister::binarySearchRI (vector<Land*> v, const string &region, unsigned int &id) const
{
	int first = 0, last = v.size() - 1;

	while (first <= last)
	{
		int middle = first + (last - first) / 2;

		if (v[middle]->region.compare(region) == 0) {
			if (v[middle]->id == id)
				return middle;
			else if (v[middle]->id < id)
				first = middle + 1;
			else
				last = middle - 1;
		}

		else if (v[middle]->region.compare(region) < 0)
			first = middle + 1;

		else
			last = middle - 1;

	}

	return -1;
}

int main ( void )
{
}

