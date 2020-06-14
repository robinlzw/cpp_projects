#include"urlDownload.h"
#include<conio.h>
#include<regex>


void urlDownload::log(const string & str){
	wlog.open("log.txt", ios::binary | ios::out | ios::app);
	wlog << (str + "\n").c_str();
	wlog.close();
}

string urlDownload::getFileName(const string & filepath){
	string name = "";
	int len = filepath.length();
	for (int i = len; i != 0; i--) {
		if (filepath[i] == '/') {
			name.assign(filepath, i + 1, len - 1);
			break;
		}
	}
	return name;
}

void urlDownload::parse_url(const string & url){
	auto hpos = url.find("http://");
	if (hpos == string::npos) {
		auto epos = url.find('/');
		host = url.substr(0, epos);
		filepath = "/";
	}
	else {
		hpos += strlen("http://");
		auto epos = url.find('/', hpos);
		if (epos == string::npos) {
			return;
		}
		host = url.substr(hpos, epos - hpos);
		filepath = url.substr(epos, url.length() - epos);
	}
}

void urlDownload::getImageUrl(const string & allHtml){
	smatch mat;
	regex pattern("src=\"(.+?\.(jpg|png))\"");
	string::const_iterator start = allHtml.begin();
	string::const_iterator end = allHtml.end();
	while (regex_search(start, end, mat, pattern))
	{
		string msg(mat[1].first, mat[1].second);
		imageurl.push_back(msg);
		start = mat[0].second;
	}
}

void urlDownload::getComUrl(const string & allHtml){
	smatch mat;
	regex pattern("href=\"(http://[^\s\"]+)\"");
	string::const_iterator start = allHtml.begin();
	string::const_iterator end = allHtml.end();
	while (regex_search(start, end, mat, pattern))
	{
		string msg(mat[1].first, mat[1].second);
		comurl.push_back(msg);
		start = mat[0].second;
	}
}

string urlDownload::iToa(int num){
	char *str = new char[10];
	string temp = "";
	itoa(num, str, 10);
	temp += str;
	delete[]str;
	return temp;
}

void urlDownload::request(const string & url){
	parse_url(url);

	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET) {
		cout << string("建立socket失败！ 错误码： " + iToa(WSAGetLastError()));
		return;
	}

	hostent *phost = gethostbyname(host.c_str());
	if (phost == NULL) {
		string temp("主机无法解析出ip! addr: " + host + filepath + "错误码： " + iToa(WSAGetLastError()));
		cout << temp;
		log(temp);
		return;
	}

	sockaddr_in server = { AF_INET };
	server.sin_port = htons(80);
	memcpy(&server.sin_addr, phost->h_addr, 4);
	if (connect(sock, (sockaddr*)&server, sizeof(server)) == SOCKET_ERROR)
	{
		cout << string("连接失败 addr: " + host + filepath + " 错误码:" + iToa(WSAGetLastError()));
		closesocket(sock);
		return;
	}
	string  reqInfo = "GET " + (string)filepath + " HTTP/1.1\r\nHost: " + (string)host + "\r\nConnection:Close\r\n\r\n";
	if (SOCKET_ERROR == send(sock, reqInfo.c_str(), reqInfo.size(), 0))
	{
		cout << string("send error! 错误码： " + iToa(WSAGetLastError()));
		closesocket(sock);
		return;
	}
}

void urlDownload::downLoadImage(const string & url){
	request(url);
	string name = getFileName(filepath);
	string savePath = "./img/" + name;
	ofstream out;
	out.open(savePath, ios::out | ios::binary);

	char buff[1024];
	string mes = "";
	memset(buff, 0, sizeof(buff));
	int len;
	len = recv(sock, buff, sizeof(buff) - 1, 0);
	mes += buff;
	char *cpos = strstr(buff, "\r\n\r\n");
	out.write(cpos + strlen("\r\n\r\n"), len - (cpos - buff) - strlen("\r\n\r\n"));

	while ((len = recv(sock, buff, sizeof(buff) - 1, 0)) > 0) {
		out.write(buff, len);
	}
	cout << "下载完成.\n" << "host: " << host << "  " << "path: " << filepath << endl;
	out.close();
	closesocket(sock);
}

void urlDownload::recvUrl(){
	static int htmlNum = 1;
	char fileName[100];
	sprintf(fileName, "data%d.txt", htmlNum);
	htmlNum++;
	char buff[1024];
	string msg = "";
	memset(buff, 0, sizeof(buff));
	int len;
	ofstream out(fileName, ios::out | ios::binary);
	while ((len = recv(sock, buff, sizeof(buff) - 1, 0)) > 0) {
		msg += buff;
		out.write(buff, len);
	}
	out.close();
	getImageUrl(msg);
	getComUrl(msg);
	closesocket(sock);
}

void urlDownload::run(const string &url){
	htmlurl.push(url);
	while (!htmlurl.empty()) {
		auto tempurl = htmlurl.front();
		htmlurl.pop();
		urlmap[tempurl]++;
		request(tempurl);
		recvUrl();
		for (auto i : imageurl) {
			downLoadImage(i);
		}
		imageurl.clear();
		for (auto i : comurl) {
			if (urlmap[i] == 0) {
				htmlurl.push(i);
			}
		}
		comurl.clear();
	}
}
