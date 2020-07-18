#pragma once
#include <windows.h>
#include <qabstractnativeeventfilter.h>
class MyXcbEventFilter : public QAbstractNativeEventFilter
{
public:
    bool nativeEventFilter(const QByteArray & eventType, void * message, long * result);

    MyXcbEventFilter(int x);
    ~MyXcbEventFilter();
};
