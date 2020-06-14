#pragma once
#include <winsock2.h>
#include<iostream>
#include <fstream>
#include<string>
#include<vector>
#include<queue>
#include<map>

using namespace std;
#pragma comment(lib, "ws2_32.lib")

class urlDownload {
private:
	//socket
	WSADATA ws;
	SOCKET sock;

	//data
	queue<string>htmlurl;
	vector<string>comurl;
	vector<string>imageurl;
	map<string, int>urlmap;
	//addr
	string host;
	string filepath;
	//log
	ofstream wlog;
	//获取资源名称
	string getFileName(const string &filepath);
	void parse_url(const string &url);
	//获取html里的img url
	void getImageUrl(const string &allHtml);
	//获取com url
	void getComUrl(const string &allHtml);
	//log
	void log(const string &str);
	string iToa(int num);
	//http Get请求
	void request(const string &url);
	//接收请求网页得到的html文本
	void recvUrl();
public:
	urlDownload() {
		CreateDirectoryA("./img", 0);
		WSAStartup(MAKEWORD(2, 2), &ws);
	}
	~urlDownload() {
		WSACleanup();
	}
	//接收网页的图片
	void downLoadImage(const string &url);
	void run(const string &url);
};
