#include <iostream>
#include <string.h>
#include "STRING.h"

using namespace std;

STRING::STRING()
{
	m_pBuffer = NULL;
	m_nLength = 0;
}

STRING::STRING(const char* s)
{
	int i;
	m_nLength = strlen(s);
	m_pBuffer = new char[m_nLength + 1];
	StrCpy(m_pBuffer, s);
}

STRING::STRING(char ch, int n)
{
	m_nLength = n;
	m_pBuffer = new char[m_nLength + 1];
	::memset(m_pBuffer, ch, m_nLength);
	m_pBuffer[m_nLength] = '\0';
}

STRING::~STRING()
{
	if (m_pBuffer)
	{
		m_pBuffer = NULL;
		delete m_pBuffer;
	}
}

void STRING::operator=(const STRING& s)
{
	if (&s == this) return;

	if (m_pBuffer)
	{
		delete m_pBuffer;
		m_pBuffer = NULL;
	}

	m_nLength = s.m_nLength;
	m_pBuffer = new char[m_nLength + 1];
	StrCpy(m_pBuffer, s.m_pBuffer);
}

void STRING::StrCpy(char* _Buffer1, const char* _Buffer2)
{
	int i;
	for (i = 0; _Buffer2[i] != '\0'; ++i)
		_Buffer1[i] = _Buffer2[i];
	_Buffer1[i] = '\0';
}

void STRING::SetChar(int _i, char _ch)
{
	if ((_i >= 0) && (_i <= m_nLength))
		m_pBuffer[_i] = _ch;
}

STRING* STRING::AddStr(STRING* _OtherStr)
{
	STRING* pPlusStr = new STRING;
	int i = m_nLength;
	pPlusStr->m_nLength = m_nLength + _OtherStr->GetLen();
	pPlusStr->m_pBuffer = new char[pPlusStr->GetLen() + 1];
	StrCpy(pPlusStr->m_pBuffer, m_pBuffer);
	for (int j = 0; _OtherStr->m_pBuffer[j] != '\0'; ++i, ++j)
		pPlusStr->SetChar(i, _OtherStr->GetChar(j));
	pPlusStr->SetChar(i, '\0');
	return pPlusStr;
}