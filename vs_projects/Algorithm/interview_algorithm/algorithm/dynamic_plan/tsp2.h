#include <iostream>
#include <algorithm>
#include <climits>
 
using namespace std;
#include<string>
#include<vector>
#include<map>
#include<algorithm>
#include <ctime>


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

/*
 note : in rest_citys, index from city 1, since we start from city 0
 */
int calmincost(int ncitys, int current_city, int rest_citys, int** dp, int** a) {
	g_all_cnt++;
    // if no city left to visit, back to initial city, i.e., city 0
    if (rest_citys == 0) {
        return a[current_city][0];
	}
	else if (dp[current_city][rest_citys] > -1) {
		g_repeat_cnt++;
		return dp[current_city][rest_citys];
	}
        
 
    int ans = INT_MAX;
    for (int i = 0; i < ncitys; ++i) {
		cout << "from city[" << i << "], by rest_citys{" << rest_citys << "}" << endl;
		cout << "(rest_citys >> (i - 1) = " << (rest_citys >> (i - 1)) << endl;
		cout << "((rest_citys >> (i - 1)) & 1) = " << ((rest_citys >> (i - 1)) & 1) << endl;
        // judge city i in rest_citys
        if (((rest_citys >> (i - 1)) & 1) == 1) {			
            int remain_citys = rest_citys ^ (1 << (i - 1));
			cout << "from city[" << i << "], by remain_citys{" << remain_citys << "}" << endl << endl;
            ans = min(ans, a[current_city][i]+calmincost(ncitys, i, remain_citys, dp, a));
        }
    }
    return dp[current_city][rest_citys] = ans;
}
 

int solve() {
	FILE *stream1;
	freopen_s(&stream1, "D:\\Dev01_C++\\cpp_projects\\algorithm_projects\\algorithm\\algorithm\\dynamic_plan\\resource\\tsp_input.data", "r", stdin);

    int n;
    cin >> n;
    int V = 1 << (n - 1);
    int** a = new int* [n];
    int** dp = new int* [n];
    for (int i = 0; i < n; ++i) {
        a[i] = new int[n];
		dp[i] = new int[V];
		for (int j = 0; j < n; ++j) {
			cin >> a[i][j];
		}
            
 
        for( int j = 0 ; j < V; ++j )
            dp[i][j] = -1;
    }
	
	cout << ">>>>>>>>>>>>>>>>>>>" << getTime() << endl;
	cout << "g_repeat_cnt = " << g_repeat_cnt << ", g_all_cnt = " << g_all_cnt << ", cost = " << calmincost(n, 0, V - 1, dp, a) << endl;
	cout << "<<<<<<<<<<<<<<<<<<<" << getTime() << endl;
	fclose(stdin);
	return 0;
}