struct HoldingStock {
 1: string stock_id,
 2: double buy_price,
 3: string long_short,
 4: double quant,
 5: double quant_sellable,
}

struct AccountBalance {
 1: double total_value,
 2: double money_left,
}

struct OrderState {
 1: string order_id,
 2: string time,
 3: string sid,
 4: string internal_order_id,
 5: string operation,
 6: string direction,
 7: double price,
 8: double quant,
 9: double deal_quant,
 10: double deal_price,
 11: string state,
 12: string desc,
}

struct LiveTradeLoginResp {
 1: i32 ret_code,
 2: string result,
}

struct LiveTradeLogoutResp {
 1: i32 ret_code,
}

struct GetAccountStateResp {
 1: i32 ret_code,
 2: string state,
 3: string desc,
}

struct GetAccountInfoResp {
 1: i32 ret_code,
 2: string result,
}

struct GetAccountBalanceResp {
 1: i32 ret_code,
 2: AccountBalance result,
}

struct GetHoldingStockResp {
 1: i32 ret_code,
 2: list<HoldingStock> result,
}

struct GetAllOrderResp {
 1: i32 ret_code,
 2: list<OrderState> result,
}

struct GetOrderStateResp {
 1: i32 ret_code,
 2: OrderState result,
}

struct CloseOrderResp {
 1: i32 ret_code,
}

struct CancelOrderResp {
 1: i32 ret_code,
}

struct PlaceOrderResp {
 1: i32 ret_code,
 2: string result,
}

service AlphaTrade {

bool Running(),
i32 GetPID(),

void KeepAlive(1:string sessionID),

LiveTradeLoginResp LiveTradeLogin(1:string sessionID, 2:string account, 3:string password1, 4:string password2, 5:string brokerStr),
LiveTradeLogoutResp LiveTradeLogout(1:string sessionID, 2:string liveTradeID),
GetAccountStateResp GetAccountState(1:string sessionID, 2:string liveTradeID),

GetAccountBalanceResp GetAccountBalance(1:string sessionID, 2:string liveTradeID),

GetHoldingStockResp GetHoldingStock(1:string sessionID, 2:string liveTradeID),
GetAllOrderResp GetAllOrder(1:string sessionID, 2:string liveTradeID),

GetOrderStateResp GetOrderState(1:string sessionID, 2:string liveTradeID, 3:string orderID),

GetAccountInfoResp GetAccountInfo(1:string sessionID, 2:string liveTradeID, 3:string key),

CancelOrderResp CancelOrder(1:string sessionID, 2:string liveTradeID, 3:string orderID),

CloseOrderResp CloseOrder(1:string sessionID, 2:string liveTradeID, 3:string orderID),
PlaceOrderResp LiveTradeBuyOpen(1:string sessionID, 2:string liveTradeID, 3:string sid, 4:double price, 5:double quant, 6:string orderType),
PlaceOrderResp LiveTradeBuyClose(1:string sessionID, 2:string liveTradeID, 3:string sid, 4:double price, 5:double quant, 6:string orderType, 7:bool closeToday),
PlaceOrderResp LiveTradeSellClose(1:string sessionID, 2:string liveTradeID, 3:string sid, 4:double price, 5:double quant, 6:string orderType, 7:bool closeToday),
PlaceOrderResp LiveTradeSellOpen(1:string sessionID, 2:string liveTradeID, 3:string sid, 4:double price, 5:double quant, 6:string orderType),

}
