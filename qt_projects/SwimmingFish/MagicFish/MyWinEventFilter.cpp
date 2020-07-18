#include "MyWinEventFilter.h"
#include "MyGlobalShortCut.h"
//#include <qt_windows.h>
MyWinEventFilter::MyWinEventFilter()
{

}
MyWinEventFilter::~MyWinEventFilter()
{

}

MyWinEventFilter::MyWinEventFilter(MyGlobalShortCut *shortcut)
    : m_shortcut(shortcut)
{

}


bool MyWinEventFilter::nativeEventFilter(const QByteArray &eventType, void *message, long *)
{
   if(eventType == "windows_generic_MSG")
    {
        MSG *msg = static_cast<MSG *>(message);
        if(msg->message == WM_HOTKEY)
        {
//            if(msg->wParam == VK_F10)
//            {
//               m_shortcut->activateShortcut();
//               return true;
//            }
            const quint32 keycode = HIWORD(msg->lParam);
            const quint32 modifiers = LOWORD(msg->lParam);
            bool res = m_shortcut->shortcuts.value(qMakePair(keycode, modifiers));
            if(res)
            {
                m_shortcut ->activateShortcut();
                return true;
            }
        }

    }

   //if (eventType == "windows_generic_MSG" || eventType == "windows_dispatcher_MSG")
   //{
	  // MSG * pMsg = reinterpret_cast<MSG *>(message);

	  // if (pMsg->message == WM_NCMOUSEMOVE)
	  // {
		 //  qDebug() << "pMsg->message == WM_NCMOUSEMOVE";
		 //  //获取到系统鼠标移动，可以做像qq一样的忙碌检测
	  // }
   //}
    return false;
}
