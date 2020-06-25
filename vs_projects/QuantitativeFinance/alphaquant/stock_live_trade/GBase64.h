// GBase64.h: interface for the Base64 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GBASE64_H__FB063327_573C_4D70_A0B4_ECC067B6F4FD__INCLUDED_)
#define AFX_GBASE64_H__FB063327_573C_4D70_A0B4_ECC067B6F4FD__INCLUDED_

#include <string>

class Base64
{
public:
	static std::string Encode(const char* pData, int nLen);
    static std::string Encode(const std::string& xstrSrc);
    static std::string Decode(const std::string& xstrSrc);
	static std::string Decode(const char* cpszSrc);
};


#endif // !defined(AFX_GBASE64_H__FB063327_573C_4D70_A0B4_ECC067B6F4FD__INCLUDED_)
