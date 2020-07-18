#include "MyXcbEventFilter.h"
#include <QDebug>
#define QDBG qDebug()<<__FILE__<<__FUNCTION__<<__LINE__
bool MyXcbEventFilter::nativeEventFilter(const QByteArray & eventType, void * message, long * result) {

    MSG * pMsg = reinterpret_cast<MSG *>(message);
    QDBG << pMsg->message;
//    if (eventType == "windows_generic_MSG" || eventType == "windows_dispatcher_MSG")
//    {
//        MSG * pMsg = reinterpret_cast<MSG *>(message);

//        if (pMsg->message == WM_NCMOUSEMOVE)
//        {
//            //获取到系统鼠标移动，可以做像qq一样的忙碌检测
//        }
//    }

    return false;
}

MyXcbEventFilter::MyXcbEventFilter(int x) {

}


MyXcbEventFilter::~MyXcbEventFilter() {
}
