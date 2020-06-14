#include <Winsock2.h>

#include "thread_broker_adapter.h"
#include "md5.h"
#include "lib.h"
#include "license_manager.h"
#include <sstream>

using namespace std;

thread_broker_adapter::thread_broker_adapter(stock_broker *p, bool create_recv_thread)
	:
	m_broker_ptr(p),
	m_started(false),
	m_create_recv_thread(create_recv_thread)
{
	setState("idle", "");
}

thread_broker_adapter::~thread_broker_adapter()
{
	delete m_broker_ptr;
}

void thread_broker_adapter::start()
{
	if (m_started) {
		return;
	}

	m_started = true;
	command cmd;
	cmd.cmd = START;

	ScopedLock lck(m_critical_sec);
	m_command_deq.push_back(cmd);
	m_event.Signal();

	m_send_thread.StartThread(SendThreadProc, this);
	cout << "send thread " << m_send_thread.GetCurrentThreadId() << " created" << endl;
}

void thread_broker_adapter::stop()
{
	command cmd;
	cmd.cmd = STOP;

	ScopedLock lck(m_critical_sec);
	m_command_deq.push_back(cmd);
	m_event.Signal();
}

//{"sid": stockid, "action" : "open", "direction" : 1, "price" : price, "quant" : quant, "deal_quant" : 0, "deal_price" : 0, "state" : "pending", "desc" : "", "id" : user_order_id}

std::string thread_broker_adapter::buy(const std::string& sid, int amount, double price, const std::string& order_type)
{
	if (getState() != "login") {
		return "";
	}

	std::string ret = m_broker_ptr->create_order("buy", "open", sid, price, amount);

	command cmd;
	cmd.cmd = BUY;
	cmd.sid = sid;
	cmd.quant = amount;
	cmd.price = price;
	cmd.order_type = order_type;
	cmd.order_id = ret;

	ScopedLock lck(m_critical_sec);

	m_command_deq.push_back(cmd);
	m_event.Signal();

	return ret;
}

std::string thread_broker_adapter::sell(const std::string& sid, int amount, double price, const std::string& order_type)
{
	if (getState() != "login") {
		return "";
	}
	
	std::string ret = m_broker_ptr->create_order("sell", "close", sid, price, amount);

	command cmd;
	cmd.cmd = SELL;
	cmd.sid = sid;
	cmd.quant = amount;
	cmd.price = price;
	cmd.order_type = order_type;
	cmd.order_id = ret;

	ScopedLock lck(m_critical_sec);
	
	m_command_deq.push_back(cmd);

	m_event.Signal();
	return ret;
}

void thread_broker_adapter::closeOrder(const std::string& order_id)
{
	command cmd;
	cmd.cmd = CANCEL;
	cmd.order_id = order_id;

	ScopedLock lck(m_critical_sec);
	m_command_deq.push_back(cmd);
	m_event.Signal();
}

std::vector<holding_item> thread_broker_adapter::getHoldingStock()
{
	return m_broker_ptr->get_holding_stock();
}

order_state thread_broker_adapter::getOrderState(const std::string& user_order_id)
{
	return m_broker_ptr->get_order_state(user_order_id);
}

std::vector<order_state> thread_broker_adapter::getAllOrder()
{
	return m_broker_ptr->get_all_order();
}

std::string thread_broker_adapter::getAccountState()
{
	ScopedLock lck(m_critical_sec);

	//cout << "current state " << m_state << endl;

	return m_state;
}

std::vector<double> thread_broker_adapter::getBalance()
{
	return m_broker_ptr->get_money_left();
}

u_long WINAPI thread_broker_adapter::SendThreadProc(LPVOID lParam)
{
	thread_broker_adapter *pThis = (thread_broker_adapter*)lParam;

	DWORD last_update_account = ::GetTickCount();
	try {
		while (true) {

			bool command_ok = false;
			int command_left = 0;
			command cmd;

			pThis->m_critical_sec.Lock();

			if (pThis->m_command_deq.size() > 0) {
				command_ok = true;
				cmd = pThis->m_command_deq[0];
				pThis->m_command_deq.pop_front();
			}

			pThis->m_critical_sec.Unlock();

			if (command_ok) {
				if (cmd.cmd == START) {
					int ret = pThis->m_broker_ptr->login();

					if (ret == 0) {

						std::string account = pThis->m_broker_ptr->get_account();
						double money_left = pThis->m_broker_ptr->get_money_left()[1];

						LicenseManager::get_instance()->set_account_money(account, money_left);

						pThis->setState("login", "login success");

						if (pThis->m_create_recv_thread) {
							pThis->m_recv_thread.StartThread(ReceiveThreadProc, pThis);
							cout << "recv thread " << pThis->m_recv_thread.GetCurrentThreadId << " created" << endl;
						}
					}
					else {
						pThis->setState("failed", "login failed");
					}
				}
				else if (cmd.cmd == BUY) {
					 pThis->m_broker_ptr->buy(cmd.sid, cmd.price, cmd.quant, cmd.order_type, cmd.order_id);
				}
				else if (cmd.cmd == SELL) {
					pThis->m_broker_ptr->sell(cmd.sid, cmd.price, cmd.quant, cmd.order_type, cmd.order_id);

				}
				else if (cmd.cmd == RESPONSE) {
					int ret = pThis->m_broker_ptr->handle_packet(cmd.data);
				}
				else if (cmd.cmd == CANCEL) {
					std::string oi = cmd.order_id;
					pThis->m_broker_ptr->cancel_order(oi);
				}
				else if (cmd.cmd == STOP) {

					break;
				}
			}
			else {
				DWORD current_tickcount = ::GetTickCount();
				if (current_tickcount - last_update_account > 400) {
					pThis->updateAccountState();
					last_update_account = current_tickcount;
				}
				pThis->m_event.Wait(100);
			}
		}

	}
	catch (std::exception& e) {
		cout << "send thread except: " << e.what() << endl;
		pThis->setState("failed", e.what());
	}
	pThis->m_broker_ptr->logout();
	pThis->m_started = false;

	cout <<"send thread "<< Win32Thread::GetCurrentThreadId() << " exited" << endl;

	return 0;
}

u_long WINAPI thread_broker_adapter::ReceiveThreadProc(LPVOID lParam)
{
	thread_broker_adapter *pThis = (thread_broker_adapter*)lParam;

	try {
		while (true) {
			
			command cmd;
			cmd.cmd = command_type::RESPONSE;

			int ret = pThis->m_broker_ptr->try_recv_packet(cmd.data);
			if (ret > 0) {
				ScopedLock lck(pThis->m_critical_sec);
				pThis->m_command_deq.push_back(cmd);
				pThis->m_event.Signal();
			}
			else {
				cout << "recv thread recv return " << ret << endl;
				break;
			}
		}
	}
	catch (std::exception& e) {
		pThis->setState("failed", e.what());
	}

	cout <<"recv thread "<< Win32Thread::GetCurrentThreadId() << " exited" << endl;

	return 0;
}

void thread_broker_adapter::updateAccountState()
{
	m_broker_ptr->update_account();
}

void thread_broker_adapter::setState(const std::string& state, const std::string& desc)
{
	ScopedLock lck(m_critical_sec);

	m_state = state;
	m_state_desc = desc;
}

std::string thread_broker_adapter::getState()
{
	ScopedLock lck(m_critical_sec);

	return m_state;
}