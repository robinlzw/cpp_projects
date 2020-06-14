// GBase64.cpp: implementation of the Base64 class.
//
//////////////////////////////////////////////////////////////////////

#include "GBase64.h"

static const char  charPad = '=';           
static const std::string   charTable =  "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
										"abcdefghijklmnopqrstuvwxyz"
										"0123456789+/";

std::string Base64::Encode(const char* pData, int nLen)
{
	std::string strSrc(pData, pData+nLen);

	return Encode(strSrc);
}

std::string Base64::Encode(const std::string& xstrSrc)
{
    std::string::size_type  i;
    char c;
    std::string::size_type  len = xstrSrc.length();
    std::string             strRet;
	
    for (i = 0; i < len; ++i) {
        c = (xstrSrc[i] >> 2) & 0x3f;
        strRet.append(1, charTable[c]);
        c = (xstrSrc[i] << 4) & 0x3f;
        if (++i < len)
            c |= (xstrSrc[i] >> 4) & 0x0f;

        strRet.append(1, charTable[c]);
        if (i < len) {
            c = (xstrSrc[i] << 2) & 0x3f;
            if (++i < len)
                c |= (xstrSrc[i] >> 6) & 0x03;

            strRet.append(1, charTable[c]);
        }
        else {
            ++i;
            strRet.append(1, charPad);
        }

        if (i < len) {
            c = xstrSrc[i] & 0x3f;
            strRet.append(1, charTable[c]);
        }
        else {
            strRet.append(1, charPad);
        }
    }

    return strRet;
}

std::string Base64::Decode(const std::string& xstrSrc)
{
    std::string::size_type  i;
    char               c;
    char               c1;
	std::string::size_type  len = xstrSrc.length();
	std::string        strRet;

    for (i = 0; i < len; ++i) {
        c = (char) charTable.find(xstrSrc[i]);
        ++i;
        c1 = (char) charTable.find(xstrSrc[i]);
        c = (c << 2) | ((c1 >> 4) & 0x3);
        strRet.append(1, c);
        if (++i < len) {
            c = xstrSrc[i];
            if (charPad == c)
                break;

            c = (char) charTable.find(c);
            c1 = ((c1 << 4) & 0xf0) | ((c >> 2) & 0xf);
            strRet.append(1, c1);
        }

        if (++i < len) {
            c1 = xstrSrc[i];
            if (charPad == c1)
                break;

            c1 = (char) charTable.find(c1);
            c = ((c << 6) & 0xc0) | c1;
            strRet.append(1, c);
        }
    }

    return strRet;
}

std::string Base64::Decode(const char* cpszSrc)
{
	return Decode(std::string(cpszSrc));
}