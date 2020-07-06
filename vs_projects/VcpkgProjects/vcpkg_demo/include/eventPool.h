#ifndef EVENT_POOL_H
#define EVENT_POOL_H

#include <vector>
#include <mutex>
#include <condition_variable>
#include <future>
#include <memory>
#include <queue> // for priority queue.
#include <chrono>
#include <string>
#include <atomic>

/*
*  基本介绍
*  a header-only event-driven library based on c++11，which use std::promise and std::future asyn-model.
*  一个基于c++11标准，仅需要头文件的事件驱动库:)，使用std::promise/std::future异步模型实现。
*  使用方法：
*  1. 创建event_pool对象并申请一个线程做事件处理，在该线程中调用run函数。
*  ************************************************
*  //run the event_pool.
   std::shared_ptr<event_pool> ev(new event_pool());
   std::thread th([=]()->void {
	   ev->run();
   });
*  ************************************************
*
*  2. 创建event_handle和time_handle对象并设置id_，type_,回调函数func_，
*  上下文args_（如果是time_handle则还要设置触发时间）等，push进event_pool对象。
*  *************************************************
*  //create time_handle.
   std::shared_ptr<time_handle> h(new time_handle());
   h->id_ = "timer test ";
   h->type_ = time_handle::type::duration;
   h->duration_ = seconds(2);
   h->args_ = nullptr;
   h->func_ = [](std::shared_ptr<time_handle> self)->void {
		   std::cout << self->id_ << " wake up !" << std::endl;
   };

   //create event_handle.
   std::shared_ptr<event_handle> eh(new event_handle());
   eh->id_ = "back cout ";
   eh->type_ = event_handle::type::every;
   eh->args_ = nullptr;
   eh->func_ = [](std::shared_ptr<event_handle> self)->void {
	   std::cout << self->id_ << " wake up !"<<std::endl;
   };

   //push them into ev.
   ev->push_timer(h);
   ev->push_event(eh);
*  ************************************************
*  3. 在需要触发事件的时候调用wake_up函数（time_handle没有wake_up函数，等待时间到达自动触发）。
*  当需要关闭event_pool时，调用stop函数，然后回收线程，没有来得及处理的事件会被丢弃，即使当event_pool
*  对象完全销毁后，仍然可以调用wake_up函数，此时会直接返回。
*  ************************************************
*     while (true) {
		char buf[1024];
		gets(buf);
		if (buf[0] == 'q') {
		  ev->stop(); // stop the event_pool.
		  break;
		}
		eh->wake_up();
	  }
	  th.join();
   ************************************************
*/

/*
*  注意事项：
*  1. 所有对象均需使用std::shared_ptr创建。
*  2. 每个time_handle对象和event_handle对象只能push进一个event_pool对象。
*  3. event_handle对象可设置两种类型：every和once，every类型允许不限次数的wake_up,
*  event_pool会处理每次wake_up，而once类型只能被唤醒一次，但允许多次调用wake_up函数（线程安全），这意味着可以在多个线程并发的触发事件。
*  4. time_handle对象可设置两种类型：duration和time_point，其中duration类型通过设置duration_成员来
*  指定从此刻开始，每间隔多少时间就触发一次。time_point类型通过设置time_point_成员来指定在哪个时刻仅触发一次。
*  5. 回调函数的输入参数就是该事件对象本身，你可以通过其访问设置的id_，type_，args_等等。
*  6. event_pool的run函数可以在多个线程并发执行（maybe？），这一点暂且不保证。
*/

/*
*特点：
* 1.轻量级，200行源代码，语言层面的跨平台，基于c++11标准。
* 2.仅需要头文件，即拿即用。
*/

/*
* todo:
* 定义更便于使用，减少出错概率的接口。
* 补充测试。
*/

/* v1.1 update
 * event_pool增加set_max_events()接口函数，控制最大异步任务数量,当前任务数量大于该值时会阻塞等待，初始化为1024。
 * push_timer和push_event接口函数现在返回std::future<void>，可以调用该对象的get方法，使得当前线程阻塞等待异步任务完成。（有些情况下不可避免的
 * 需要在异步框架中增加一些同步操作）
 */

using namespace std::chrono;
class event_pool;

class event_handle : public std::enable_shared_from_this<event_handle> {
	friend class event_pool;
public:
	enum class type { once, every };
	type type_;
	std::string id_;
	std::function<void(std::shared_ptr<event_handle>)> func_;
	std::shared_ptr<void> args_;
	void wake_up();
private:
	std::weak_ptr<event_pool> event_;
	bool trigger_;
	std::atomic<bool> done_; //only for once state event_handle.
	std::shared_ptr<std::promise<void>> promise_;
public:
	event_handle() :trigger_(false), done_(false) {

	}
};

class time_handle : public std::enable_shared_from_this<time_handle> {
	friend class event_pool;
public:
	enum class type { duration, timepoint };
	type type_;
	std::string id_;
	std::function<void(std::shared_ptr<time_handle>)> func_;
	std::shared_ptr<void> args_;
	time_point<system_clock, milliseconds> time_point_; //only for timepoint
	milliseconds duration_; //only fo duration
private:
	std::shared_ptr<std::promise<void>> promise_;
};

class event_pool : public std::enable_shared_from_this<event_pool> {
	friend class event_handle;
	friend class time_handle;
private:
	std::mutex mut_;
	std::condition_variable at_least_one_wake_up_;
	std::condition_variable too_many_events_;
	std::vector<std::shared_ptr<event_handle>> handles_;
	std::vector<std::shared_ptr<event_handle>> active_handles_;
	uint64_t triggers_;
	uint64_t events_;
	uint64_t max_events_;
	bool stop_;

	//for timer.
	using ptr_time_handle = std::shared_ptr<time_handle>;
	struct cmp_for_ptr_handle {
		bool operator()(ptr_time_handle h1, ptr_time_handle h2) {
			return h1->time_point_ > h2->time_point_;
		}
	};

	std::priority_queue<ptr_time_handle, std::vector<ptr_time_handle>, cmp_for_ptr_handle> timers_;

	//hold mutex.
	void remove_all_triggered_handle_and_reset() {
		for (auto it = handles_.begin(); it != handles_.end();) {
			if ((*it)->trigger_ == true) {
				it = handles_.erase(it);
			}
			else {
				++it;
			}
		}
		triggers_ = 0;
	}

	std::vector<std::shared_ptr<event_handle>> get_ready() {
		std::vector<std::shared_ptr<event_handle>> result;
		std::vector<std::shared_ptr<time_handle>> tmp;
		std::unique_lock<std::mutex> mut(mut_);
		if (timers_.empty() == true) {
			at_least_one_wake_up_.wait(mut, [this]()->bool {
				return this->active_handles_.empty() == false || this->timers_.empty() == false || this->stop_ == true;
			});
		}
		else {
			time_point<system_clock, milliseconds> now = time_point_cast<milliseconds>(system_clock::now());
			milliseconds dt = timers_.top()->time_point_ - now;
			at_least_one_wake_up_.wait_for(mut, milliseconds(dt));
		}
		//即使被stop唤醒，也尽量完成event。

		//惰性删除已经被处理的事件：event_handle个数如果大于等于1024，则一次性删除一次。
		if (triggers_ >= 1024) {
			remove_all_triggered_handle_and_reset();
		}

		time_point<system_clock, milliseconds> now = time_point_cast<milliseconds>(system_clock::now());
		while (timers_.empty() != true) {
			if (timers_.top()->time_point_ <= now) {
				tmp.push_back(timers_.top());
				timers_.pop();
				--events_;
			}
			else {
				break;
			}
		}
		result.swap(active_handles_);
		events_ -= active_handles_.size();
		mut.unlock();
		too_many_events_.notify_all();
		for (auto each : tmp) {
			each->func_(each);
			if (each->promise_) {
				each->promise_->set_value();
				each->promise_.reset();
			}
			if (each->type_ == time_handle::type::duration) {
				push_timer(each);
			}
		}
		return result;
	}

public:
	event_pool() :triggers_(0), events_(0), max_events_(1024), stop_(false) {

	}

	std::future<void> push_event(std::shared_ptr<event_handle> h) {
		std::unique_lock<std::mutex> mut(mut_);
		too_many_events_.wait(mut, [this]()->bool {return this->events_ <= max_events_; });
		h->event_ = shared_from_this();
		h->promise_.reset(new std::promise<void>());
		auto result = h->promise_->get_future();
		handles_.push_back(h);
		++events_;
		return result;
	}

	std::future<void> push_timer(std::shared_ptr<time_handle> h) {
		std::unique_lock<std::mutex> mut(mut_);
		too_many_events_.wait(mut, [this]()->bool {return this->events_ <= max_events_; });
		if (h->type_ == time_handle::type::duration) {
			h->time_point_ = time_point_cast<milliseconds>(system_clock::now()) + h->duration_;
		}
		h->promise_.reset(new std::promise<void>());
		auto result = h->promise_->get_future();
		//no matter which type of h,we always use time_point_ data member.
		timers_.push(h);
		++events_;
		at_least_one_wake_up_.notify_all();
		return result;
	}

	void set_max_events(uint64_t max_events) {
		max_events_ = max_events;
	}

	void stop() {
		std::unique_lock<std::mutex> mut(mut_);
		stop_ = true;
		at_least_one_wake_up_.notify_all();
	}

	void run() {
		while (true) {
			std::vector<std::shared_ptr<event_handle>> ready = get_ready();
			for (std::shared_ptr<event_handle> each : ready) {
				if (each->func_) {
					each->func_(each);
					if (each->promise_) {
						each->promise_->set_value();
						each->promise_.reset();
					}
				}
			}
			std::unique_lock<std::mutex> mut(mut_);
			if (stop_ == true) {
				return;
			}
		}
	}
};

//对于once的event来说，只能被唤醒一次，但wake_up函数可多次调用（线程安全）
inline
void event_handle::wake_up() {
	std::shared_ptr<event_pool> hold = event_.lock();
	if (!hold) {
		//invalid event_.
		return;
	}
	bool except_ = false;
	if (type_ == type::once) {
		if (done_.compare_exchange_strong(except_, true) == false) {
			//have been waked_up.
			return;
		}
	}
	std::unique_lock<std::mutex> mut(hold->mut_);
	if (hold->stop_ == true) {
		//event_ stop.
		return;
	}
//	assert(trigger_ == false);
	hold->active_handles_.push_back(shared_from_this());
	if (type_ == type::once) {
		trigger_ = true;
		hold->triggers_ += 1;
	}// esle type_ == type::every, and trigger_ always remain false,so event_ will never delete it.
	hold->at_least_one_wake_up_.notify_all();
}

#endif // EVENT_POOL_H
#pragma once
