//
//  QueueSystem.h
//  QueueSystem
//
//  Created by Changkun on 16/7/6.
//  Copyright © 2016 Shiyanlou.com. All rights reserved.
//

#ifndef QueueSystem_h
#define QueueSystem_h

#include "Event.h"
#include "Queue.h"
#include "ServiceWindow.h"

class QueueSystem {
    
public:
    // 初始化队列系统
    QueueSystem(int total_service_time, int window_num);
    
    // 销毁
    ~QueueSystem();
    
    // 启动模拟
    void simulate(int simulate_num);
    
    double getAvgStayTime() const {
        return avg_stay_time;  //顾客平均停留时间
    }
    double getAvgCustomers() const {
        return avg_customers;  //平均服务的顾客人数
    }
    
private:
    // 让队列系统运行一次
    double run();
    
    // 初始化各种参数
    void init();
    
    // 清空各种参数
    void end();
    
    // 获得空闲窗口索引
    int getIdleServiceWindow();
    
    // 处理顾客到达事件
    void customerArrived();
    
    // 处理顾客离开事件
    void customerDeparture();
    
    // 服务窗口的总数
    int window_num;
    
    // 总的营业时间
    int total_service_time;
    
    // 顾客的逗留总时间
    int total_customer_stay_time;
    
    // 总顾客数
    int total_customer_num;
    
    ServiceWindow*  windows;  //服务窗口
    Queue<Customer> customer_list;  //顾客等待队列
    Queue<Event>       event_list;  //事件队列
    Event*          current_event;  //当前事件
    
    double avg_customers;
    double avg_stay_time;

};


#endif /* QueueSystem_h */
