#pragma once

#include "GWin32Thread.h"
#include "GWin32Event.h"
#include "GScopedLock.h"
#include "GWin32CriticalSection.h"
#include "stock_broker.h"
#include <deque>
#include <map>

enum command_type
{
	START = 0,
	BUY = 1,
	SELL = 2,
	STOP = 3,
	CANCEL = 4,

	RESPONSE = 5,
};

struct command
{
	int cmd;

	std::string sid;
	double price;
	int quant;
	std::string order_type;
	std::string order_id;
	std::string data;
};

//{"sid": stockid, "action" : "open", "direction" : 1, "price" : price, "quant" : quant, "deal_quant" : 0, "deal_price" : 0, "state" : "pending", "desc" : "", "id" : user_order_id}

class thread_broker_adapter
{
public:
	thread_broker_adapter(stock_broker *p, bool create_recv_thread);
	~thread_broker_adapter();

	void start();
	void stop();

	std::string buy(const std::string& sid, int amount, double price, const std::string& order_type);

	std::string sell(const std::string& sid, int amount, double price, const std::string& order_type);

	void closeOrder(const std::string& order_id);

	std::vector<holding_item> getHoldingStock();
				
	order_state getOrderState(const std::string& user_order_id);

	std::vector<order_state> getAllOrder();
				
	std::string getAccountState();
				
	std::vector<double> getBalance();
	
	bool stopped() { return m_started == false; }

private:
	void updateAccountState();
	void setState(const std::string& state, const std::string& desc);
	std::string getState();

	static u_long WINAPI SendThreadProc(LPVOID lParam);
	static u_long WINAPI ReceiveThreadProc(LPVOID lParam);

private:
	Win32Thread m_send_thread;
	Win32Thread m_recv_thread;

	stock_broker *m_broker_ptr;
	Win32CriticalSection m_critical_sec;

	std::deque<command> m_command_deq;

	std::string m_state;
	std::string m_state_desc;

	Win32Event m_event;
	bool m_started;
	bool m_create_recv_thread;
};
