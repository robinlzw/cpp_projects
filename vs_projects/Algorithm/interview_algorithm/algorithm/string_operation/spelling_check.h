/*
我叫王大锤，是一家出版社的编辑。我负责校对投稿来的英文稿件，这份工作非常烦人，因为每天都要去修正无数的拼写错误。但是，优秀的人总能在平凡的工作中发现真理。我发现一个发现拼写错误的捷径：

1. 三个同样的字母连在一起，一定是拼写错误，去掉一个的就好啦：比如 helllo -> hello
2. 两对一样的字母（AABB型）连在一起，一定是拼写错误，去掉第二对的一个字母就好啦：比如 helloo -> hello
3. 上面的规则优先“从左到右”匹配，即如果是AABBCC，虽然AABB和BBCC都是错误拼写，应该优先考虑修复AABB，结果为AABCC

我特喵是个天才！我在蓝翔学过挖掘机和程序设计，按照这个原理写了一个自动校对器，工作效率从此起飞。用不了多久，我就会出任CEO，当上董事长，迎娶白富美，走上人生巅峰，想想都有点小激动呢！
……
万万没想到，我被开除了，临走时老板对我说： “做人做事要兢兢业业、勤勤恳恳、本本分分，人要是行，干一行行一行。一行行行行行；要是不行，干一行不行一行，一行不行行行不行。” 我现在整个人红红火火恍恍惚惚的……

请听题：请实现大锤的自动校对程序

输入描述:
第一行包括一个数字N，表示本次用例包括多少个待校验的字符串。

后面跟随N行，每行为一个待校验的字符串。

输出描述:
N行，每行包括一个被修复后的字符串。

输入例子1:
2
helloo
wooooooow

输出例子1:
hello
woow
*/

#include<iostream>
using namespace std;
#include<string>
#include<vector>
#include<cctype>

// 纠正字符串
void correctStr(string &inputStr) {
	int head = 0, next = head + 2;

	while (inputStr[head] != '\0' && inputStr[head + 1] != '\0' && inputStr[next] != '\0')
	{
		string printStr;
		if (inputStr[head] == inputStr[next] && inputStr[head+1] == inputStr[next]) {  // 连续3个相同字符
			printStr.append(inputStr.substr(0, head + 2));  // 拷贝至head+1处
			printStr.append(inputStr.substr(next + 1, inputStr.length() - next - 1));  // 从next+1处拷贝
			head = 0;
			next = head + 2;
		}
		else if (inputStr[head] == inputStr[head + 1] && inputStr[head] != inputStr[next] && inputStr[next] == inputStr[next + 1]) {  // AABB			
			printStr.append(inputStr.substr(0, next + 1));  // 拷贝至next处
			printStr.append(inputStr.substr(next + 2, inputStr.length() - next - 2));  // 从next+2处拷贝
			head = 0;
			next = head + 2;
		}
		else {	
			printStr = inputStr;
			head++;
			next = head + 2;
		}
		inputStr = printStr;
	}
	cout << inputStr << endl;
}


int solve() {

	int m;

	while (cin >> m) {
		vector<string> inputStrArray;
		while (m) {
			string inputStr;
			cin >> inputStr;
			inputStrArray.push_back(inputStr);
			m--;
		}

		for (auto &mystring : inputStrArray) {
			correctStr(mystring);
		}		
	}

	return 0;
}