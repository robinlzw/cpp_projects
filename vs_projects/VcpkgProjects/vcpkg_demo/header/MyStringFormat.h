#pragma once
#include <string>
#include <vector>
#include <windows.h>
using std::vector;
using std::string;
using std::wstring;
class MyStringFormat
{
public:
	MyStringFormat(void);
	~MyStringFormat(void);
public:
	//ascii ת Unicode 
	static wstring Acsi2WideByte(string& strascii);
	//Unicode ת utf8
	static string Unicode2Utf8(const wstring& widestring);
	//ascii תUtf8 
	static string ASCII2UTF_8(string& strAsciiCode);

	//UTF-8 ת Unicode 
	static wstring Utf82Unicode(const string& utf8string);
	//unicode ת ascii 
	static string WideByte2Acsi(wstring wstrcode);
	//utf-8 ת ascii 
	static string UTF_82ASCII(string& strUtf8Code);
};
