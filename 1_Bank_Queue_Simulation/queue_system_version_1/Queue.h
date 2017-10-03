//
//  Queue.h
//  QueueSystem
//
//  Created by Changkun on 16/7/6.
//  Copyright © 2016 Shiyanlou.com. All rights reserved.
//

#ifndef Queue_h
#define Queue_h

#include <iostream>
#include <cstdlib>
#include "Event.h"

// 带头结点的队列
template <typename T>
class Queue
{
public:
    // 构造一个带头节点的链式队列，初始时这个头节点同时位于对首和队尾，即front和rear指针相等
    Queue() {
        this->front = new T;
        // 如果内存申请失败，则不应该继续运行程序了
        if (!this->front) {  //this->front = 0
            exit(-1);
        }
        
        // 初始化节点
        this->front->next = NULL;
        this->rear = this->front;
    }
    // 销毁一个队列时候需要释放节点中申请的内存
    ~Queue() {
        clearQueue();  //先释放队列中每个位置的节点所申请的内存
        delete this->front;  //再删除头节点
        this->front = NULL;
        this->rear  = NULL;
    }
    void clearQueue() {
        T* temp_node;  //用临时指针指向要删除的节点(不包括头节点，因为要用头节点引出其它节点)
       
        //循环删除节点
        while (this->front->next) {
            temp_node = this->front->next;
            this->front->next = temp_node->next;
            delete temp_node;
        }
        
        //恢复对首指针和对尾指针的位置(变成构造函数里的状态了)
        this->front->next = NULL;
        this->rear = this->front;
    }
    // 入队时，传递顾客节点指针，外部数据不应该由此类进行管理，所以将数据拷贝一份并返回头指针
    T* enqueue(T& node) {
        T* new_node = new T;
        if (!new_node) {
            exit(-1);
        }
        *new_node = node;
        this->rear->next = new_node;
        this->rear = new_node;
        return this->front;
    }

    // 出队时，从队头元素出队
    T* dequeue() {
        // 如果队列空，则返回空指针
        if (!this->front->next) {
            return NULL;
        }
        
        T* temp_node;
        temp_node = this->front->next;
        this->front->next = temp_node->next;

        // 如果队列中只有一个节点，那么记得将队尾节点指针置为头结点
        if (this->rear == temp_node) {
            this->rear = this->front;
        }
        return temp_node;  //返回指向该节点的指针
    }

    // 当节点是事件时的顺序插入
    T* orderEnqueue(Event& event) {
        Event* temp = new Event;
        if (!temp) {  //temp = 0
            exit(-1);
        }
        *temp = event;
        
        // 如果这个列表里没有事件, 则把 temp 事件插入
        if (!this->front->next) {  //this->front->next = 0
            this->enqueue(*temp);
            return this->front;
        }
        
        // 按时间顺序插入
        Event* temp_already_event_list = this->front;
        // 如果有下一个事件，且下一个事件的发生时间小于要插入事件的发生时间，则继续将指针后移
        while (temp_already_event_list->next && temp_already_event_list->next->occur_time < event.occur_time) {
            temp_already_event_list = temp_already_event_list->next;  //当插入事件的发生时间小于指针当前所指节点的发生时间才退出循环.
        }
        
        // 将事件插入到队列中
        temp->next = temp_already_event_list->next;
        temp_already_event_list->next = temp;
        
        return this->front;  //每次都是返回对首指针
    }

    //获取队列长度
    int  length() {
        T* temp_node;
        temp_node = this->front->next;
        int length = 0;
        while (temp_node) {
            temp_node = temp_node->next;
            ++length;
        }
        return length;
    }


private:
    T* front;  // 指向对首的指针
    T* rear;   // 指向队尾的指针

};


#endif /* Queue_h */
