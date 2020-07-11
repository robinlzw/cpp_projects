/*
链接：https://www.nowcoder.com/questionTerminal/5afcf93c419a4aa793e9b325d01957e2
来源：牛客网

 小明是一名算法工程师，同时也是一名铲屎官。某天，他突发奇想，想从猫咪的视频里挖掘一些猫咪的运动信息。为了提取运动信息，他需要从视频的每一帧提取“猫咪特征”。一个猫咪特征是一个两维的vector<x, y>。如果x_1=x_2 and y_1=y_2，那么这俩是同一个特征。
	   因此，如果喵咪特征连续一致，可以认为喵咪在运动。也就是说，如果特征<a, b>在持续帧里出现，那么它将构成特征运动。比如，特征<a, b>在第2/3/4/7/8帧出现，那么该特征将形成两个特征运动2-3-4 和7-8。
现在，给定每一帧的特征，特征的数量可能不一样。小明期望能找到最长的特征运动。

输入描述:
第一行包含一个正整数N，代表测试用例的个数。

每个测试用例的第一行包含一个正整数M，代表视频的帧数。

接下来的M行，每行代表一帧。其中，第一个数字是该帧的特征个数，接下来的数字是在特征的取值；比如样例输入第三行里，2代表该帧有两个猫咪特征，<1，1>和<2，2>
所有用例的输入特征总数和<100000

N满足1≤N≤100000，M满足1≤M≤10000，一帧的特征个数满足 ≤ 10000。
特征取值均为非负整数。


输出描述:
对每一个测试用例，输出特征运动的长度作为一行
示例1
输入
1
8
2 1 1 2 2
2 1 1 1 4
2 1 1 2 2
2 2 2 1 4
0
0
1 1 1
1 1 1
输出
3
说明
特征<1,1>在连续的帧中连续出现3次，相比其他特征连续出现的次数大，所以输出3

备注:
如没有长度大于2的特征运动，返回1
*/

#include<iostream>
using namespace std;
#include<string>
#include<vector>
#include<map>
#include<algorithm>
#include <iterator>

typedef std::pair<int, int> feature;

std::string featrue2string(feature inputFeature) {
	return std::to_string(inputFeature.first) + "#" + std::to_string(inputFeature.second);
}

int getContinuousCommonFeatureLength(std::string featureStr, std::vector<std::vector<std::string> > &featureStrListVector) {
	int lastContinuousCommonFeatureLength = 0, nowContinuousCommonFeatureLength = 0;

	for (auto &featureStrLis : featureStrListVector) {
		if (featureStrLis.end() == find(featureStrLis.begin(), featureStrLis.end(), featureStr)) {
			if (nowContinuousCommonFeatureLength > lastContinuousCommonFeatureLength) {
				lastContinuousCommonFeatureLength = nowContinuousCommonFeatureLength;
			}			
			nowContinuousCommonFeatureLength = 0;
		}
		else {
			nowContinuousCommonFeatureLength++;
		}
	}
	
	return  (nowContinuousCommonFeatureLength > lastContinuousCommonFeatureLength) ? nowContinuousCommonFeatureLength : lastContinuousCommonFeatureLength;
}

void getLongestCommonFeature(std::vector<std::vector<feature> > &featureImageVector) {
	std::vector<std::vector<std::string> > featureStrListVector;
	std::map<std::string, int> continuous_feature_cnt_map;

	for (auto &featureImage : featureImageVector) {
		std::vector<std::string> featureStrList;
		for (auto &feature : featureImage) {
			std::string featureStr = featrue2string(feature);
			featureStrList.push_back(featureStr);
			if (continuous_feature_cnt_map.find(featureStr) != continuous_feature_cnt_map.end()) {
				continuous_feature_cnt_map[featureStr] += 1;
			}
			else {
				continuous_feature_cnt_map[featureStr] = 1;
			}
		}
		featureStrListVector.push_back(featureStrList);
	}

	//for (auto &continuous_feature_cnt : continuous_feature_cnt_map) {
	//	std::cout << "continuous_feature_cnt: " << continuous_feature_cnt.first << " --> " << continuous_feature_cnt.second << std::endl;
	//}
	//std::cout << "--------------------------------" << std::endl;

	std::map<int, std::string> tmp;
	std::transform(continuous_feature_cnt_map.begin(), continuous_feature_cnt_map.end(), std::inserter(tmp, tmp.begin()),
		[](std::pair<std::string, int> a) { return std::pair<int, std::string>(a.second, a.first); });

	/*for (auto &continuous_feature_cnt : tmp) {
		std::cout << "continuous_feature_cnt: " << continuous_feature_cnt.first << " --> " << continuous_feature_cnt.second << std::endl;
	}*/

	for (map<int, string>::iterator iter_map = --tmp.end(); iter_map != tmp.begin(); iter_map--) {
		std::cout << "continuous_feature_cnt: " << iter_map->first << " --> " << getContinuousCommonFeatureLength(iter_map->second, featureStrListVector) << std::endl;
		if (iter_map->first > 2) {
			getContinuousCommonFeatureLength(iter_map->second, featureStrListVector);
		}
	}

	/*for (auto &continuous_feature_cnt : tmp) {
		std::cout << "continuous_feature_cnt: " << continuous_feature_cnt.first << " --> " << continuous_feature_cnt.second << std::endl;
	}*/
	// std::cout << "getLongestCommonFeature: " << (tmp.begin())->first << " --> " << (tmp.begin())->second << std::endl;

}

void getLongestCommonFeature2(std::vector<std::vector<feature> > &featureImageVector) {
	std::vector<std::vector<std::string> > featureStrListVector;
	std::map<std::string, int> continuous_feature_cnt_map;

	for (auto &featureImage : featureImageVector) {
		std::vector<std::string> featureStrList;
		for (auto &feature : featureImage) {
			std::string featureStr = featrue2string(feature);
			featureStrList.push_back(featureStr);
			if (continuous_feature_cnt_map.find(featureStr) != continuous_feature_cnt_map.end()) {
				continuous_feature_cnt_map[featureStr] += 1;
			}
			else {
				continuous_feature_cnt_map[featureStr] = 1;
			}
		}
		featureStrListVector.push_back(featureStrList);
	}


	int longestCommonFeatureLength = 1;
	for (map<string, int>::iterator iter_map = continuous_feature_cnt_map.begin(); iter_map != continuous_feature_cnt_map.end(); iter_map++) {
		if (iter_map->second >= 2) {
			int cnt = getContinuousCommonFeatureLength(iter_map->first, featureStrListVector);
			std::cout << "continuous_feature_cnt: " << iter_map->first << ": " << iter_map->second << " --> " << cnt << std::endl;			
			longestCommonFeatureLength = longestCommonFeatureLength > cnt ? longestCommonFeatureLength : cnt;
		}
	}

	std::cout << "getLongestCommonFeature2: " << longestCommonFeatureLength;
}



int solve() {
	int N;  // 测试用例个数
	cin >> N;

	while (N) {
		std::vector<std::vector<feature> > featureImageVector;
		int M;  // 特征图个数
		cin >> M;
				
		while (M) {
			std::vector<feature> featureImage;
			int featureImageSize;  // 特征图大小
			cin >> featureImageSize;
			while (featureImageSize) {
				int featureX, featureY;
				cin >> featureX >> featureY;
				featureImage.push_back(std::make_pair(featureX, featureY));
				featureImageSize--;
			}
			featureImageVector.push_back(featureImage);
			M--;
		}
		getLongestCommonFeature2(featureImageVector);

		N--;
	}


	return 0;
}