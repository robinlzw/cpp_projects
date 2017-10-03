//
//  ServiceWindow.h
//  QueueSystem
//
//  Created by Changkun on 16/7/6.
//  Copyright © 2016 Shiyanlou.com. All rights reserved.
//

#ifndef ServiceWindow_h
#define ServiceWindow_h

#include "Node.h"

enum WindowStatus {
    SERVICE,
    IDLE,
};

class ServiceWindow {
public:
    ServiceWindow() {
        window_status = IDLE;
    };

    bool isIdle() const {
        if (window_status == IDLE) {
            return true;
        } else {
            return false;
        }
    }

    void serveCustomer(Customer &customer) {
        this->customer = customer;
    }

    void setBusy() {
        window_status = SERVICE;
    }

    void setIdle() {
        window_status = IDLE;
    }

    int getCustomerArriveTime() const {
        return customer.arrive_time;
    }

    int getCustomerDuration() const {
        return customer.duration;
    }

private:
    Customer customer;
    WindowStatus window_status;
};

#endif /* ServiceWindow_h */
