#include "../header/crawler_test2.h"


using namespace std;

#define  URL_REFERER "https://acm.sjtu.edu.cn/OnlineJudge/"

void printFunc(string page)
{
	CDocument doc;
	doc.parse(page.c_str());

	CSelection c = doc.find("#status tr");
	for (int i = 0; i < c.nodeNum(); i++)
	{
		for (int j = 0; j < c.nodeAt(i).childNum(); j++)
		{
			CNode nd = c.nodeAt(i).childAt(j);
			string text = nd.text();
			cout << MyStringFormat::UTF_82ASCII(text) << "  ";
		}
		cout << endl;
	}
}

static size_t OnWriteData(void* buffer, size_t size, size_t nmemb, void* lpVoid)
{
	string* str = dynamic_cast<string*>((string *)lpVoid);
	if (NULL == str || NULL == buffer)
	{
		return -1;
	}

	char* pData = (char*)buffer;
	str->append(pData, size * nmemb);

	return nmemb;
}


bool HttpRequest(const char* url,
	string& strResponse,
	bool get/* = true*/,
	const char* headers/* = NULL*/,
	const char* postdata/* = NULL*/,
	bool bReserveHeaders/* = false*/,
	int timeout/* = 10*/)
{
	CURLcode res;
	CURL* curl = curl_easy_init();
	if (NULL == curl)
	{
		return false;
	}

	curl_easy_setopt(curl, CURLOPT_URL, url);

	//响应结果中保留头部信息
	if (bReserveHeaders)
		curl_easy_setopt(curl, CURLOPT_HEADER, 1);
	curl_easy_setopt(curl, CURLOPT_COOKIEFILE, "");
	curl_easy_setopt(curl, CURLOPT_READFUNCTION, NULL);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, OnWriteData);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&strResponse);
	curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1);
	//设定为不验证证书和HOST
	//curl_easy_setopt(curl, CURLOPT_PROXY, "127.0.0.1:8888");//设置代理
	//curl_easy_setopt(curl, CURLOPT_PROXYPORT, 9999); //代理服务器端口
	curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false);
	curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, false);

	//设置超时时间
	curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, timeout);
	curl_easy_setopt(curl, CURLOPT_TIMEOUT, timeout);
	curl_easy_setopt(curl, CURLOPT_REFERER, URL_REFERER);

	curl_easy_setopt(curl, CURLOPT_USERAGENT, "Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/71.0.3578.98 Safari/537.36");
	//不设置接收的编码格式或者设置为空，libcurl会自动解压压缩的格式，如gzip
	//curl_easy_setopt(curl, CURLOPT_ACCEPT_ENCODING, "gzip, deflate, br");
	//设置hostConnection: Keep-Alive
	struct curl_slist *chunk = NULL;
	chunk = curl_slist_append(chunk, "Host: acm.sjtu.edu.cn");
	chunk = curl_slist_append(chunk, "Connection: Keep-Alive");
	curl_easy_setopt(curl, CURLOPT_HTTPHEADER, chunk);

	//添加自定义头信息
	if (headers != NULL)
	{
		chunk = curl_slist_append(chunk, headers);
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, chunk);
	}

	if (!get && postdata != NULL)
	{
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postdata);
	}

	res = curl_easy_perform(curl);
	bool bError = false;
	if (res == CURLE_OK)
	{
		int code;
		res = curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &code);
		if (code != 200 && code != 302)
		{
			bError = true;
		}
	}
	else
	{
		bError = true;
	}

	curl_easy_cleanup(curl);

	return !bError;
}


void test2_crawler()
{
	string response;
	HttpRequest("https://acm.sjtu.edu.cn/OnlineJudge/status", response, true, NULL, NULL, false, 10);
	printFunc(response);
}
