#include<iostream>
#include<vector>
#include<set>
#include<algorithm>
using namespace std;

namespace array_cycle_find_next_bigger_num {
void cycle_find_next_bigger_num(vector<int> arr) {
	int p1(0);

	while (p1 < arr.size()) {
		int p2(p1+1);
		bool found = true;
		if (p2 == arr.size()) {
			p2 = 0;
		}
		while (p2 < arr.size() && arr[p2] <= arr[p1]) {
			if (p2 == arr.size() - 1) {
				p2 = 0;
			}
			if (p2 == p1) {
				found = false;
				cout << "-1" << endl;
				break;
			}
			p2++;
		}
		if (found && p2 < arr.size()) {
			cout << "find " << arr[p2] << " > " << arr[p1] << endl;	
		}
		
		p1++;		
	}
}

int solve() {
	//char* inputStr;
	//string myDataList;
	//inputStr = (char*)malloc(500 * 4 * sizeof(char*));
	vector<int> arr;
	int N;
	//while ((cin >> inputStr))
	//{		
	//	string myData(inputStr);
	//	std::cout << "myData = " << myData.c_str() << endl;
	//	if (myData.find('[')) {
	//		string getData1 = myData.substr(myData.find('[') + 1, myData.length() - myData.find('['));
	//		std::cout << "getData1 = " << getData1.c_str() << endl;
	//		if (myData.find(']')) {
	//			string getData2 = getData1.substr(0, getData1.find(']'));
	//			myDataList = getData2;

	//			std::cout << "myDataList = " << myDataList.c_str() << endl;
	//			break;
	//		}
	//	}
	//}
	//free(inputStr);

	//for (int i = 0, p = 0; i < myDataList.length(); i++) {
	//	if (myDataList[i] == ',') {
	//		string printStr = myDataList.substr(p, i-p+1);
	//		std::cout << "printStr = " << printStr.c_str() << endl;
	//		p = i;
	//		//atoi()
	//	}
	//}
	cin >> N;
	while (N--) {
		int x;
		cin >> x;
		arr.push_back(x);
	}
	cycle_find_next_bigger_num(arr);

	system("pause");
	return 0;
}
}