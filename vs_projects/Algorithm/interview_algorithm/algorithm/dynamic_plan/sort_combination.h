/*

我叫王大锤，是一名特工。我刚刚接到任务：在字节跳动大街进行埋伏，抓捕恐怖分子孔连顺。和我一起行动的还有另外两名特工，我提议

1. 我们在字节跳动大街的N个建筑中选定3个埋伏地点。
2. 为了相互照应，我们决定相距最远的两名特工间的距离不超过D。

我特喵是个天才! 经过精密的计算，我们从X种可行的埋伏方案中选择了一种。这个方案万无一失，颤抖吧，孔连顺！
……
万万没想到，计划还是失败了，孔连顺化妆成小龙女，混在cosplay的队伍中逃出了字节跳动大街。只怪他的伪装太成功了，就是杨过本人来了也发现不了的！

请听题：给定N（可选作为埋伏点的建筑物数）、D（相距最远的两名特工间的距离的最大值）以及可选建筑的坐标，计算在这次行动中，大锤的小队有多少种埋伏选择。
注意：
1. 两个特工不能埋伏在同一地点
2. 三个特工是等价的：即同样的位置组合(A, B, C) 只算一种埋伏方法，不能因“特工之间互换位置”而重复使用


输入描述:
第一行包含空格分隔的两个数字 N和D(1 ≤ N ≤ 1000000; 1 ≤ D ≤ 1000000)

第二行包含N个建筑物的的位置，每个位置用一个整数（取值区间为[0, 1000000]）表示，从小到大排列（将字节跳动大街看做一条数轴）


输出描述:
一个数字，表示不同埋伏方案的数量。结果可能溢出，请对 99997867 取模

示例1
输入
4 3
1 2 3 4
输出
4
说明
可选方案 (1, 2, 3), (1, 2, 4), (1, 3, 4), (2, 3, 4)

示例2
输入
5 19
1 10 20 30 50
输出
1
说明
可选方案 (1, 10, 20)
*/

#include<iostream>
using namespace std;
#include<string>
#include<vector>
#include<set>
#include<algorithm>

long long C(long long n) {
	return (n - 1) * n / 2;
}

void getResult(int D, vector<int> &pos_array) {
	set<set<int> > posSetSet;
	std::sort(pos_array.begin(), pos_array.end());
	// for_each(pos_array.begin(), pos_array.end(), [](int val) {  cout << val << " "; });

	for (vector<int>::iterator curStartPos = pos_array.begin(); curStartPos < pos_array.end(); curStartPos++)
	{
		
		std::vector<int>::iterator find_max_pos = std::find_if(pos_array.begin(), pos_array.end(), [&D, &curStartPos](int x)
		{
			return x - *curStartPos == D;			
		});
		
	/*	vector<int>::iterator find_max_pos = pos_array.begin();
		for (find_max_pos; find_max_pos < pos_array.end(); find_max_pos++) {
			if (*find_max_pos - *curStartPos >= 3) {
				cout << endl << "find_max_pos = " << *find_max_pos << ", curStartPos = " << *curStartPos << endl;
				break;
			}
		}*/
			
		if (find_max_pos != pos_array.end()) {
			cout << endl << "find_max_pos = " << *find_max_pos << ", curStartPos = " << *curStartPos << endl;			
			for (vector<int>::iterator personIt1 = curStartPos; personIt1 <= find_max_pos; personIt1++)
			{
				for (vector<int>::iterator personIt2 = curStartPos; personIt2 <= find_max_pos; personIt2++)
				{
					for (vector<int>::iterator personIt3 = curStartPos; personIt3 <= find_max_pos; personIt3++)
					{		
						set<int> posSet;
						posSet.insert(*personIt1);
						posSet.insert(*personIt2);
						posSet.insert(*personIt3);
						if (posSet.size() == 3) {
							posSetSet.insert(posSet);
						}						
					}
				}
			}
		}
	}
	
	for_each(posSetSet.begin(), posSetSet.end(), [](set<int> val) {
		for_each(val.begin(), val.end(), [](int pos) {
			cout << pos << " "; });
		cout << endl;
	});
	cout << "posSetSet.size() = " << posSetSet.size() % 99997867 << endl;
}

void getResult2(int D, vector<long long> &pos_array) {
	int count = 0;
	for (vector<long long>::iterator curStartPos = pos_array.begin(); curStartPos < pos_array.end(); curStartPos++) {
		vector<long long>::iterator find_max_pos = curStartPos + 1;
		for (; find_max_pos < pos_array.end() && *find_max_pos - *curStartPos <= D; find_max_pos++) {}  // 找到最远距离		
		if (*--find_max_pos - *curStartPos <= D) {
			cout << endl << "find_max_pos = " << *find_max_pos << ", curStartPos = " << *curStartPos << endl;
			if (find_max_pos - curStartPos - 1 >= 1) {
				int tempN = find_max_pos - curStartPos;
				count += (tempN * (tempN - 1)) / 2;
				cout << "count = " << count << endl;
			}
		}
	}	
}

void getResult3(int D, vector<long long> &pos_array)
{
	int count = 0;
	for (int i = 0, j = 0; i < pos_array.size(); i++) {		
		while (i >= 2 && (pos_array[i] - pos_array[j]) > D) {
			j++;
		}
		count += C(i - j);
	}
	cout << count % 99997867;

}

int solve() {
	int N, D;
	vector<long long> pos_array;
	cin >> N >> D;

	while (N) {
		int pos;
		cin >> pos;
		pos_array.push_back(pos);
		N--;
	}

	getResult3(D, pos_array);


	return 0;
}