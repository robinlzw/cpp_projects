/*
写出一个程序，接受一个十六进制的数，输出该数值的十进制表示。（多组同时输入 ）

输入描述 :
输入一个十六进制的数值字符串。

输出描述 :
输出该数值的十进制字符串。

输入例子1 :
0xA

输出例子1 :
10
*/

#include<string>
#include<iostream>
using namespace std;
#include<math.h>
#include<cctype>

int solve1() {

	string inputStr;
	
	while (cin >> inputStr) {
		int result = 0;
		if (isxdigit((*(inputStr.c_str())))) {
			sscanf_s(inputStr.c_str(), "%x", &result);
			cout << result << endl;
		}
	}
	
	return 0;
}


int solve2() {

	string inputStr;

	while (cin >> inputStr) {
		long result = 0;
		if (isxdigit((*(inputStr.c_str())))) {
			char *endptr;
			result = strtol(inputStr.c_str(), &endptr, 16);
			cout << result << endl;
		}
	}

	return 0;
}

