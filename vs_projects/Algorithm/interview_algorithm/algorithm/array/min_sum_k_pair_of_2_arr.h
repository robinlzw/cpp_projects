#include<iostream>
#include<vector>
#include<set>
#include<algorithm>
using namespace std;
namespace array_min_sum_k_pair_of_2_arr {
	int getPairSum(pair<int, int> &inputPair) {
		return inputPair.first + inputPair.second;
	}

	void min_sum_k_pair_of_2_arr(vector<int> arr1, vector<int> arr2, int k) {
		vector<pair<int, int>> min_k_pair_vector;

		int result = 0;

		vector<vector<pair<int, int>>> pair_arr_matrix;
		for (int i = 0; i < arr1.size(); i++) {
			vector<pair<int, int>> pair_arr;
			for (int j = 0; j < arr2.size(); j++) {
				pair_arr.push_back(make_pair(arr1[i], arr2[j]));
				if (min_k_pair_vector.size() < k) {
					min_k_pair_vector.push_back(make_pair(arr1[i], arr2[j]));
				}
				else {

				}
			}
			pair_arr_matrix.push_back(pair_arr);
		}
		


		cout << result;
	}


	int solve() {
		FILE *stream1;
		freopen_s(&stream1, "D:\\Dev01_C++\\cpp_projects\\algorithm_projects\\algorithm\\algorithm\\array\\data\\data1.txt", "r", stdin);

		int arr1_size, arr2_size, k;
		vector<int> arr1, arr2;

		cin >> arr1_size;
		while (arr1_size--)
		{
			int x;
			cin >> x;
			arr1.push_back(x);
		}

		cin >> arr2_size;
		while (arr2_size--)
		{
			int x;
			cin >> x;
			arr2.push_back(x);
		}

		cin >> k;
		fclose(stdin);

		min_sum_k_pair_of_2_arr(arr1, arr2, k);

		system("pause");
		return 0;
	}
}