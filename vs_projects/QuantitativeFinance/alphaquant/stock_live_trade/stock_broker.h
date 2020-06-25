#pragma once

#include <string>
#include <iostream>
#include <stdint.h>
#include <memory>
#include <time.h>
#include <list>
#include <vector>
#include <sstream>
#include <algorithm>


struct holding_item
{
	std::string sid;
	std::string sname;
	double quant;
	double quant_available;
	double buy_price;

};

struct internal_order_item
{
	std::string order_id;
	std::string sid;
	double price;
	uint32_t quant;
	uint32_t deal_quant;
	double deal_price;
	std::string sname;
	std::string operation;
	std::string state;
	std::string day;
	std::string time;
};

struct order_state
{
	order_state()
	{
		deal_price = 0.0;
		deal_quant = 0;
		packet_id = 0;
	}

	std::string sid;
	std::string operation;
	std::string direction;
	double price;
	double deal_price;
	int quant;
	int deal_quant;
	std::string state;
	std::string desc;
	std::string user_order_id;
	std::string internal_order_id;
	std::string time;

	uint32_t packet_id;
};

class stock_broker
{
public:
	virtual ~stock_broker() {}

	virtual int login() = 0;
	virtual void logout() = 0;

	virtual std::string create_order(const std::string& operation, const std::string& direction, const std::string& sid, double price, int amount) = 0;

	virtual void buy(const std::string& sid, double price, int quant,  const std::string& price_type, const std::string& user_order_id) = 0;
	virtual void sell(const std::string& sid, double price, int quant, const std::string& price_type, const std::string& user_order_id) = 0;

	//order_item get_order_state(const std::string& order_id);
	virtual void cancel_order(const std::string& user_order_id) = 0;

	virtual order_state get_order_state(const std::string& user_order_id) = 0;

	virtual std::string get_last_msg() = 0;
	virtual std::vector<order_state> get_all_order() = 0;

	virtual std::vector<holding_item> get_holding_stock() = 0;
	virtual std::vector<double> get_money_left() = 0;

	virtual int try_recv_packet(std::string& pkt) = 0;

	virtual int handle_packet(const std::string& pkt) = 0;

	virtual int update_account() = 0;

	virtual std::string get_account() = 0;
};

