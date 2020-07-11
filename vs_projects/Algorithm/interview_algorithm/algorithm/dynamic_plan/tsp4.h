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
std::vector<std::vector<int>> g_saved_cost_2d_vector;


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

int get_saved_cost_j_value() {
	int result = 0;
	for (int i = 1; i < N; i++) {
		if (g_visited_city[i] == '1') {
			result += (1 << (i-1));
		}
	}
	return result;
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


			if (g_saved_cost_2d_vector[i][get_saved_cost_j_value()] == -1) {
				g_saved_cost_2d_vector[i][get_saved_cost_j_value()] = cost_of_last_city4(i);
			}
			else {
#ifdef DEBUG_LOG_ENABLE
				g_repeat_cnt++;
#endif
			}
						

			int new_cost = g_saved_cost_2d_vector[i][get_saved_cost_j_value()] + g_costMatrix[i][city];  // 最后去的城市为 i
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

		std::vector<int> g_saved_cost_1d_vector;
		for (int j = 0; j < (1 << (N - 1)); ++j) {
			g_saved_cost_1d_vector.push_back(-1);
		}
		g_saved_cost_2d_vector.push_back(g_saved_cost_1d_vector);
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