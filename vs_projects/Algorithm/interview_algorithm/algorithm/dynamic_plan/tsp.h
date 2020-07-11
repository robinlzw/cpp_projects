/*
链接：https://www.nowcoder.com/questionTerminal/3d1adf0f16474c90b27a9954b71d125d
来源：牛客网

小明目前在做一份毕业旅行的规划。打算从北京出发，分别去若干个城市，然后再回到北京，每个城市之间均乘坐高铁，且每个城市只去一次。
由于经费有限，希望能够通过合理的路线安排尽可能的省一些路上的花销。给定一组城市和每对城市之间的火车票的价钱，
找到每个城市只访问一次并返回起点的最小车费花销。

输入描述:
城市个数n（1<n≤20，包括北京）

城市间的车票价钱 n行n列的矩阵 m[n][n]


输出描述:
最小车费花销 s
示例1
输入
4
0 2 6 5
2 0 4 4
6 4 0 2
5 4 2 0
输出
13
说明
共 4 个城市，城市 1 和城市 1 的车费为0，城市 1 和城市 2 之间的车费为 2，城市 1 和城市 3 之间的车费为 6，城市 1 和城市 4 之间的车费为 5，依次类推。
假设任意两个城市之间均有单程票可购买，且票价在1000元以内，无需考虑极端情况。
*/

#include<iostream>
using namespace std;
#include<string>
#include<vector>
#include<map>
#include<algorithm>

int N;  // 城市个数
int **g_costMatrix;
std::vector<bool> g_visited;
std::map<std::vector<int>, int> g_saved_cost_map;
std::map<std::string, int> g_saved_cost_dict;


int cost_of_last_city(int city, std::vector<int> remain_city_vector) {  // 上一个城市为 city 需要的花费
	int cost_to_city = 1000000000;
	if (remain_city_vector.size() == 0) {
		std::cout << 0 << " --> " << city << ", cost = " << g_costMatrix[0][city] << std::endl;
		return g_costMatrix[0][city];  // 第一个去的城市		
	}

	int last_city = 0;
	for (int i = 0; i < remain_city_vector.size(); i++) {
		std::vector<int> new_remain_city_vector = remain_city_vector;
		new_remain_city_vector.erase(find(new_remain_city_vector.begin(), new_remain_city_vector.end(), remain_city_vector[i]));
		int new_cost = cost_of_last_city(remain_city_vector[i], new_remain_city_vector) + g_costMatrix[remain_city_vector[i]][city];  // 最后去的城市为 remain_city_vector[i]
		std::cout << remain_city_vector[i] << " --> " << city << ", new_cost = " << new_cost << std::endl;
		if (cost_to_city > new_cost) {
			cost_to_city = new_cost;
			last_city = remain_city_vector[i];
		}
	}
	std::cout << " ########## " << last_city << " --> " << city << std::endl;
	return cost_to_city;
}

int cost_of_last_city2(int city) {  // 上一个城市为 city 需要的花费
	int cost_to_city = 1000000000;
	g_visited[city] = true;
	for (int i = 0; i < N; i++) {
		if (false == g_visited[i]) {
			g_visited[i] = true;
			int new_cost = cost_of_last_city2(i) + g_costMatrix[i][city];  // 最后去的城市为 i
			if (cost_to_city > new_cost) {
				cost_to_city = new_cost;
			}
			g_visited[i] = false;
		}
	}

	if (find(g_visited.begin(), g_visited.end(), false) == g_visited.end()) {
		std::cout << 0 << " --> " << city << ", cost = " << g_costMatrix[0][city] << std::endl;
		return g_costMatrix[0][city];  // 第一个去的城市		
	}


	return cost_to_city;
}

int cost_of_last_city3(int city, std::vector<int> remain_city_vector) {  // 上一个城市为 city 需要的花费
	int cost_to_city = 1000000000;
	if (remain_city_vector.size() == 0) {
		std::cout << 0 << " --> " << city << ", cost = " << g_costMatrix[0][city] << std::endl;
		return g_costMatrix[0][city];  // 第一个去的城市		
	}

	int last_city = 0;
	for (int i = 0; i < remain_city_vector.size(); i++) {
		std::vector<int> new_remain_city_vector = remain_city_vector;
		std::vector<int> save_new_remain_city_vector = remain_city_vector;
		save_new_remain_city_vector.insert(save_new_remain_city_vector.begin(), remain_city_vector[i]);
		new_remain_city_vector.erase(find(new_remain_city_vector.begin(), new_remain_city_vector.end(), remain_city_vector[i]));
		
		int new_cost;
		if (g_saved_cost_map.find(save_new_remain_city_vector) == g_saved_cost_map.end()) {			
			g_saved_cost_map[save_new_remain_city_vector] = cost_of_last_city3(remain_city_vector[i], new_remain_city_vector);			
		}
		else {
			std::cout << "不是第一次计算" << std::endl;
		}
		new_cost = g_saved_cost_map[save_new_remain_city_vector] + g_costMatrix[remain_city_vector[i]][city];  // 最后去的城市为 remain_city_vector[i]		
		
		std::cout << remain_city_vector[i] << " --> " << city << ", new_cost = " << new_cost << std::endl;
		if (cost_to_city > new_cost) {
			cost_to_city = new_cost;
			last_city = remain_city_vector[i];
		}
	}
	std::cout << " ########## " << last_city << " --> " << city << std::endl;
	return cost_to_city;
}

std::string get_saved_cost_map_key() {
	std::string key;
	for (int i = 0; i < N; i++) {
		if (false == g_visited[i]) {  // 还未去过的城市
			key.append(std::to_string(i));
		}
	}
	return key;	
}

int cost_of_last_city4(int city) {  // 上一个城市为 city 需要的花费
	int cost_to_city = 1000000000;
	g_visited[city] = true;
	for (int i = 0; i < N; i++) {
		if (false == g_visited[i]) {
			g_visited[i] = true;
			std::string key = get_saved_cost_map_key() + "#" + std::to_string(i);  // 从 还未去过的城市集合 到 i

			if (g_saved_cost_dict.find(key) == g_saved_cost_dict.end()) {
				g_saved_cost_dict[key] = cost_of_last_city4(i);
			}
			
			int new_cost = g_saved_cost_dict[key] + g_costMatrix[i][city];  // 最后去的城市为 i
			if (cost_to_city > new_cost) {
				cost_to_city = new_cost;
			}
			g_visited[i] = false;
		}
	}

	if (find(g_visited.begin(), g_visited.end(), false) == g_visited.end()) {
		std::cout << 0 << " --> " << city << ", cost = " << g_costMatrix[0][city] << std::endl;
		return g_costMatrix[0][city];  // 第一个去的城市		
	}


	return cost_to_city;
}

void getLowestCostTravel() {
	int cost = 0;
	std::vector<int> remain_city_vector;
	for (int i = 1; i < N; i++) {
		remain_city_vector.push_back(i);  // 其余城市
	}
	//cost = cost_of_last_city(0, remain_city_vector);  // 最后去的城市为 0 (也就是回到起点)
	//cost = cost_of_last_city2(0);
	//cost = cost_of_last_city3(0, remain_city_vector);  // 最后去的城市为 0 (也就是回到起点)
	cost = cost_of_last_city4(0);
	std::cout << "cost = " << cost << std::endl;
}


int solve() {	
	FILE *stream1;
	freopen_s(&stream1, "D:\\Dev01_C++\\cpp_projects\\algorithm_projects\\algorithm\\algorithm\\dynamic_plan\\resource\\tsp_input.data", "r", stdin);

	cin >> N;

	g_costMatrix = (int**)malloc((sizeof(int*))*N);   //长度为N 每个都是一个指针
	for (int i = 0; i < N; i++)
	{
		g_costMatrix[i] = (int*)malloc(sizeof(int)*N);
		g_visited.push_back(false);
	}


	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> g_costMatrix[i][j];
		}
	}
	getLowestCostTravel();

	for (int i = 0; i < N; i++)
	{
		free(g_costMatrix[i]);
	}
	free(g_costMatrix);

	fclose(stdin);

	return 0;
}