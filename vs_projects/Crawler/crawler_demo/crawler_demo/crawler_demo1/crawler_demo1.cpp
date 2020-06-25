#include <iostream>
#include <string.h>
#include <windows.h>
#include <winhttp.h>
#pragma comment(lib, "winhttp.lib")
using namespace std;

//定义我们将要用的句柄
HINTERNET hSession = NULL;
HINTERNET hConnect = NULL;
HINTERNET hRequest = NULL;

int main() {
	//1.初始化一个WinHTTP-session句柄，参数1为此句柄的名称，此处我命名为WinHTTP
	hSession = WinHttpOpen(L"WinHTTP", WINHTTP_ACCESS_TYPE_DEFAULT_PROXY, WINHTTP_NO_PROXY_NAME, WINHTTP_NO_PROXY_BYPASS, 0);
	if (hSession == NULL) {
		cout << "Error:Open session failed: " << GetLastError() << endl;
		return -1;
	}

	//2.通过上述句柄连接到服务器，需要指定服务器IP和端口号。若连接成功，返回的hConnect句柄不为NULL
	LPCWSTR host = L"www.baidu.com";//此处我们以百度为例
	hConnect = WinHttpConnect(hSession, host, INTERNET_DEFAULT_HTTPS_PORT, 0);
	if (hConnect == NULL) {
		cout << "Error:Connect failed: " << GetLastError() << endl;
		return -1;
	}

	//3.通过hConnect句柄创建一个hRequest句柄，用于发送数据与读取从服务器返回的数据。
	hRequest = WinHttpOpenRequest(hConnect, L"GET", NULL, NULL, WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES, WINHTTP_FLAG_SECURE);
	//其中参数2表示请求方式，此处为GET；参数3:给定Post的具体地址，如填L"getServiceInfo"时具体地址为http://192.168.50.112/getServiceInfo
	if (hRequest == NULL) {
		cout << "Error:OpenRequest failed: " << GetLastError() << endl;
		return -1;
	}

	//4.1.向服务器发送post数据
	//(1)指定发送的数据内容
	string data = "This is my data to be sent";
	const void *ss = (const char *)data.c_str();

	//(2)发送请求
	BOOL bResults;
	bResults = WinHttpSendRequest(hRequest, WINHTTP_NO_ADDITIONAL_HEADERS, 0, const_cast<void*>(ss), data.length(), data.length(), 0);
	if (!bResults) {
		cout << "Error:SendRequest failed: " << GetLastError() << endl;
		return -1;
	}
	else {
		//（3）发送请求成功则准备接受服务器的response。注意：在使用 WinHttpQueryDataAvailable和WinHttpReadData前必须使用WinHttpReceiveResponse才能access服务器返回的数据
		bResults = WinHttpReceiveResponse(hRequest, NULL);
	}
	//4.2.获取服务器返回数据的header信息。这一步我用来获取返回数据的数据类型。
	LPVOID lpHeaderBuffer = NULL;
	DWORD dwSize = 0;
	if (bResults) {
		//(1) 获取header的长度
		WinHttpQueryHeaders(hRequest, WINHTTP_QUERY_RAW_HEADERS_CRLF, WINHTTP_HEADER_NAME_BY_INDEX, NULL, &dwSize, WINHTTP_NO_HEADER_INDEX);

		//(2) 根据header的长度为buffer申请内存空间
		if (GetLastError() == ERROR_INSUFFICIENT_BUFFER) {
			lpHeaderBuffer = new WCHAR[dwSize / sizeof(WCHAR)];

			//(3) 使用WinHttpQueryHeaders获取header信息
			bResults = WinHttpQueryHeaders(hRequest, WINHTTP_QUERY_RAW_HEADERS_CRLF, WINHTTP_HEADER_NAME_BY_INDEX, lpHeaderBuffer, &dwSize, WINHTTP_NO_HEADER_INDEX);
		}
	}
	printf("Header contents: \n%S", lpHeaderBuffer);

	/*解析上述header信息会发现服务器返回数据的charset为uft-8。这意味着后面需要对获取到的raw data进行宽字符转换。一开始由于没有进行转换所以得到的数据都是乱码。
	出现乱码的原因是：HTTP在传输过程中是二值的，它并没有text或者是unicode的概念。HTTP使用7bit的ASCII码作为HTTP headers，但是内容是任意的二值数据，需要根据header中指定的编码方式来描述它（通常是Content-Type header）。
	因此当你接收到原始的HTTP数据时，可以先将其保存到char[] buffer中，然后利用WinHttpQueryHearders()获取HTTP头，得到内容的Content-Type,这样你就知道数据到底是啥类型的了，是ASCII还是Unicode或者其他。
	一旦你知道了具体的编码方式，就可以通过MultiByteToWideChar()将其转换成合适编码的字符，存入wchar_t[]中。
	如下4.4所示。
	*/

	//4.3.获取服务器返回数据
	LPSTR pszOutBuffer = NULL;
	DWORD dwDownloaded = 0;//实际收取的字符数
	if (bResults) {
		do {
			//(1)获取返回数据的大小（以字节为单位）
			dwSize = 0;
			if (!WinHttpQueryDataAvailable(hRequest, &dwSize)) {
				cout << "Error：WinHttpQueryDataAvailable failed：" << GetLastError() << endl;
				break;
			}
			if (!dwSize)
				break;//数据大小为0时跳出循环

			//(2)根据返回数据的长度为buffer来申请内存空间
			pszOutBuffer = new char[dwSize + 1];
			if (!pszOutBuffer) {
				cout << "Out of memory." << endl;
				dwSize = 0;
				break;
			}
			else {
				//(3)通过WinHttpReadData读取服务器的返回数据
				ZeroMemory(pszOutBuffer, dwSize + 1);//将buffer置0
				if (!WinHttpReadData(hRequest, pszOutBuffer, dwSize, &dwDownloaded)) {
					cout << "Error：WinHttpQueryDataAvailable failed：" << GetLastError() << endl;
				}
				else
					cout << pszOutBuffer;

				//4.4. 将返回数据转换成UTF8
				wchar_t *pwText = NULL;
				DWORD dwNum = MultiByteToWideChar(CP_ACP, 0, pszOutBuffer, -1, NULL, 0);//返回原始ASCII码的字符数目
				pwText = new wchar_t[dwNum];//根据ASCII码的字符数来分配UTF8的空间
				MultiByteToWideChar(CP_UTF8, 0, pszOutBuffer, -1, pwText, dwNum);//将ASCII码转换成UTF8
				printf("Received contents: \n%S", pwText);

				delete[] pszOutBuffer;//用完回收是写C++的好习惯
			}
		} while (dwSize > 0);
	}

	//5.依次关闭request，connect，session句柄
	if (hRequest)
		WinHttpCloseHandle(hRequest);
	if (hConnect)
		WinHttpCloseHandle(hConnect);
	if (hSession)
		WinHttpCloseHandle(hSession);

	return 0;
}
