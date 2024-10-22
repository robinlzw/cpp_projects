
// gaoyuanDlg.cpp : 实现文件
//
/*
新浪行情接口：http://hq.sinajs.cn/list=sh601006
转换后的接口：http://123.125.104.104/list=sh601006
所以要将域名转换为ip
hq.sinajs.cn-->123.125.104.104


*/
#include "stdafx.h"
#include "gaoyuan.h"
#include "gaoyuanDlg.h"
#include "afxdialogex.h"
#include  <io.h>
#include  <stdio.h>
#include  <stdlib.h>
#include <fstream>  
#include <string>  
#include <iostream> 

using namespace std;
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框
#define WM_SHOWTASK (WM_USER + 1)  //托盘:设置响应消息
// 热键的标识符
#define hotKeyID GlobalAddAtom(_T("MyHotkey"))

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
enum { IDD = IDD_ABOUTBOX };

	protected:
		virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CgaoyuanDlg 对话框



CgaoyuanDlg::CgaoyuanDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CgaoyuanDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CgaoyuanDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CgaoyuanDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(WM_SHOWTASK, OnShowTask)
	ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_WM_CLOSE()
	ON_WM_TIMER()
	ON_WM_CTLCOLOR()
	ON_WM_LBUTTONDOWN()
	ON_WM_KEYDOWN()
	ON_MESSAGE(WM_HOTKEY, OnHotKey)  // 热键的消息映射
END_MESSAGE_MAP()


// CgaoyuanDlg 消息处理程序
#include <fstream>
BOOL CgaoyuanDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	bIsShow = true;
	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码
	//透明窗体
	LONG para = GetWindowLong(this->GetSafeHwnd(), GWL_EXSTYLE);
	para |= WS_EX_LAYERED;
	SetWindowLong(this->GetSafeHwnd(), GWL_EXSTYLE, para);
	SetLayeredWindowAttributes(GetSysColor(COLOR_BTNFACE), 0, LWA_COLORKEY);
	//置顶显示
	::SetWindowPos(m_hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
	//托盘显示
	TuoPan();//最小化到托盘
	//ShowWindow(SW_SHOWNORMAL);//桌面显示
	ModifyStyleEx(WS_EX_APPWINDOW, WS_EX_TOOLWINDOW);//从任务栏中去掉.
	SetTimer(1, 1000, NULL);
	m_isInit = false;
	memset(m_text, 0, sizeof(m_text));
	//list_stock.insert("");
	
	
	//右下角显示数据
	RECT rectDesktop;
	SystemParametersInfo(SPI_GETWORKAREA, 0, &rectDesktop, 0); // 获得屏幕工作区大小 left:0,top:0,right:width,bottom:height
	RECT rectDlg;
	this->GetWindowRect(&rectDlg); // 获取当前窗口工作区大小
	int dlgWidth = rectDlg.right - rectDlg.left;
	int dlgHeight = rectDlg.bottom - rectDlg.top;
	//this->ShowWindow(SW_SHOWNORMAL);
	this->MoveWindow(rectDesktop.right - dlgWidth, rectDesktop.bottom - dlgHeight, dlgWidth, dlgHeight);
	//注册全局快捷键
	OnBtnHotKey();
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CgaoyuanDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CgaoyuanDlg::OnPaint()
{
	if (IsIconic())//是否点击了最小化，点击了则返回true
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CgaoyuanDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



HBRUSH CgaoyuanDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性

	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	if (pWnd->GetDlgCtrlID() == IDC_STATIC)
	{
		pDC->SetTextColor(RGB(0, 0, 0));
		pDC->SetBkMode(TRANSPARENT);
		return (HBRUSH)GetStockObject(NULL_BRUSH);
	}
	return hbr;
}

void CgaoyuanDlg::TuoPan()
{
	nid.cbSize = (DWORD)sizeof(NOTIFYICONDATA);
	nid.hWnd = this->m_hWnd;
	nid.uID = IDR_MAINFRAME;
	nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
	nid.uCallbackMessage = WM_SHOWTASK;//自定义的消息名称 
	nid.hIcon = LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_MAINFRAME));
	strcpy(nid.szTip, "秘密武器"); //鼠标放托盘上，气泡提示信息内容
	Shell_NotifyIcon(NIM_ADD, &nid); //在托盘区添加图标 
	//ShowWindow(SW_SHOWNORMAL); //窗口一直保持最大化，显示在桌面
}


LRESULT CgaoyuanDlg::OnShowTask(WPARAM wParam, LPARAM lParam)
{
	//wParam接收的是图标的ID，而lParam接收的是鼠标的行为 
	if (wParam != IDR_MAINFRAME) return 1;
	switch (lParam)
	{
	case WM_RBUTTONUP://右键起来时弹出快捷菜单，这里只有一个“关闭” 
	{
		LPPOINT lpoint = new tagPOINT;
		::GetCursorPos(lpoint);//得到鼠标位置 
		CMenu menu;
		menu.CreatePopupMenu();//声明一个弹出式菜单 
		//增加菜单项“关闭”，点击则发送消息WM_DESTROY给主窗口，将程序结束。 
		//menu.AppendMenu(MF_STRING, WM_DESTROY, "增加");
		menu.AppendMenu(MF_STRING, WM_DESTROY, "退出");
		
		//确定弹出式菜单的位置 
		SetForegroundWindow();//弹出菜单失去焦点后自动消失
		menu.TrackPopupMenu(TPM_LEFTALIGN, lpoint->x, lpoint->y, this);
		//资源回收 
		HMENU hmenu = menu.Detach();
		menu.DestroyMenu();
		delete lpoint;
	}
	break;
	case WM_LBUTTONDBLCLK://双击左键的处理 
	{
		//Shell_NotifyIcon(NIM_DELETE,&nid);//删除托盘图标
		ShowWindow(SW_SHOWNORMAL);//激活并显示一个窗口
		this->SetWindowPos(&wndTopMost,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE);//使窗口总是在最前面
	}
	break;
	}
	return 0;
}

void CgaoyuanDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	if (nType == SIZE_MINIMIZED)
	{
		
		ShowWindow(SW_SHOW); // 恢复初始窗口状态         
	}
}

void CgaoyuanDlg::OnDestroy()
{
	CDialog::OnDestroy();

	// TODO: Add your message handler code here
	Shell_NotifyIcon(NIM_DELETE, &nid); //退出程序后删除托盘图标
}

void CgaoyuanDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDialog::OnClose();
}


//定时器，间隔时间是settime设置的。
void CgaoyuanDlg::OnTimer(UINT_PTR nIDEvent)
{
	//count++;//计数器
	int frontSize = 20;
	

	//固定位置输出效果
	CClientDC dc(this); // 用于绘制的设备上下文
	CRect rect;
	GetClientRect(&rect);
	CFont font;
	font.CreateFont(frontSize,       //   字体的高度   
		0,
		0,
		0,
		FW_NORMAL,
		FALSE,
		FALSE,
		0,
		ANSI_CHARSET,
		OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_SWISS,
		_T("宋体"));
	CFont *oldfont = dc.SelectObject(&font);
	dc.SetBkMode(TRANSPARENT);
	//dc.SetTextColor(RGB(248, 248, 255));
	dc.SetTextColor(RGB(0, 0, 255));
	//mapStock_[count/mapStock_.size()]
	OpenCfgFile();
	//dc.TextOut(rect.left, rect.top, m_text);//0点位置
	int offset = 0;
	//下面这句清屏要放在最靠近TexOut的地方，不然会显示闪屏
	RedrawWindow();//用于清屏，以便下次显示内容不跟上次显示内容叠加
	if (bIsShow)//清屏后是否显示桌面文字：true：显示；false：不显示
	{
		for (auto &it : mapStock_)
		{
			sprintf(m_text,"%8s:%s",it.second.name.c_str(),it.second.price.c_str());
			dc.TextOut(rect.left, rect.top - offset, m_text);//0点位置
			offset -= frontSize;
		}
		dc.SelectObject(&oldfont);
	}
	CDialogEx::OnTimer(nIDEvent);
}


//新浪行情地址:http://hq.sinajs.cn/list=sh601006


bool CgaoyuanDlg::OpenCfgFile()
{
	mapStock_.clear();
	memset(m_text,0,sizeof(m_text));
	//检查配置文件
	if (_access("gaoyuan.dat", 0) != -1)
	{
		//数据文件存在
		ifstream iofile("gaoyuan.dat");
		if (!iofile)
		{
			cout << "gaoyuan.dat文件打开失败" << endl;
			strcpy(m_text, "gaoyuan.dat文件打开失败");
			return TRUE;
		}
		//char buf[1024] = {0};
		string sLine;
		int iCount = 0;
		while (getline(iofile, sLine)) // line中不包括每行的换行符  
		{
			cout << sLine << endl;
			mapStock_[iCount].price = "0.00";
			mapStock_[iCount].stock = sLine;
			iCount++;
		}
		iofile.close();		
	}
	else
	{
		//数据文件不存在
		fstream iofile("gaoyuan.dat", ios::out);
		if (!iofile)
		{
			cout << "gaoyuan.dat文件打开失败" << endl;
			strcpy(m_text, "gaoyuan.dat文件打开失败");
			return TRUE;
		}
		char buf[1024] = { 0 };
		iofile << "sh000001" << endl << "sz399001";
		iofile.close();
		mapStock_[0].price = "0.00";
		mapStock_[0].stock = "sh000001";
		mapStock_[1].price = "0.00";
		mapStock_[1].stock = "sz399001";
	}
	GetQuotationData(&mapStock_);
	return true;
}

void CgaoyuanDlg::GetQuotationData(map<int, s_data_s> *pMapStockInfo)
{
	
	CString strStockObject[64];
	CString strContent = "";
	CString strData = "";
	CString strObject = "0";
	for (auto &it : *pMapStockInfo)
	{
		int nCnt = 0;
		int nIdx = 0;
		DWORD dwStatus;
		CInternetSession session("HttpClient");
		char buf[1024] = { 0 };
		sprintf(buf, "http://hq.sinajs.cn/list=%s", it.second.stock.c_str());
		cout << "buf = " << buf << endl;
		CHttpFile *pHttpFile = (CHttpFile *)session.OpenURL(buf);
		pHttpFile->QueryInfoStatusCode(dwStatus);

		if (HTTP_STATUS_OK == dwStatus)
		{
			while (pHttpFile->ReadString(strData))
			{
				nIdx = strData.Find("\"");
				strContent = strData.Mid(nIdx + 1);
				strContent.TrimRight("\";");
			}

			strObject = "";
			while (!strContent.IsEmpty())
			{
				nIdx = strContent.Find(",");

				if (nIdx >= 0)
				{
					strObject = strContent.Left(nIdx);
					strStockObject[nCnt++] = strObject;

					strObject = strContent.Mid(nIdx + 1);
					strContent = strObject;
				}
				else
				{
					strStockObject[nCnt++] = strObject;
					strContent = "";
				}
			}
			it.second.price = strStockObject[3];//保存股票价格
			it.second.name = strStockObject[0];//保存股票名称
		}
		pHttpFile->Close();
		delete pHttpFile;
		session.Close();
	}
	

	
	return;
}

//为了能让无标题窗口用鼠标拖动而增加该事件方法
void CgaoyuanDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	PostMessage(WM_NCLBUTTONDOWN, HTCAPTION, MAKELPARAM(point.x, point.y));
	CDialogEx::OnLButtonDown(nFlags, point);
}




//ctrl+x这个快捷键只能在光标在窗体上的时候用，最小化时无法使用快捷键。
/************************************************************************/
/* 快捷键ctrl+x，但是失去焦点后无法使用                                           */
/************************************************************************/
BOOL CgaoyuanDlg::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN)
	{
		switch (pMsg->wParam)
		{
		case VK_ESCAPE:
			SetFocus();
			return TRUE;
		case 'X':
			if (::GetKeyState(VK_CONTROL) < 0)
			{
				bIsShow = !bIsShow;
				RedrawWindow();//按下快捷键后，立即清屏
			}
			return TRUE;
		}
	}
	return CDialog::PreTranslateMessage(pMsg);
}


/************************************************************************/
/* 按下全局快捷键调用本函数                                           */
/************************************************************************/
LRESULT CgaoyuanDlg::OnHotKey(WPARAM wParam, LPARAM lParam)
{
	if (hotKeyID == (int)wParam)
	{
		//AfxMessageBox("按下");
		bIsShow = !bIsShow;
		RedrawWindow();//按下快捷键后，立即清屏
	}

	return TRUE;
}

/************************************************************************/
/* 注册全局快捷键                                                       */
/************************************************************************/
void CgaoyuanDlg::OnBtnHotKey()
{
	// 注销原有的热键
	::UnregisterHotKey(m_hWnd, hotKeyID);
	// 获取新的热键
	//WORD wvk, wmod;
	//从界面获取设定快捷键
	//m_HotKey.GetHotKey(wvk, wmod);
	// 注册新的热键
	//BOOL result = RegisterHotKey(m_hWnd, hotKeyID, wmod, wvk);
	BOOL result = RegisterHotKey(m_hWnd, hotKeyID, 0, VK_F8);
	if (!result)
	{
		MessageBox("注册热键失败:请使用管理员启动");
		exit(1);
	}
}

void CgaoyuanDlg::OnDestroyHotKey()
{
	CDialog::OnDestroy();

	// 注销热键
	::UnregisterHotKey(m_hWnd, hotKeyID);
}