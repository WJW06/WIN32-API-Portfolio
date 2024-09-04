#pragma once
class STRING
{
public:
	STRING();
	STRING(const char* s);
	STRING(char ch, int n);
	~STRING();
private:
	char* m_pBuffer;
	int m_nLength;
public:
	void operator=(const STRING& s);

	void	StrCpy(char* _Buffer1, const char* _Buffer2);
	char* GetBuffer() { return m_pBuffer; }
	int		GetLen(void) { return m_nLength; }
	char	GetChar(int _i) { return m_pBuffer[_i]; }
	void	AddLen(int _Len) { m_nLength += _Len; }
	void	SetBuffer(char* _Buffer) { m_pBuffer = _Buffer; }
	void	SetLength(int _Length) { m_nLength = _Length; }
	void	SetChar(int _i, char _ch);
	STRING* AddStr(STRING* _OtherStr);
};