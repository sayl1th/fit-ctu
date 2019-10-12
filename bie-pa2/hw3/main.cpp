#ifndef __PROGTEST__
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cctype>
#include <ctime>
#include <climits>
#include <cmath>
#include <cassert>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include <list>
#include <algorithm>
#include <functional>
#include <memory>
using namespace std;
class InvalidRangeException
{
};
#endif /* __PROGTEST__ */

// uncomment if your code implements initializer lists
// #define EXTENDED_SYNTAX
class CRangeList;

class CRange
{
public:
    CRange() = default;
    CRange(long long start) : m_start(start), m_end(start) {}
    CRange(long long start, long long end) : m_start(start), m_end(end)
    {
        if (start > end)
            throw InvalidRangeException();
    }
    
    friend CRangeList operator+(const CRange &lhs,const CRange &rhs);
    friend CRangeList operator-(const CRange &lhs,const CRange &rhs);
    
    long long int getM_start() const {
        return m_start;
    }
    
    void setM_start(long long int m_start) {
        this->m_start = m_start;
    }
    
    long long int getM_end() const {
        return m_end;
    }
    
    void setM_end(long long int m_end) {
        this->m_end = m_end;
    }
    
private:
    long long m_start;
    long long m_end;
    
};

//----------------------------------------------------------
static bool compareIntervals(const CRange &lhs, const CRange &rhs)
{
    if (lhs.getM_start() == rhs.getM_start())
        return lhs.getM_end() < rhs.getM_end();
    else
        return lhs.getM_start() < rhs.getM_start();
}

vector<CRange> unMerge(vector<CRange> &v1, const vector<CRange> &v2)
{
    unsigned pos = 0;
    vector<CRange> tmp;
    bool changed = false;
    
    
    for (unsigned i = 0; i < v1.size(); i++)
    {
        if (pos >= v2.size())
        {
            tmp.push_back(v1[i]);
        }
        
        else if (v1[i].getM_start() < v2[pos].getM_start())
        {
            if (v1[i].getM_end() < v2[pos].getM_start()) {
                tmp.push_back(v1[i]);
            }
            
            else if (v1[i].getM_end() > v2[pos].getM_end())
            {
                if (changed == false)
                {
                    CRange range1(v1[i].getM_start(), v2[pos].getM_start() - 1);
                    tmp.push_back(range1);
                    CRange range2(v2[pos].getM_end() + 1, v1[i].getM_end());
                    tmp.push_back(range2);
                }
                
                else {
                    tmp.back().setM_start(v1[i].getM_start());
                    tmp.back().setM_end(v2[pos].getM_start() - 1);
                    CRange range2(v2[pos].getM_end() + 1, v1[i].getM_end());
                    tmp.push_back(range2);
                }
                
                v1[i].setM_start(v2[pos].getM_end()+1);
                pos++;
            }
            
            else if (v1[i].getM_end() <= v2[pos].getM_end())
            {
                if (changed == false)
                {
                    CRange range(v1[i].getM_start(), v2[pos].getM_start() - 1);
                    tmp.push_back(range);
                }
                
                else
                {
                    tmp.back().setM_start(v1[i].getM_start());
                    tmp.back().setM_end(v2[pos].getM_start()-1);
                }
                
                v1[i].setM_end(v2[pos].getM_start() - 1);
            }
        }
        
        else if (v1[i].getM_start() > v2[pos].getM_start())
        {
            if (v1[i].getM_start() > v2[pos].getM_end())
            {
                tmp.push_back(v1[i]);
                pos++;
            }
            
            
            else if (v1[i].getM_end() > v2[pos].getM_end())
            {
                
                CRange range((v2[pos].getM_end() + 1), v1[i].getM_end());
                tmp.push_back(range);
                v1[i].setM_start(v2[pos].getM_end() + 1);
                pos++;
            }
            
            else if (v1[i].getM_end() <= v2[i].getM_end())
            {
            }
        }
        
        else
        {
            if (v1[i].getM_end() == v2[pos].getM_end())
            {
                pos++;
            }
            
            else if (v1[i].getM_end() < v2[pos].getM_end())
            {
                
            }
            
            else
            {
                CRange range(v2[pos].getM_end()+ 1, v1[i].getM_end());
                tmp.push_back(range);
                v1[i].setM_start(v2[pos].getM_end() + 1);
                pos++;
            }
        }
        
        if (pos != 0 && pos < v2.size())
        {
            if (v1[i].getM_end() < v2[pos].getM_start() )
            {
                continue;
            }
            
            else{
                changed = true;
                i--;
            }
        }
    }
    
    return tmp;
}
//---------------------------------------------------------------------
class CRangeList
{
public:
    
    CRangeList() = default;
    CRangeList &operator+=(const CRange&);
    CRangeList &operator+=(const CRangeList&);
    CRangeList &operator-=(const CRange&);
    CRangeList &operator-=(const CRangeList&);
    CRangeList &operator=(const CRange&);
    
    bool Includes(const CRange&) const;
    bool Includes(long long num) const;
    
    bool operator==(const CRangeList&) const;
    bool operator!=(const CRangeList&) const;
    friend ostream &operator<<(ostream &os, const CRangeList&);
    CRangeList &operator+ (const CRangeList&);
    CRangeList &operator- (const CRangeList&);
    CRangeList &operator+ (const CRange&);
    CRangeList &operator- (const CRange&);
    
    
    vector<CRange> m_intervals {0};
    
    bool binarySearchIncld(const vector<CRange> &v, const CRange &crg) const;
    
    vector<CRange> mergeIntervals()
    {
        vector<CRange> result_set;
        if(m_intervals.empty())
        {
            return m_intervals;
        }
    
        result_set.push_back(m_intervals[0]);
        
        for (unsigned i = 1; i < m_intervals.size(); i++)
        {
            if (m_intervals[i].getM_start() == LLONG_MIN)
                result_set.back().setM_end(max(result_set.back().getM_end(), m_intervals[i].getM_end()));
            
            else if (result_set.back().getM_end() < m_intervals[i].getM_start() - 1)
                result_set.push_back(m_intervals[i]);
            else
                result_set.back().setM_end(max(result_set.back().getM_end(), m_intervals[i].getM_end()));
        }
        return result_set;
    }
    
};
//-------------------------CRange-----------------------------------------------------

CRangeList operator+ (const CRange &lhs, const CRange &rhs)
{
    CRangeList rangeList;
    
    if (lhs.getM_start() < rhs.getM_start())
    {
        rangeList.m_intervals.push_back(lhs);
        rangeList.m_intervals.push_back(rhs);
    } else {
        rangeList.m_intervals.push_back(rhs);
        rangeList.m_intervals.push_back(lhs);
    }
    
    rangeList.m_intervals = rangeList.mergeIntervals();
    
    return rangeList;
}


CRangeList operator-(const CRange &lhs, const CRange &rhs)
{
    
    CRangeList rangeList;
    CRangeList tmp;
    
    rangeList.m_intervals.push_back(lhs);
    tmp.m_intervals.push_back(rhs);
    
    rangeList.m_intervals = unMerge(rangeList.m_intervals,tmp.m_intervals);
    
    return rangeList;
}

//-----------------CRangeList------------------------


CRangeList &CRangeList::operator=(const CRange &rhs)
{

    m_intervals.clear();
    m_intervals.push_back(rhs);
    
    return *this;
}

CRangeList &CRangeList::operator+=(const CRange &rhs)
{
    auto it = lower_bound(m_intervals.begin(), m_intervals.end(),rhs, compareIntervals);
    m_intervals.insert(it, rhs);
    m_intervals = mergeIntervals();
    
    return *this;
}
CRangeList &CRangeList::operator-=(const CRange &rhs)
{
    vector<CRange> tmp;
    
    tmp.push_back(rhs);
    
    m_intervals = unMerge(m_intervals, tmp);
    
    return *this;
}


CRangeList &CRangeList::operator+ (const CRangeList &rhs)
{
    
    vector<CRange> tmp (m_intervals.size() + rhs.m_intervals.size());
    
    merge(m_intervals.begin(), m_intervals.end(), rhs.m_intervals.begin(), rhs.m_intervals.end(), tmp.begin(), compareIntervals);
    
    m_intervals.resize(tmp.size());
    m_intervals = tmp;
    
    m_intervals = mergeIntervals();
    
    return *this;
}

CRangeList &CRangeList::operator- (const CRangeList &rhs)
{
    m_intervals = unMerge(m_intervals, rhs.m_intervals);
    
    return *this;
}

CRangeList &CRangeList::operator+ (const CRange &rhs)
{
    auto it = lower_bound(m_intervals.begin(), m_intervals.end(),rhs, compareIntervals);
    m_intervals.insert(it, rhs);
    m_intervals = mergeIntervals();
    
    return *this;
}

CRangeList &CRangeList::operator- (const CRange &rhs)
{
    
    vector<CRange> tmp;
    tmp.push_back(rhs);
    m_intervals = unMerge(m_intervals, tmp);
    
    return *this;
}

CRangeList &CRangeList::operator+=(const CRangeList &rhs)
{
    vector<CRange> tmp (m_intervals.size() + rhs.m_intervals.size());
    
    merge(m_intervals.begin(), m_intervals.end(), rhs.m_intervals.begin(), rhs.m_intervals.end(), tmp.begin(), compareIntervals);
    
    m_intervals.resize(tmp.size());
    m_intervals = tmp;
    m_intervals = mergeIntervals();
    
    return *this;
}

CRangeList &CRangeList::operator-=(const CRangeList &rhs)
{
    
    m_intervals = unMerge(m_intervals, rhs.m_intervals);
    
    m_intervals = mergeIntervals();
    
    return *this;
}

bool CRangeList::operator==(const CRangeList &rhs) const
{
    if (m_intervals.size() != rhs.m_intervals.size())
        return false;
    
    else
    {
        for (unsigned i = 0; i < m_intervals.size(); i++)
        {
            if (m_intervals[i].getM_start() != rhs.m_intervals[i].getM_start() && m_intervals[i].getM_end() != rhs.m_intervals[i].getM_end())
                return false;
        }
        return true;
    }
}

bool CRangeList::operator!=(const CRangeList &rhs) const
{
    if (m_intervals.size() != rhs.m_intervals.size())
        return true;
    
    else
    {
        for (unsigned i = 0; i < m_intervals.size(); i++)
        {
            if (m_intervals[i].getM_start() != rhs.m_intervals[i].getM_start() && m_intervals[i].getM_end() != rhs.m_intervals[i].getM_end())
                return true;
        }
        return false;
    }
}

bool CRangeList::Includes(const CRange &crg) const
{
    return binarySearchIncld(m_intervals, crg);
}

bool CRangeList::Includes(long long num) const
{
    CRange crg(num,num);
    
    return binarySearchIncld(m_intervals, crg);
    
}
ostream &operator<<(ostream &os, const CRangeList &crg)
{
    os << "{";
    for (unsigned i = 0; i < crg.m_intervals.size(); i++)
    {
        if (crg.m_intervals[i].getM_start() == crg.m_intervals[i].getM_end())
            os << crg.m_intervals[i].getM_start();
        else
            os << "<" << crg.m_intervals[i].getM_start() << ".." << crg.m_intervals[i].getM_end() << ">";
        
        (i + 1) == crg.m_intervals.size() ? os << "" : os << ",";
    }
    os << "}";
    return os;
}

bool CRangeList::binarySearchIncld(const vector<CRange> &v, const CRange &crg) const
{
    long first = 0, last = v.size() - 1;
    
    while (first <= last)
    {
        long  middle = first + (last - first) / 2;
        
        
        if (v[middle].getM_start() <= crg.getM_start() && v[middle].getM_end() >= crg.getM_start())
        {
            if (v[middle].getM_end() >= crg.getM_end())
                return true;
            else
                return false;
            
        }
        else if (v[middle].getM_start() < crg.getM_start())
            first = middle + 1;
        
        else if (v[middle].getM_start() > crg.getM_start())
            last = middle - 1;
        
    }
    
    return false;
}

#ifndef __PROGTEST__
string toString (const CRangeList& x)
{
    ostringstream oss;
    oss << x;
    return oss . str ();
}

int main()
{
}

#endif /* __PROGTEST__ */
