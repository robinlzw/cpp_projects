import sys
import traceback
if sys.version_info >= (3,0):
    import urllib.request
else:
    import urllib2
import sys
import threading
import time

g_lock = threading.Lock()
g_stock_price_data = {}
g_stock_set = set()


def _parse_sina_real_time_data_response(resp_str):
    ret = {}
    for line in resp_str.split("\n"):
        try:
            start = line.find('="')
            if start == -1 :
                continue

            sid = line[start-6:start]

            start += 2

            end = line.find('";')
            if end == -1:
                continue

            content = line[start:end]

            result_list = content.split(',')
            #result_list[0] = result_list[0].decode('gbk')

            ret[sid] = result_list
        except:
            print(sys.exc_info())

    return ret

def _get_sina_name(sid):
    code = int(sid)
    highest_bit = int(code/100000)
    prefix = "sz"
    if highest_bit == 6:
        prefix = "sh"

    code = "%s%06d" % (prefix, code)

    return code


def _get_real_time_data(sid_list):
    try:
        url = "http://hq.sinajs.cn/list="
        for i in range(len(sid_list)):

            sina_name = _get_sina_name(sid_list[i])
            fix = ""
            if i != 0:
                fix = ","
            url = url + fix + sina_name

        if sys.version_info >= (3,0):
            resp_str = str(urllib.request.urlopen(url).read().decode("GBK"))
        else:
            resp_str = urllib2.urlopen(url).read().decode("GBK")

        ret = _parse_sina_real_time_data_response(resp_str)
        #print("get ", len(sid_list), " realtime data success")
        return ret
    except:
        print("get realtime data failed ", sys.exc_info(), traceback.format_exc())
        return {}


def subscribe_stock(stock_id):
    g_lock.acquire()
    g_stock_set.add(stock_id)
    g_lock.release()

def unsubscribe_stock(stock_id):
    g_lock.acquire()
    try:
        g_stock_set.remove(stock_id)
    except:
        pass
    g_lock.release()


def get_stock_live_data(stock_id):

    ret = None

    subscribe_stock(stock_id)

    g_lock.acquire()
    if stock_id in g_stock_price_data:
        try:
            ret = {}
            info = g_stock_price_data[stock_id]
            ret['name'] = info[0]
            ret['datetime'] = info[30] + " " + info[31]
            ret['open'] = float(info[1])
            ret['high'] = float(info[4])#high
            ret['low'] = float(info[5])#low
            current_price = float(info[3])
            ret['close'] = current_price#close  current price
            ret['volume'] = int(info[8])#Volume
            ret['preclose'] = float(info[2])

            ret['bid'] = [[float(info[11]), float(info[10])], [float(info[13]), float(info[12])], [float(info[15]), float(info[14])], [float(info[17]), float(info[16])], [float(info[19]), float(info[18])]]
            ret['ask'] = [[float(info[21]), float(info[20])], [float(info[23]), float(info[22])], [float(info[25]), float(info[24])], [float(info[27]), float(info[26])], [float(info[29]), float(info[28])]]

        except:
            print("except ",sys.exc_info())

    g_lock.release()

    return ret


def _thread_proc():
    while True:
        try:
            g_lock.acquire()
            stockid_list = list(g_stock_set.copy())
            g_lock.release()

            if len(stockid_list) > 0:
                ret = _get_real_time_data(stockid_list)
                g_lock.acquire()
                try:
                    g_stock_price_data.update(ret)
                except:
                    print('except: ', sys.exc_info())
                g_lock.release()
        except:
            print('except: ', sys.exc_info())

        time.sleep(1)


ret = threading._start_new_thread(_thread_proc, ())

#for test
if __name__ == "__main__":
    subscribe_stock('600016')
    #subscribe_stock('600036')

    while True:
        print(get_stock_live_data('600016'))
        time.sleep(1)