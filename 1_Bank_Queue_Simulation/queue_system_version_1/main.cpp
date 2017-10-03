//
// main.cpp
// QueueSystem
//
//  Created by Changkun on 16/7/6.
//  Copyright © 2016 Shiyanlou.com. All rights reserved.
//

#include "QueueSystem.h"

#include <iostream>
#include <cstdlib>
using std::srand;
using std::cout;
using std::endl;

int main() {
    
#ifdef __APPLE__
    srand((unsigned)time(0)); //  使用当前时间作为随机数种子
#else
    srand(time(0));
#endif

    const int total_service_time = 240;  //总服务时间,按分钟数计算
    const int window_num         = 4;  //窗口数量
    const int simulate_num       = 10000;  //模拟次数
    
    QueueSystem system(total_service_time, window_num);
    system.simulate(simulate_num);
    
    cout << "The average time of customer stay in bank: "
    << system.getAvgStayTime() << endl;
    cout << "The number of customer arrive bank per minute: " << system.getAvgCustomers() << endl;
    
    return 0;
}
