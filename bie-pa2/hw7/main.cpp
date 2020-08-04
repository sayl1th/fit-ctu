#ifndef __PROGTEST__
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <deque>
#include <map>
#include <set>
#include <list>
#include <algorithm>

#if defined ( __cplusplus ) && __cplusplus > 199711L /* C++ 11 */
#include <unordered_map>
#include <unordered_set>
#include <memory>
#include <functional>
#endif /* C++ 11 */

using namespace std;
#endif /* __PROGTEST__ */

class NoRouteException
{
};

using filter = function<bool (*)(int)>;


template <typename _T, typename _E>
class CRoute
{
public:
    CRoute() = default;// default constructor
    ~CRoute() = default;// destructor
    CRoute& Add(const _T &from, const _T &to, const _E &desc) // Add
    {
        adjList[from].push_back({to, desc});
        
        adjList[to].push_back({from, desc});
        return *this;
    }
    

    template<typename function = filter>
    
    list<_T> Find(const _T &start, const _T &end, function func )
    {
        list<_T> toReturn;

        
        if (start == end) {
            toReturn.push_back(start);
            return toReturn;
        }
        
        list<_T> queue;
        set<_T> visited;
        _T node = start;
        map<_T, pair<_T, unsigned int>> parent;
        
        visited.insert(node);
        queue.push_back(node);
        
        while (!queue.empty()) {
            node = queue.front();
            
            
            queue.pop_front();

            
            auto it = adjList.find(node);
            
            if (it != adjList.end()) {
                
                for (auto &i : it->second ) {
                    _T place = i.first;
                    
                    if (!func(i.second))
                        continue;
                    
                    if (visited.find(place) == visited.end()) {
                        visited.insert(place);
                        queue.push_back(place);
                        parent.insert(make_pair (place, make_pair(node, 1)));
                    }
                    
                    if (i.first == end) {
                        _T tmp = i.first;
                        toReturn.push_front(i.first);
                        auto it = parent.find(tmp);
                        while (it->second.second != 0) {
                            toReturn.push_front(it->second.first);
                            tmp = it->second.first;
                            it = parent.find(tmp);
                            
                            if (it == parent.end())
                                break;
                            
                        }
                        if (toReturn.size() == 0)
                            throw NoRouteException();
                        return toReturn;
                    }
                }
            }
        }
        
        if (toReturn.size() == 0)
            throw NoRouteException();
        return toReturn;
    }
    
    list<_T> Find(const _T &start, const _T &end)
    {
        list<_T> toReturn;


        if (start == end) {
            toReturn.push_back(start);
            return toReturn;
        }

        list<_T> queue;
        set<_T> visited;
        _T node = start;
        map<_T, pair<_T, int>> parent;

        visited.insert(node);
        queue.push_back(node);

        while (!queue.empty()) {
            node = queue.front();


            queue.pop_front();

            auto it = adjList.find(node);

            if (it != adjList.end()) {

                for (auto &i : it->second ) {
                    _T place = i.first;

                    if (visited.find(place) == visited.end()) {
                        visited.insert(place);
                        queue.push_back(place);
                        parent.insert(make_pair (place, make_pair(node, 1)));
                    }

                    if (i.first == end) {
                        _T tmp = i.first;
                        toReturn.push_front(i.first);
                        auto it = parent.find(tmp);
                        while (it->second.second != 0) {
                            toReturn.push_front(it->second.first);
                            tmp = it->second.first;
                            it = parent.find(tmp);

                            if (it == parent.end())
                                break;

                        }
                        if (toReturn.size() == 0)
                            throw NoRouteException();
                        return toReturn;
                    }
                }
            }
        }

        if (toReturn.size() == 0)
            throw NoRouteException();

        return toReturn;
    }
    

private:
    
    map<_T, vector<pair<_T, _E>>> adjList;
};

#ifndef __PROGTEST__
//=================================================================================================
class CTrain
{
public:
    CTrain                        ( const string    & company,
                                   int               speed )
    : m_Company ( company ),
    m_Speed ( speed )
    {
    }
    //---------------------------------------------------------------------------------------------
    string                   m_Company;
    int                      m_Speed;
    
};
//=================================================================================================
class TrainFilterCompany
{
public:
    TrainFilterCompany            ( const set<string> & companies )
    : m_Companies ( companies )
    {
    }
    //---------------------------------------------------------------------------------------------
    bool                     operator ()                   ( const CTrain & train ) const
    {
        return m_Companies . find ( train . m_Company ) != m_Companies . end ();
    }
    //---------------------------------------------------------------------------------------------
private:
    set <string>             m_Companies;
};
//=================================================================================================
class TrainFilterSpeed
{
public:
    TrainFilterSpeed              ( int               min,
                                   int               max )
    : m_Min ( min ),
    m_Max ( max )
    {
    }
    //---------------------------------------------------------------------------------------------
    bool                     operator ()                   ( const CTrain    & train ) const
    {
        return train . m_Speed >= m_Min && train . m_Speed <= m_Max;
    }
    //---------------------------------------------------------------------------------------------
private:
    int                      m_Min;
    int                      m_Max;
};
//=================================================================================================
bool               NurSchnellzug                           ( const CTrain    & zug )
{
    return ( zug . m_Company == "OBB" || zug . m_Company == "DB" ) && zug . m_Speed > 100;
}
//=================================================================================================
static string      toText                                  ( const list<string> & l )
{
    ostringstream oss;
    
    auto it = l . cbegin();
    oss << *it;
    for ( ++it; it != l . cend (); ++it )
        oss << " > " << *it;
    return oss . str ();
}
//=================================================================================================
int main ( void )
{

}
#endif  /* __PROGTEST__ */
