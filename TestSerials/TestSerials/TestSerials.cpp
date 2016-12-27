// TestSerials.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "Serialize.h"

int _tmain(int argc, _TCHAR* argv[])
{

	CSerial m_Serial;
	string str = "fsafasf";
	m_Serial << 1;
	m_Serial << 50;
	m_Serial << 'a';
	m_Serial << str;
	string test = m_Serial.buffer();

	CSerial m_Serial1(test);

	int _int;
	int _float;
	char  _char;
	string str1 = "";
	m_Serial1 >> _int >> _float >> _char >>str1;

	return 0; 
}

