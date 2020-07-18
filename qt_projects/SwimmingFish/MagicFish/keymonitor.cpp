#include "keymonitor.h"
#include "capturer.h"
#include <QDebug>

LRESULT CALLBACK KeyboardHookProc(int nCode, WPARAM wParam, LPARAM lParam);

HMODULE WINAPI ModuleFromAddress(PVOID pv);
static HHOOK hHook;
static HHOOK g_hMouseHook;

LRESULT KeyboardHookProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    KBDLLHOOKSTRUCT *Key_Info = (KBDLLHOOKSTRUCT*)lParam;
    if (HC_ACTION == nCode)
    {
        if (WM_KEYDOWN == wParam || WM_SYSKEYDOWN == wParam)  //?????????
        {
            //if (Key_Info->vkCode <= 107 && Key_Info->vkCode >= 65)
            {
                qDebug() << Key_Info->vkCode;
                if (KeyCapturer::instance())
                {
                    KeyCapturer::instance()->setkeyValue(Key_Info->vkCode);
                }
            }
        }
    }
    return CallNextHookEx(hHook, nCode, wParam, lParam);
}

LRESULT CALLBACK MouseHookProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    qDebug() << "MouseHookProc00";
    if (nCode == HC_ACTION)
    {
        //????
        if(wParam == WM_LBUTTONDOWN||wParam == WM_RBUTTONDOWN||wParam == WM_MBUTTONDOWN||wParam ==WM_LBUTTONUP||wParam ==WM_RBUTTONUP||wParam == WM_MBUTTONUP){
                //????????????????
            qDebug() << "MouseHookProc11";
        }


        PMOUSEHOOKSTRUCT mhs = (PMOUSEHOOKSTRUCT)lParam;

        qDebug() << mhs->wHitTestCode;

        switch (wParam)
        {
        case WM_NCLBUTTONDOWN:
        {
            if (HTCAPTION == mhs->wHitTestCode)
            {
                //::SendMessage(mhs->hwnd, WM_NCLBUTTONDOWN, HTCAPTION, MAKELONG(mhs->pt.x, mhs->pt.y));


            }
        }
        break;
        case WM_NCLBUTTONUP:
        {

        }
        break;
        case WM_LBUTTONUP:
        {
            //::PostMessage(mhs->hwnd, WM_NCLBUTTONUP, HTCAPTION, MAKELONG(mhs->pt.x, mhs->pt.y));
        }
        break;
        case WM_RBUTTONUP:
        {

        }
        break;
        case WM_NCLBUTTONDBLCLK:
        {

        }
        break;
        }
#ifdef _FEATURE_PBGROUP
        if (//wParam == WM_NCLBUTTONDOWN ||
         //wParam == WM_NCRBUTTONDOWN ||
            wParam == WM_NCLBUTTONUP ||
            wParam == WM_NCRBUTTONUP ||
            wParam == WM_LBUTTONUP ||
            wParam == WM_RBUTTONUP)
        {
            //??phonebook?????????
            ::SendMessage(Config::m_pWndPhonebook->GetSafeHwnd(), WM_LBUTTONUP, HTCAPTION, MAKELONG(mhs->pt.x, mhs->pt.y));
        }
#endif
    }

    return CallNextHookEx(g_hMouseHook, nCode, wParam, lParam);
}

HMODULE ModuleFromAddress(PVOID pv)
{
    MEMORY_BASIC_INFORMATION mbi;
    if (VirtualQuery(pv, &mbi, sizeof(mbi)) != 0) {
        return (HMODULE)mbi.AllocationBase;
    }
    else {
        return NULL;
    }
}

int startHook()
{
    hHook = SetWindowsHookExW(WH_KEYBOARD_LL, KeyboardHookProc, ModuleFromAddress((PVOID)KeyboardHookProc), 0);
    // g_hMouseHook = SetWindowsHookEx(WH_MOUSE, (HOOKPROC)MouseHookProc, (HINSTANCE)AfxGetInstanceHandle(), 0);
    HINSTANCE hInstance = GetModuleHandle(NULL);
    g_hMouseHook = SetWindowsHookEx(WH_MOUSE_LL, (HOOKPROC)MouseHookProc, ModuleFromAddress((PVOID)MouseHookProc), 0);

    int error = GetLastError();
    return error;
}

bool stopHook()
{
    return UnhookWindowsHookEx(hHook);
}

