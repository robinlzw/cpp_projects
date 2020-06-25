#pragma once

#include <string>
#include <time.h>
#include <vector>
#include <boost/tuple/tuple.hpp>

std::string gen_uuid();

const std::string currentDateTime();

void getWin32MacAddresses(std::vector<std::string> &vMacAddresses);

template<class STR, class OI>
void SplitString(const STR &strSrc, OI oi, const STR &strDelimiter) {
	int nLastPos = 0;

	while (nLastPos <= strSrc.size()) {
		int nPos;
		if ((nPos = strSrc.find(strDelimiter, nLastPos)) == STR::npos) {//not found
			*oi++ = strSrc.substr(nLastPos, STR::npos);
			return;
		}
		else {//found
			*oi++ = strSrc.substr(nLastPos, nPos - nLastPos);
			nLastPos = nPos + strDelimiter.size();
		}
	}
}

template<class OI>
void SplitString(const std::string &strSrc, OI oi) {
	std::string white_space_str = " \t\n\r\f";

	std::string::size_type nLastPos = 0;

	while (nLastPos <= strSrc.size()) {
		std::string::size_type nPos;
		if ((nLastPos = strSrc.find_first_not_of(white_space_str, nLastPos)) == std::string::npos)
			return;

		if ((nPos = strSrc.find_first_of(white_space_str, nLastPos)) == std::string::npos) {
			*oi++ = strSrc.substr(nLastPos);
			return;
		}
		else {
			*oi++ = strSrc.substr(nLastPos, nPos - nLastPos);
			nLastPos = nPos;
		}
	}
}

boost::tuple<std::string, uint16_t> DetectBestServer(const std::vector<boost::tuple<std::string, uint16_t>> &server_vec);