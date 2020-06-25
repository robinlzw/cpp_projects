#include <stdio.h>
#include <tchar.h>
#include <windows.h>
#include<urlmon.h>
#pragma comment(lib, "urlmon.lib")

int main() {
	TCHAR url[] = TEXT("https://img.paulzzh.tech/touhou/random?site=all&size=all");//一个很正常向的东方project图片API
	TCHAR filePath[] = _T("祖传色图.jpg");
	HRESULT res = URLDownloadToFile(NULL, url, filePath, 0, NULL);
	if (res == S_OK) {
		printf("色图Ok，单击任意键以退出喵\n");
		system("pause");
	}
	else if (res == E_OUTOFMEMORY) {
		printf("你的电脑内存不足喵\n");
		system("pause");
	}
	else if (res == INET_E_DOWNLOAD_FAILURE) {
		printf("色图服务器挂了喵\n");
		system("pause");
	}
	else {
		printf("Other error: %d\n", res);
		system("pause");
	}
	return 0;
}
