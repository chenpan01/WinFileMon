
// 3.2Dlg.h : 头文件
//

#pragma once
#include "SetMenu.h"
#include "ShowListCtrl.h"

// CMy32Dlg 对话框
class CMy32Dlg : public CDialogEx
{
// 构造
public:
	CMy32Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MY32_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

public:
	CSetMenu m_setmenu;
	CShowListCtrl m_showlistctrl;



// 实现
protected:
	HICON m_hIcon;
	HANDLE hThread[50];

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton4();
	afx_msg void OnLvnItemchangedList2(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton3();
public:

	afx_msg void OnBnClickedButton2();
	static DWORD WINAPI ThreadProc(LPVOID lParam);
	#define LVS_EX_HIDELABELS 0x00020000 
	
	afx_msg void OnBnClickedButton5();
};
