#pragma once

#include "utility.h"
#include "md5.h"
#include "PracticalSocket.h"

#include <sstream>
#include <iostream>
#include <string>
#include <time.h>
#include <WinSock2.h>
#include <iphlpapi.h>
#include <algorithm>
#include <thrift/transport/TSocket.h>
#pragma comment(lib, "IPHLPAPI.lib")

using namespace std;

std::string gen_uuid()
{
	static uint32_t s_count = 0;

	time_t rawtime;
	struct tm * timeinfo;
	char buffer[80] = { 0 };

	time(&rawtime);
	timeinfo = localtime(&rawtime);

	strftime(buffer, 80, "%Y%m%d%H%M%S", timeinfo);

	ostringstream oss;
	oss << std::string(buffer) << ::GetTickCount() << ++s_count << &rawtime;

	MD5 hash(oss.str());
	return hash.toStr();
}

const std::string currentDateTime() {
	time_t     now = time(0);
	struct tm  tstruct;
	char       buf[80];
	tstruct = *localtime(&now);
	// Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
	// for more information about date/time format
	strftime(buf, sizeof(buf), "%Y-%m-%d %X", &tstruct);

	return buf;
}


void getWin32MacAddresses(std::vector<std::string> &vMacAddresses)
{
	vMacAddresses.clear();
	IP_ADAPTER_INFO AdapterInfo[32];       // Allocate information for up to 32 NICs
	DWORD dwBufLen = sizeof(AdapterInfo);  // Save memory size of buffer
	DWORD dwStatus = GetAdaptersInfo(      // Call GetAdapterInfo
		AdapterInfo,                 // [out] buffer to receive data
		&dwBufLen);                  // [in] size of receive data buffer

									 //No network card? Other error?
	if (dwStatus != ERROR_SUCCESS)
		return;

	PIP_ADAPTER_INFO pAdapterInfo = AdapterInfo;
	char szBuffer[512] = {0};
	while (pAdapterInfo)
	{
		if (pAdapterInfo->Type == MIB_IF_TYPE_ETHERNET)
		{
			sprintf_s(szBuffer, sizeof(szBuffer), "%.2x-%.2x-%.2x-%.2x-%.2x-%.2x"
				, pAdapterInfo->Address[0]
				, pAdapterInfo->Address[1]
				, pAdapterInfo->Address[2]
				, pAdapterInfo->Address[3]
				, pAdapterInfo->Address[4]
				, pAdapterInfo->Address[5]
			);
			vMacAddresses.push_back(szBuffer);
		}
		pAdapterInfo = pAdapterInfo->Next;

	}

	std::sort(vMacAddresses.begin(), vMacAddresses.end());
}

boost::tuple<std::string, uint16_t> DetectBestServer(const std::vector<boost::tuple<std::string, uint16_t>> &server_vec)
{
	cout << "detect server" << endl;

	std::string host;
	uint16_t port = 0;

	long long min = 100000;

	for (int i = 0; i < server_vec.size(); ++i) {
		long long microseconds;
		auto start = std::chrono::steady_clock::now();
		try {
			/*
			apache::thrift::transport::TSocket s(server_vec[i].get<0>(), server_vec[i].get<1>());
			s.setConnTimeout(3000);
			s.open();
			*/

			TCPSocket socket(server_vec[i].get<0>(), server_vec[i].get<1>());

			auto elapsed = std::chrono::steady_clock::now() - start;
			microseconds = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count();
			
		}
		catch (...) {
			microseconds = 10000;
		}

		if (microseconds < min || host.size() == 0) {
			min = microseconds;
			host = server_vec[i].get<0>();
			port = server_vec[i].get<1>();
		}
	}

	cout << "detect server end" << endl;

	return boost::make_tuple(host, port);
}