/*
链接：https://www.nowcoder.com/questionTerminal/448127caa21e462f9c9755589a8f2416
来源：牛客网

小包最近迷上了一款叫做雀魂的麻将游戏，但是这个游戏规则太复杂，小包玩了几个月了还是输多赢少。
于是生气的小包根据游戏简化了一下规则发明了一种新的麻将，只留下一种花色，并且去除了一些特殊和牌方式（例如七对子等），具体的规则如下：

总共有36张牌，每张牌是1~9。每个数字4张牌。
你手里有其中的14张牌，如果这14张牌满足如下条件，即算作和牌
14张牌中有2张相同数字的牌，称为雀头。
除去上述2张牌，剩下12张牌可以组成4个顺子或刻子。顺子的意思是递增的连续3个数字牌（例如234,567等），刻子的意思是相同数字的3个数字牌（例如111,777）

例如：
1 1 1 2 2 2 6 6 6 7 7 7 9 9 可以组成1,2,6,7的4个刻子和9的雀头，可以和牌
1 1 1 1 2 2 3 3 5 6 7 7 8 9 用1做雀头，组123,123,567,789的四个顺子，可以和牌
1 1 1 2 2 2 3 3 3 5 6 7 7 9 无论用1 2 3 7哪个做雀头，都无法组成和牌的条件。

现在，小包从36张牌中抽取了13张牌，他想知道在剩下的23张牌中，再取一张牌，取到哪几种数字牌可以和牌。

输入描述:
输入只有一行，包含13个数字，用空格分隔，每个数字在1~9之间，数据保证同种数字最多出现4次。


输出描述:
输出同样是一行，包含1个或以上的数字。代表他再取到哪些牌可以和牌。若满足条件的有多种牌，请按从小到大的顺序输出。若没有满足条件的牌，请输出一个数字0
示例1
输入
1 1 1 2 2 2 5 5 5 6 6 6 9
输出
9
说明
可以组成1,2,6,7的4个刻子和9的雀头
示例2
输入
1 1 1 1 2 2 3 3 5 6 7 8 9
输出
4 7
说明
用1做雀头，组123,123,567或456,789的四个顺子
示例3
输入
1 1 1 2 2 2 3 3 3 5 7 7 9
输出
0
说明
来任何牌都无法和牌

*/

#include<iostream>
using namespace std;
#include<string>
#include<vector>
#include<set>
#include<algorithm>


bool huPai(vector<int> &card_array)
{
	if (0 == card_array.size())
		return true;

	for_each(card_array.begin(), card_array.end(), [](int val) {
		std::cout << val << " ";
	});
	std::cout << endl << endl;

	vector<int> copy_card_array;
	for (int k = 0; k < card_array.size(); k++) {
		if (k <= card_array.size() - 3 && card_array[k] == card_array[k+1] && card_array[k] == card_array[k + 2]) {  // card_array[k] 贡献一个刻子
			std::cout << card_array[k] << " 贡献一个刻子" << endl;
			copy_card_array = card_array;
			copy_card_array.erase(find(copy_card_array.begin(), copy_card_array.end(), card_array[k]));
			copy_card_array.erase(find(copy_card_array.begin(), copy_card_array.end(), card_array[k]));
			copy_card_array.erase(find(copy_card_array.begin(), copy_card_array.end(), card_array[k]));
			if (true == huPai(copy_card_array)) {
				std::cout << "huPai success" << endl;
				return true;
			}
		}	
		else {  // card_array[k] 贡献一个顺子
			copy_card_array = card_array;
			vector<int>::iterator k_it = find(copy_card_array.begin(), copy_card_array.end(), card_array[k]);
			vector<int>::iterator k_plus1_it = find(copy_card_array.begin(), copy_card_array.end(), card_array[k] + 1);
			vector<int>::iterator k_plus2_it = find(copy_card_array.begin(), copy_card_array.end(), card_array[k] + 2);
			if (copy_card_array.end() != k_plus1_it && copy_card_array.end() != k_plus2_it) {
				std::cout << card_array[k] << card_array[k] + 1 << card_array[k] + 2 << " 贡献一个顺子" << endl;
				copy_card_array.erase(k_it);
				k_plus1_it = find(copy_card_array.begin(), copy_card_array.end(), card_array[k] + 1);				
				copy_card_array.erase(k_plus1_it);
				k_plus2_it = find(copy_card_array.begin(), copy_card_array.end(), card_array[k] + 2);
				copy_card_array.erase(k_plus2_it);

				if (true == huPai(copy_card_array)) {
					std::cout << "huPai success" << endl;
					return true;
				}
			}
		}
	}

	return false;
}

void canWin(int *card_array)
{
	for (int i = 1; i < 10; i++) {
		if (card_array[i] < 4) {  // 如果加一张牌i
			card_array[i]++;
			
			for (int j = 1; j < 10; j++) {
				vector<int> copy_card_array;
				for (int cc = 1; cc < 10; cc++) {
					int card_cc_num = card_array[cc];
					while (card_cc_num) {
						copy_card_array.push_back(cc);
						card_cc_num--;
					}
				}

				if (card_array[j] >= 2) {  // 如果牌j做雀头, 看能否和牌 -- 剩下的牌j只能做顺子
					copy_card_array.erase(find(copy_card_array.begin(), copy_card_array.end(), j));
					copy_card_array.erase(find(copy_card_array.begin(), copy_card_array.end(), j));
					std::cout << "加一张牌" << i << ", " << j << "做雀头" << endl;
					
					// 剩余12张牌, 看能否和牌
					// m 个顺子, (4 - m) 个刻子;  每种牌最多贡献一个刻子
					if (huPai(copy_card_array)) {
						std::cout << "***********************************************" << endl;
						std::cout << "加一张牌" << i << ", " << j << "做雀头 hupai 成功" << endl;
					}
				}
			}
			card_array[i]--;
		}
	}
}

int solve() {
	int N(13);
	int bucket[10] = {};

	while (N) {
		int card;
		cin >> card;
		bucket[card]++;
		N--;
	}

	canWin(bucket);


	return 0;
}