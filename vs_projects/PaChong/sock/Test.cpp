#include <winsock2.h>
#include<iostream>
#include"urlDownload.h"


int main() {

	urlDownload t;
	t.run("http://news.qq.com/");
	
	system("pause");
	return 0;
}