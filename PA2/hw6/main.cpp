#ifndef __PROGTEST__
#include <cassert>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <list>
#include <algorithm>
#include <memory>
#include <functional>
using namespace std;
#endif /* __PROGTEST__ */

class CComputer;
class CNetwork;

class CComponent
{
public:
    virtual ~CComponent() { };
    
    virtual void print(ostream &os, const string &pref) const = 0;
    virtual void printHeader(ostream &os, const string &pref) const = 0;
    virtual CComputer* FindComputer(const string &name) = 0;
    virtual CNetwork* FindNetwork(const string &name) = 0;
    virtual CComponent* clone(list<pair<string, string>> remap) = 0;
    virtual CComponent* clone() const & = 0;
};


class CComputer
{
public:
    CComputer() = default;
    explicit CComputer(string name) : m_name(name) {}
    ~CComputer() = default;
    
    CComputer& AddComponent(const CComponent &component);
    CComputer& AddAddress(const string &addr);
    CComputer* FindComputer(const string &name);
    CNetwork* FindNetwork(const string &name);
    CComputer Duplicate(list<pair<string, string>> remap);
    
    void print(ostream& os, const string &pref) const;
    void printHeader(ostream& os, const string &pref) const;
    friend ostream &operator<< (ostream &os, const CComputer &comp);
    
    string get_name() const
    {
        return m_name;
    }
    
protected:
    string m_name;
    list<shared_ptr<CComponent>> m_components;
    list<string> m_addresses;
};


class CNetwork : public CComponent
{
public:
    CNetwork() = default;
    explicit CNetwork(string name) : m_name(name) {}
    ~CNetwork() override = default;
    
    CNetwork& AddComputer (const CComputer &comp);
    CComputer* FindComputer(const string &name) override;
    CNetwork* FindNetwork(const string &name) override;
    CComponent* clone(list<pair<string, string>> remap) override;
    CComponent* clone() const & override;
    
    void print(ostream &os, const string &pref) const override;
    void printHeader(ostream &os,const string &pref) const override;
    friend ostream& operator<< (ostream &os, const CNetwork &net);
private:
    string m_name;
    vector<CComputer> m_compList;
};

class CCPU : public CComponent
{
public:
    CCPU() = default;
    CCPU(int cores, int frequency) : m_cores(cores), m_frequency(frequency) {}
    ~CCPU() override = default;
    
    CComponent* clone() const & override;
    CComponent* clone(list<pair<string, string>> remap) override;
    CComputer* FindComputer(const string &name) override  { return nullptr; }
    CNetwork* FindNetwork(const string &name) override  { return nullptr; }
    
    void print(ostream& os, const string &pref) const override {}
    void printHeader(ostream &os, const string &pref) const override;
    
protected:
    int m_cores;
    int m_frequency;
};


class CMemory : public CComponent
{
public:
    CMemory() = default;
    explicit CMemory(int memorySize) : m_memorySize(memorySize) {}
    ~CMemory() override = default;
    
    CComponent* clone() const & override;
    CComponent* clone(list<pair<string, string>> remap) override;
    CComputer* FindComputer(const string &name) override  { return nullptr; }
    CNetwork* FindNetwork(const string &name) override  { return nullptr; }
    
    void print(ostream& os,const string &pref) const override {}
    void printHeader(ostream &os, const string &pref) const override;
    
protected:
    int m_memorySize;
};


class CDisk : public CComponent
{
public:
    CDisk() = default;
    CDisk(string type,int size) : m_type(type), m_size(size) {}
    ~CDisk() override = default;
    
    CComponent* clone() const & override;
    CComponent* clone(list<pair<string, string>> remap) override;
    CComputer* FindComputer(const string &name) override { return nullptr; }
    CNetwork* FindNetwork(const string &name) override  { return nullptr; }
    
    CDisk& AddPartition(const int &size,const string &desc);
    
    void print(ostream &os,const string &pref) const override;
    void printHeader(ostream &os, const string &pref) const override;
    
    static const string SSD;
    static const string MAGNETIC;
    
protected:
    string m_type;
    int m_size;
    list<pair<int, string>> m_partitions;
};

//======CComputer==================================

CComputer& CComputer::AddComponent(const CComponent &component)
{
    m_components.push_back(shared_ptr<CComponent> (component.clone()));
    return *this;
}

CComputer& CComputer::AddAddress(const string &addr)
{
    m_addresses.push_back(addr);
    return *this;
}

CComputer* CComputer::FindComputer(const string &name)
{
    CComputer *comp = nullptr;
    
    if (m_name == name)
        return this;
    
    else {
        for (auto &i : m_components) {
            comp = i->FindComputer(name);
            
            if (comp != nullptr)
                return comp;
        }
    }
    return comp;
}

CNetwork* CComputer::FindNetwork(const string &name)
{
    CNetwork *network = nullptr;
    
    for(const auto &i : m_components) {
        
        network = i->FindNetwork(name);
        if (network != nullptr)
            return network;
    }
    
    return network;
}

void CComputer::print(ostream& os, const string &pref) const
{
    for (const auto &i : m_addresses) {
        
        os << pref << "+-" << i << endl;
    }
    
    unsigned cntr = 0;
    
    for (const auto & i : m_components) {
        if (cntr == m_components.size() - 1) {
            i->printHeader(os, pref + "\\-");
            i->print(os, pref + "  ");
            cntr++;
        } else {
            i->printHeader(os, pref + "+-");
            i->print(os, pref + "| ");
            cntr++;
        }
    }
}

void CComputer::printHeader(ostream& os, const string &pref) const
{
    os << pref << "Host: " << m_name << endl;
}

CComputer CComputer::Duplicate(list<pair<string, string>> remap)
{
    
    auto it = find_if(remap.begin(), remap.end(), [this](const pair<string, string> &elem) {return (elem.first == this->m_name);});
    string newName;
    
    if (it != remap.end())
        newName = it->second;
    else
        newName = m_name;
    
    CComputer computer(newName);
    
    computer.m_addresses = m_addresses;
    
    for (auto &i : m_components) {
        computer.m_components.push_back(shared_ptr<CComponent> (i.get()->clone(remap)));
    }
    
    return computer;
}

ostream &operator<< (ostream &os, const CComputer &comp)
{
    comp.printHeader(os,"");
    comp.print(os,"");
    return os;
}

//======CNetwork==================================

CComponent* CNetwork::clone() const &
{
    return new CNetwork(*this);
}

CNetwork& CNetwork::AddComputer (const CComputer &comp)
{
    m_compList.push_back(comp);
    return *this;
}

CComputer* CNetwork::FindComputer(const string &name)
{
    CComputer *comp = nullptr;
    
    for (auto &i : m_compList) {
        comp = i.FindComputer(name);
        
        if (comp != nullptr)
            return comp;
    }
    
    return comp;
}

CNetwork* CNetwork::FindNetwork(const string &name)
{
    
    CNetwork *network = nullptr;
    
    if (m_name == name)
        return this;
    
    else {
        for (auto &i : m_compList) {
            network = i.FindNetwork(name);
            
            if (network != nullptr)
                return network;
        }
    }
    
    return network;
}

CComponent* CNetwork::clone(list<pair<string, string>> remap)
{
    auto it = find_if(remap.begin(), remap.end(), [this]
                      (const pair<string, string> &elem){return elem.first == m_name;});
    
    string newName;
    
    if (it != remap.end())
        newName = it->second;
    else
        newName = m_name;
    
    CNetwork* network = new CNetwork(newName);
    
    for (auto &i : m_compList) {
        network->m_compList.push_back(i.Duplicate(remap));
    }
    
    return network;
}

void CNetwork::print(ostream &os, const string &pref) const
{
    unsigned cntr = 0;
    
    for (const auto &i : m_compList) {
        
        if (cntr == m_compList.size() - 1) {
            i.printHeader(os, pref + "\\-");
            i.print(os, pref + "  ");
            cntr++;
        } else {
            i.printHeader(os, pref + "+-");
            i.print(os, pref + "| ");
            cntr++;
        }
    }
}

void CNetwork::printHeader(ostream &os,const string &pref) const
{
    os << pref << "Network: " << m_name << endl;
}


ostream& operator<< (ostream &os, const CNetwork &net)
{
    net.printHeader(os, "");
    net.print(os, "");
    return os;
}

//======CCPU==================================

CComponent* CCPU::clone() const &
{
    return new CCPU(*this);
}

CComponent* CCPU::clone(list<pair<string, string>> remap)
{
    return new CCPU(*this);
}


// the description of the cpu
void CCPU::printHeader(ostream &os, const string &pref) const
{
    os << pref << "CPU, " << m_cores << " cores @ " << m_frequency << "MHz" << endl;
}


//======CMemory==================================

CComponent* CMemory::clone() const &
{
    return new CMemory(*this);
}

CComponent* CMemory::clone(list<pair<string, string>> remap)
{
    return new CMemory(*this);
}

void CMemory::printHeader(ostream &os, const string &pref) const
{
    os << pref <<"Memory, " << m_memorySize << " MiB" << endl;
}

//======CDisk==================================

const string CDisk::SSD = "SSD";
const string CDisk::MAGNETIC = "HDD";

CComponent* CDisk::clone() const &
{
    return new CDisk(*this);
}

CComponent* CDisk::clone(list<pair<string, string>> remap)
{
    return new CDisk(*this);
}

CDisk& CDisk::AddPartition(const int &size,const string &desc)
{
    pair<int, string> partition;
    partition.first = size;
    partition.second = desc;
    m_partitions.push_back(partition);
    return *this;
}

void CDisk::print(ostream &os,const string &pref) const
{
    unsigned cntr = 0;
    
    for (const auto &i : m_partitions) {
        if (cntr == m_partitions.size() - 1)
        {
            os << pref + "\\-" << "[" << cntr << "]: " << i.first << " GiB, " << i.second << endl;
        } else {
            os << pref + "+-" << "[" <<  cntr << "]: " << i.first << " GiB, " << i.second << endl;
        }
        cntr++;
    }
}

void CDisk::printHeader(ostream &os, const string &pref) const
{
    os << pref << m_type << ", " << m_size << " GiB" << endl;
}


#ifndef __PROGTEST__
template<typename _T>
string toString ( const _T & x )
{
    ostringstream oss;
    oss << x;
    return oss . str ();
}

int main ( void )
{

}

#endif /* __PROGTEST__ */
