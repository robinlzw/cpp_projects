#include <iostream>
#include <algorithm>
#include <climits>
 
using namespace std;
#include<string>
#include<vector>
#include<map>
#include<algorithm>
#include <ctime>

#define DEBUG_LOG_ENABLE

int N;  // 城市个数
int **g_costMatrix;
std::map<std::string, int> g_saved_cost_dict;
std::string g_visited_city;
std::string g_all_visited_city;
int g_repeat_cnt = 0;  // 重复计算次数
int g_all_cnt = 0;  // 计算次数

string getTime()
{
	time_t timep;
	time(&timep);
	char tmp[64];
	struct tm nowTime;
	localtime_s(&nowTime, &timep);
	strftime(tmp, sizeof(tmp), "%Y-%m-%d-%H:%M:%S", &nowTime);
	return std::string(tmp);
}

std::string get_saved_cost_map_key() {
	std::string key;
	for (int i = 1; i < N; i++) {
		if ('0' == g_visited_city[i]) {  // 还未去过的城市
			key.append(std::to_string(i));
		}
	}
	return key;
}

int cost_of_last_city4(int city) {  // 上一个城市为 city 需要的花费
	g_all_cnt++;
	int cost_to_city = 1000000000;

	if (g_all_visited_city == g_visited_city) {
#ifdef DEBUG_LOG_ENABLE
		std::cout << 0 << " --> " << city << ", cost = " << g_costMatrix[0][city] << std::endl;
#endif
		return g_costMatrix[0][city];  // 第一个去的城市		
	}

	for (int i = 1; i < N; i++) {
		if (g_visited_city[i] == '0') {
			g_visited_city[i] = '1';
		
			//std::string key = get_saved_cost_map_key() + "#" + std::to_string(i);  // 从 还未去过的城市集合 到 i
			std::string key = g_visited_city + "#" + std::to_string(i);  // 从 还未去过的城市集合 到 i
#ifdef DEBUG_LOG_ENABLE
			std::cout << "key = " << key << std::endl;
#endif
			
			if (g_saved_cost_dict.find(key) == g_saved_cost_dict.end()) {  // 时间消耗在 map 的查找上
				g_saved_cost_dict[key] = cost_of_last_city4(i);
			}
			else {
#ifdef DEBUG_LOG_ENABLE
				g_repeat_cnt++;
#endif
			}
			

			int new_cost = g_saved_cost_dict[key] + g_costMatrix[i][city];  // 最后去的城市为 i
			if (cost_to_city > new_cost) {
				cost_to_city = new_cost;
			}
			g_visited_city[i] = '0';
		}
	}

	return cost_to_city;
}

int solve() {
	FILE *stream1;
	freopen_s(&stream1, "D:\\Dev01_C++\\cpp_projects\\algorithm_projects\\algorithm\\algorithm\\dynamic_plan\\resource\\tsp_input.data", "r", stdin);
	

    cin >> N;
	g_costMatrix = new int*[N];
    for (int i = 0; i < N; ++i) {
		g_costMatrix[i] = new int[N];
		for (int j = 0; j < N; ++j) {
			cin >> g_costMatrix[i][j];
		}
    }
 
	fclose(stdin);
		
	for (int i = 0; i < N; ++i) {
		g_visited_city.append("0");
		g_all_visited_city.append("1");
	}	
	
	g_visited_city[0] = '1';
	cout << ">>>>>>>>>>>>>>>>>>>" << getTime() << endl;
	cout << "g_repeat_cnt = " << g_repeat_cnt << ", g_all_cnt = " << g_all_cnt << ", cost = " << cost_of_last_city4(0) << endl;
	cout << "<<<<<<<<<<<<<<<<<<<" << getTime() << endl;	
	return 0;
}