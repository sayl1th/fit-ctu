#ifndef __PROGTEST__
#include <cassert>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include <map>

#include <set>
#include <list>
#include <algorithm>
#include <memory>
#include <functional>

using namespace std;


class CTimeStamp {
public:
    
    CTimeStamp(int year, int month, int day, int hour, int minute, double sec) : m_year(year), m_month(month), m_day(day), m_hour(hour), m_minute(minute),m_sec(sec) {}
    
    int Compare(const CTimeStamp &x) const
    {
        if (m_year > x.m_year)
            return 1;
        
        else if (m_year == x.m_year) {
            
            if (m_month > x.m_month)
                return 1;
            
            else if (m_month == x.m_month) {
                
                if (m_day > x.m_day)
                    return 1;
                
                else if (m_day == x.m_day) {
                    
                    if (m_hour > x.m_hour)
                        return 1;
                    
                    else if (m_hour == x.m_hour) {
                        
                        if (m_minute > x.m_minute)
                            return 1;
                        
                        else if (m_minute == x.m_minute) {
                            
                            if (m_sec > x.m_sec)
                                return 1;
                            
                            else if (m_sec == x.m_sec)
                                return 0;
                            
                            else return -1;
                        } else return -1;
                    } else return -1;
                } else return -1;
            } else return -1;
        } else return -1;
    }
    
    friend ostream &operator<<(ostream &os, const CTimeStamp &x);
    
private:
    int m_year;
    int m_month;
    int m_day;
    int m_hour;
    int m_minute;
    double m_sec;
    
};

ostream &operator<<(ostream &os, const CTimeStamp &x)
{
    os << x.m_year << "-" << setfill('0') << setw(2) << x.m_month << "-" << x.m_day << " " << x.m_hour << ":" << setfill('0') << setw(2) <<x.m_minute << ":" << setprecision(3) <<fixed << x.m_sec;
    
    return os;
}

class CMail {
public:
   
    CMail(const CTimeStamp &timeStamp,
          const string &from,
          const string &to,
          const string &subject) : m_timeStamp(timeStamp), m_from(from), m_to(to), m_subject(subject) {}
    
    int CompareByTime(const CTimeStamp &x) const
    {
        return m_timeStamp.Compare(x);
    }
    
    int CompareByTime(const CMail &x) const
    {
        return m_timeStamp.Compare(x.m_timeStamp);
    }
    
    const string &From(void) const { return m_from;}
    
    const string &To(void) const { return m_to; }
    
    const string &Subject(void) const {return m_subject;}

    const CTimeStamp &TimeStamp(void) const { return m_timeStamp;}
    
    friend ostream &operator<<(ostream &os,
                               const CMail &x);
    
private:
    CTimeStamp m_timeStamp;
    string m_from;
    string m_to;
    string m_subject;
};

ostream &operator<<(ostream &os, const CMail &x)
{
    os << x.m_timeStamp << " " << x.m_from << " -> " << x.m_to << ", subject: " << x.m_subject;
    return os;
}


// your code will be compiled in a separate namespace
namespace MysteriousNamespace {
#endif /* __PROGTEST__ */
    
    //----------------------------------------------------------------------------------------
    class CMailLog {
    public:
        
        CMailLog() = default;
        int ParseLog(istream &in);
        
        list<CMail> ListMail(const CTimeStamp &from,
                             const CTimeStamp &to) const;
        
        set<string> ActiveUsers(const CTimeStamp &from,
                                const CTimeStamp &to) const;
        
    private:

        
        int convert(const string &month) const
        {
            if (month == "Jan")
                return 1;
            else if (month == "Feb")
                return 2;
            else if (month == "Mar")
                return 3;
            else if (month == "Apr")
                return 4;
            else if (month == "May")
                return 5;
            else if (month == "Jun")
                return 6;
            else if (month == "Jul")
                return 7;
            else if (month == "Aug")
                return 8;
            else if (month == "Sep")
                return 9;
            else if (month == "Oct")
                return 10;
            else if (month == "Nov")
                return 11;
            else if (month == "Dec")
                return 12;
            else
                return -1;
        }
    
        struct CustomComp {
            bool operator()(const CTimeStamp &lhs,const CTimeStamp &rhs) const{
                if (lhs.Compare(rhs) == - 1)
                    return true;
                else
                    return false;
                    
            }
        };
        
        static bool customComp(const CTimeStamp &lhs,const CTimeStamp &rhs)  {
            if (lhs.Compare(rhs) == -1)
                return true;
            else
                return false;
        }

        
        typedef multimap<string, CMail> id_map;
        typedef multimap<CTimeStamp, CMail, CustomComp> time_map;
        
        id_map idMap;
        time_map timeMap;
        
    };
    
    int CMailLog::ParseLog(istream &in)
    {
        string line, data;
        int logs = 0;
        
        
        while (getline(in,line))
        {
            string to, from, subject, id;
            int day, month, year, hour, minute;
            double sec;


            istringstream record(line);
            record >> data;
            month = convert(data);

            record >> data;
            day = stoi(data);

            record >> data;
            year = stoi(data);

            record >> data;

            istringstream tmp2(data);
            string tmp;

            getline(tmp2, tmp, ':');
            hour = stoi(tmp);

            getline(tmp2, tmp, ':');
            minute = stoi(tmp);

            getline(tmp2, tmp, ':');
            sec = stod(tmp);

            record >> data;
            record >> data;

            tmp2.clear();
            tmp2.str(data);
            getline(tmp2, tmp, ':');
            id = tmp;

            record >> data;

            tmp2.clear();
            tmp2.str(data);
            getline(tmp2, tmp, '=');
            
            
            if(tmp2.good())
            {
            
                if (tmp == "from") {
                    getline(tmp2, tmp);
                    from = tmp;
                    
                    while (record >> data)
                    {
                        from+= data;
                    }
                    
                    CTimeStamp timestamp(year,month,day, hour,minute,sec);
                    CMail mail(timestamp, from, to, subject);
                    
                    idMap.insert(make_pair(id, mail));
                } else if (tmp == "to") {
                    getline(tmp2, tmp);
                    to = tmp;
                    
                    while (record >> data)
                    {
                       to+= data;
                    }
                    
                    id_map::iterator it = idMap.find(id);
                    
                    from = it->second.From();
                    subject = it->second.Subject();
                    
                    if (it->second.To() == "")
                    {
                        idMap.erase(it);
                    }
                    CTimeStamp timestamp(year,month,day, hour,minute,sec);
                    CMail mail(timestamp, from, to, subject);
                    idMap.insert(make_pair(id, mail));
                    timeMap.insert(make_pair(timestamp, mail));
                    logs++;

                } else if (tmp == "subject") {
                    
                    getline(tmp2, tmp);
                    subject = tmp;
                    
                    while (record >> data)
                    {
                        subject+= " " + data;
                    }
                    
                    
                    id_map::iterator it = idMap.find(id);
                    
                    from = it->second.From();
                    idMap.erase(it);
                    CTimeStamp timestamp(year,month,day, hour,minute,sec);
                    CMail mail(timestamp, from, to, subject);
                    idMap.insert(make_pair(id, mail));
                }
            } else
                continue;
            
            tmp2.clear();
            record.clear();
        }

        return logs;
    }
    
    list<CMail> CMailLog::ListMail(const CTimeStamp &from,const CTimeStamp &to) const
    {
        list<CMail> tmp;
        auto lo = timeMap.lower_bound(from);
        auto hi = timeMap.upper_bound(to);

        
        
        for(; (lo != hi) ; lo++)
        {
            tmp.push_back(lo->second);
        }
        
        return tmp;
    }
    
    set<string> CMailLog::ActiveUsers(const CTimeStamp &from, const CTimeStamp &to) const
    {
        set<string> tmp;
        
        auto lo = timeMap.lower_bound(from);
        auto hi = timeMap.upper_bound(to);
        
        for(; lo != hi; lo++) {
            tmp.insert(lo->second.From());
            tmp.insert(lo->second.To());
        }

        return tmp;
    }
    
    
    //----------------------------------------------------------------------------------------
#ifndef __PROGTEST__
} // namespace
string printMail(const list<CMail> &all) {
    ostringstream oss;
    for (const auto &mail : all)
        oss << mail << endl;
    return oss.str();
}

string printUsers(const set<string> &all) {
    ostringstream oss;
    bool first = true;
    for (const auto &name : all) {
        if (!first)
            oss << ", ";
        else
            first = false;
        oss << name;
    }
    return oss.str();
}


int main(void) {
    
}

#endif /* __PROGTEST__ */
