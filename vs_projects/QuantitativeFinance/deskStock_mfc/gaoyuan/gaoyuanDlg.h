
// gaoyuanDlg.h : 头文件
//

#pragma once
#include <afxinet.h>
#include <string>
#include <map>
using namespace std;

typedef struct data_s
{
	string stock;
	string price;
	string name;
}s_data_s;
// CgaoyuanDlg 对话框
class CgaoyuanDlg : public CDialogEx
{
// 构造
public:
	bool m_isInit;
	int m_nLeft;
	CString m_szText;
	bool bIsShow;
	char m_text[1024]; 
	map<int, s_data_s> mapStock_;
	CHotKeyCtrl	m_HotKey;
	//int count;
	CgaoyuanDlg(CWnd* pParent = NULL);	// 标准构造函数
	void TuoPan();//设置托盘
	void GetQuotationData(map<int, s_data_s> *pMapStockInfo);
	bool OpenCfgFile();
	NOTIFYICONDATA nid;//NOTIFYICONDATA结构包含了系统用来处理托盘图标的信息
	LRESULT OnShowTask(WPARAM wParam, LPARAM lParam);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnClose();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnDestroy();
// 对话框数据
	enum { IDD = IDD_GAOYUAN_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;
	void OnBtnHotKey();
	void OnDestroyHotKey();
	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg LRESULT OnHotKey(WPARAM wParam, LPARAM lParam);  // 热键消息响应函数的声明
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
