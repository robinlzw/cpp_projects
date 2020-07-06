#pragma once
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <vector>
#include <windows.h>
#include <atlstr.h>
#include <iostream>
#include <list>
#include <thread>

#include <gumbo.h>
#define CURL_STATICLIB
#include <curl/curl.h>


#pragma comment(lib,"ws2_32.lib")
#pragma comment(lib,"wldap32.lib")

//
//#ifdef _DEBUG
//#pragma comment(lib,"..\\lib\\win32_debug\\libcurld.lib")
//#pragma comment(lib,"..\\lib\\win32_debug\\libcrypto.lib")
//#pragma comment(lib,"..\\lib\\win32_debug\\libssl.lib")
//#pragma comment(lib,"..\\lib\\win32_debug\\gumbo.lib")
//#else
//#pragma comment(lib,"..\\lib\\win32_release\\libcurl.lib")
//#pragma comment(lib,"..\\lib\\win32_release\\libcrypto.lib")
//#pragma comment(lib,"..\\lib\\win32_release\\libssl.lib")
//#pragma comment(lib,"..\\lib\\win32_release\\gumbo.lib")
//#endif

void test1_crawler();