#ifndef __PROGTEST__
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cassert>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <memory>
#include <utility>
using namespace std;

class InvalidIndexException
{
};

#endif /* __PROGTEST__ */


class CString
{
public:
	shared_ptr<char> m_str;
	size_t m_strLength;
	size_t m_ofs;
	size_t m_len;
	
	
	~CString() {m_str.reset();}
	
	CString() :  m_str(nullptr), m_strLength(0), m_ofs(0), m_len(0) {}
	
	CString(size_t strLength, size_t ofs, size_t len, shared_ptr<char> &str): m_strLength(strLength) ,m_ofs(ofs), m_len(len) {m_str = str;}
	
	CString(size_t strLength, size_t ofs, size_t len, const char *str): m_strLength(strLength), m_ofs(ofs), m_len(len) {
		m_str = shared_ptr<char> (new char[strlen(str) + 1]);//, default_delete<char[]>());
		strcpy(m_str.get(), str);
	}
};

class CVector {
public:
	
	
	CVector() : m_capacity(50), m_size(0), m_stringLength(0) {
		m_data = new CString[m_capacity];
	}
	
	
	~CVector()
	{
		delete[] m_data;
		
	}
	CVector &operator=(const CVector &src)
	{
		if (this == &src)
			return *this;
		
		delete[] m_data;
		
		m_size = src.m_size;
		m_capacity = src.m_capacity;
		m_stringLength = src.m_stringLength;
		auto tmp = new CString[m_capacity];
		for (size_t i = 0; i < m_size; i++)
			tmp[i] = src[i];
		
		m_data = tmp;
		
		
		return *this;
		
	}
	
	size_t size() const { return m_size; }
	
	CString &operator[](size_t idx)
	{
		
		return m_data[idx];
	}
	
	CString &operator[](size_t idx) const
	{
		
		return m_data[idx];
	}
	
	
	void push(const CString &src)
	{
		if (m_capacity == m_size)
		{
			m_capacity*= 2;
			auto newdata = new CString[m_capacity];
			
			for (size_t i = 0; i < m_size; i++)
				newdata[i] = m_data[i];
			
			delete[] m_data;
			
			m_data = newdata;
			
		}
		
		m_data[m_size] = src;
		m_size+=1;
		m_stringLength+=src.m_len;
	}
	
	size_t getM_stringLength() const {
		return m_stringLength;
	}
	
	
private:
	
	CString *m_data;
	size_t m_capacity;
	size_t m_size;
	size_t m_stringLength;
};



class CPatchStr
{
public:
	CPatchStr ( void );
	CPatchStr ( const char * str );
	CPatchStr(const CPatchStr &src);
	CPatchStr &operator= (const CPatchStr &src);
	CPatchStr   SubStr    ( size_t            from,
						   size_t            len ) const;
	CPatchStr & Append    ( const CPatchStr & src );
	
	CPatchStr & Insert    ( size_t            pos,
						   const CPatchStr & src );
	CPatchStr & Delete    ( size_t            from,
						   size_t            len );
	char      * ToStr     ( void ) const;
	
private:
	CVector m_vector;
	
	size_t binarySearchPos(size_t pos) const {
		size_t first = 0, last = m_vector.size() - 1;
		size_t middle = 0;
		
		if (m_vector[first].m_strLength > pos) return 0;
		
		
		if (m_vector[last].m_strLength + m_vector[last].m_len - 1 < pos)
			return last;
		
		
		while (first <= last) {
			middle = first + (last - first) / 2;
			
			if (m_vector[middle].m_strLength > pos)
				last = middle - 1;
			
			else if (m_vector[middle].m_strLength + m_vector[middle].m_len - 1 < pos)
				first = middle + 1;
			
			else
				break;
			
		}
		
		return middle;
	}
};


CPatchStr::CPatchStr(void)
{
	
}

CPatchStr::CPatchStr(const char *str)
{
	m_vector.push(CString(0, 0, strlen(str), str));
}

CPatchStr::CPatchStr(const CPatchStr &src)
{
	size_t length = 0;
	
	for (size_t i = 0; i < src.m_vector.size(); i++) {
		m_vector.push(CString(length, src.m_vector[i].m_ofs, src.m_vector[i].m_len, src.m_vector[i].m_str));
		length+= src.m_vector[i].m_len;
	}
}

CPatchStr &CPatchStr::operator=(const CPatchStr &src)
{
	if (this == &src)
		return *this;
	
	CPatchStr str;
	unsigned long length = 0;
	
	
	for (size_t i = 0; i < src.m_vector.size(); i++) {
		str.m_vector.push(CString(length, src.m_vector[i].m_ofs, src.m_vector[i].m_len, src.m_vector[i].m_str));
		length+= src.m_vector[i].m_len;
	}
	m_vector = str.m_vector;
	return *this;
}

CPatchStr &CPatchStr::Append(const CPatchStr &src)
{
	auto index = src.m_vector.size();
	size_t length = m_vector.getM_stringLength();
	
	
	for(size_t i = 0; i < index; i++) {
		m_vector.push(CString(length, src.m_vector[i].m_ofs, src.m_vector[i].m_len, src.m_vector[i].m_str));
		length+=src.m_vector[i].m_len;
	}
	return *this;
}


CPatchStr &CPatchStr::Insert (size_t pos,const CPatchStr & src)
{
	if (pos > m_vector.getM_stringLength())
		throw InvalidIndexException();
	
	else if (pos == m_vector.getM_stringLength()) {
		
		Append(src);
		return *this;
	}
	
	CPatchStr toReturn;
	
	size_t frm = binarySearchPos(pos);
	size_t strLength = 0;
	
	size_t lengthEnd  = m_vector[frm].m_strLength;
	size_t lengthFrom = lengthEnd + m_vector[frm].m_len;
	
	
	
	for (size_t i = 0;  i < frm; i++) {
		toReturn.m_vector.push(CString(strLength,m_vector[i].m_ofs, m_vector[i].m_len, m_vector[i].m_str));
		strLength+=m_vector[i].m_len;
	}
	
	if (pos > lengthEnd) {
		CString tmp(strLength,m_vector[frm].m_ofs,pos - lengthEnd,m_vector[frm].m_str);
		toReturn.m_vector.push(tmp);
		strLength+= pos - lengthEnd;
	}
	
	for (size_t i = 0; i < src.m_vector.size(); i++) {
		toReturn.m_vector.push(CString(strLength, src.m_vector[i].m_ofs, src.m_vector[i].m_len, src.m_vector[i].m_str));
		strLength+=src.m_vector[i].m_len;
	}
	
	CString tmp(strLength,m_vector[frm].m_ofs + pos - lengthEnd,lengthFrom - pos,m_vector[frm].m_str);
	toReturn.m_vector.push(tmp);
	
	strLength+= lengthFrom - pos;
	
	frm++;
	
	for(; frm < m_vector.size(); frm++) {
		toReturn.m_vector.push(CString(strLength, m_vector[frm].m_ofs, m_vector[frm].m_len, m_vector[frm].m_str));
		strLength+=m_vector[frm].m_len;
	}
	
	*this = toReturn;
	
	return *this;
	
}

CPatchStr CPatchStr::SubStr(size_t from, size_t len) const
{
	if (from + len > m_vector.getM_stringLength())
		throw InvalidIndexException();
	
	CPatchStr toReturn;
	
	if (len == 0)
	{
		CString tmp;
		toReturn.m_vector.push(tmp);
		return toReturn;
	}
	
	
	auto end = from + len  - 1;
	
	size_t strLength = 0;
	size_t frm = binarySearchPos(from), ln = binarySearchPos(end);
	size_t idx = 0;
	size_t lengthFrom = m_vector[frm].m_strLength + m_vector[frm].m_len;
	
	
	
	if (frm > 0)
		idx = lengthFrom - m_vector[frm].m_len;
	
	if (frm + 1 == ln) {
		CString tmp(strLength,m_vector[frm].m_ofs + from - idx,lengthFrom - from,m_vector[frm].m_str);
		toReturn.m_vector.push(tmp);
		
		strLength+= lengthFrom - from;
		
		CString tmp2(strLength, m_vector[ln].m_ofs,end - lengthFrom + 1,m_vector[ln].m_str);
		toReturn.m_vector.push(tmp2);
		
	}
	
	else if (frm == ln) {
		CString tmp(strLength, m_vector[frm].m_ofs -idx + from,len,m_vector[frm].m_str);
		toReturn.m_vector.push(tmp);
	}
	else {
		CString tmp(strLength, m_vector[frm].m_ofs + from - idx,lengthFrom - from,m_vector[frm].m_str);
		toReturn.m_vector.push(tmp);
		
		strLength+= lengthFrom - from;
		
		frm++;
		
		for (; frm < ln; frm++) {
			toReturn.m_vector.push(CString(strLength, m_vector[frm].m_ofs, m_vector[frm].m_len, m_vector[frm].m_str));
			lengthFrom+=m_vector[frm].m_len;
			strLength+= m_vector[frm].m_len;
		}
		
		CString tmp2(strLength,m_vector[ln].m_ofs,end - lengthFrom + 1,m_vector[ln].m_str);
		toReturn.m_vector.push(tmp2);
		
	}
	
	return toReturn;
	
}

CPatchStr &CPatchStr::Delete ( size_t from,size_t len )
{
	if (from + len > m_vector.getM_stringLength())
		throw InvalidIndexException();
	
	
	else if (len == 0 )
		return *this;
	
	auto end = from + len  - 1;
	
	CPatchStr toReturn;
	
	size_t frm = binarySearchPos(from);
	size_t ln = binarySearchPos(end);
	size_t lengthFrom = m_vector[frm].m_strLength + m_vector[frm].m_len;
	size_t lengthEnd = m_vector[ln].m_strLength + m_vector[ln].m_len;
	size_t strLength = 0;
	
	
	for (size_t i = 0; i < frm; i++) {
		toReturn.m_vector.push(CString(strLength,m_vector[i].m_ofs, m_vector[i].m_len, m_vector[i].m_str));
		strLength+=m_vector[i].m_len;
	}
	
	if (from > lengthFrom - m_vector[frm].m_len)
	{
		CString tmp(strLength,m_vector[frm].m_ofs, from - (lengthFrom -  m_vector[frm].m_len), m_vector[frm].m_str);
		toReturn.m_vector.push(tmp);
		strLength += from - (lengthFrom - m_vector[frm].m_len);
	}
	
	if (end < lengthEnd - 1)
	{
		CString tmp(strLength,m_vector[ln].m_ofs + end - (lengthEnd - m_vector[ln].m_len)  + 1,lengthEnd - end - 1,m_vector[ln].m_str);
		toReturn.m_vector.push(tmp);
		strLength+= lengthEnd - end - 1;
	}
	
	
	ln++;
	
	for (; ln < m_vector.size(); ln++) {
		toReturn.m_vector.push(CString(strLength,m_vector[ln].m_ofs, m_vector[ln].m_len, m_vector[ln].m_str));
		strLength+=m_vector[ln].m_len;
	}
	
	
	*this = toReturn;
	
	return *this;
	
}


char* CPatchStr::ToStr(void) const
{
	char *tmp;
	
	if (m_vector.size()== 0)
	{
		tmp = new char[1];
		tmp[0] = '\0';
		return tmp;
	}
	else
	{
		tmp = new char [m_vector.getM_stringLength()+1];
		
		size_t index = 0;
		
		
		for (size_t i = 0; i < m_vector.size(); i++)
		{
			for (size_t j = m_vector[i].m_ofs; j < m_vector[i].m_len+m_vector[i].m_ofs; j++)
			{
				tmp[index++] = *(m_vector[i].m_str.get() + j);
			}
		}
		
		tmp[index] = '\0';
		
		return tmp;
	}
	
}

#ifndef __PROGTEST__
bool stringMatch ( char       * str,
				  const char * expected )
{
	bool res = strcmp ( str, expected ) == 0;
	delete [] str;
	return res;
}

int main ( void )
{
}
#endif /* __PROGTEST__ */
