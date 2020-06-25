#pragma once

#include "PracticalSocket.h"
#include "lib.h"
#include "zlib\zlib.h"
#include "md5.h"
#include "stock_broker.h"
#include "GWin32CriticalSection.h"

#include <string>
#include <iostream>
#include <stdint.h>
#include <memory>
#include <time.h>
#include <list>
#include <vector>
#include <sstream>
#include <algorithm>
#include <map>
#include <boost/tuple/tuple.hpp>


class hexin_stock_broker_guangfa : public stock_broker
{
public:
	hexin_stock_broker_guangfa(const std::vector<boost::tuple<std::string, uint16_t>> &server_vec, const std::string& account, const std::string& password1, const std::string& password2, bool wait_response = true);
	virtual ~hexin_stock_broker_guangfa();

	virtual int login();
	virtual void logout();

	virtual std::vector<holding_item> get_holding_stock();
	virtual std::vector<double> get_money_left();

	virtual std::string create_order(const std::string& operation, const std::string& direction, const std::string& sid, double price, int amount);

	virtual void buy(const std::string& sid, double price, int quant, const std::string& price_type, const std::string& user_order_id);
	virtual void sell(const std::string& sid, double price, int quant, const std::string& price_type, const std::string& user_order_id);

	//order_item get_order_state(const std::string& order_id);
	virtual void cancel_order(const std::string& user_order_id);

	virtual order_state get_order_state(const std::string& user_order_id);

	virtual std::string get_last_msg() { return m_last_msg; }
	virtual std::vector<order_state> get_all_order();

	virtual int try_recv_packet(std::string& pkt);
	virtual int handle_packet(const std::string& pkt);

	virtual int update_account();

	virtual std::string get_account();

private:
	int send_login_packet();
	int send_get_gddm_packet();

	int send_get_account_holding();
	int handle_get_holding_response(const std::string& resp);

	int send_get_account_balance();
	int handle_get_balance_response(const std::string& resp);

	int send_get_account_all_order();
	int handle_all_order_response(const std::string& resp);

	int send_buy(const std::string& sid, double price, int quant, const std::string& price_type);
	int handle_buy_response(const std::string& resp);

	int send_sell(const std::string& sid, double price, int quant, const std::string& price_type);
	int handle_sell_response(const std::string& resp);

	int send_cancel(const std::string& order_id, const std::string& sid);
	int handle_cancel_response(const std::string& resp);

private:
	bool m_wait_response;
	bool m_login;

	bool m_waiting_holding_resp;
	bool m_waiting_balance_resp;
	bool m_waiting_get_order_resp;

	std::string m_server;
	int m_port;

	std::vector<boost::tuple<std::string, uint16_t>> m_server_vec;

	std::string m_encrypt_key1;
	std::string m_encrypt_key2;

	std::string m_decrypt_key1;
	std::string m_decrypt_key2;

	uint32_t m_packet_index = 2;

	char m_session_id[4] = { 0 };

	TCPSocket m_socket;

	std::string m_account;
	std::string m_password;
	std::string m_comm_password;
	std::string m_account_name;
	std::string m_fund_account;

	std::vector<std::string> m_sh_gddm_list;
	std::vector<std::string> m_sz_gddm_list;

	std::vector<double> m_balance;
	std::vector<holding_item> m_holding_stock;
	std::vector<internal_order_item> m_all_internal_order;

	std::string m_last_msg;

	Win32CriticalSection m_critical_sec;

	std::map<std::string, order_state> m_pending_order_map;
	std::map<std::string, order_state> m_completed_order_map;
};

